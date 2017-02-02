#define DETECTOR_ACTIVE_STATE 0 // State when detector is active

#define RELAY_ON 1 // State when relay is activated
#define SPEAKER_ON 0 // State when speaker is activated

#define RELAY_DURATION 5000 // Duration of alarm lights
#define SPEAKER_DURATION 3000 // Duration of alarm sound

#define RELAY_PIN 13 // Output pin for relay
#define SPEAKER_PIN 12 // Output pin for speaker
#define DETECTOR_PIN 11 // Input pin for detector


boolean alarmLock = false;


/*
Activates the alarm.
*/
void activateAlarm(){
    if(alarmLock){
        return;
    }
    
    alarmLock = true;
    
    digitalWrite(RELAY_PIN, RELAY_ON);
    digitalWrite(SPEAKER_PIN, SPEAKER_ON);
    
    delay(SPEAKER_DURATION);
    
    digitalWrite(SPEAKER_PIN, !SPEAKER_ON);
    
    delay(abs(RELAY_DURATION - SPEAKER_DURATION));
    
    digitalWrite(RELAY_PIN, !RELAY_ON);
    
    alarmLock = false;
}


/*
Returns whether the circuit is closed or not.
*/
boolean checkCircuit(){    
    return digitalRead(DETECTOR_PIN) == DETECTOR_ACTIVE_STATE;
}


void setup() {
    pinMode(RELAY_PIN, OUTPUT); // Set pin controlling relay as output
    pinMode(SPEAKER_PIN, OUTPUT); // Set pin controlling speaker as output
    pinMode(DETECTOR_PIN, INPUT); // Set pin for detecting closed circuit as input
    
    digitalWrite(RELAY_PIN, !RELAY_ON);
    digitalWrite(SPEAKER_PIN, !SPEAKER_ON);
    
    Serial.begin(9600);
}


void loop() {    
    if(!alarmLock && checkCircuit()){
        // Activate alarm
        activateAlarm();
    }
}

