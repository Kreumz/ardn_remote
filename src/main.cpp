/*

Remote controller

*/
#include <Arduino.h>
#include <SPI.h>
#include "RF24.h"
#include "printf.h"

#define STAT_LED 4

#define jB1 1 // Joystick button 1
#define jB2 0 // Joystick button 2
#define t1 7  // Toggle switch 1
#define t2 4  // Toggle switch 1
#define b1 8  // Button 1
#define b2 9  // Button 2
#define b3 2  // Button 3
#define b4 3  // Button 4

RF24 radio(7, 8); // CE: 7 CSN: 8

const uint64_t pipes[2] = {0xF0F0F0F0D2, 0xF0F0F0F0E1}; // Communication adress

struct Commands
{
  byte joy1X;
  byte joy1Y;
  byte joy2X;
  byte joy2Y;
  byte joy1Button;
  byte joy2Button;
  byte pot1;
  byte pot2;
  byte sw1;
  byte sw2;
  byte button1;
  byte button2;
  byte button3;
  byte button4;
};

Commands commands;

void SetDefaultValues()
{
  // Set initial default values
  commands.joy1X = 138;
  commands.joy1Y = 50;
  commands.joy2X = 254;
  commands.joy2Y = 255;
  commands.joy1Button = 1;
  commands.joy2Button = 1;
  commands.pot1 = 1;
  commands.pot2 = 1;
  commands.sw1 = 1;
  commands.sw2 = 1;
  commands.button1 = 1;
  commands.button2 = 1;
  commands.button3 = 1;
  commands.button4 = 1;
}

void blink()
{
  digitalWrite(STAT_LED, 1);
  delay(100);
  digitalWrite(STAT_LED, 0);
  delay(100);
  digitalWrite(STAT_LED, 1);
  delay(100);
  digitalWrite(STAT_LED, 0);
  Serial.println("Ready");
}

void setup(void)
{
  Serial.begin(9600);

  pinMode(STAT_LED, OUTPUT);

  SetDefaultValues();

  radio.begin();
  radio.setAutoAck(false);
  radio.setChannel(0x55);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening(); // Start listening
  printf_begin();
  radio.printDetails(); // Dump the configuration of the rf unit for debugging
  radio.stopListening();
  blink();
}

void loop(void)
{
  /*commands.j1PotX = map(analogRead(A1), 0, 1023, 0, 255); // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
  commands.j1PotY = map(analogRead(A0), 0, 1023, 0, 255);
  commands.j2PotX = map(analogRead(A2), 0, 1023, 0, 255);
  commands.j2PotY = map(analogRead(A3), 0, 1023, 0, 255);
  commands.pot1 = map(analogRead(A7), 0, 1023, 0, 255);
  commands.pot2 = map(analogRead(A6), 0, 1023, 0, 255);
  commands.j1Button = digitalRead(jB1);
  commands.j2Button = digitalRead(jB2);
  commands.sw1 = digitalRead(t1);
  commands.sw2 = digitalRead(t2);
  commands.button1 = digitalRead(b1);
  commands.button2 = digitalRead(b2);
  commands.button3 = digitalRead(b3);
  commands.button4 = digitalRead(b4);*/

  if (commands.sw1 == 0)
  {
    //read_IMU();    // Use MPU6050 if switch is activated
  }
  radio.write(&commands, sizeof(Commands));

  delay(100);
}