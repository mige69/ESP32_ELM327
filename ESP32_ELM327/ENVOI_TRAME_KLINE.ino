
void envoi_trame_kline() {
  for (int x = 0; x <= length; x++) {  // messagelength=number of parameters stored in array
    K_LINE.write(buff_envoi[x]);
    Serial.print(buff_envoi[x], HEX);
  }


  K_LINE.flush();
  Serial.println("");

  if (K_LINE.available()) {
    while (K_LINE.available()) {
      K_LINE.read();
    }
  }


  delay(45);  //90 100 110

  byte inByte;
  byte i = 0;
  byte counter = 0;

  // memset(buff_recoit, 0, sizeof(buff_recoit));

  // byte incomingdata[] = {};
  if (K_LINE.available()) {  // reading data

    while (K_LINE.available() > 0) {

      inByte = K_LINE.read();

/*      
      if (!bool_format) {
        if (inByte == format || inByte == format_init) {
          i = 0;
          bool_format = true;
        }
      }
      if (bool_format) {
        Serial.println("bool_format");
        buff_recoit[i] = inByte;
        if (buff_recoit[i] < 16) Serial.print('0');
        Serial.print(buff_recoit[i], HEX);
        Serial.print(" ");
        i++;
      }
*/

      buff_recoit[i] = inByte;
      Serial.print(buff_recoit[i], HEX);
      i++;
    }
    Serial.println("");
    // Serial.print("i =");
    // Serial.println(i);

    if (bool_init_bus) {
      Serial.println("bool_init_bus");
      // counter = i - 2;
      // Serial.println(counter);
      byte lenght_trame = 0;
      //   byte trame = 0;
      /*
      if (buff_recoit[3] <= 1) {
        //  Serial.print("number = ");
        //  Serial.println(buff_recoit[3]);
      } else {

        if (buff_recoit[0] == format && buff_recoit[1] == ecuadrr && buff_recoit[2] == testaddr) {
         // Serial.print("format = ");
        //  Serial.println(format, HEX);
          // if (buff_recoit[1] == ecuadrr) {
         // Serial.print("ecuadrr = ");
         // Serial.println(ecuadrr, HEX);
          //  if (buff_recoit[2] == testaddr) {
         // Serial.print("testaddr = ");
         // Serial.println(testaddr, HEX);
          lenght_trame = buff_recoit[3];
         // Serial.print("lenght_trame = ");
        //  Serial.println(lenght_trame);
          counter = i - 1;
          checksum_result = buff_recoit[counter];
        //  Serial.print("checksum_result = ");
        //  Serial.println(checksum_result, HEX);
          counter = i - 5;
        //  Serial.print("counter = ");
        //  Serial.println(counter);
          if (lenght_trame == counter) {
            lenght_trame = i - 1;
            byte checksum = 0;
            for (byte x = 0; x < lenght_trame; x++) {
              checksum = checksum + buff_recoit[x];
            }
            checksum_ok = checksum % 256;

          //  Serial.print("checksum_ok = ");
          //  Serial.println(checksum_ok, HEX);
          //  Serial.print("checksum_result = ");
          //  Serial.println(checksum_result, HEX);
            if (checksum_ok == checksum_result) {
              if (bool_header_byte) {
                SerialBT.print(string_header);
                Serial.print(string_header);
                SerialBT.print(LR);
                Serial.print(LR);
              }
              counter = i - 2;

              for (byte d = 4; d <= counter; d++) {
                if (buff_recoit[d] < 16) SerialBT.print('0');
                Serial.print(buff_recoit[d], HEX);
                SerialBT.print(buff_recoit[d], HEX);
                SerialBT.print(" ");
              }

              SerialBT.print(PROMPT);
              Serial.println("");
            }
          }
        }
        // }
        //}
      }
*/

      if (buff_recoit[0] == format && buff_recoit[1] == ecuadrr && buff_recoit[2] == testaddr) {
        // String dataString = "";
        Serial.println("buff_recoit");
        if (buff_recoit[3] <= 1) {
          Serial.println(buff_recoit[3]);
        } else {
          counter = i - 2;
          Serial.print("i = ");
          Serial.println(i);
          Serial.print("counter = ");
          Serial.println(counter);
          //  Serial.print("buff_recoit = ");
          // if (bool_header_byte) {
          //   SerialBT.print(string_header);
          // SerialBT.print(LR);
          //  SerialBT.print(" ");
          // }
          for (byte d = 4; d <= counter; d++) {
            if (buff_recoit[d] < 16) SerialBT.print('0');
            Serial.print(buff_recoit[d], HEX);
            SerialBT.print(buff_recoit[d], HEX);
            SerialBT.print(" ");
          }

          SerialBT.print(PROMPT);
          Serial.println("");
        }
      }

      Buffer_zero();
      //bool_trame_ok = false;
    }

    // Serial.println("");
    //}

    //Serial.println("");
  }

  if (bool_start) {
    Serial.print("i =");
    Serial.println(i);
    //  Serial.println("");
    Serial.println("bus init =");
    //  Serial.println(buff_recoit[4], HEX);

    for (byte d = 0; d < i; d++) {

      //  Serial.print(buff_recoit[d], HEX);
      SerialBT.print(buff_recoit[d], HEX);
      SerialBT.print(" ");
    }
    SerialBT.print(LR);
    //SerialBT.print(OK);
    SerialBT.print(PROMPT);



    if (buff_recoit[4] == bus_init) {

      if (!bool_init_trame_keep_alive) {
        buff_alive_kline[0] = buff_recoit[0];
        format = buff_recoit[0];
        ecuadrr = buff_recoit[1];
        testaddr = buff_recoit[2];
        // Serial.print("format = ");
        // Serial.println(format, HEX);
        buff_alive_kline[2] = buff_recoit[1];
        //Serial.print("testaddr = ");
        //Serial.println(testaddr, HEX);
        buff_alive_kline[1] = buff_recoit[2];
        // Serial.print("ecuadrr = ");
        // Serial.println(ecuadrr, HEX);
        buff_alive_kline[3] = keep_alive_somme;  //format_init
        buff_alive_kline[4] = keep_alive;        //format_init

        length = 5;
        byte checksum = 0;
        String checksum_hex = "";
        for (byte x = 0; x < length; x++) {
          // Serial.print(hex[x], HEX);
          checksum = checksum + buff_alive_kline[x];
        }
        checksum_ok = checksum % 256;
        //  Serial.print("checksum_ok = ");
        //  Serial.println(checksum_ok, HEX);

        buff_alive_kline[length] = checksum_ok;
        bool_alive_kline = true;
      }



      //  for (byte x = 0; x <= length; x++) {
      //    Serial.print(buff_alive_kline[x], HEX);
      //  }
      //  Serial.println("");

      //  Serial.print("lenght = ");
      //  Serial.print(length);
      //  Serial.println("");

      bool_start = false;
      init_atfi = false;
      trame_kline = true;
      bool_init_bus = true;
      envoi_rep = "BUS INIT:";
      //SerialBT.print(envoi_rep);
      //SerialBT.print(OK);
      //SerialBT.print(PROMPT);  ////
      envoi_reponse();
    }
    Buffer_zero();
  }


  Serial.println("");
}
