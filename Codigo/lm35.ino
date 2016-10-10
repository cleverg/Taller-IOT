float temperatura;
int temPin=5;


void setup(){

	Serial.begin(9600);

}

void loop{

	temperatura=analogRead(temPin);
	temperatura=temperatura*0.48828125;
	Serial.print("TEMPERATURA= ");
	Serial.print(temperatura);
	Serial.print("*C");
	Serial.println();
	delay(1000);

}

