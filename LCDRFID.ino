#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

//Card symbols i taken from a random person after failing to make my own Source:https://forum.arduino.cc/t/1602-module-character-set-and-card-suit-characters/175365
uint8_t heart[] = {
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
};  

uint8_t diamond[] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
};  

uint8_t spade[] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B00100,
  B01110,
  B00000,
  B00000,
};  

uint8_t smileyface[] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b10001,
  0b01110,
  0b00000,
  0b00000
};  

uint8_t firsthalfclub[] = {
  B00011, B00111, B00011, B01101, B11111, B01101, B00001, B00011
}; 

uint8_t secondhalfclub[] = {
  B11000, B11100, B11000, B10110, B11111, B10110, B10000, B11000
}; 

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
void setup() 
{
  //send the custom characters to the LCD's CGRAM
  lcd.createChar(0, diamond);
  lcd.createChar(1, firsthalfclub);
  lcd.createChar(4, secondhalfclub);
  lcd.createChar(2, spade);
  lcd.createChar(3, heart);
  lcd.createChar(5, smileyface);

  lcd.clear();

  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Prints a sentence
  lcd.setCursor(0, 0);
  lcd.print("I wonder what i do?");
  lcd.setCursor(0, 1);
  lcd.print("do?");

}
void loop() 
{
 // lcd.setCursor(0,1);
 // lcd.print(millis()/1000);
   // Turn off the display:
  //lcd.noDisplay();
  //delay(500);
  // Turn on the display:
  lcd.display();
  delay(500);
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor jus
  lcd.setCursor(0,0);
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
 // if (content.substring(1) == "BD 31 15 2B") //change here the UID of the card/cards that you want to give access
  if (content.substring(1) == "63 C5 2F 35")
  {
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.println("Authorized access");
    Serial.println();
    lcd.print("Wow Heres a clue");

    //Clue that ties to actual objects for the second part
    lcd.setCursor(0,1);
    lcd.write(byte(0));
    lcd.setCursor(6,1);
    lcd.write(byte(1));
    lcd.setCursor(7,1);
    lcd.write(byte(4));
    lcd.setCursor(2,1);
    lcd.write(byte(2));
    lcd.setCursor(4,1);
    lcd.write(byte(3));
    delay(3000);

    //Goes back to the default display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("i wonder what i");
    lcd.setCursor(0, 1);
    lcd.print("do?");
  }
 
 else   {

  //shows that its the wrong card(decoy card)
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.println(" Access denied");
    lcd.print(" wrong card lol ");
    lcd.setCursor(0,1);
    lcd.write(byte(5));
    lcd.setCursor(2,1);
    lcd.write(byte(5));
    lcd.setCursor(4,1);
    lcd.write(byte(5));
    delay(3000);

    //Goes back to the default display
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("i wonder what i");
    lcd.setCursor(0, 1);
    lcd.print("do?");
  }
} 


