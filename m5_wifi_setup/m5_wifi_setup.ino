//M5でWifi接続するために最初にこの設定プログラムを書き込む
#include <Preferences.h>
Preferences preferences;

void setup() {
  preferences.begin("AP-info", false);            // 名前空間"AP-info"の指定と書き込みモード（false)
  preferences.putString("ssid", "your ssid");     // ssidの値を指定
  preferences.putString("pass", "your pass"); // passwordの値を指定 
  preferences.end();                              // 処理の終了
}

void loop() {
  
}


