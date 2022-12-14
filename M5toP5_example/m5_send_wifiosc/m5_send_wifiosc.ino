//M5でWifi接続して通信するプログラム
//このプログラムの前にWifi_setup.inoを実行しておく
#include <ArduinoOSCWiFi.h>      //OSCライブラリ
#include <WiFi.h>                // Wifi制御用ライブラリ
#include <Preferences.h>         // 不揮発静メモリ制御ライブラリ
#include <M5StickC.h>            // M5StickC 用ライブラ
#define SEND_PORT 12000           // OSC で使うポート番号
#define SEND_IP "192.168.2.129"  // 受け取る側のIP

Preferences preferences;
char ssid[33];      // アクセスポイント情報（SSID）の格納用
char password[65];  // アクセスポイント情報（パスワード）の格納用
String myIP = "";
int pushCount;

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(9); //明るさ0~12
  M5.Lcd.setRotation(1); //0上，1左，2下，3右
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  //M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(1.5);
  Serial.begin(115200);
  delay(500);
  connectWifi();
}

void loop() {
  M5.update();

  //ボタンが押されtいるか
  int isPush = M5.BtnA.isPressed();
  OscWiFi.send(SEND_IP, SEND_PORT, "/button/push", isPush);
  
  //ボタンを押した回数カウント
  if (M5.BtnA.wasPressed()) {
    pushCount ++;
    OscWiFi.send(SEND_IP, SEND_PORT, "/button/count", pushCount);
  }

  //ボタンの状態を表示
  M5.Lcd.setCursor(5, 50);
  M5.Lcd.print("Push:");
  M5.Lcd.print(isPush);
  //押した回数の表示
  M5.Lcd.setCursor(5, 60);
  M5.Lcd.print("Count:");
  M5.Lcd.print(pushCount);

  delay(100);
}

void connectWifi() {
  // Wi-Fiアクセスポイント情報取得
  preferences.begin("AP-info", true);                         // 名前空間"AP-info"の指定と読み込みモード（true)
  preferences.getString("ssid", ssid, sizeof(ssid));          // ssidの値を指定
  preferences.getString("pass", password, sizeof(password));  // passwordの値を指定
  preferences.end();

  // Wi-Fi接続 We start by connecting to a WiFi network
  Serial.println();  // シリアルポート経由でPCのシリアルモニタに出力
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);  // Wi-Fi接続開始
  // Wi-Fi接続の状況を監視（WiFi.statusがWL_CONNECTEDになるまで繰り返し
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Wi-Fi接続結果をシリアルモニタへ出力
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  displayWifiInfo();
}


void displayWifiInfo() {
  //M5 DisplayにWiFi情報表示
  M5.Lcd.setCursor(5, 10);
  M5.Lcd.print("WiFi:");
  M5.Lcd.print(ssid);

  M5.Lcd.setCursor(5, 20);
  M5.Lcd.print("My IP:");
  M5.Lcd.print(WiFi.localIP());
  M5.Lcd.setCursor(5, 40);
  M5.Lcd.print("SEND IP:");
  M5.Lcd.print(SEND_IP);
}
