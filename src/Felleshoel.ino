#define ALARM_DURATION 3000 // Alarm duration
#define RELAY_ON 0 // State when relay is activated

int relay_pin = 13;
int detector_pin = 12;

boolean alarmLock = false;

/*
Activates the alarm for [ALARM_DURATION] milliseconds.
*/
void activateAlarm(){
    if(alarmLock){
        return;
    }
    
    alarmLock = true;
    
    digitalWrite(relay_pin, RELAY_ON);
    delay(ALARM_DURATION);
    digitalWrite(relay_pin, !RELAY_ON);
    
    alarmLock = false;
}


/*
Returns whether the circuit is closed or not.
*/
boolean checkCircuit(){
    return digitalRead(detector_pin);
}


void setup() {
    pinMode(relay_pin, OUTPUT); // Set pin controlling alarm as output
    pinMode(detector_pin, INPUT); // Set pin for detecting closed circuit as input
    
    digitalWrite(relay_pin, !RELAY_ON);
}


void loop() {
    boolean circuitClosed = checkCircuit();
    
    if(!alarmLock && circuitClosed){
        // Activate alarm
        activateAlarm();
    }
}

