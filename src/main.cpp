#include <Arduino.h>
#define btnIN A0 //Entrada analogica
#define LED 10   //Salida digital

enum funMode
{
  OFF,
  BLINK1,
  BLINK2,
  BLINK3,
  BLINK4,
  NBSTATE
};

int L_STD = LOW;
unsigned long pre_Millis, pas_Millis;
unsigned long lastDeTime = 0;       //Ultimo tiempo definido como 0 o inicio (rebote)
int LstBSTD = HIGH;                 //Ultimo estado pre-definido es Alto
int btnSTD = 0;                     //Estado presente
int funcSTD = 0;                    //Estados para de la funcion de seleccion de Menu
int BP1 = 50, BP2 = 100, BP3 = 200; //Blink intermidiate time
int interB = 100;                  //Blink intermidiate time general

//Desvanecido//
int brightness= 0; 
int fade = 5; 

unsigned long tiempo;
unsigned long time=0;
unsigned long retardado=100;

void setup()
{
  pinMode(btnIN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
   
}

void loop()
{
  Funcion1(); //Button detection
  Funcion2(); //Menu de seleccion
  Desvanecido();
}
/////////////////////////////////////////////
void Funcion1()
{
  int reading = digitalRead(btnIN);
  if (reading != LstBSTD)
  {                        //Ultima estado definido del buton
    lastDeTime = millis(); //lastDeubonceTime
    if ((millis() - lastDeTime) > 100)
    {
      if (reading != btnSTD)
      {
        btnSTD = reading;
      }
      if (btnSTD == HIGH)
      {
        funcSTD += 1;
      }
    }
  }
  LstBSTD = reading;
  funcSTD = funcSTD % NBSTATE;
}
void Funcion2()
{
  switch (funcSTD)
  {
  case OFF:
    //FuncionOFF - LED
    digitalWrite(LED, LOW);
    break;
  case BLINK1:
    //FuncionBlink1 - LED
    FuncionB1(LP1);
    break;
  case BLINK2:
    //FuncionBlink2 - LED
    FuncionB2(LP2);
    break;
  case BLINK3:
  //FuncionBlink3 - LED
    FuncionB3(LP3);
    break;
  //FuncionBlink4 - LED
  case BLINK4:
    FuncionB4(interL);
    break;
  }
}
void FuncionB1(int LP1)
{
  delay(LP1);
  digitalWrite(LED, LOW);
  delay(LP1);
  digitalWrite(LED, HIGH);
}
void FuncionB2(int LP2)
{
  delay(LP2);
  digitalWrite(LED, LOW);
  delay(LP2);
  digitalWrite(LED, HIGH);
}
void FuncionB3(int LP3)
{
  delay(LP3);
  digitalWrite(LED, LOW);
  delay(LP3);
  digitalWrite(LED, HIGH);
}
void FuncionB4(int interB) {
  pre_Millis = millis();
  if ((pre_Millis - pas_Millis) >= interB) {
    pas_Millis = pre_Millis;
    if(L_STD = LOW) {
      L_STD = HIGH;
    } else {
      L_STD = LOW;
    }
  }

}

void Desvanecido(){
    tiempo = millis ();
  if(tiempo>time+retardado){
  time=tiempo;
  // Brillo del pin 9: 
  analogWrite (LED, brightness);
 // cambia el brillo para la proxima vez a traves del ciclo: 
 brightness = brightness + fade; 
 // invierte la direccion del fundido en los extremos del fundido: 
 if (brightness == 0 || brightness == 255) {
   fade = -fade;
    } 
 
 }
    }