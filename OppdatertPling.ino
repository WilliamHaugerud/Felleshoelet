//Oppdatert 23.03.2023 av William og Håkon
//Vi gjorde det så lett som mulig hehe. Fjerna mye rare greier
#define DETECTOR_ACTIVE_STATE 0 // State when detector is active

#define LIGHT_ON 1 // State when light is activated
#define SPEAKER_ON 1 // State when speaker is activated

#define LIGHT_DURATION 5000 // Duration of alarm lights
#define SPEAKER_DURATION 3000 // Duration of alarm sound

#define LIGHT_PIN 9 // Output pin for light
#define SPEAKER_PIN 10 // Output pin for speaker
#define DETECTOR_PIN 4 // Input pin for detector

int lightOnlyDuration = LIGHT_DURATION - SPEAKER_DURATION;


/*
Activates the alarm.
*/
void runAlarm(){
    digitalWrite(LIGHT_PIN, LIGHT_ON);
    digitalWrite(SPEAKER_PIN, SPEAKER_ON);
    
    delay(SPEAKER_DURATION);
    
    digitalWrite(SPEAKER_PIN, !SPEAKER_ON);
    
    delay(lightOnlyDuration);
    
    digitalWrite(LIGHT_PIN, !LIGHT_ON);
}


/*
Returns whether the circuit is closed or not.
*/
boolean checkCircuit(){    
    //return digitalRead(DETECTOR_PIN) == DETECTOR_ACTIVE_STATE;
    int value = analogRead(A0);
    float voltage = value * 5.0/1023;
    Serial.println(voltage);
    if (voltage > 4.0)
      return true; // Skrevet av Håkon :3
    else
      return false;
}


void setup() {
    pinMode(LIGHT_PIN, OUTPUT); // Set pin controlling light as output
    pinMode(SPEAKER_PIN, OUTPUT); // Set pin controlling speaker as output
    pinMode(DETECTOR_PIN, INPUT); // Set pin for detecting closed circuit as input
    
    digitalWrite(LIGHT_PIN, !LIGHT_ON);
    digitalWrite(SPEAKER_PIN, !SPEAKER_ON);
    Serial.begin(9600);
}


void loop() {    
    if(checkCircuit()){
        // Activate alarm
        runAlarm();
    }
}
