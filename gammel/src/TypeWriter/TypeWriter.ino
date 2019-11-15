
int inputPin = 8;
int relayPin = 9;
int speakerPin = 3;

#define RELAY_TIME 10
#define SPEAKER_TIME 3

#define RELAY_ACTIVE LOW
#define RELAY_OFF HIGH

#define SPEAKER_ON HIGH
#define SPEAKER_OFF LOW

int current = LOW;

void setup(){
  pinMode(inputPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);

  digitalWrite(relayPin, RELAY_OFF);
  digitalWrite(speakerPin, SPEAKER_OFF);
}


void loop(){
  current = digitalRead(inputPin);
  int temp = LOW;
  
  if (current == HIGH){
   while (current == HIGH){
      current = digitalRead(inputPin);
      delay(25);
      temp = digitalRead(inputPin);
      if (temp == LOW){
        delay(25);
        temp = digitalRead(inputPin);
        if (temp == LOW){
          current = LOW;
        } else {
         current = HIGH;
        }
      }
        //ARMED
    }

    // TRIGGER THE STUFFZ
    digitalWrite(relayPin, RELAY_ACTIVE);
    digitalWrite(speakerPin, SPEAKER_ON);
    delay(SPEAKER_TIME*1000);
    digitalWrite(speakerPin, SPEAKER_OFF);
    //PLING
    delay((RELAY_TIME - SPEAKER_TIME) *1000);
    digitalWrite(relayPin, RELAY_OFF);
  }
}
