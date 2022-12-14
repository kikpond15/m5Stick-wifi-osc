//M5でWifi接続して通信するプログラム
//このプログラムの前にWifi_setup.inoを実行しておく
#include <ArduinoOSCWiFi.h>  //OSCライブラリ
#include <WiFi.h>            // Wifi制御用ライブラリ
#include <Preferences.h>     // 不揮発静メモリ制御ライブラリ
#include <M5StickC.h>        // M5StickC 用ライブラ
#define PORT 12000           // OSC で使うポート番号

Preferences preferences;
char ssid[33];      // アクセスポイント情報（SSID）の格納用
char password[65];  // アクセスポイント情報（パスワード）の格納用
String remoteIP = "";
int r, b, g;
uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
  return ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
}

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(9);  //明るさ0~12
  M5.Lcd.setRotation(1);   //0上，1左，2下，3右
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1.5);
  Serial.begin(115200);
  delay(500);
  connectWifi();
}

void loop() {
  OscWiFi.update();
  OscWiFi.subscribe(PORT, "/color", [&](int _r, int _g, int _b) {
    r = _r;
    g = _g;
    b = _b;
    M5.Lcd.fillScreen(getColor(_r, _g, _b));
  });


  M5.Lcd.setTextColor(getColor(255-r, 255-g, 255-b));
  displayWifiInfo();
  M5.Lcd.setCursor(5, 40);
  M5.Lcd.print("Remote IP:");
  M5.Lcd.print(remoteIP);
  M5.Lcd.setCursor(5, 50);
  M5.Lcd.print("color:");
  M5.Lcd.print(r);
  M5.Lcd.print(',');
  M5.Lcd.print(g);
  M5.Lcd.print(',');
  M5.Lcd.print(b);
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
}
