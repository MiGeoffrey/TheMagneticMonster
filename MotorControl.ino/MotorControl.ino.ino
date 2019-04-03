// Basic Arduino server

// === Definitions =================================================

int pStep = 12;
int pDir = 13;
int period = 2000;
boolean isRunning = false;

// === Setup =======================================================

void setup() {                

  // --- Pin setup
  pinMode(pStep, OUTPUT);
  digitalWrite(pStep, LOW);
  pinMode(pDir, OUTPUT);
  digitalWrite(pDir, LOW);

  // --- Serial communication
  Serial.begin(115200);
  Serial.setTimeout(10);
  
}

// === Main loop ===================================================

void loop() {

  // --- Manage inputs ---------------------------------------------
  
  if (Serial.available()) {   

    String input = Serial.readString();
    input.trim();
    
    // --- Get information
    if (input.equals("GetInfo")) {
      
      Serial.println("TheMagneticMonster");
      
    // --- Left
    } else if (input.equals("left")) {
      
      digitalWrite(pDir, LOW);
      Serial.println("LeftDir");
      
     // --- Right
    } else if (input.equals("right")) {
      
      digitalWrite(pDir, HIGH);
      Serial.println("RightDir");
     
    // --- Run
    } else if (input.equals("run")) {
      
      isRunning = true;
      Serial.println("Running");
     
    // --- Stop
    } else if (input.equals("stop")) {
      
      isRunning = false;
      Serial.println("Stop");
      
    }
  }
  
  // --- Actions ---------------------------------------------------
  
  if (isRunning) {

    digitalWrite(pStep, HIGH); 
    delayMicroseconds(period/2);

    digitalWrite(pStep, LOW);
    delayMicroseconds(period/2);
  
  }
  
}
