
#include <Joystick.h> // Precisa dessa biblioteca para funcionar

bool pressionado; // Se o botão do joystick tá pressionado ou não
#define Joystick_VRX2 A2 // Setando os pinos abaixo cada um com sua função
#define Joystick_VRY2 A3
#define Joystick_VRX  A0 
#define Joystick_VRY  A1
#define Joystick_SW   3
#define Button_B      13
#define Button_Y      2
#define Button_A      11
#define Button_X      10
#define Button_left   7
#define Button_up     6
#define Button_down   5
#define Button_right  4
#define Button_Start  9
#define Button_Select 8

// Criando um objeto do tipo Joystick, onde simulará um gamepad
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD, 
  15, 0,                  // Quantidade de botões, número de Hat Switch
  true, true, true,     // Eixos X e Y no joystick, eixo Z para ser o usado no 2º joystick
  true, false, false,   // Rx para ser usado no 2º joystick, sem Ry nem Rz
  false, false,          // Sem rudder ou throttle
  false, false, false);  // Sem acelerador, freio, ou direção
  
void setup() {
  Serial.begin(9600);
  pinMode(Joystick_VRX2, INPUT); // Setando como entrada porque estes pinos deverão ler o valor do joystick
  pinMode(Joystick_VRY2, INPUT); 
  pinMode(Joystick_VRX, INPUT); 
  pinMode(Joystick_VRY, INPUT); 
  pinMode(Joystick_SW , INPUT_PULLUP); // Todos os botões abaixo estão setados como INPUT_PULLUP, dispensando resistores
  pinMode(Button_left , INPUT_PULLUP);
  pinMode(Button_up , INPUT_PULLUP);
  pinMode(Button_down , INPUT_PULLUP);
  pinMode(Button_right , INPUT_PULLUP);
  pinMode(Button_B , INPUT_PULLUP);
  pinMode(Button_Y , INPUT_PULLUP);
  pinMode(Button_A , INPUT_PULLUP);
  pinMode(Button_X , INPUT_PULLUP);
  pinMode(Button_Start , INPUT_PULLUP);
  pinMode(Button_Select , INPUT_PULLUP);

  Joystick.begin();
  Joystick.setXAxisRange(-127, 127); // Definindo os limites dos eixos do gamepad
  Joystick.setYAxisRange(-127, 127);
  Joystick.setZAxisRange(-127, 127);
  Joystick.setRxAxisRange(-127, 127);
}

void loop() {
  //Setando os valores dos eixos e butões
  Joystick.setXAxis(map(analogRead(Joystick_VRY),0,1023,-127,127)); // Utilizando a função Map para que o sinal original de 0 1023 seja adequado a -127 a 127
  Joystick.setYAxis(map(analogRead(Joystick_VRX),0,1023,127,-127)); // Utilizando a função Map como no exemplo anterior, mas utilizando a vantagem da inversão
  Joystick.setZAxis(map(analogRead(Joystick_VRX2),0,1023,-127,127)); // Mesma coisa para o 2º joystick
  Joystick.setRxAxis(map(analogRead(Joystick_VRY2),0,1023,127,-127));

  // Como estamos usando INPUT_PULLUP, o valor dos botões precisa ser invertido
  Joystick.setButton(10, !digitalRead(Joystick_SW)); // Botão do joystick

  pressionado = digitalRead(Joystick_SW);

  if (pressionado == true) { // Ação de trocar a utilidade dos botões da esquerda
    Joystick.setButton(11, !digitalRead(Button_left));
    Joystick.setButton(12, !digitalRead(Button_up));
    Joystick.setButton(13, !digitalRead(Button_down));
    Joystick.setButton(14, !digitalRead(Button_right));
  } else {
    Joystick.setButton(4, !digitalRead(Button_left));
    Joystick.setButton(5, !digitalRead(Button_up));
    Joystick.setButton(6, !digitalRead(Button_down));
    Joystick.setButton(7, !digitalRead(Button_right));
  }
  Joystick.setButton(0, !digitalRead(Button_X)); 
  Joystick.setButton(1, !digitalRead(Button_A));
  Joystick.setButton(2, !digitalRead(Button_B));
  Joystick.setButton(3, !digitalRead(Button_Y));
  Joystick.setButton(9, !digitalRead(Button_Start));
  Joystick.setButton(8, !digitalRead(Button_Select));
  delay(10); // Um pequeno delay na ordem de fração do nosso movimento dos dedos
}