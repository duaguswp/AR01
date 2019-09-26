
/*
 예제 3.2
 I2C를 이용한 LCD 출력
*/

// I2C 통신 라이브러리 설정
#include <Wire.h>
// I2C LCD 라리브러리 설정
#include <LiquidCrystal_I2C.h>

// LCD I2C address 설정 PCF8574:0x27, PCF8574A:0x3F
LiquidCrystal_I2C lcd(0x27,16,2);  // LCD address:0x27, 16X2 LCD, 0x3F
int blinkNumber = 0;
void setup()
{
  // 9600 bps로 시리얼 통신 설정
  Serial.begin(9600);
  lcd.init(); // LCD 설정
  lcd.clear();      // LCD를 모두 지운다.
  lcd.backlight();  // 백라이트를 켠다.  
  // Arduino LCD, Welcome 표시  
  lcd.setCursor(0,0);
  lcd.print("Arduino LCD");
  lcd.setCursor(0,1);
  lcd.print("Welcome");
  delay(250);  


}
void loop() {
  if(Serial.available()){       
   char val = Serial.read(); 
    if(isDigit(val)){
      blinkNumber = (val - '0');
    }
    
   
    
  for(char i = 0; i< blinkNumber; i++)
    {
       lcd.noBacklight();
  delay(200);
       lcd.backlight();
  delay(200);
    }
    while(Serial.available()>0){
    lcd.clear();
    lcd.print("write :");
    lcd.write(blinkNumber);
    }
  }
  
}
