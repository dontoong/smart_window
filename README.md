# 환영합니다
2022 대학생 캡스톤디자인 경진대회에 참여하였습니다.<br/><br/>
프로젝트명 : 미세먼지 예측을 통한 자동 개폐 창문 제작<br/><br/>
팀명 : 베덕단<br/><br/>
팀장 : 김명근 / 팀원 : 신창건, 임정수, 정다진<br/><br/>
개발 기간 : 2022.03 ~ 2022.12<br/><br/>
프로젝트 중 팀 총괄, 센서 회로 설계 및 [하드웨어 개발 부분](https://github.com/dontoong/smart_window#하드웨어-개발김명근팀장-정다진-개발)을 담당하였습니다.<br/><br/>
[소프트웨어 개발 보러 가기](https://github.com/dontoong/smart_window#소프트웨어-개발임정수-신창건-개발)<br/><br/>
[하드웨어 개발 보러 가기](https://github.com/dontoong/smart_window#하드웨어-개발김명근팀장-정다진-개발)<br/><br/>

# 서론
## 미세먼지의 위험성
- 미세먼지에 대한 노출은 심장 및 폐 관련 질환 등을 발생시킴.
- 단기적으로는 천식 발작, 급성 기관지염, 부정맥과 같은 증상을 악화시키고 미세먼지 농도가 높은 곳에서 오래 노출되는 경우 심혈관질환, 호흡기질환, 폐암 발생의 위험이 증가.
### 생길 수 있는 증상
- 기침과 같은 호흡기 점막 자극 증상, 폐 기능 감소 및 악화로 인한 호흡 곤란, 가슴 답답함, 쌕쌕거림, 천식 증상.
- 혈관기능장애로 인한 가슴 압박감, 가슴 통증, 가슴 두근거림, 호흡 곤란 등 심혈관계 증상.
- 가려움, 피부 알레르기, 아토피피부.
- 통증, 이물감, 가려움증을 동반하는 알레르기, 결막염과 안구건조증.
<br/>
![image](https://github.com/dontoong/smart_window/assets/106039761/902c6c02-d9a3-4e51-8407-0a68061d8619)
<br/><br/>

## 주제 선정
- 일반 가정 및 회사에서는 환기를 위해 주기적으로 창문을 개폐하는 것을 통해 환기를 시키는데, 미세먼지 농도가 높을 때 환기를 시키면 오히려 악영향을 끼치게 되는 문제점이 발생. 이와 같은 문제점을 해결하고자 함.<br/><br/>
- 단순히 현재의 미세먼지 농도를 측정하여 창문을 닫는 것뿐만 아니라, 인공지능 분야를 접목하여 1시간 뒤의 미세먼지 농도를 예측하여 그 수치에 따라 창문을 자동으로 개폐하여 높은 농도의 미세먼지 유입을 예방하는 작품을 만들고자 함.<br/><br/>

## TinyML이란?
![image](https://github.com/dontoong/smart_window/assets/106039761/64c11f61-ceaa-4303-a2b3-40061eee413f)

# 개발 구상
## 개발 목표
![image](https://github.com/dontoong/smart_window/assets/106039761/97814f2e-c6e2-4790-aa77-a45e3392d65a)

## 동작 구조 순서
![image](https://github.com/dontoong/smart_window/assets/106039761/5fdc010c-d862-4163-9871-6c5fe943a8fe)

# 소프트웨어 개발(임정수, 신창건 개발)
## 소프트웨어 개발 환경
![image](https://github.com/dontoong/smart_window/assets/106039761/d0802473-8b64-490f-a831-713bd086a038)

## 공공데이터 활용
![image](https://github.com/dontoong/smart_window/assets/106039761/9cd9d623-22b2-4671-928d-4fbefbbf9224)
<br/><br/>
![image](https://github.com/dontoong/smart_window/assets/106039761/7a9183b9-eb3e-4784-9e8a-1aa8a1401917)

<br/><br/>

## 상관분석
![image](https://github.com/dontoong/smart_window/assets/106039761/24b0a12e-1e66-4f6f-a7e0-2e5e223a9678)\
<br/><br/>

## 사용할 데이터 분류
![image](https://github.com/dontoong/smart_window/assets/106039761/2efa2613-f591-4b8c-8c64-219766180400)
<br/><br/>

## 결측치 제거(1)
![image](https://github.com/dontoong/smart_window/assets/106039761/b0635f7d-da1a-4417-bb62-a537c3ef0f4c)
<br/><br/>

## 이상치 제거
![image](https://github.com/dontoong/smart_window/assets/106039761/19628ec6-d7b2-46a7-afeb-170c06d90bb2)
<br/><br/>

## 결측치 제거(2)
![image](https://github.com/dontoong/smart_window/assets/106039761/a83fb3a2-1df5-4d1b-8b8e-40012078e004)
<br/><br/>

## 데이터 표준화
![image](https://github.com/dontoong/smart_window/assets/106039761/1791fe4f-9236-4a6c-b192-15f708c2a5df)
<br/><br/>

## 데이터 분할
![image](https://github.com/dontoong/smart_window/assets/106039761/b42f455a-61ec-4ab9-9d6d-3b7abb8f5912)
<br/><br/>

## 모델 학습
![image](https://github.com/dontoong/smart_window/assets/106039761/b5bf8200-b4bd-4179-829e-c97fdb38b9a1)
<br/><br/>
![image](https://github.com/dontoong/smart_window/assets/106039761/f10001a7-d329-47ec-b625-8bf66b66201a)
<br/><br/>

## 모델 평가
![image](https://github.com/dontoong/smart_window/assets/106039761/d9c931a8-9a91-45d8-bb52-9e143942123a)
<br/><br/>
![image](https://github.com/dontoong/smart_window/assets/106039761/e61f4057-3b70-4b9c-8e94-79f50eb42a22)
<br/><br/>

## 예측 모델
![image](https://github.com/dontoong/smart_window/assets/106039761/dffa9db8-7937-41d3-ad39-40b7c6d15212)
<br/><br/>

## 모델 양자화
![image](https://github.com/dontoong/smart_window/assets/106039761/04a4f368-55d1-4374-9c4f-d22b60c891a4)
<br/><br/>

## 모델 탑재
![image](https://github.com/dontoong/smart_window/assets/106039761/e5c60039-b5b6-42b4-b30f-ab46129bfc4a)
<br/><br/>

## 센서 입력값 수신
![image](https://github.com/dontoong/smart_window/assets/106039761/7d4da563-1404-4f75-a3a8-e3cb92957884)
<br/><br/>

## 보드간 UART 통신
![image](https://github.com/dontoong/smart_window/assets/106039761/2c6adcd7-7c1d-4a19-a1fc-8e45c5e69084)
<br/><br/>
![image](https://github.com/dontoong/smart_window/assets/106039761/8d33a1e9-87e8-4fbc-b621-e46acab17e74)
<br/><br/>

# 하드웨어 개발(김명근(팀장), 정다진 개발)
## 하드웨어 구성
![image](https://github.com/dontoong/smart_window/assets/106039761/ca249f9b-1312-47ce-ab6a-d7249a44926d)
<br/><br/>

## 하드웨어(아두이노 보드) 선택
![image](https://github.com/dontoong/smart_window/assets/106039761/7c53c91a-df78-440d-bcb3-88b03c42c513)
<br/><br/>

## 하드웨어 동작 구조
![image](https://github.com/dontoong/smart_window/assets/106039761/56281e2a-407b-46a4-b50b-828742a02693)
<br/><br/>

## 회로 설계
![image](https://github.com/dontoong/smart_window/assets/106039761/cf39f3a1-c764-4f05-86c3-2b476a89118a)
<br/><br/>

![image](https://github.com/dontoong/smart_window/assets/106039761/9d834117-e8b5-47c6-86b4-ece8d6a782df)
<br/><br/>

![image](https://github.com/dontoong/smart_window/assets/106039761/545841b8-7a1c-4324-af20-f7a96d8b15e0)
<br/><br/>

![image](https://github.com/dontoong/smart_window/assets/106039761/15a94d52-7c4e-496f-91f8-947ac62eca36)
<br/><br/>

![image](https://github.com/dontoong/smart_window/assets/106039761/4b678dde-729b-474a-a726-98635dd926a4)
<br/><br/>

![image](https://github.com/dontoong/smart_window/assets/106039761/2d1e8af3-ff91-4f46-bb71-2e3e2193ae19)
<br/><br/>

![image](https://github.com/dontoong/smart_window/assets/106039761/d7e3b3b3-ffec-49eb-b49e-50031f991006)
<br/><br/>

![image](https://github.com/dontoong/smart_window/assets/106039761/5bd34308-3cf2-40fd-b406-df4c12d2b0c8)
<br/><br/>

# 동작 방식 및 구조
## 실제 동작 방식
![image](https://github.com/dontoong/smart_window/assets/106039761/8bdc5255-078b-4dd3-9d9d-a1a1bc098b93)


