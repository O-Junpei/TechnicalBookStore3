
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

void getRequest(String id){
   // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    String url = directory;
    url += "?id=";
    url += id;

    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }
 }

