const int Beep = 2;           //warning sound
const int Ext_LED = 3;        //external LED
const int H_Trig = 5;         //ultrasonic wave trig
const int H_Echo = 6;         //ultrasonic wave echo
const int Shelf_LED = 7;      //shelf status LED
const int Red_LED = 10;       //Red LED
const int Yellow_LED = 11;    //Yellow LED
const int Green_LED = 12;     //Green LED

const int Door_LDR = A0;      //door LDR
const int Shelf_LDR = A1;     //shelf LDR
 
int State_Door;         //door open/close status
int State_Shelf;        //something is/isn't on the shelf status

State_Door = 0;         //initialize variables
State_Shelf = 0;
 

void setup()
{
      Serial.begin(9600);
      
      pinMode(Ext_LED, OUTPUT);     // external LED
      pinMode(Beep, OUTPUT);        // warning sound 
         
      pinMode(H_Trig, OUTPUT);      // ultrasonic sensor Trig pin
      pinMode(H_Echo,INPUT);        // ultrasonic sensor Echo pin
      
      pinMode(Shelf_LED, OUTPUT);   // shelf LED     
      pinMode(Red_LED, OUTPUT);     // RED LED
      pinMode(Yellow_LED, OUTPUT);  // YELLOW LED
      pinMode(Green_LED, OUTPUT);   // GREEN LED
      
      pinMode(Door_LDR, INPUT);     // door LDR
      pinMode(Shelf_LDR, INPUT);    // shelf LDR
} 
 
 
void loop() 
{
      long duration;
      long cm;
    
      // door LDR
      State_Door = analogRead(Door_LDR);              // save Door LDR to State_Door
    
      // ultrasonic
      digitalWrite(H_Trig, HIGH);                     // Trig on for 10us
      delayMicroseconds(10);                          
      digitalWrite(H_Trig, LOW);                      // Trig off
      duration = pulseIn(H_Echo, HIGH);               // Echo pin: calculate HIGH->Low differences
      cm = microsecondsToCentimeters(duration);       // change to cm
 
  
      // when door is closed
      if (State_Door > 980) {                       
          digitalWrite(Shelf_LED, LOW);               // shelf LED off       
 
            // 휴지 
            if (cm > 100) {                           // if 100 < distance
                  digitalWrite(Ext_LED, HIGH);              // external LED on         
                  digitalWrite(Beep, HIGH);                 // beep on
                  digitalWrite(Red_LED, HIGH);              // Red LED 
                  delay(1000);
                  digitalWrite(Red_LED, LOW);
            }
            else if (cm > 10 && cm < 100) {           // if 10 < distance < 100
                  digitalWrite(Ext_LED, LOW);               // external LED off
                  digitalWrite(Beep, LOW);                  // beep off
                  digitalWrite(Yellow_LED, HIGH);           // Yellow LED
                  delay(1000);
                  digitalWrite(Yellow_LED, LOW);
            }
            else {                                    // if distance < 10
                  digitalWrite(Ext_LED, LOW);               // external LED off
                  digitalWrite(Beep, LOW);                  // beep off
                  digitalWrite(Green_LED, HIGH);            // Green LED
                  delay(1000);
                  digitalWrite(Green_LED, LOW);
            }
          
      }
      
      // when door is open
      else {                                        
 
            // external LED
            if (cm > 100) {                           // if 100 < distance
                  digitalWrite(Ext_LED, HIGH);              // external LED on
            }
            else {                                   // if distance < 100
                  digitalWrite(Ext_LED, LOW);               // external LED off
            }
   
            // shelf
            State_Shelf = analogRead(Shelf_LDR);
                
            if(State_Shelf > 100) {                   // if something is on the shelf
                  digitalWrite(Beep,HIGH);                  // beep on          
                  digitalWrite(Shelf_LED, HIGH);            // shelf LED on
                  delay(State_Shelf);                       // delay
             }
             else {                                   // if something isn'f on the shelf
                  digitalWrite(Beep, LOW);                  // beep off
                  digitalWrite(Shelf_LED, LOW);             // shelf LED off 
                  delay(State_Shelf);                       // delay
             }
           
      }
      
}
 
 
long microsecondsToCentimeters(long microseconds) {
    return microseconds / 29 / 2;
}

