#include <RCSwitch.h>
// Define which pin to be used to communicate with Base pin of TIP120 transistor

RCSwitch mySwitch = RCSwitch();

int ledPin = 13;
int TIP120pin = 11; //for this project, I pick Arduino's PMW pin 11
int pirState = LOW;
int inputPin = 2;
int val = 0;



void setup()
{
	pinMode(ledPin, OUTPUT);
	pinMode(TIP120pin, OUTPUT); // Set pin for output to control TIP120 Base pin
	pinMode(inputPin, INPUT);  //Declare sensor as input
	analogWrite(TIP120pin, 0); // By changing values from 0 to 255 you can control motor speed
	//Serial.begin(9600);
	mySwitch.enableTransmit(10); //RF connected to pin 10
}

void loop()
{
	val = digitalRead(inputPin);

	if (val == HIGH)
	{

		if (pirState == LOW)
		{
			//Serial.println("Motion detected!");
			mySwitch.send(5393, 24);
			delay(1000);
			digitalWrite(ledPin, HIGH);
			delay(120000);
			digitalWrite(ledPin, LOW);
			analogWrite(TIP120pin, 255);
			pirState = HIGH;

		}

		delay(300000);
		analogWrite(TIP120pin, 0);

		for (int i = 0; i < 20; i++)
		{
			digitalWrite(ledPin, HIGH);
			delay(125);
			digitalWrite(ledPin, LOW);
			delay(500);

		}

	}

	else
	{
		digitalWrite(ledPin, LOW);
		delay(300);
		analogWrite(TIP120pin, 0);
		delay(300);

		if (pirState == HIGH)
		{
			//Serial.println("Motion ended!");
			mySwitch.send(5732, 24);
			delay(1000);
			pirState = LOW;

		}

	}

}
