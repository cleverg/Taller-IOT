int valor=1;

void setup(){
 pinMode(13,OUTPUT);
 Serial.begin(9600);
}

void loop()
{
     valor=analogRead(0);
    Serial.println(valor);
delay(1000);
}
