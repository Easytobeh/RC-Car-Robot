/*In using the virtual wire library for the RF transmitter and reader module, it is important to
   know that digital Pin 10, 11 and 12 are dedicated as press to talk pin, receiver pin and
   transmitter pin respectively, However they can be set in the library source file VirtualWire.cpp
   alternatively the transmitter and receiver pins can be set using the commands; vw_set_rx_pin()
   and vw_set_tx_pin(). In the case of this sketch, I have set it at pin 10 which is the default
   value. This is actually not necessary as the compiler assumes the default if not explicitly defined

*/
#include <VirtualWire.h>
#include <ServoTimer2.h>
#define EN1 2
#define EN2 11
#define motionLED 8
#define trigPin 6
#define echoPin 7
#define posMotor1 3
#define negMotor1 4
#define posMotor2 13
#define negMotor2 12
#define rx_in_pin 10
#define servoPin 5

ServoTimer2 myServo;

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
unsigned long previousMillis = 0;
const long interval = 500;
int duration, distance;

void stopMotion();
void moveFwd();
void moveBack();
void goLeft();
void goRight();
int checkDistance();
void defaultPinMode();

void setup()
{
  myServo.attach(servoPin);
  myServo.write(1300);
  defaultPinMode();
  stopMotion();
  //digitalWrite(13,false);
  Serial.println("...waiting to receive message");
  vw_setup(2000);         //sets bits per second
  vw_set_rx_pin(rx_in_pin);
  vw_rx_start();
  servoControl();

}

void loop()
{
  
  if (vw_get_message(buf, &buflen))
  {
    for (int i = 0; i < buflen; i++)
    {
      Serial.println(buf[i]);
      //FORWARD MOTION
      if (buf[i] == 'F')
      {

        if (checkDistance() <= 20) //If obstacle in front
        {
          stopMotion();
          digitalWrite(motionLED, LOW);
          myServo.write(0); //look to the Right
          if (checkDistance() <= 20) {
            delay(1000);
            myServo.write(1800); //look to the left if obstacle is found on the right
            if (checkDistance() <= 20){
              delay(1000);
              myServo.write(1300);
            }
            else //if no obstacle on the left
            {
              delay(500);
            myServo.write(1300);
            goLeft(); //turn Right
            delay(1000);
            stopMotion();
              
            }
          }
          else { //if no obstacle on the right
            delay(500);
            myServo.write(1300);
            goRight(); //turn Right
            delay(1000);
            stopMotion();
          }
        }
        else
          moveFwd();
      }

      //BACKWARD MOTION
      if (buf[i] == 'B')
        moveBack();

      //RIGHT TURN
      if (buf[i] == 'R')
        goRight();

      //LEFT TURN
      if (buf[i] == 'L')
        goLeft();

      //STOP
      if (buf[i] == 'S')
        stopMotion();
    }
  }
}//end of loop


void defaultPinMode() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(motionLED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(posMotor1, OUTPUT);
  pinMode(negMotor1, OUTPUT);
  pinMode(posMotor2, OUTPUT);
  pinMode(negMotor2, OUTPUT);

}

int checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}

void servoControl() {
  myServo.write(0);
  delay(200);
  //myServo.write(1300);
  //delay(1000);
  myServo.write(1800);
  delay(200);
  myServo.write(1300);
}

void moveBack() {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(motionLED, LOW);
  digitalWrite(posMotor1, LOW);
  digitalWrite(posMotor2, LOW);
  digitalWrite(negMotor1, LOW);
  digitalWrite(negMotor2, LOW);

  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, HIGH);
  digitalWrite(motionLED, HIGH);
  digitalWrite(posMotor1, LOW);
  digitalWrite(posMotor2, LOW);
  digitalWrite(negMotor1, HIGH);
  digitalWrite(negMotor2, HIGH);
}

void moveFwd() {
  //  digitalWrite(EN1, LOW);
  //  digitalWrite(EN2, LOW);
  //  digitalWrite(motionLED, LOW);
  //  digitalWrite(posMotor1, LOW);
  //  digitalWrite(posMotor2, LOW);
  //  digitalWrite(negMotor1, LOW);
  //  digitalWrite(negMotor2, LOW);

  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, HIGH);
  digitalWrite(motionLED, HIGH);
  digitalWrite(posMotor1, HIGH);
  digitalWrite(posMotor2, HIGH);
  digitalWrite(negMotor1, LOW);
  digitalWrite(negMotor2, LOW);
}

void goLeft() {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(motionLED, LOW);
  digitalWrite(posMotor1, LOW);
  digitalWrite(posMotor2, LOW);
  digitalWrite(negMotor1, LOW);
  digitalWrite(negMotor2, LOW);

  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  digitalWrite(motionLED, HIGH);
  digitalWrite(posMotor1, LOW);
  digitalWrite(posMotor2, HIGH);
  digitalWrite(negMotor1, LOW);
  digitalWrite(negMotor2, LOW);
}

void goRight() {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(motionLED, LOW);
  digitalWrite(posMotor1, LOW);
  digitalWrite(posMotor2, LOW);
  digitalWrite(negMotor1, LOW);
  digitalWrite(negMotor2, LOW);

  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  digitalWrite(motionLED, HIGH);
  digitalWrite(posMotor1, HIGH);
  digitalWrite(posMotor2, LOW);
  digitalWrite(negMotor1, LOW);
  digitalWrite(negMotor2, LOW);
}

void stopMotion() {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, LOW);
  digitalWrite(motionLED, LOW);

  digitalWrite(posMotor1, LOW);
  digitalWrite(posMotor2, LOW);
  digitalWrite(negMotor1, LOW);
  digitalWrite(negMotor2, LOW);
  //servoControl();
}
