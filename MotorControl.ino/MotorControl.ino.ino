// Basic Arduino server

// === Definitions =================================================

int pStep = 12;
int pDir = 13;
float period;
byte SerialOK=0;
char str[10];
int i;
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

  //saisie de la période
  Serial.println("enter the period");
  while(SerialOK==0){
    if(Serial.available()>0){
      delay(5);
      for(i=0;i<10;i++) str[i]=NULL;
        i=0;
      while(Serial.available()){
        str[i++]= Serial.read();
        Serial.print(str[i]);
      }
      if(atof(str)!=10) SerialOK=1;
    }
      //Serial.print("period=");
     // period = Serial.read();
      //if(period != 0){
      //  Serial.println("the period is");
      //  Serial.println(period);
      //  SerialOK=1;
     // }else Serial.println("recommence");
    //}
 
  }
  period = atof(str);
  Serial.println("the period is");
  Serial.println(period);
  Serial.println("le programme est pret"); 
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
    } else if (input.equals("right")) {
      
      digitalWrite(pDir, LOW);
      Serial.println("LeftDir");
      
     // --- Right
    } else if (input.equals("left")) {
      
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
