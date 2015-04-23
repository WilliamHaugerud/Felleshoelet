
int inputPin = 8;
int ledPin = 9;

int lastState = HIGH ;
int currentState = HIGH;
int current = LOW;

void setup(){
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.begin(9600);
}


void loop(){
  current = digitalRead(inputPin);
  int temp = LOW;
  if (current == HIGH){
   while (current == HIGH){
      current = digitalRead(inputPin);
      delay(30);
      temp = digitalRead(inputPin);
      if (temp == LOW){
        delay(30);
        temp = digitalRead(inputPin);
        if (temp == LOW){
          current = LOW;
        } else {
         current = HIGH;
        }
      }
      Serial.println("ARMED AND READY");
    }
    digitalWrite(ledPin, LOW);
   Serial.println("PLING");
   delay(10000);
   digitalWrite(ledPin, HIGH);
  }
  /*
  currentState = digitalRead(inputPin);
  if(lastState == HIGH){
    if(currentState == LOW){
      digitalWrite(ledPin, HIGH);
      Serial.println("PLING!");
      delay(4000);
      digitalWrite(ledPin, LOW);
    }
  }
  Serial.println("Venter på kontakt");
  lastState = currentState;
  */
}
