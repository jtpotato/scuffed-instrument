#include <Servo.h>

Servo metronome;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT); // buzzer port D5
  metronome.attach(7);
}

int duration = 500;
bool metronomeRest = true;

int milisecondIndex = 0;

bool isOn = false;

void loop() {
  // put your main code here, to run repeatedly:
  int rotatingThingInput = analogRead(0);

  bool is_button_pressed = digitalRead(6);
  bool off_button_pressed = digitalRead(8);

  if (off_button_pressed) {
    if (isOn) {
      isOn = false;
    }
    else {
      isOn = true;
    }
  }

  int freq = 440;

  freq = round(rotatingThingInput / 12) * (880 / 12) + 880;

  if (is_button_pressed) {
    tone(5, freq);
    analogWrite(4, 255); // shine ✨
  }
  else {
    noTone(5);
    analogWrite(4, 0);
  }

  // check if metronome should tick
  if (milisecondIndex % duration == 0 && isOn) {
      if (metronomeRest) {
        metronome.write(70);
        metronomeRest = false;
      }
      else {
        metronome.write(30);
        metronomeRest = true;
      }
  }

  delay(1);
  milisecondIndex += 1;
}
