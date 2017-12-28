#include <WiFi.h>
#include <time.h>
#include <SD.h>
#include <RCS620S.h>

//Wifi関係
#define JST     3600* -9
const char* ssid = "Buffalo-G-ACB0";
const char* password = "pchhgjb6bu55e";
const char* host = "swiswiswift.sakura.ne.jp";
const char* directory = "/felica/notification.php";

//フェリカ関係
#define COMMAND_TIMEOUT 400
#define POLLING_INTERVAL 500
RCS620S rcs620s;

//ブザー関連
#define BUZZER_PIN 22      // ブザーを鳴らすためのピン
#define LEDC_CHANNEL 0      // チャンネル
#define LEDC_TIMER_BIT 14
#define LEDC_BASE_FREQ 5000


//SD関係
#define LOG_FILE_NAME "/log.txt"
#define SD_CS 5
static File s_myFile;

void setup() { 

  Serial.begin(115200);      // for RC-S620/S
  Serial.println("Initing");

  //wifi
  wifiConnect();

  // 音を鳴らす準備
  ledcSetup(LEDC_CHANNEL, LEDC_BASE_FREQ, LEDC_TIMER_BIT);
  ledcAttachPin(BUZZER_PIN, LEDC_CHANNEL);
  callZeldaSound();

  //SDの確認
  SD_init();

  //felica
  int ret;
  ret = rcs620s.initDevice();
  while (!ret) {
      ret = rcs620s.initDevice();
      Serial.println(" blooking ");
      delay(1000);
  }
}

void loop() {
  int ret, i;

  // Polling
  rcs620s.timeout = COMMAND_TIMEOUT;
  ret = rcs620s.polling();
  
  if(ret) {

    String felicaID = "";
    for(i = 0; i < 8; i++)
    {
      if(rcs620s.idm[i] / 0x10 == 0) felicaID += "0";
      //Serial.print(rcs620s.idm[i], HEX);
      felicaID += String(rcs620s.idm[i], HEX);
    }

    callZeldaSound();

    String date = String(getTimeString());

    SD_write(date, felicaID);
    Serial.println(date);
    Serial.println(felicaID);

    getRequest(felicaID);

    delay(5000);
    
  } else {
    Serial.println("Polling...");
    delay(100);
  }
 
  rcs620s.rfOff();
  delay(POLLING_INTERVAL);
}

