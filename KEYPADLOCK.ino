#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

char inputArray[4]; //array to gather keypad presses from the user
char Password[4] = {'4', '5', '2', '7'}; //array to hold the correct password
int correct = 12; //shows where the green LED is connected on the Arduino
int incorrect = 13; //shows where the red LED is connected on the Arduino
int i = 0;  //holds the numeric value 
int open()
{
  digitalWrite(correct, HIGH);  //turns the green LED on if the password is correct
  digitalWrite(incorrect, LOW); //turns the red LED off when password is correct
  Serial.println("Access Granted");
}

int MainPassword()
{
  if((inputArray[0] == Password[0] && inputArray[1] == Password[1] && inputArray[2] == Password[2] &&
      inputArray[3] == Password[3])) 
   {
      open();
   }
   else
   {
    digitalWrite(incorrect, HIGH);
    digitalWrite(correct, LOW);
    Serial.println("Incorrect Password");
   }
}//end MainPassword()

void setup()
{
  Serial.begin(9600);
  pinMode(correct, OUTPUT);
  pinMode(incorrect, OUTPUT);
  
}//end Setup()
  
void loop()
{
 
  char password = customKeypad.getKey();

    if (password)
    {
      inputArray[i] = password;
      i++;
    }
  
    if (i == 4)
    {
      MainPassword();
      {
        i = 0;// reset i
      }//end MasterPassword
      
    }//end if
    
 
}//end loop()






