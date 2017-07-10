
// Muthanna A. Attyah 2017
// Please feel free to use and share code.

#define rxPin 2       // Serial input connects to Emic2 SOUT
#define txPin 3       // Serial output connects to Emic2 SIN
#define ledPin 13     // Arduino on-board LED on this pin

#define song1   "S [:phone arpa speak on][:rate 200][:n0][hxae<300,10>piy<300,10> \
                brrrx<600,12>th<100>dey<600,10>tuw<600,15> yu<1200,14>_<300> hxae<300,10>piy<300,10> \
                brrrx<600,12>th<100>dey<600,10> tuw<600,17>yu<1200,15>_<300> hxae<300,10>piy<300,10> \
                brrrx<600,22>th<100>dey<600,19> dih<600,15>r \
                eh<600,14>m<100,12>ih<350,12>k_<120>_<300> hxae<300,20>piy<300,20> \
                brrrx<600,19>th<100>dey<600,15> tuw<600,17> yu<1200,15>][:n0]\n"

#define song2P1 "S [:phone arpa speak on][:rate 100][:n0][ow<200,18>ow<200,15> sey<400,11> kae<400,15>n \
                yu<400,18>w siy<600,23> _<300> bay<350,27> dhah<50,25> dao<400,23>nz rr<400,15>ll \
                iy<400,17> llay<600,18>t _<300> wah<200>t sow<200> praw<600,27>dlliy<200,25> wiy<400,23> \
                hxey<400,22>eld _<300> ae<300,20>t dhah<100,22> tway<400,23> llay<400>ts llae<400,18>st \
                glliy<400,15>m iy<200,11>nx _<300> hxuw<300,18>z brao<100,15>d stray<400,11>ps \
                ae<400,15>nd bray<400,18>t stah<600,23>rz _<300> thruw<300,27> dhah<100,25> peh<400,23> \
                rrel<400,15> ah<400,17>s fay<600,18>t _<300> ow<200,18>r dhah<200,18> \
                rrae<600,27>mpah<200,25>rts wiy<400,23> waa<600,22>cht wrr<300,20> sow<100,22> \
                gae<400,23>llah<400>ent lliy<400,18> striy<400,15>miy<200,11>nx _<300>][:n0]\n"

#define song2P2 "S [:phone arpa speak on][:rate 100][:n0][ae<300,27>nd dhah<100> raa<400> keh<400,28>ts r \
                eh<400,30>d glley<700>r _<300> dhah<100,28> baa<400,27>mz brr<400,25>stih<400,27>nx \
                ih<400,28>n ey<600>r _<300> gey<400>v pruw<600,27>f thruw<200,25> dhah<400,23> \
                nay<900,22>t dhae<300,20>d aw<100,22>rr fllae<400,23>g wah<400,15> stih<400,17>ll \
                dheh<600,18>r _<300> ow<400> sey<400,23> dah<400>z dhae<200,23>ae<200,22>t \
                stah<400,20>r spae<400>ngel<400>d bae<400,25>nrr<200,28>rr<200,27> \
                yxeh<200,25>eh<200,23>t wey<800,23>ey<150,25>ey<150,23>ey<1200,22>v _<900> \
                fow<300,18>rdhah<300> llae<900,23>ae<400,25>nd ah<300,27>v dhah<300,28> \
                friy<1000,30>iy<1000,35> _<900> ae<300,23>nd dhah<300,25> hxow<1000,27>m _<600> \
                ah<300,28>v dhah<1000,25> brrey<1500,23>v _<900>][:n0]\n"
                

void emicInit(void);  // To initilize EMIC2 board
void emicWait(void);  // To wait for EMIC2 until current task is finished.

void setup()  // Set up code called once on start-up
{
  
  pinMode(ledPin, OUTPUT);  // define pin modes

  emicInit();
    
}

void loop()  // Main code, to run repeatedly
{

  Serial.print("D0\n"); // Introduction speech
  emicWait();

  delay(500);
  Serial.print("S I will repeat in spanich\n");
  emicWait();

  delay(500);
  Serial.print("D2\n"); // Spanish Language
  emicWait();

  delay(500);
  Serial.print("S Now I will sing a song for you\n");
  emicWait();

  Serial.print("D1\n"); // Sing a song
  emicWait();

  Serial.print("P0\n");  //Change to DECTalk parser
  emicWait();
  
  Serial.print("S I can also talk like a Robot\n");
  emicWait();
  
  delay(500);
  Serial.print("S [:rate 200][:n0][:dv ap 90 pr 0] All your base are belong to us\n");
  emicWait();

  delay(500);
  Serial.print("S I have another song\n");
  emicWait();

  delay(500);
  Serial.print(song2P1);
  emicWait();
  Serial.print(song2P2);
  emicWait();

  delay(500);
  Serial.print("S And my last song\n");
  emicWait();

  delay(500);
  Serial.print(song1);
  emicWait();
  
  Serial.print("P1\n");  //Change to EPSON parser

  delay(500);
  Serial.print("S Demonstration complete\n");
  emicWait();

  Serial.print("S Thank you very much\n");
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
  Serial.begin(9600);     // set the data rate for the SoftwareSerial port
  digitalWrite(ledPin, LOW);  // turn LED off
  
  /*
    When the Emic 2 powers on, it takes about 3 seconds for it to successfully intialize. It then sends a ":" character to indicate it's ready to accept
    commands. If the Emic 2 is already initialized, a CR will also cause it to send a ":"
  */
  
  Serial.print('\n');             // Send a CR in case the system is already up
  while (Serial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  Serial.flush();                 // Flush the receive buffer

  Serial.print("R\n");            // Revert to default Settings
  emicWait();
  
  Serial.print("V15\n");          // Set Volume to 15 dB
  emicWait();
}

// ---------------------------------------------------------------------
// Wait for EMC to finish the current task, Keep LED ON while waiting.
// ---------------------------------------------------------------------
void emicWait(void)
{
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (Serial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);          // Turn off LED and return.
}

