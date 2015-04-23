
int inputPin = 8;
int ledPin = 9;

#define PLING_TIME 10

int current = LOW;

void setup(){
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
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
        //ARMED
    }
    digitalWrite(ledPin, LOW);
    //PLING
   delay(PLING_TIME*1000);
   digitalWrite(ledPin, HIGH);
  }
}
