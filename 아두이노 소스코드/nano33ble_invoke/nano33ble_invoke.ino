// 라이브러리 모델 및 헤더 포함
#include "PM10_cnn_test.h"
#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>
#include <String.h>
#define NUM_HOURS 6

constexpr float pm10_mean  = 43.883407f;
constexpr float pm25_mean  = 23.474103f;
constexpr float co_mean = 0.465331f;
constexpr float pm10_std   = 30.883249f;
constexpr float pm25_std   = 16.988391f;
constexpr float co_std = 0.235374f;

// 입력 기능에 대한 순환 버퍼
float pm10_vals[NUM_HOURS] = {0.0f};
float pm25_vals[NUM_HOURS] = {0.0f};
float co_vals[NUM_HOURS] = {0.0f};
int cur_idx                = 0;
bool is_valid              = false;

// 마이크로컨트롤러 글로벌 변수를 위한 TensorFlow Lite
const tflite::Model* tflu_model            = nullptr;
tflite::MicroInterpreter* tflu_interpreter = nullptr;
TfLiteTensor* tflu_i_tensor                = nullptr;
TfLiteTensor* tflu_o_tensor                = nullptr;
tflite::MicroErrorReporter tflu_error;
tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;

// 메모리 할당
constexpr int tensor_arena_size = 9 * 1024;
byte tensor_arena[tensor_arena_size] __attribute__((aligned(16)));

// 받아올 센서값 초기화
float pm10 = 0.00f;
float pm25 = 0.00f;
float co = 0.00f;
float read_pm10 =0.00f; 
float read_pm25 =0.00f; 
float read_co =0.00f; 

// 텐서플로우 라이트 라이브러리 초기화 및 모델 업로드
void tflu_initialization() {
  // 모델 로드
  const tflite::Model* tflu_model = ::tflite::GetModel(PM10_cnn_test_tflite);
  if (tflu_model->version() != TFLITE_SCHEMA_VERSION) {
    while (1); 
    }

  // 작업 확인자 인스턴스화
  tflite::AllOpsResolver resolver;

  // 인터프리터 인스턴스화
  tflu_interpreter = new tflite::MicroInterpreter(tflu_model, resolver, tensor_arena, tensor_arena_size, &tflu_error);

  // 텐서 할당
  tflu_interpreter->AllocateTensors();

  // 입력 및 출력 텐서의 포인터를 가져옵니다.
  tflu_i_tensor = tflu_interpreter->input(0);
  tflu_o_tensor = tflu_interpreter->output(0);
  Serial.print("start");
}

void setup() {

  //시리얼 포트 초기화
  Serial.begin(9600);
  Serial1.begin(1200);
  tflu_initialization();
}

void loop() {
  // Serial1 포트에서 수신되는 값이 존재 할 때
  while (Serial1.available() > 0) {
    // 받은 값을 String 형으로 출력
    // 출력형태는 ('00a00b0.00')
    String sendata = Serial1.readString();

    // 미세먼지 값(PM10)은 a 앞까지, 초미세먼지 값(PM25)은 a 다음값부터 b 앞까지, 일산화탄소 값(CO)은 b 다음값부터 끝까지의 값으로 구분
    int index_a = sendata.indexOf('a');
    int index_b = sendata.indexOf('b');
    String pm10_String = sendata.substring(0,index_a);
    String pm25_String = sendata.substring(index_a+1,index_b);
    String co_String = sendata.substring(index_b+1);

    // 받아온 문자를 문자형 데이터 String형에서 Float 형태로 변환
    read_pm10 = pm10_String.toFloat();
    read_pm25 = pm25_String.toFloat();
    read_co = co_String.toFloat();

    // 임의로 지정한 테스트용 센서값
    // float read_pm10 = 20.00f;
    // float read_pm25 = 19.00f;
    // float read_co = 0.30f;

    // 변수 이름 변경
    pm10 = read_pm10;
    pm25 = read_pm25;
    co = read_co;

    // Z 점수 스케일링
    pm10 = (pm10 - pm10_mean) / pm10_std;
    pm25 = (pm25 - pm25_mean) / pm25_std;
    co = (co - co_mean) / co_std;

    // 배열에 넣기 위한 초기화
    pm10_vals[cur_idx] = pm10;
    pm25_vals[cur_idx] = pm25;
    co_vals[cur_idx] = co;
    
    // 최근 세 샘플에 대한 인덱스 가져오기
    // 6시간
    const int idx0 = cur_idx;
    const int idx1 = (cur_idx - 1 + NUM_HOURS) % NUM_HOURS;
    const int idx2 = (cur_idx - 2 + NUM_HOURS) % NUM_HOURS;
    const int idx3 = (cur_idx - 3 + NUM_HOURS) % NUM_HOURS;
    const int idx4 = (cur_idx - 4 + NUM_HOURS) % NUM_HOURS;
    const int idx5 = (cur_idx - 5 + NUM_HOURS) % NUM_HOURS;

    // 입력값(18)
    // 6시간의 미세먼  지, 초미세먼지, 일산화탄소 값

    // 미세먼지
    tflu_i_tensor->data.f[0] = pm10_vals[idx5];
    tflu_i_tensor->data.f[1] = pm10_vals[idx4];
    tflu_i_tensor->data.f[2] = pm10_vals[idx3];
    tflu_i_tensor->data.f[3] = pm10_vals[idx2];
    tflu_i_tensor->data.f[4] = pm10_vals[idx1];
    tflu_i_tensor->data.f[5] = pm10_vals[idx0];

    // 초미세먼지
    tflu_i_tensor->data.f[6] = pm25_vals[idx5];
    tflu_i_tensor->data.f[7] = pm25_vals[idx4];
    tflu_i_tensor->data.f[8] = pm25_vals[idx3];
    tflu_i_tensor->data.f[9] = pm25_vals[idx2];
    tflu_i_tensor->data.f[10] = pm25_vals[idx1];
    tflu_i_tensor->data.f[11] = pm25_vals[idx0];

    // 일산화탄소
    tflu_i_tensor->data.f[12] = co_vals[idx5];
    tflu_i_tensor->data.f[13] = co_vals[idx4];
    tflu_i_tensor->data.f[14] = co_vals[idx3];
    tflu_i_tensor->data.f[15] = co_vals[idx2];
    tflu_i_tensor->data.f[16] = co_vals[idx1];
    tflu_i_tensor->data.f[17] = co_vals[idx0];

    // 모델 추론
    TfLiteStatus invoke_status = tflu_interpreter->Invoke();
    if (invoke_status != kTfLiteOk) {
      return;
    }

    // 출력값
    float out_pm10 = tflu_o_tensor->data.f[0];
    
    // 항상 True
    is_valid = (is_valid || cur_idx == 5);


    if (is_valid) {
      Serial1.print(out_pm10);

      // 입력값에 사용되는 함수(24)
    }
      cur_idx = (cur_idx + 1) % NUM_HOURS;
  }

  // 테스트용 딜레이
      //delay(1000);

      // 1시간마다 측정하기 위해 딜레이 지정
      delay(3600000);
}
