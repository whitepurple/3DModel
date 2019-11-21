#include <NeoSWSerial.h>
int RX = 3;
int TX = 2;
 NeoSWSerial mySerial(RX, TX);  
int dir_l = 4;
int dir_r = 7;
int pwm_l = 6;
int pwm_r = 5;
int led_green = 9;
int led_blue = 10;
int led_red = 11;
int piezo_pin = 8;
int button = 16;

void setup() {
   Serial.begin(9600);
   mySerial.attachInterrupt( handleRxChar );  
   mySerial.begin(9600);
   
   pinMode(dir_l, OUTPUT);
   pinMode(dir_r, OUTPUT);
   pinMode(pwm_l, OUTPUT);
   pinMode(pwm_r, OUTPUT);
   pinMode(led_green, OUTPUT);
   pinMode(led_blue, OUTPUT);
   pinMode(led_red, OUTPUT); 
   pinMode(piezo_pin, OUTPUT);
   pinMode(button, INPUT_PULLUP);  
 }

char btbuf;

volatile uint32_t flag;

static void handleRxChar( uint8_t c )   
    {
     btbuf = (char)c;
     flag = true;
    }
    
void loop() { 
   if (flag /*mySerial.available()*/)
   {
    flag = false;
    // btbuf = mySerial.read();
     Serial.println(btbuf); //디버깅용           
    if ('U' == btbuf) 
    {
     Serial.println("forward"); 
     moving(HIGH, HIGH, 200, 200);
    }
    else if ('u' == btbuf) 
    {
     Serial.println("forward"); 
     moving(LOW, LOW, 0, 0);
    }   
    else if ('D' == btbuf) 
    {
     Serial.println("backward"); 
     moving(LOW, LOW, 200, 200);
    }  
    else if ('d' == btbuf) 
    {
     Serial.println("backward"); 
     moving(HIGH, HIGH, 0, 0);
    }  
            else if ('L' == btbuf) 
    {
     Serial.println("left rotate"); 
     moving(LOW, HIGH, 200, 200);
    }  
    else if ('l' == btbuf) 
    {
     Serial.println("left rotate"); 
     moving(LOW, HIGH, 0, 0);
    }  
        else if ('R' == btbuf) 
    {
     Serial.println("right rotate"); 
     moving(HIGH, LOW, 200, 200);
    }  
    else if ('r' == btbuf) 
    {
     Serial.println("right rotate"); 
     moving(HIGH, LOW, 0, 0);
    }  
        else if ('B' == btbuf) 
    {
     Serial.println("left axis"); 
     moving(LOW, HIGH, 0, 200);
    }  
    else if ('b' == btbuf) 
    {
     Serial.println("left axis"); 
     moving(LOW, LOW, 0, 0);
    }  
        else if ('E' == btbuf) 
    {
     Serial.println("right axis"); 
     moving(HIGH, LOW, 200, 0);
    }  
    else if ('e' == btbuf) 
    {
     Serial.println("right axis"); 
     moving(LOW, LOW, 0, 0);
    }  
        else if ('F' == btbuf) 
    {
     Serial.println("Accerlate"); 
     moving(HIGH, HIGH, 255, 255);
    }  
    else if ('f' == btbuf) 
    {
     Serial.println("Accerlate"); 
     moving(LOW, LOW, 0, 0);
    }  
          else if ('A' == btbuf) 
    {
     Serial.println("RGB LED"); 
     rgb(LOW, LOW, HIGH);
    }  
    else if ('a' == btbuf) 
    {
     Serial.println("RGB LED"); 
    //  rgb(HIGH, HIGH, HIGH);
       rgb(LOW, LOW, LOW);      
    } 
      else if ('M' == btbuf) 
    {
     Serial.println("BEEBOY Green"); 
     rgb(LOW, HIGH, HIGH); 
    }  
    else if ('N' == btbuf) 
    {
     Serial.println("BEEBOY Blue"); 
      rgb(HIGH, LOW, HIGH);
    } 
     else if ('O' == btbuf) 
    {
     Serial.println("BEEBOY Red"); 
      rgb(HIGH, HIGH, LOW);
    }
    else if ('S' == btbuf) 
    {
     Serial.println("Music"); 
    digitalWrite(piezo_pin, HIGH);
  //  delay(300);   
    }
    else if ('s' == btbuf) 
    {
     Serial.println("Music"); 
    digitalWrite(piezo_pin, LOW);
 //   delay(300);
    }    
   }   
}

void moving(int dirl, int dirr, int pwml, int pwmr)  
{
  digitalWrite(dir_l, dirl);
  digitalWrite(dir_r, dirr);
  analogWrite(pwm_l, pwml);
  analogWrite(pwm_r, pwmr);
}

void rgb(int ledgreen, int ledblue, int ledred)  
{
  digitalWrite(led_green, ledgreen);
  digitalWrite(led_blue, ledblue);
  digitalWrite(led_red, ledred);
}
