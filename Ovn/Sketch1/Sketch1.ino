/*
Name:		Sketch2.ino
Created:	9/11/2017 8:53:58 AM
Author:	kjhn
*/

int ADCDrej = A0;
int ADCPin1 = A1;
int ADCPin2 = A2;
int ADCReadingTemp;
int ADCReading1;
int ADCReading2;
int ADCReadingDrej;
float ADCVoltage;
int temp;
float wantedTemp;
int heater = 12;
//-----------------------------------------------------------------------------------------------------------
int knapPinOp = 7;
int knapPinNed = 8;
int knapCounter;
int knapStatusOp;
int knapStatusNed;
bool checkOp = false;
bool checkNed = false;

// the setup function runs once when you press reset or power the board
void setup() {


	pinMode(ADCPin1, INPUT);
	pinMode(ADCPin2, INPUT);
	pinMode(ADCDrej, INPUT);
	pinMode(heater, OUTPUT);
	//-------------------------------------------------------------------------------------------------------------
	pinMode(knapPinOp, INPUT);
	pinMode(knapPinNed, INPUT);

	Serial.begin(115200);
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	ADCReading1 = analogRead(ADCPin1); //analogRead retunere heltal i intervallet 0-1023
	ADCReading2 = analogRead(ADCPin2); //analogRead retunere heltal i intervallet 0-1023
	ADCReadingTemp = ADCReading1-ADCReading2; //analogRead retunere heltal i intervallet 0-1023
	ADCReadingDrej = analogRead(ADCDrej); //analogRead retunere heltal i intervallet 0-1023
	ADCVoltage = (5.0 / 1023) * (ADCReadingTemp); //5V sættes til 5.0 for at tvinge resultatet til float 

	temp = (ADCVoltage) * 100;
	Serial.print("[Temp: " + String(temp) + "] ");
	ADCReadingDrej = analogRead(ADCDrej);
	wantedTemp = 200.0 / 1023 * ADCReadingDrej;
	Serial.print("[Drej Wanted Temp: " + String(wantedTemp) + "]");
	if (temp <= knapCounter) {
		digitalWrite(heater,HIGH);
	}
	else {
		digitalWrite(heater, LOW);
	}
//-------------------------------------------------------------------------------------------------------------------------
	knapStatusOp = digitalRead(knapPinOp);
	if (knapStatusOp == HIGH && checkOp == true) {
		digitalWrite(LED_BUILTIN, HIGH);
		knapCounter = knapCounter + 10;
		checkOp = false;
	}
	else if (knapStatusOp == LOW && checkOp == false)
	{
		digitalWrite(LED_BUILTIN, LOW);
		checkOp = true;
	}

	knapStatusNed = digitalRead(knapPinNed);
	if (knapStatusNed == HIGH && checkNed == true) {
		digitalWrite(LED_BUILTIN, HIGH);
		knapCounter = knapCounter - 10;
		checkNed = false;
	}
	else if (knapStatusNed == LOW && checkNed == false)
	{
		digitalWrite(LED_BUILTIN, LOW);
		checkNed = true;
	}
	if (knapCounter > 200)
	{
		knapCounter = 200;
	}
	else if (knapCounter < 0) {
		knapCounter = 0;
	}
	Serial.println("[Knap Wanted Temp: " + String(knapCounter) + "]");
	delay(200);
}
