/*
 예제 7.1
 스텝모터 구동
 */
int cw_sw = 2;
int stop_sw = 3;
int ccw_sw = 4;
// 스텝 모터 신호핀 설정
int motorPin1 = 8;
int motorPin2 = 9;
int motorPin3 = 10;
int motorPin4 = 11;

boolean cwsw = false;
boolean ccwsw = false;
boolean stopsw = true;

// 스텝 모터의 스텝 설정
// 0~7은 동작 신호, 8번째는 모터 정지 신호
int steps[] = {B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001, B0000};

void setup() {
  //모터 신호핀을 출력으로 설정
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  pinMode(cw_sw, INPUT_PULLUP);
  pinMode(ccw_sw, INPUT_PULLUP);
  pinMode(stop_sw, INPUT_PULLUP);

  // 시리얼 통신 설정  
  Serial.begin(9600);
}

void loop(){

  if(digitalRead(cw_sw)==LOW){
    cwsw = true;
    ccwsw = false;
    stopsw = false;
  }
  else if(digitalRead(ccw_sw)==LOW){
    cwsw = false;
    ccwsw = true;
    stopsw = false;
  }
  else if(digitalRead(stop_sw)==LOW){
    cwsw = false;
    ccwsw = false;
    stopsw = true;
  }
  // CW로 회전시 모터를 CW방향으로 회전시킨다.
  if(cwsw == true){
    // 시리얼 통신 메세지를 출력한다.
    Serial.print("CW Motor");
    // CW로 회전시킨다.
    clockwise();
  }
  // CCW로 회전시 모터를 CCW방향으로 회전시킨다.
  else if(ccwsw == true){
    // 시리얼 통신 메세지를 출력한다.
    Serial.print("CCW Motor");
    // CCW로 회전시킨다.
    counterClockwise();
  }
  else if(stopsw == true){
    Serial.println("Motor Stop");
    motorStop();
  }
}

void counterClockwise(){
  // 0~7 번째 신호를 순차적으로 출력시킨다.
  for(int i = 0; i < 8; i++)
  {
    motorSignalOutput(i);
    delayMicroseconds(1000);
  }
}

void clockwise(){
  // 7~0 번째 신호를 순차적으로 출력시킨다.
  for(int i = 7; i >= 0; i--)
  {
    motorSignalOutput(i);
    delayMicroseconds(1000);
  }
}

void motorStop(){
  // 정지신호를 출력시킨다.
  motorSignalOutput(8); 
}

void motorSignalOutput(int out)
{
  // out 변수에 해당하는 모터 시그날을 출력한다.
  digitalWrite(motorPin1, bitRead(steps[out], 0));
  digitalWrite(motorPin2, bitRead(steps[out], 1));
  digitalWrite(motorPin3, bitRead(steps[out], 2));
  digitalWrite(motorPin4, bitRead(steps[out], 3));
}
