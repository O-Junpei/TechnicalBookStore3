void SD_init()
{
    Serial.print("Initializing SD card...");

    if (!SD.begin(SD_CS)) {
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("initialization done.");        
}

String SD_read() {

    String str;

    File file = SD.open(LOG_FILE_NAME, FILE_READ);

    if(file){
        //---1byteずつ読み込んだ文字を結合
        while (file.available()) {
            str += char(file.read());
        }
    } else{
        Serial.println(" error...");
    }
    file.close();
    return str;
}

void SD_write(String date, String id)
{
    String backLog = SD_read();
    String newLog = date + "," + id;

    s_myFile = SD.open(LOG_FILE_NAME, FILE_WRITE);
    if (s_myFile) {
        Serial.print("Writing to test.txt...");
        s_myFile.print(backLog);
        s_myFile.println(newLog);
        s_myFile.close();
        Serial.println("done.");
    } else {
        Serial.println("error opening test.txt");
    }
}
