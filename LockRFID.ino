//Lock with keyboard and smart card
#include <SPI.h>
#include <MFRC522.h>

//Arduino NANO
#define RST_PIN         9          
#define SS_PIN          10     
// ADMIN UID E0 2A F9 73
/*char keys[4][4] =   
{ // 4    5   6   7
    {'1','2','3','A'},// 0
    {'4','5','6','B'},// 1
    {'7','8','9','C'},// 2
    {'*','0','#','D'},// 3
  //
};
*/

String key = "";
String password ="123456ABC";
bool pushing;
MFRC522 mfrc522(SS_PIN, RST_PIN);

//Card
byte masterCard[4];
unsigned long uidDec, uidDecTemp;

//

void setup() 
{
  

  Serial.begin(115200);
  
  SPI.begin();
  mfrc522.PCD_Init();

  
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT); 
  Serial.println("Started");
}

void loop() 
{
  //Test on holding a button
   
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    if(analogRead(0)+analogRead(1)+analogRead(2)+analogRead(3) == 4092) pushing = false;
    
    //Action when push
    if(pushing != true)
    {
      if(analogRead(0)<800&&analogRead(4)>200) 
      {
        key +="1";Serial.println('1');
        pushing = true;
      }
      if(analogRead(0)<800&&analogRead(5)>200) 
      {
        key +="2";Serial.println('2');
        pushing = true;
      }
      if(analogRead(0)<800&&analogRead(6)>200) 
      {
        key +="3";Serial.println('3');
        pushing = true;
      }
      if(analogRead(0)<800&&analogRead(7)>200) 
      {
        key +="A";Serial.println('A');
        pushing = true;
      }
      if(analogRead(1)<800&&analogRead(4)>200) 
      {
        key +="4";Serial.println('4');
        pushing = true;
      }
      if(analogRead(1)<800&&analogRead(5)>200) 
      {
        key +="5";Serial.println('5');
        pushing = true;
      }
      if(analogRead(1)<800&&analogRead(6)>200) 
      {
        key +="6";Serial.println('6');
        pushing = true;
      }
      if(analogRead(1)<800&&analogRead(7)>200) 
      {
        key +="B";Serial.println('B');
        pushing = true;
      }
      if(analogRead(2)<800&&analogRead(4)>200) 
      {
        key +="7";Serial.println('7');
        pushing = true;
      }
      if(analogRead(2)<800&&analogRead(5)>200) 
      {
        key +="8";Serial.println('8');
        pushing = true;
      }
      if(analogRead(2)<800&&analogRead(6)>200) 
      {
        key +="9";Serial.println('9');
        pushing = true;
      } 
      if(analogRead(2)<800&&analogRead(7)>200) 
      {
        key +="C";Serial.println('C');
        pushing = true;
      }
      if(analogRead(3)<800&&analogRead(4)>200) 
      {
        Serial.println(key);
        if(key == password)
        {
          Serial.println("Password is right");
          digitalWrite(7,LOW); 
          delay(500);
          digitalWrite(7,HIGH); 
          key ="";
        }
        else
          {
            Serial.println("Password is wrong");
            key ="";
          }
        pushing = true;
      }
      if(analogRead(3)<800&&analogRead(5)>200) 
      {
        key +="0";Serial.println('0');
        pushing = true;
      }
      if(analogRead(3)<800&&analogRead(6)>200) 
      {
        key ="";Serial.println("Eresed");
        pushing = true;
      }
      if(analogRead(3)<800&&analogRead(7)>200) 
      {
        key +="D";Serial.println('D');
        pushing = true;
      }
      if(pushing == true)
      {
        while(true)
        {
          delay(200);
          break;
        }
      }
    }
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      return;
    }
    else
    {
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        uidDecTemp = mfrc522.uid.uidByte[i];
        uidDec = uidDec*256+uidDecTemp;  
      }  
      Serial.println("Card UID: ");
      Serial.println(uidDec);
      
      if((uidDec == 3760912755||uidDec == 3862135739)&&digitalRead(7))
      {
        digitalWrite(7,LOW);
        delay(1000);
        digitalWrite(7,HIGH);
      }
      else
      {
        Serial.println("Wrong card");
      }
    }
    
  ~mfrc522(){};
  
 
}
