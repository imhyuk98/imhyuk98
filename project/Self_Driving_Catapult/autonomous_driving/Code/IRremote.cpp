#include <IRremote.h>
#include <Servo.h>

#define irReceiverPin A4  // IR 수신기 핀
#define servoPin A3       // 서보 모터 핀

IRrecv irReceiver(irReceiverPin);  // IR 수신 객체
decode_results irResults;           // 수신된 IR 신호를 저장하는 객체
Servo servoMotor;                   // 서보 모터 객체

bool buttonPressed = false;  // 버튼이 눌렸는지 여부를 저장하는 변수
int angle = 45;        // 서보 모터의 시작 각도

void setup() {
  irReceiver.enableIRIn();  // IR 수신기 초기화
  servoMotor.attach(servoPin);  // 서보 모터 핀 초기화
  servoMotor.write(angle); // 시작 각도로 서보 모터 설정
}

void loop() {
  if (irReceiver.decode(&irResults)) {  // IR 신호를 수신했을 때
    if (irResults.value == 0xFFB04F) {  // 수신된 IR 신호가 0xFFB04F일 때 동작
      buttonPressed = true;  // 버튼이 눌렸음을 표시
      angle = 50;     // 서보 모터 각도를 180도로 설정
      servoMotor.write(angle);  // 서보 모터를 설정한 각도로 회전
      delay(1000);  // 1초 동안 유지
      angle = 115;  // 서보 모터 각도를 45도로 설정
      servoMotor.write(angle);  // 서보 모터를 설정한 각도로 회전
    }
    irReceiver.resume();  // IR 신호 수신 재개
  }
}
