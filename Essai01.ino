  #include <SoftwareSerial.h>
  #include <DFPlayerMini_Fast.h>

  SoftwareSerial mySerial(8, 9); // RX, TX
  DFPlayerMini_Fast myMP3;

  const unsigned long trackDuration = 3 * 60 * 1000; // replace with the exact duration of the mp3 file --> 3 * 60 * 1000 = 180000ms = 3min
  const byte potPin = A1;
  #define BrocheTX 9 
  unsigned long prevTime = millis();
  byte volumeLevel = 0; //variable for holding volume level

  void setup()
  {
  Serial.begin(9600);
  mySerial.begin(9600);
  myMP3.begin(mySerial);
  
  myMP3.play(4);
  }

  void loop()
  {
  volumeLevel = map(analogRead(potPin), 0, 1023, 0, 30);   //scale the pot value and volume level
  pinMode (BrocheTX, OUTPUT);
  delay(5);
  myMP3.volume(volumeLevel);
  Serial.println(volumeLevel);
  delay(5);
  pinMode (BrocheTX, INPUT_PULLUP);
  if((millis() - prevTime) >= trackDuration)
  {
  prevTime += trackDuration;
    
  pinMode (BrocheTX, OUTPUT);
  delay(5);
  myMP3.play(4);
  delay(5);
  pinMode (BrocheTX, INPUT_PULLUP);
    
  }
  }
