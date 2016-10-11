#include <SoftwareSerial.h>
SoftwareSerial BT1(4, 2); // RX | TX
int n1=0;
float temperatura;
int temPin=5;

void setup()
  {Serial.begin(9600);
   BT1.begin(9600);
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   
   }



void loop() 
{ while (BT1.available() >0 )
  {char c = BT1.read();
  if (c == 71) 
  {Serial.println("Peticion enviada");
   delay(500);
   servidor();
     }
 }
 
}



void escribir(String text)
{BT1.print("AT+CIPSEND=0,");  
 BT1.println(text.length());
 if (BT1.find(">"))             // Si se recibe el mensaje
 {Serial.println(text);
  BT1.println(text);            //mandamos el mensaje por el wifi 
  delay(10);
  while ( BT1.available() > 0 ) 
  {if (  BT1.find("SEND OK") )  //buscamos "ok" y luego salimos
   break; 
  }
 }
}

void servidor(void) 
    { escribir("<!DOCTYPE HTML>");
      escribir("<html>");                                                  //una pagina web necesita esto <HTML> y </HTML> es el inicio y fin del documento
      escribir("<head><title>Prueba arduino esp8266 html :)</title>");    //nombre de la pestaña que llevara la pagina
      escribir("<meta http-equiv=\"refresh\" content=\"10\"></head>");    //tiempo para refrescar la pagina web
      escribir("<body><h1> <FONT SIZE=\"5\" COLOR=\"red\"> Ejemplos </h1>");                              //titulo del inicio de la pagina
      escribir(" <BODY BGCOLOR=\"black\"> ");  
      escribir("<a href=\"https://scontent-lax3-1.xx.fbcdn.net/v/t1.0-9/13177574_219712101746944_5721148665796146934_n.jpg?oh=990d07e4819af97361e23e745ff6a574&oe=5864394B\" target=\"_blank\"><img src=\"https://scontent-lax3-1.xx.fbcdn.net/v/t1.0-9/13177574_219712101746944_5721148665796146934_n.jpg?oh=990d07e4819af97361e23e745ff6a574&oe=5864394B\"  WIDTH=500 HEIGHT=500 BORDER=0  /></a><br /><br />");
      //Cargamos una imagen 

      temperatura=analogRead(temPin);
      temperatura=temperatura*0.48828125;
            escribir("<FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"blue\"> La Temperatura </FONT>"); //escribimos y cambiamos el tamaño, letra y color
            escribir(" es de ");
            escribir(String(temperatura));  //imprimimos la variable
            escribir("<br />");
            escribir("<br />");
      
      
                              
         for (int n1 = 0; n1 < 3; n1++) 
         { int lectura = analogRead(n1);
            escribir("<FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"blue\"> Entrada del sensor </FONT>"); //escribimos y cambiamos el tamaño, letra y color
            escribir("(a");
            escribir( String(n1));  
            escribir(")");
            escribir(" es ");
            escribir(String(lectura));  //imprimimos la variable
            escribir("<br />");
            escribir("<br />");
          }

           for (int n2 = 8; n2 < 10; n2++) 
         { int estado = digitalRead(n2) ;
            escribir("<FONT FACE=\"Arial\" SIZE=\"5\" COLOR=\"green\"> Entrada digital </FONT>"); //escribimos y cambiamos el tamaño, letra y color
            escribir("(pin");
            escribir( String(n2));  
            escribir(")");
            escribir(" es ");
            escribir(String(estado));  //imprimimos la variable
            escribir("<br />");
            escribir("<br />");
          }
            
            escribir("<DIV align=\"center\"><A HREF=\"http://techne.space\" target=\"_blank\">Techne.Space</a><BR></DIV>");

       delay(1);
       BT1.println("AT+CIPCLOSE=0");
       //delay(500);
    }
