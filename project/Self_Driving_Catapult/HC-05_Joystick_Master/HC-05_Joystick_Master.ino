//조이스틱 값 블루투스로 전달하는 코드 (마스터, HC-05)
#include <SoftwareSerial.h>

//블루투스 통신 객체 선언 (Tx, Rx)
SoftwareSerial BTSerial (2, 3);

//조이스틱 핀 번호 및 데이터 저장 변수 선언
int pin[2] = {A0, A1}, value[2];

void setup() {
  //블루투스 통신 설정
  BTSerial.begin(9600);
}

void loop() {
  for(int i=0; i<2; i++){
    //조이스틱 값 배열에 저장
    value[i] = analogRead(pin[i]);

    //x, y축 값을 전송 및 구분 가능하도록 데이터 변환 (map함수)
    if(i == 0){
      value[i] = map(value[i], 0, 1023, 0, 127);
    }
    else{
      value[i] = map(value[i], 0, 1023, 128, 255);
    }

    //블루투스 통신으로 데이터 전송
    BTSerial.write(value[i]);
    delay(1);
  }
}
