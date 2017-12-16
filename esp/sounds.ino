
//ゼルダの謎解き音
void callZeldaSound() {
  ledcWriteTone(LEDC_CHANNEL, 3136); // ソ
  delay(150);
  ledcWriteTone(LEDC_CHANNEL, 2960); // ♯ファ
  delay(150);
  ledcWriteTone(LEDC_CHANNEL, 2489); // ♯レ
  delay(150);
  ledcWriteTone(LEDC_CHANNEL, 1760); // ラ
  delay(150);
  ledcWriteTone(LEDC_CHANNEL, 1661); // ♯ソ
  delay(150);
  ledcWriteTone(LEDC_CHANNEL, 2637); // ミ
  delay(150);
  ledcWriteTone(LEDC_CHANNEL, 3322); // ♯ソ
  delay(150);
  ledcWriteTone(LEDC_CHANNEL, 4186); // ド
  delay(150);
  ledcWriteTone(LEDC_CHANNEL, 0);    // 音を止める
}

