const byte numChars = 100; //max number of chars to input
char receivedChars[numChars]; //array to store received chars in
int time_unit = 100; //one unit of time will be 100 milliseconds and we will go from there
int ledPin = 13;
boolean newData = false;

const char *letters[] = {
  // The letters A-Z in Morse code  
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."         
};
 
const char *numbers[] = {
  // The numbers 0-9 in Morse code  
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", 
  "--...", "---..", "----."
};

void setup() {
  Serial.begin(9600);
  Serial.println("Enter your phrase to be transmit in Morse Code or '!' to exit: ");
}

void loop() {
  runProgram();
  Serial.end(); //if i make it out of runProgram it means there was a sentinel, turn off the serial input
}

void runProgram()
{
  boolean done = false;
  while(!done) 
  {
    done = recvWithEndMarker();
    transmitMorse();
  }
}

boolean recvWithEndMarker() 
{
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;
  boolean result = false; 
  while (Serial.available() > 0 && newData == false)
  {
    rc = Serial.read();
    if (rc == '!') //sentinel
    {
      Serial.println("Exiting.");
      result = true;
    }
    else if (rc != endMarker) 
    {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx > numChars) //too long
      {
        Serial.println("Your string has exceeded the maximum limit of 100 characters");
        ndx = numChars - 1; //just overwrite the last char
      }
    }
    else
    {
      receivedChars[ndx] = '\0'; //terminate the string
      ndx = 0;
      newData = true;
    }
  }
  return result;
}

void transmitMorse() 
{
  if (newData == true) 
  {
    Serial.println("Transmitting the following string in Morse Code: ");
    Serial.println(receivedChars);
    int i = 0;
    int index=0;
    while(receivedChars[i] != '\0')
    {
      char one_char = receivedChars[i];
      //is it a space? delay 4 units (3 were already waited at the end of last letter)
      //this assumes we don't start with a space
      if(one_char == ' ')
      {
        delay(4*time_unit); 
      }
      else if(isalpha(one_char))
      {
        //get the letter from the table
        if(one_char >= 'a') //lowercase v capital
        {
          index = one_char - 'a';
        }
        else
        {
          index = one_char - 'A';
        }
        playLetter(letters[index]);
      }
      else if(isdigit(one_char))
      {
        //get the number from the table
        playLetter(numbers[int(one_char)]);
      }
      else
      {
        Serial.println("Unknown char. Cannot transmit as Morse. Skipping.");
      }
      //otherwise just play the letter
      i++;
    }
    newData = false;
    delay(1000);
    Serial.println("Enter another string to transmit, or '!' to quit.");
  }
}

void playLetter(const char *input)
{
  int i = 0;
  while(input[i] != '\0')
  {
    if(input[i] == '.')
    {
      digitalWrite(ledPin, HIGH);
      delay(time_unit);
      digitalWrite(ledPin, LOW);
    }
    else
    {
      //it is a dash
      digitalWrite(ledPin, HIGH);
      delay(3*time_unit);
      digitalWrite(ledPin, LOW);
    }
    delay(time_unit); //the time between letters is the duration of a dot
    i++;
  }
  delay(2*time_unit); //the time between letters is the duration of a dash, we already waited one unit
}
