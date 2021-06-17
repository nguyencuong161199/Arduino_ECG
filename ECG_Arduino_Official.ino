#define SERIAL_BUFFER_SIZE 8192
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX, TX , đổi ngược chân khi ở bên arduino
unsigned long myTime = 0;
unsigned long lastMicros = 0;

char c; 

void setup() {
 
  // initialize the serial communication:


  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -

  Serial.println("CLEARDATA"); //clears up 
  Serial.println("RESETTIMER"); //resets timer to 0
  Serial.begin(115200);
  BTSerial.begin(9600); 
}


const unsigned long READ_PERIOD = 6000;  // 4000 us: 250 Hz _____ (1/T)=>F*10^-6
void loop() {
  
static unsigned long lastRead = 0;
    if (micros() - lastRead >= READ_PERIOD) {
        lastRead += READ_PERIOD;
        
        //Serial.println(micros());
        int data = analogRead(A0);
        //Serial.println(data+""+myTime);
        //Serial.println(String(data)+ " -" + String(micros()));
        //delay(1);
        BTSerial.println(String(data));// + "-" + String(0));
        }


    if(BTSerial.available() > 0){ 
        while(BTSerial.available() > 0){ 
          c = BTSerial.read(); 
          delay(10); //Delay required 
          if (c == 13 or c == 10)
          {
            continue;
          }
          //Serial.print("Received: ");
          Serial.println(c);         
          //delay(1000); 
        }
    }
  
}
        
    
