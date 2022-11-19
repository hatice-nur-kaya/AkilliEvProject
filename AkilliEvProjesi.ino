#include <SPI.h>                        
#include <MFRC522.h>                   
MFRC522 rfid(10,9); 
int led=2;
int pirPin=5;
int ledPin=4;
int deger=0;
String readString;  
#include <Servo.h>
Servo servoM;
int pos = 0;         
byte kart[4] = {199,221,56,44};          
void setup() 
{
  Serial.begin(9600);                     
  SPI.begin();    
  pinMode(led,OUTPUT);
  pinMode(pirPin, INPUT);
pinMode(ledPin, OUTPUT);                        
  rfid.PCD_Init();                        
  servoM.attach(3);
}

void loop() 
{
  while(Serial.available())
  {
    delay(3);
    char c=Serial.read();
    readString+=c;
  }
  deger=digitalRead(pirPin);
  
Serial.println(deger);
if(deger==HIGH){
digitalWrite(ledPin,HIGH);
}
else{
digitalWrite(ledPin,LOW);
}
  if(readString.length()>0)
  {
    Serial.println(readString);
    if(readString=="on")
    {
      digitalWrite(led,HIGH);
    }
    if(readString=="off")
    {
      digitalWrite(led,LOW);
    }
    readString="";
  }
  if ( ! rfid.PICC_IsNewCardPresent())    
    return;
  if ( ! rfid.PICC_ReadCardSerial())     
    return;

  if (rfid.uid.uidByte[0] == kart[0] &&     

    rfid.uid.uidByte[1] == kart[1] &&
    rfid.uid.uidByte[2] == kart[2] &&
    rfid.uid.uidByte[3] == kart[3] ) {
        Serial.print("Hoş Geldiniz!\n");
       for (pos = 0; pos <= 180; pos += 5) 
       {                                  
       servoM.write(pos);            
       delay(50);                       
       }
    }

    else{                                
      Serial.println("Kartınız tanımlanamadı!");
       ekranaYazdir();
    }
  rfid.PICC_HaltA();
}
void ekranaYazdir() {
  Serial.print("ID Numarasi: ");
  for (int sayac = 0; sayac < 4; sayac++) {
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println("");
}
