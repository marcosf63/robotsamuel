/*
   Projeto Robot do Samuel (meu filho)
   Este prgram controla o robot do samuel
   Autor: Marcos Oliveira e Samuel Oliveira
   e-mail: marcosf63@gmail.com
   V0 - Versao sem a garra robotica

*/

#include <AFMotor.h>
#include <Servo.h> 
#include <NewPing.h>
#include <time.h>

#define TRIG_PIN A3
#define ECHO_PIN A4
#define MAX_DISTANCE 200
#define VELOCIDADE_MAXIMA 200
#define AJUSTE_DA_VELOCIDADE 37
#define DISTANCIA_DE_PARADA 20
#define DIREITA 1
#define ESQUERDA 0


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor motor2(4, MOTOR12_1KHZ); // create motor #2, using M2 output, set to 1kHz PWM frequency

Servo myservo;  // create servo object to control a servo

int velocidade_motor;
int distancia, ultimo_sentido = DIREITA, sentido;

//-------------------------------------------- DECLARANDO AS FUNCOES ----------------------------------------------------------------
int checa_distancia();      // Checa aa distancia dos obstaculos
int procura_sentido();      // procura um sentido livre para o robot, esquerda ou direita
void inicaliza_servo();     // coloca o servo na posicao inicial com o sonar virado para frente
void vira_servo_direira();  // vira o servo para a direita
void vira_servo_esquerda(); // vira o servo para esquerda
void move_para_frente();    // move o robot para frente
void vira_para_direita();    // vira o robot para a direita
void vira_para_esquerda();   // vira o robot para a esquerda
void para();                // para o robot




//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  myservo.attach(9);
  inicaliza_servo();
  move_para_frente();
  //Serial.begin(115200);
  
}
//------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
  distancia = checa_distancia();
  //Serial.println(distancia);
  if (distancia != 0 && distancia < DISTANCIA_DE_PARADA){
    para();
    sentido = procura_sentido();
    if(sentido == DIREITA){
      vira_para_direita();
      
    } else {
      vira_para_esquerda();
    }
    
    
  }
 move_para_frente(); 
  
}
//-------------------------------------------------------------------------------------------------------------------------------------
int procura_sentido(){
  delay(1000);
  vira_servo_direira();
  int distancia_direita = checa_distancia();
  delay(1000);
  inicaliza_servo();
  delay(1000);
  vira_servo_esquerda();
  int distancia_esquerda = checa_distancia();
  delay(1000);
  inicaliza_servo();
  delay(1000);
  if(distancia_direita == 0 && distancia_esquerda == 0){
    if (ultimo_sentido == DIREITA){
      ultimo_sentido  = ESQUERDA;
      return ESQUERDA;
    }
    return DIREITA;
  }
  if(distancia_direita > distancia_esquerda){
    ultimo_sentido = DIREITA;
    return DIREITA;
  } else {
    ultimo_sentido = ESQUERDA;
    return ESQUERDA;
  }
  
}

int checa_distancia(){
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping();
  return (uS / US_ROUNDTRIP_CM);
}

void inicaliza_servo(){
  myservo.write(90);
}

void vira_servo_direira(){
  myservo.write(0);
}

void vira_servo_esquerda(){
  myservo.write(180);
}


void move_para_frente(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  for (velocidade_motor = 0; velocidade_motor < VELOCIDADE_MAXIMA; velocidade_motor +=2){
    motor1.setSpeed(VELOCIDADE_MAXIMA);
    motor2.setSpeed(VELOCIDADE_MAXIMA + AJUSTE_DA_VELOCIDADE);
  
  }
  
}

void vira_para_direita(){
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(400);
  
  
}

void vira_para_esquerda(){
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(400);
  
  
}

void para(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
