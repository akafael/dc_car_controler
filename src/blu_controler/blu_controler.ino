/* 
  Autor: Mateus Lima e Rafael Lima
  Descrição: Este é um código que possibilita o controle de um 
             carro bluetooth montado em arduino com uma shield 
             ponte H, através do protocolo serial
*/

#include <FastLED.h> // Controle Fita Led

// Fita LED
CRGB leds[NUM_LEDS];
const CRGB colorPalet[] = {0xF7F7F7, // White Smoke
                           0xBA0034, // Crimson Glory
                           0xF70035, // Carmine Red
                           0xFA07F2,
                           0xDD49B8, // Pink (PANTONE)
                           0xF7F7F7, // White Smoke
                           0x00BAAD, // Amazonite
                           0x00F7E6, // Tuorquoise Blue
                           0xFA07F2, 
                           0xDD49B8};// Pink (PANTONE)

/*
  Aqui definimos a velocidade máxima dos motores porem isso 
  depende tambem da fonte de energia que esteja utilizando 
  para alimentar os motores, logo se o valor atribuido for 
  equivalente a 255, por PWM os motores receberão tensão 
  total da fonte que estiver utilizando.
*/

#define FatCorr 0.75
#define vel_dir 10
#define vel_esq 11
#define Vmax 255

int vel = 127;
/*
   Variáveis que controlaram as velocidades do motor direito 
   e esquerdo
*/

#define Farol_dianteiro 8
#define Farol_traseiro 7
#define Pisca_alerta 2
#define buzina 13

//variável que atribuimos a leitura Serial do módulo bluetooth
#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 9

char state;

void setup() {
  // Inicializa Pinos
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(vel_esq,OUTPUT);
  pinMode(vel_dir,OUTPUT);

  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
}

void loop() {
  // Atribui os valores da leitura serial na variável "state"
  if (Serial.available() > 0) {
    state  = Serial.read();
    Serial.write(state);
  }

  /*
    Aqui controlamos a velocidade que o carro bluetooth irá
    se locomover, portanto multiplicamos a velocidade maxima
    por valores decimais para reduzir proporcionamente as 
    velocidades dos motores direito e esquerdo. 
    
    Quando a variavel "state" assumir o caractere 7,através do meio 
    serial, as velocidades são correspondentes à 70% da velocidade 
    máxima dos motores
  */
  
  if (state == '0') {
    vel = Vmax * 0;
  }
  else if (state == '1') {
    vel = Vmax * 0.1;
  }
  else if (state == '2') {
    vel = Vmax * 0.2;
  }
  else if (state == '3') {
    vel = Vmax * 0.3;
  }
  else if (state == '4') {
    vel = Vmax * 0.39; 
  }
  else if (state == '5') {
    vel = Vmax * 0.5;
  }
  else if (state == '6') {
    vel = Vmax * 0.6;
  }
  else if (state == '7') {
    vel = Vmax * 0.7;
  }
  else if (state == '8') {
    vel = Vmax * 0.78;
  }
  else if (state == '9') {
    vel = Vmax * 0.9;
  }
  else if (state == 'q') {
    vel = Vmax;
  }

  // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
  if (state == 'F') {
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,1);
    digitalWrite(IN4,0);
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }

  else if (state == 'G') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,1);
    digitalWrite(IN4,0); 
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }

  else if (state == 'I') {   // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,1);
    digitalWrite(IN4,0);
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }

  else if (state == 'B') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }

  else if (state == 'H') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }

  else if (state == 'J') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }

  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    digitalWrite(vel_dir,vel * FatCorr);
    digitalWrite(vel_esq,vel);
  }
  else if (state == 'W') {   // Se o estado recebido for igual a 'W', Farol dianteiro acende.
    
  }
  else if (state == 'w') {   // Se o estado recebido for igual a 'w', Farol dianteiro apaga.
    
  }
  else if (state == 'U') {   // Se o estado recebido for igual a 'U', Farol traseiro acende.
    
  }
  else if (state == 'u') {   // Se o estado recebido for igual a 'u', Farol traseiro apaga.
    
  }
  else if (state == 'V') {   // Se o estado recebido for igual a 'V', liga buzina.
    
  }
  else if (state == 'v') {   // Se o estado recebido for igual a 'v', desliga buzina.
    
  }
  else if (state == 'X') {   // Se o estado recebido for igual a 'X', Pisca alerta acende.
    
  }
  else if (state == 'x') {   // Se o estado recebido for igual a 'x', Pisca alerta apaga.
    
  }
}

void moveCarroFrente()
{
  digitalWrite(IN1,1);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,1);
  digitalWrite(vel_dir,vel * FatCorr);
  digitalWrite(vel_esq,vel);
}
