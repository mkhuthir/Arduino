
#include <SoftwareSerial.h> // include the SoftwareSerial library so we can use it to talk to the Emic 2 module

#define rxPin 2       // Serial input connects to Emic2 SOUT
#define txPin 3       // Serial output connects to Emic2 SIN
#define ledPin 13     // Arduino on-board LED on this pin

SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);  // set up a new serial port

void emicInit(void);  // To initilize EMIC2 board
void emicWait(void);  // To wait for EMIC2 until current task is finished.

void setup()  // Set up code called once on start-up
{
  
  pinMode(ledPin, OUTPUT);  // define pin modes
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  emicInit();
    
}

void loop()  // Main code, to run repeatedly
{
  
  
  emicSerial.print("S Hello. My name is the Emic 2 Text-to-Speech module. I would like to sing you a song.\n"); // Speak some text
  emicWait();
      
  delay(500);    // 500 ms delay
  
  emicSerial.print("D1\n"); // Sing a song
  emicWait();

  emicSerial.print("S Demonstration complete\n");
  emicWait();

  emicSerial.print("S Thank you very much\n");
  emicWait();
  
  while(1)      // Demonstration complete!
  {
    delay(100);
    digitalWrite(ledPin, HIGH);
    delay(100);              
    digitalWrite(ledPin, LOW);
  }
  
}

// ---------------------------------------------------------------------
// Initilizes emic serial port and wait for ":" charcter.
// ---------------------------------------------------------------------
void emicInit(void)
{
  emicSerial.begin(9600);     // set the data rate for the SoftwareSerial port
  digitalWrite(ledPin, LOW);  // turn LED off
  
  /*
    When the Emic 2 powers on, it takes about 3 seconds for it to successfully intialize. It then sends a ":" character to indicate it's ready to accept
    commands. If the Emic 2 is already initialized, a CR will also cause it to send a ":"
  */
  
  emicSerial.print('\n');             // Send a CR in case the system is already up
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  emicSerial.flush();                 // Flush the receive buffer
}

// ---------------------------------------------------------------------
// Wait for EMC to finish the current task, Keep LED ON while waiting.
// ---------------------------------------------------------------------
void emicWait(void)
{
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);          // Turn off LED and return.
}

