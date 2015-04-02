/*
   Projeto Robot do Samuel (meu filho)
   Este prgram controla o robot do samuel
   Autor: Marcos Oliveira e Samuel Oliveira
   e-mail: marcosf63@gmail.com
   Versao: 1.0
   Adicionei um controle remoto 6 canais
   Adicionei uma garra robotica

*/

#include <AFMotor.h>
#include <Servo.h>


#define VELOCIDADE_MAXIMA 150
#define AJUSTE_DA_VELOCIDADE 37




AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2(4, MOTOR12_1KHZ); // create motor #2, using M2 output, set to 1kHz PWM frequency

Servo servo1, servo2;
int ch1, ch2, ch3, ch4, x, y;
int velocidade_motor;


//-------------------------------------------- DECLARANDO AS FUNCOES ----------------------------------------------------------------

void move_para_frente();  // move o robot para frente
void move_para_tras();  // move o motor para tras
void vira_para_direita();    // vira o robot para a direita
void vira_para_esquerda();   // vira o robot para a esquerda
void para();                // para o robot




//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
  para();
  servo1.attach(10);
  servo2.attach(9);
  servo2.write(0);
  
  
  
}
//------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
   ch3 = pulseIn(7, HIGH, 25000);
   ch4 = pulseIn(6, HIGH, 25000);
 
   
   
   while (ch4 >= 1500 && ch4 < 1600) {
      ch1 = pulseIn(14, HIGH, 25000);
      ch2 = pulseIn(15, HIGH, 25000);
      ch3 = pulseIn(7, HIGH, 25000);
      ch4 = pulseIn(6, HIGH, 25000);
      if (ch3 >= 1650) {
        move_para_frente();
        
      } else {
        if (ch3 < 1450){
          move_para_tras();
        } else {
          para();
        }
      }
      //delay(3000);
      //controle da garra
      servo1.write(map(ch1, 1100, 1900, 0,90));
      servo1.write(map(ch2, 1100, 1900, 0,90));
      
      
      
   }
   
   if (ch4 < 1500) {
     vira_para_esquerda();
     //delay(3000);
   } else {
     if (ch4 >= 1600)
       vira_para_direita();
       //delay(3000);
   }
   

 
 
 

 
 
 
  
 
}
//-------------------------------------------------------------------------------------------------------------------------------------



void move_para_frente(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  for (velocidade_motor = 0; velocidade_motor < VELOCIDADE_MAXIMA; velocidade_motor +=2){
    motor1.setSpeed(velocidade_motor);
    motor2.setSpeed(velocidade_motor);
  
  }
  
}

void move_para_tras(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  for (velocidade_motor = 0; velocidade_motor < VELOCIDADE_MAXIMA; velocidade_motor +=2){
    motor1.setSpeed(velocidade_motor);
    motor2.setSpeed(velocidade_motor);
  
  }
  
}


void vira_para_esquerda(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(200);
  
  
}

void vira_para_direita(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(200);
  
  
}

void para(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}