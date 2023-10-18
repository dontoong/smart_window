// 라이브러리 및 헤더 포함
#include "Wire.h"
#include <LCD_I2C.h>
#include <SoftwareSerial.h>
#include <String.h>
#include "PMS.h"

const int rxPin = 10;
const int txPin = 11;
SoftwareSerial co_serial(rxPin, txPin); // 일산화탄소 센서, 디지털 10번, 11번을 시리얼 핀으로 사용
SoftwareSerial pms_serial(12,13); // // 미세먼지 센서, 디지털 12번, 13번을 시리얼 핀으로 사용
PMS pms(pms_serial);
PMS::DATA data;

LCD_I2C lcd(0x27, 20, 4); // LCD주소는 0x27 또는 0x3F이며 현재 사용하는 lcd 센서는 0x27

int rail_move = 33; // 리니어레일 이동, 디지털 33번 핀
int open_or_close = 35; // 리니어레일 방향전환, 디지털 35번 핀

// 리니어레일 방향 전환 변수
int open = HIGH;
int close = LOW;


// 창문 상태에 사용되는 변수(state)
// on은 열림, off는 닫힘 상태를 표현
// 초기 state 값은 0으로 초기화
bool on = true;
bool off = false;
bool state = false;
bool val = false;
int piezo = 31; // 피에조 센서, 디지털 31번핀
int numTones = 8;
int tones[] = {3136, 3520, 3951, 4186, 4698};
int water_pin = 0;

// lcd 모니터
void lcd_main(int &pm10, int &water) {

  // 1번째 줄
  lcd.setCursor(0, 0);
  lcd.print("Pred PM10 : ");

  // 2번째 줄
  lcd.setCursor(0, 1);
  lcd.print("PM10 : ");
  lcd.print(pm10); // 현재 미세먼지 출력
  lcd.print("ppm   "); // 미세먼지의 단위 표시

  // 3번째 줄
  // 빗물감지센서의 수치에 따라 LCD에 Rainy 또는 Not Rainy 출력
  lcd.setCursor(0, 2); // 3번째 줄
  lcd.print("Rain : "); // 
  if (water > 150) {
    lcd.print("Rainy    ");
  }
  else {
    lcd.print("Not Rainy");
  }
}

// 창문이 열릴때 lcd 출력값 변경
void open_Window() {
  lcd.setCursor(0, 3); // 4번째 줄
  lcd.print("Window : Opened ");
}

// 창문이 닫힐때 lcd 출력값 변경
void close_Window() {
  lcd.setCursor(0, 3); // 4번째 줄
  lcd.print("Window : Closed");
}


// 창문이 열리는 함수
void opening_Window() {
  lcd.setCursor(0, 0);
  lcd.print("Window Opening...   ");
  digitalWrite(open_or_close, open);
  for (int x = 0; x < 11000; x++) {
    digitalWrite(rail_move, HIGH);
    delayMicroseconds(100);
    digitalWrite(rail_move, LOW);
    delayMicroseconds(100);
  }
  lcd.clear();
}

// 창문이 닫히는 함수
void closing_Window() {
  lcd.setCursor(0, 0);
  lcd.print("Window Closing...   ");
  digitalWrite(open_or_close, close);
  for (int x = 0; x < 11000; x++) {
    digitalWrite(rail_move, HIGH);
    delayMicroseconds(100);
    digitalWrite(rail_move, LOW);
    delayMicroseconds(100);
  }
  lcd.clear();
}

void piezo_sound() {
  delay(250);
  tone(piezo, tones[0]);    delay(250);
  tone(piezo, tones[1]);    delay(250);
  tone(piezo, tones[2]);    delay(750);
  tone(piezo, tones[3]);    delay(250);
  noTone(piezo);    delay(10);
  tone(piezo, tones[3]);    delay(500);
  tone(piezo, tones[4]);    delay(500);
  noTone(piezo);    delay(10);
  tone(piezo, tones[4]);    delay(1000);
  tone(piezo, tones[2]);    delay(500);
  tone(piezo, tones[4]);    delay(500);
  tone(piezo, tones[3]);    delay(750);
  tone(piezo, tones[2]);    delay(250);
  tone(piezo, tones[3]);    delay(500);
  tone(piezo, tones[1]);    delay(500);
  tone(piezo, tones[2]);    delay(1250);
  noTone(piezo);
}

