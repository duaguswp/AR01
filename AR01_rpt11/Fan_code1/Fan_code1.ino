#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3f,16,2);
   
int motor_A = 3;
int motor_B = 4;
int pwm = 5;
const int stopBtn = 6;
const int goBtn = 7;
const int alertLED = 9;
const char echoPin = 12;
const char trigPin = 13;

int speed = 127;
int pulseWidth;
int distance;
 
void setup()
{
  Serial.begin(9600);
  lcd.init();
 
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,1);
  lcd.print("HUMIDITY: ");
  
  Serial.println("EMsek");
  pinMode(motor_A, OUTPUT);
  pinMode(motor_B, OUTPUT); 
  pinMode(stopBtn, INPUT_PULLUP);
  pinMode(goBtn, INPUT_PULLUP);
  pinMode(alertLED, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  digitalWrite(trigPin, LOW);
 

}
 
void loop()
{

  delay(1000);
  int temp = dht.readTemperature();
  int humi = dht.readHumidity();
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pulseWidth = pulseIn(echoPin, HIGH);  
  distance = pulseWidth / 58; 
  
  Serial.print("distance : ");
  Serial.println(distance);
  if (digitalRead(stopBtn) == LOW)
  {
    speed = 0;
  }
  
  if (digitalRead(goBtn) == LOW)
  {
    speed = 127;
  }
  
  lcd.print("TEMP:     ");
  lcd.print(temp);
   Serial.print("temp: ");
  Serial.println(temp);
  lcd.setCursor(0,1);
  lcd.print("HUMIDITY: ");
  lcd.print(humi);
 Serial.print("humi : ");
  Serial.println(humi);
  
  if ((humi >= 0) && (temp >= 0) && (distance <= 20))
  {
    digitalWrite(motor_A, HIGH);
    digitalWrite(motor_B, LOW);
    analogWrite(pwm, speed);
      
    digitalWrite(alertLED, HIGH);
  }
  else
  {
    digitalWrite(motor_A, HIGH);
    digitalWrite(motor_B, LOW);
    analogWrite(pwm, 0);
            
    digitalWrite(alertLED, LOW);
  }
  
  delay(500);
  
  lcd.clear();
}
