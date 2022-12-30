#include "main.h"

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  P.begin();
}

void loop() {

  if (digitalRead(2) == LOW && message_sent == 0){
    while (Serial.available() > 0){
      Serial.readStringUntil('\n');
    }
    Serial.println("StartApiProcedure");
    message_sent = 1;
  }

  if(Serial.available() > 0 && message_red == 0) {
    String line_content = Serial.readStringUntil('\n');

    if (line_content.startsWith("Ack. StartApiProcedure")){
      content = "";
    for(int i = 0; i<20; i++){
      String data_ack;
      String data;
      bool acknowledge = 0;
      // data verification
      int char_len = 0;
      while (char_len<12)
      {
        while (!Serial.available()){}
        char one_char = Serial.read();
        data_ack += one_char;
        char_len++;

        String check_message = "Object" + (String)(i + 1) + "Send";
        if(data_ack.startsWith(check_message)){
          data_ack = "";
          acknowledge = 1;
          break;
      }
      }
      delay(2);
      if(Serial.available())
        Serial.readStringUntil('\n');
        
      if(acknowledge==0){
        content = "something went wrong";
        break;
      }

      // data
      char_len = 0;
      while (char_len<50)
      {
        while (!Serial.available()){}
        char one_char = Serial.read();
        if(one_char == "|"[0])
          break;
        data += one_char;
        char_len++;
      }
      delay(2);
      if(Serial.available())
        Serial.readStringUntil('\n');
      content = content + data + '\n';
      Serial.println("Ack");
    }
    Serial.println("To jest content");
    Serial.println(content);
    P.print(content);
    }
  }

  if (digitalRead(3) == LOW && serial_written == 0){
    Serial.println("Done.");
    Serial.println(content);
    serial_written = 1;
  }
}