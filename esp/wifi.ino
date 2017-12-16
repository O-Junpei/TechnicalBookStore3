
void wifiConnect(){
  Serial.print("wifi connect start");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.printf("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  configTime( JST, 0, "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
}

String getTimeString(){

  static const char *wd[7] = {"Sun","Mon","Tue","Wed","Thr","Fri","Sat"};
  struct tm *tm;

  int count = 0;
  //10秒試みてダメなら諦める。
  do {
    time_t t;
    t = time(NULL);
    tm = localtime(&t);

    if (tm->tm_year+1900>2015){
        Serial.println("2015以上");
        break;
    }else{
        Serial.println("2015以下");
    }   
    delay(1000);
    count++;
  } while(count < 10);

  if (count > 10){
    return "Error";  
  }

  return String(tm->tm_year+1900)+"/"+String(tm->tm_mon+1)+"/"+String(tm->tm_mon+1)+"/"+String(tm->tm_mday)+"("+wd[tm->tm_wday]+") "+String(tm->tm_hour)+":"+String(tm->tm_min)+":"+String(tm->tm_min);
}
