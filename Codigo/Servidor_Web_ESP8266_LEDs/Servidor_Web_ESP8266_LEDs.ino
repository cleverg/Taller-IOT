#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial esp8266(4,2); 

void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600); 
  
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
  
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
   
 /* sendData("AT+RSTrn",2000,DEBUG); // Resetea el modulo
  sendData("AT+CWMODE=2rn",1000,DEBUG); // Configura como un AP.
  sendData("AT+CIFSRrn",1000,DEBUG); // Obtiene la IP
  sendData("AT+CIPMUX=1rn",1000,DEBUG); // Configuras multiples opciones.
  sendData("AT+CIPSERVER=1,80rn",1000,DEBUG); // Enciende el puerto 80*/
}

void loop()
{
  if(esp8266.available()) // Verifica si el modulo esta mandando un mensaje.
  {

    
    if(esp8266.find("+IPD,"))
    {
     delay(1000); //Espera hasta que se llene el buffer (Leyendo toda la informacion del serial.)
     // Obteniendo todos los datos te puedes deconectar.
     int connectionId = esp8266.read()-48; // Restas 48 debido a que read() regresa 
                                           // el ASCII decimal y 0 (Es el primer decimal) empieza en 48
          
     esp8266.find("pin="); // Encuentra el texto "pin="
     
     int pinNumber = (esp8266.read()-48)*10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
     pinNumber += (esp8266.read()-48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
     
     digitalWrite(pinNumber, !digitalRead(pinNumber)); // Cambia de pins   
     
     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // Agrega una conexion al id
     closeCommand+="rn";
     
     sendData(closeCommand,1000,DEBUG); // Cierra la conexion
    }
  }
}

/*
* Name: sendData
* Description: Function used to send data to ESP8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the esp8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
