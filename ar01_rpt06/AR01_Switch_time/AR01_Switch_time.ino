#include <LiquidCrystal_I2C.h>




/*
 예제 5.3
 디지털 신호 입력 시간 측정하기
 */
#include <Wire.h>

// 2번핀을 스위치 입력으로 설정
const int inputPin = 2;

// 현재의 시간을 저장하기 위한 변수
long startTime = 0;
// 실제 스위치가 눌린 후 지연되는 시간
long swCountTimer = 0;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    lcd.init(); // LCD 설정
  lcd.clear();      // LCD를 모두 지운다.
  lcd.backlight();  // 백라이트를 켠다.  
  // Arduino LCD, Welcome 표시  
  lcd.setCursor(0,0);
  lcd.print("Arduino LCD");
  lcd.setCursor(0,1);
  lcd.print("Click switch");
  // 스위치 입력을 위하여 2번핀을 입력으로 설정하고 풀업시킨다
  pinMode(inputPin, INPUT_PULLUP);
  // 시리얼 통신을 설정한다  
  Serial.begin(9600);  
}

void loop(){
  // 스위치 입력이 발생하였을 경우 실행
  if(digitalRead(inputPin) == LOW){ 
    lcd.clear();
    // 현재의 시간을 startTime 변수에 넣는다.  	
    startTime = millis();
  lcd.setCursor(0,0);
  lcd.print("AR17 time check");
  lcd.setCursor(0,1);
  lcd.print("AR01");
    // 스위치가 입력되는 동안 지연시킨다.
    while(digitalRead(inputPin) == LOW);
    // swCountTimer 변수에 스위치가 눌려진 시간을 넣는다.
    // 여기까지 측정된 시간에서 앞서 저장한 시간이 스위치가 눌려진 시간이 된다
    swCountTimer = millis() - startTime;
    // 시리얼 통신으로 값을 출력한다.
  lcd.setCursor(5,1);
  lcd.print(swCountTimer);
  lcd.print("ms");
    Serial.print(swCountTimer);
    Serial.println(" ms");
  };
}
