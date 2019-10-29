/*In using the virtual wire library for the RF transmitter and reader module, it is important to 
 * know that digital Pin 10, 11 and 12 are dedicated as press to talk pin, receiver pin and
 * transmitter pin respectively, However they can be set in the library source file VirtualWire.cpp
 * alternatively the transmitter and receiver pins can be set using the commands; vw_set_rx_pin()
 * and vw_set_tx_pin(). In the case of this sketch, I have set it at pin 13. That's my choice. The 
 * compiler assumes the default value if not explicitly defined in the sketch.
 */
#include <VirtualWire.h>
#define tx_out_pin 3
#define x_axis A0    /* Select the input pin for the joystick's X-Axis */
#define y_axis A1    /* Select the input pin for the joystick's Y-Axis */
#define testLed 8
#define stopButton A3      /* Select the input pin for the joystick's push button */
char *sendByte;
int valx,valy,_stop;

/* Initialise serial and DIO */
void setup()
{

  /* Setup the serial port for displaying the status of the sensor */ 
  Serial.begin(9600);
  //set transmitting data pin
  vw_setup(2000);
  vw_set_tx_pin(tx_out_pin);

  pinMode(stopButton, INPUT);
  pinMode(testLed, OUTPUT);
  digitalWrite(testLed, LOW);
}


/* Main program loop */
void loop()
{
 //Serial.println(analogRead(stopButton));
  digitalWrite(testLed, LOW);
  _stop = analogRead(stopButton);
  valy = analogRead(y_axis);
  valx = analogRead(x_axis);
  //MOVE MOTOR FORWARD
  if (valx < 500) {
    sendByte = "F";
    Serial.println(sendByte);
    vw_send((uint8_t *)sendByte, strlen(sendByte));
    digitalWrite(testLed, HIGH);
    vw_wait_tx();
    delay(10);

  }
  //MOVE MOTOR BACKWARDS
  if (valx > 600) {
    sendByte = "B";
    Serial.println(sendByte);
    vw_send((uint8_t *)sendByte, strlen(sendByte));
    digitalWrite(testLed, HIGH);
    vw_wait_tx();
    delay(10);
  }
  //TURN MOTOR LEFT
  if (valy > 600) {
    sendByte = "L";
    Serial.println(sendByte);
    vw_send((uint8_t *)sendByte, strlen(sendByte));
    digitalWrite(testLed, HIGH);
    vw_wait_tx();
    delay(10);
  }
  //TURN MOTOR RIGHT
  if (valy < 500) {
    sendByte = "R";
    Serial.println(sendByte);
    vw_send((uint8_t *)sendByte, strlen(sendByte));
    digitalWrite(testLed, HIGH);
    vw_wait_tx();
    delay(10);
  }
  
    //STOP MOTOR
    if (_stop < 1)
  {
    sendByte = "S";
    Serial.println(sendByte);
    vw_send((uint8_t *)sendByte, strlen(sendByte));
    digitalWrite(testLed,HIGH);
    vw_wait_tx();
    delay(10);
  }
}
