#include "Keyboard.h"
#define input_a0 0
#define input_a1 1
#define input_a2 2

bool pressed_a1 = false;
bool pressed_a2_low_light = false;
bool pressed_a2_high_light = false;
bool pressed_a2_light_off = true;

void setup(){
  Serial.begin(9600);
  pinMode(input_a0, INPUT);
  Keyboard.begin();
}

void loop(){
  int input_value_a0 = analogRead(input_a0);
  float result_a0 = map(input_value_a0, 0, 1023, 0, 255);
  if(result_a0 >= 100){
    Serial.println("flash luz alta " + String(result_a0));

    Keyboard.print("l");
  }

  // setas esquerda e direita
  int input_value_a1 = analogRead(input_a1);
  float result_a1 = map(input_value_a1, 0, 1023, 0, 255);
  if(result_a1 >= 100 && result_a1 < 167 && pressed_a1 == false){
    Serial.println("seta direita " + String(result_a1));
    pressed_a1 = true;

    Keyboard.print("m");
  }
  if(result_a1 >= 167 && pressed_a1 == false){
    Serial.println("seta esquerda " + String(result_a1));
    pressed_a1 = true;

    Keyboard.print("n");
  }
  if(result_a1 < 100 && pressed_a1 == true){
    Serial.println("pressed_a1 " + String(pressed_a1));
    pressed_a1 = false;
  }


  // controle do farol
  int input_value_a2 = analogRead(input_a2);
  float result_a2 = map(input_value_a2, 0, 1023, 0, 255);
  Serial.println("result_a2: " + String(result_a2));

  if(
    result_a2 >= 100
    && result_a2 <= 130
    && pressed_a2_low_light == false
    && (pressed_a2_light_off == true || pressed_a2_high_light == true)
  ){
    Serial.println("luz baixa " + String(result_a2));
    pressed_a2_low_light = true;
    pressed_a2_high_light = false;
    pressed_a2_light_off = false;
    Keyboard.print("i");
  }

  if(
    result_a2 >= 150
    && pressed_a2_high_light == false
    && pressed_a2_light_off == false
  ){
    Serial.println("luz alta " + String(result_a2));
    pressed_a2_high_light = true;
    pressed_a2_low_light = false;
    pressed_a2_light_off = false;
    Keyboard.print("o");
  }

  if(
    result_a2 < 100
    && pressed_a2_light_off == false
    && (pressed_a2_low_light == true || pressed_a2_high_light == false)
  ){
    Serial.println("luz desligada " + String(result_a2));
    pressed_a2_low_light = false;
    pressed_a2_high_light = false;
    pressed_a2_light_off = true;
    Keyboard.print("p");
  }
  delay(20);
}
