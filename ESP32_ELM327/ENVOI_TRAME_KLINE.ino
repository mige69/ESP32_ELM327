
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

  if (K_LINE.available()) {  // reading data

    while (K_LINE.available() > 0) {
      inByte = K_LINE.read();
      buff_recoit[i] = inByte;
      i++;
    }


    if (bool_init_bus) {
     byte lenght_trame = 0;

      if (buff_recoit[0] == format && buff_recoit[1] == ecuadrr && buff_recoit[2] == testaddr) {
        if (buff_recoit[3] <= 1) {
        } else {
          counter = i - 2;
          for (byte d = 4; d <= counter; d++) {
            if (buff_recoit[d] < 16) SerialBT.print('0');
            SerialBT.print(buff_recoit[d], HEX);
            SerialBT.print(" ");
          }

          SerialBT.print(PROMPT);
        }
      }

      Buffer_zero();

    }

  }

  if (bool_start) {

    for (byte d = 0; d < i; d++) {
      SerialBT.print(buff_recoit[d], HEX);
      SerialBT.print(" ");
    }
    SerialBT.print(LR);
    SerialBT.print(PROMPT);



    if (buff_recoit[4] == bus_init) {

      if (!bool_init_trame_keep_alive) {
        buff_alive_kline[0] = buff_recoit[0];
        format = buff_recoit[0];
        ecuadrr = buff_recoit[1];
        testaddr = buff_recoit[2];
        buff_alive_kline[2] = buff_recoit[1];
        buff_alive_kline[1] = buff_recoit[2];
        buff_alive_kline[3] = keep_alive_somme;  //format_init
        buff_alive_kline[4] = keep_alive;        //format_init

        length = 5;
        byte checksum = 0;
        String checksum_hex = "";
        for (byte x = 0; x < length; x++) {
          checksum = checksum + buff_alive_kline[x];
        }
        checksum_ok = checksum % 256;
        buff_alive_kline[length] = checksum_ok;
        bool_alive_kline = true;
      }

      bool_start = false;
      init_atfi = false;
      trame_kline = true;
      bool_init_bus = true;
      envoi_rep = "BUS INIT:";

      envoi_reponse();
    }
    Buffer_zero();
  }

}
