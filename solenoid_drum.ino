
byte BPM = 120; // beats per minute

// calculate how many milliseconds long a sixteenth note is at this tempo
long BeatDuration16 = round((60000 / BPM)/4);

long lastBeat = 0;
int sixteenths = 0;

const int ledPin = 13; // this is de pin for the LED onboard the Arduino
const int drum1 = 12; // this is the pin which connects to the solenoid 


void setup() {

  // wait for the button to be pressed before starting making noise
  const byte buttonPin = 8;
  pinMode(buttonPin, INPUT_PULLUP);
  while (digitalRead(buttonPin) == HIGH);
  
  pinMode(ledPin, OUTPUT); // define the LED pin as an output
  
  pinMode(drum1, OUTPUT); // define the solenoid pin as an output
  digitalWrite(drum1, LOW);
  
  lastBeat = millis(); // start the timer

}


void loop() {
  
  // only do something on every sixteenth note
  if( (millis() - lastBeat) >= BeatDuration16 ) {
    
    lastBeat = millis( );
    
    // keep track of on which 16th note of the bar we are
    if (++sixteenths > 16) { sixteenths = 1; }

    // do something every quarter note (that's every beat)
    if (!(sixteenths % 4)) { digitalWrite(ledPin, HIGH); } else { digitalWrite(ledPin, LOW); }

    // turn the solenoid on on every other quarter note (so half as fast)
    if ( sixteenths == 1 || sixteenths == 9 ) { digitalWrite(drum1, HIGH); }
    else { digitalWrite(drum1, LOW); }

  }
    
}