void setup() {
  pms_serial.begin(9600);
  Serial1.begin(1200);
  Serial.begin(9600);
  co_serial.begin(9600);//AGSM sensor module connection
  delay(1000);

  co_serial.write('c');
  co_serial.write('\r');

  // 각 센서들 초기화
  pinMode(rail_move, OUTPUT);
  pinMode(open_or_close, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(water_pin, INPUT);
  pinMode(2, INPUT);
  lcd.begin();
  lcd.backlight();

  // LCD 출력
  lcd.setCursor(0, 0); // 1번째 줄
  lcd.print("Loading..");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.print(".");
  delay(1000);
  lcd.clear();
  lcd.print("Welcome!");
  delay(2000);

  // LCD 다시 출력
  lcd.clear();

  // 1번째 줄 : 예측된 미세먼지 값 출력
  lcd.setCursor(0, 0);
  lcd.print("Welcome!");

  // 2번째 줄 : 현재 미세먼지 출력
  lcd.setCursor(0, 1);
  lcd.print("PM10 : ");

  // 3번째 줄 : 비의 여부 출력
  lcd.setCursor(0, 2);
  lcd.print("Rain : ");
  
  // 4번째 줄 : 창문의 개폐여부 출력
  lcd.setCursor(0, 3);
  lcd.print("Window : ");
}

void loop() {
  //Serial1.begin(9600);
  //Serial.begin(9600);
  // 센서값 로드
  pms_serial.listen();
  while (pms_serial.available()) {
    while (pms.read(data)) {
      int water = analogRead(water_pin);
      int pm10 = data.PM_AE_UG_10_0;
      int pm25 = data.PM_AE_UG_2_5;
      Serial.print("PM10.0 (ug/m3) : ");
      Serial.println(pm10);
      Serial.print("PM2.5 (ug/m3) : ");
      Serial.println(pm25);

      delay(1000);
      co_serial.listen();
      co_serial.write('\r');
      delay(1000);
      while (co_serial.available()) {
        // inByte에는 일산화탄소 뿐만이 아닌 온도, 습도, 센서 시리얼번호 등 여러 정보가 한꺼번에 출력
        // 일산화탄소만 출력하도록 변환
        String inByte = co_serial.readString();
        int index = inByte.indexOf(',',14);
        String coString = inByte.substring(14,index);

        float co = coString.toFloat();
        co/=1000;
        // 미세먼지, 초미세먼지, 일산화탄소 센서값 출력
        Serial.print("CO : ");
        Serial.println(co, 1);

        // 센서값 전송
        Serial1.print((String)pm10);
        delay(50);
        Serial1.print('a');
        delay(50);
        Serial1.print((String)pm25);
        delay(50);
        Serial1.print('b');
        delay(50);
        Serial1.print((String)co);
        delay(50);
      }
  
    delay(1000);

    // LCD 전환
    lcd_main(pm10, water);
    // 창문 제어

    // 추론 한 예측값과 비의 유무를 판단해 창문을 개폐하고 LCD에 상태 반영
    // 추론이 진행되지않아 예측값이 나오지 않을 경우, 비의 유무만 판단
    // 빗물감지센서의 값이 150 미만일때 창문 열기
      // 150 이상일 경우에는 창문 닫기
      
    if (water < 150  && val == true && state == false) {
        piezo_sound();
        opening_Window();
        lcd_main(pm10, water);
        open_Window();
        state = true;
    }
    else if (water < 150  && val == false && state == true)
    {
        piezo_sound();
        closing_Window();
        lcd_main(pm10, water);
        close_Window();
        state = false;
      }
    else if (water > 150  && val == false && state == true)
    {
        piezo_sound();
        closing_Window();
        lcd_main(pm10, water);
        close_Window();
        state = false;
      }
    else if (water > 150  && val == true && state == true)
    {
        piezo_sound();
        closing_Window();
        lcd_main(pm10, water);
        close_Window();
        state = false;
      }
      
    }
//          piezo_sound();
//          closing_Window();
//          lcd_main(pm10, water);
//          close_Window();
//          state = off;
    // Serial1 포트에 데이터가 수신되는 값이 존재 할 때
    while (Serial1.available() > 0) {
    
      // 나노 보드에서 추론한 미세먼지 예측값 수신
      float read_invoke = Serial1.parseFloat();
      //Serial.println(read_invoke);

//      // LCD에 예측된 미세먼지 값 출력
//      lcd.setCursor(0,0);
//      lcd.print("Pred PM10 : ");
//      lcd.print(read_invoke);

      // 미세먼지 상태와 비의 유무를 판단해 창문을 개폐하고 LCD에 상태 반영
      // 미세먼지 나쁨의 수치는 81 미만이고, 빗물감지 센서로 인해 창문의 상태가 열린 상태일 경우 창문 열기 상태 유지
      // 나머지 상태일 때는 창문 닫기
      if (read_invoke < 81 ) {
          val = true;
          // LCD에 예측된 미세먼지 값 출력
          lcd.setCursor(0,0);
          lcd.print("Pred PM10 : ");
          lcd.print("LOW   ");
        }
      else {
          val = false;
          // LCD에 예측된 미세먼지 값 출력
          lcd.setCursor(0,0);
          lcd.print("Pred PM10 : ");
          lcd.print("HIGH   ");
          }
        }
      }

       
  delay(1000);
}
