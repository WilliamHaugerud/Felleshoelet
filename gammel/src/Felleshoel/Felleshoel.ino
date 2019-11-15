#define DETECTOR_ACTIVE_STATE 0 // State when detector is active

#define LIGHT_ON 1 // State when light is activated
#define SPEAKER_ON 0 // State when speaker is activated

#define LIGHT_DURATION 5000 // Duration of alarm lights
#define SPEAKER_DURATION 3000 // Duration of alarm sound

#define LIGHT_PIN 9 // Output pin for light
#define SPEAKER_PIN 7 // Output pin for speaker
#define DETECTOR_PIN 4 // Input pin for detector

int lightOnlyDuration = LIGHT_DURATION - SPEAKER_DURATION;
boolean alarmLock = false;


/*
Activates the alarm.
*/
void activateAlarm(){
    if(alarmLock){
        return;
    }
    
    alarmLock = true;
    
    digitalWrite(LIGHT_PIN, LIGHT_ON);
    digitalWrite(SPEAKER_PIN, SPEAKER_ON);
    
    delay(SPEAKER_DURATION);
    
    digitalWrite(SPEAKER_PIN, !SPEAKER_ON);
    
    delay(lightOnlyDuration);
    
    digitalWrite(LIGHT_PIN, !LIGHT_ON);
    
    alarmLock = false;
}


/*
Returns whether the circuit is closed or not.
*/
boolean checkCircuit(){    
    return digitalRead(DETECTOR_PIN) == DETECTOR_ACTIVE_STATE;
}


void setup() {
    pinMode(LIGHT_PIN, OUTPUT); // Set pin controlling light as output
    pinMode(SPEAKER_PIN, OUTPUT); // Set pin controlling speaker as output
    pinMode(DETECTOR_PIN, INPUT); // Set pin for detecting closed circuit as input
    
    digitalWrite(LIGHT_PIN, !LIGHT_ON);
    digitalWrite(SPEAKER_PIN, !SPEAKER_ON);
}


void loop() {    
    if(!alarmLock && checkCircuit()){
        // Activate alarm
        activateAlarm();
    }
}

