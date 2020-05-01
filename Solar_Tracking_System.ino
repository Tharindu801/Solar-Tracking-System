const int ldrPin1 = A1;
const int ldrPin2 = A2;

const int relay1 = 12;
const int relay2 = 11;

// End point push buttons
const int buttonPin_End_Left = 9;
const int buttonPin_End_Right = 8;

//Auto Button
const int buttonPin_Auto = 7;
//Manual Button
const int buttonPin_Manual = 6;



// Rotate Button
const int buttonPin_Rotate_Left = 5;
const int buttonPin_Rotate_Right = 4;

void setup() {
  Serial.begin(115200);
  
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  pinMode(ldrPin1, INPUT);
  pinMode(ldrPin2, INPUT);
     
  pinMode(buttonPin_End_Left, INPUT);
  pinMode(buttonPin_End_Right, INPUT);

  pinMode(buttonPin_Auto, INPUT);
  pinMode(buttonPin_Manual, INPUT);
    
  pinMode(buttonPin_Rotate_Left, INPUT);
  pinMode(buttonPin_Rotate_Right, INPUT);

  delay(1000);
 
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);


}

void loop() {

  int ldrStatus1 = analogRead(ldrPin1);
  int ldrStatus2 = analogRead(ldrPin2);

  int buttonPin_Auto_State = digitalRead(buttonPin_Auto);
  int buttonPin_Manual_State = digitalRead(buttonPin_Manual);
     
  int buttonPin_Rotate_Left_State = digitalRead(buttonPin_Rotate_Left);
  int buttonPin_Rotate_Right_State = digitalRead(buttonPin_Rotate_Right);


  int buttonStateLeft = digitalRead(buttonPin_End_Left);
  int buttonStateRight = digitalRead(buttonPin_End_Right);

  Serial.println(ldrStatus1);
  Serial.println(ldrStatus2);
  
  // Auto Mode
   if(buttonPin_Auto_State == HIGH){
     // if(true){
        Serial.println("Auto Mode");
        resetPosition(buttonStateLeft);
      
        
        int calculateValue1 = 0;
        int calculateValue2 = 0;
      
        for(int i=0; i<60; i++){
          calculateValue1 = calculateValue1 + ldrStatus1;
          calculateValue2 = calculateValue2 + ldrStatus2;
          Serial.print("Right : ");
          Serial.println(calculateValue1);
          Serial.print("Left : ");
          Serial.println(calculateValue2);
          
          if(digitalRead(buttonPin_Manual) == HIGH){
              break;
              Serial.println("Break Automode");
            }
            if(digitalRead(buttonPin_End_Left) == HIGH){
              resetPosition(buttonStateLeft);
              break;
            }
          delay(500); // *******************************************************
        }
        
        Serial.println();
        calculateValue1 = calculateValue1/60;
        calculateValue2 = calculateValue2/60;
        Serial.println(calculateValue1);
        Serial.println(calculateValue2);
        
        if(calculateValue1 > calculateValue2 ){
             
          digitalWrite(relay2, HIGH); 
          digitalWrite(relay1, LOW);  
          Serial.println("Right");
          delay(200);
          
          resetPosition(buttonStateLeft);
             
        }else if (calculateValue2 > calculateValue1){
            //turn LED on
          digitalWrite(relay1, HIGH); 
          digitalWrite(relay2, LOW); 
          Serial.println("Left");
          delay(200);
           
          resetPosition(buttonStateLeft);
          
        }else  
           digitalWrite(relay1, HIGH);    
           digitalWrite(relay2, HIGH);     
           delay(200);
        }
         digitalWrite(relay1, HIGH);     
         digitalWrite(relay2, HIGH);     
        // delay(840000); 
         for(int i=1; i<=60; i++){
           
            Serial.println("********************************");
           Serial.println(i);
           
            if(digitalRead(buttonPin_Manual) == HIGH){
              break;
              Serial.println("Break Automode");
            }
            if(digitalRead(buttonPin_End_Left) == HIGH){
              resetPosition(buttonStateLeft);
              break;
            } 
            
            delay(100);
         }
    }
   // Manual Mode
    if(buttonPin_Manual_State == HIGH){
      Serial.println("Manual Mode");
        if(buttonPin_Rotate_Left_State == HIGH && buttonStateLeft == LOW){
          digitalWrite(relay1, HIGH); 
          digitalWrite(relay2, LOW); 
          Serial.println("Turn Left");
        }else if(buttonPin_Rotate_Right_State == HIGH && buttonStateRight == LOW){
          digitalWrite(relay2, HIGH); 
          digitalWrite(relay1, LOW); 
          Serial.println("Turn Right");
        }else{
          digitalWrite(relay2, HIGH); 
          digitalWrite(relay1, HIGH);
        }
       delay(200);
    }
  
}
void resetPosition(int value){
  
  if(value == HIGH){
    Serial.println("Touched End Left");

    while(digitalRead(buttonPin_End_Right) == LOW){
      Serial.println("Not ********** Touched End Right");
      digitalWrite(relay2, HIGH); 
      digitalWrite(relay1, LOW); 
    }
    
     if(digitalRead(buttonPin_End_Right) == HIGH){
      Serial.println("Touched End Right");
       digitalWrite(relay1, HIGH); 
     }
     
  }
}

