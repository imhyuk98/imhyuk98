//블루투스 통신으로 값 전달받아 DC모터 동작하는 코드 (슬레이브, HC-06)
#include <SoftwareSerial.h>

//블루투스 시리얼 객체 선언 (Tx, Rx)
SoftwareSerial BTSerial (12, 11);

//양쪽 모터와 연결된 PWM 핀 번호 배열에 저장
int rightWheel[2] = {3, 4};
int leftWheel[2] = {6, 7};
#define ENA 2 
#define ENB 5
//속도를 저장할 변수 선언
int rfSpd = 0, rbSpd = 0;
int lfSpd = 0, lbSpd = 0;

void setup() {
  //블루투스 통신 설정
  BTSerial.begin(9600);

  //양쪽 모터 핀모드 설정
  for(int i=0; i<2; i++){
    pinMode(rightWheel[i], OUTPUT);
    pinMode(leftWheel[i], OUTPUT);
  }
}

void loop() {
  //블루투스로 데이터가 전달된다면
  if(BTSerial.available()){
    //전달된 데이터 읽기 및 읽은 값 정수로 변환
    unsigned char bt = BTSerial.read();
    int n = (int)bt;
    delay(1);

    //오른쪽 모터에 대한 속도 설정
    if(n >= 128){
      if(n >= 200){
        rfSpd = map(n, 200, 255, 100, 255);
        rbSpd = 0;
      }
      else if(n <= 184){
        rfSpd = 0;
        rbSpd = map(n, 184, 128, 100, 255);
      }
      else{
        rfSpd = 0;
        rbSpd = 0;
      }
    }

    //왼쪽 바퀴에 대한 설정
    if(n <= 127){
      if(n >= 72){
        lfSpd = map(n, 72, 127, 100, 255);
        lbSpd = 0;
      }
      else if(n <= 56){
        lfSpd = 0;
        lbSpd = map(n, 56, 0, 100, 255);
      }
      else{
        lfSpd = 0;
        lbSpd = 0;
      }
    }

    //각 모터 전압 값 전달 (PWM 방식)
    
    analogWrite(rightWheel[0], rfSpd);
    analogWrite(rightWheel[1], rbSpd);
    analogWrite(leftWheel[0], lfSpd);
    analogWrite(leftWheel[1], lbSpd);
    

}
}
