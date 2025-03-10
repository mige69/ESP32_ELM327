

void AT_COMMANDS_INT(String command) {
  Serial.println(command);


  if (command.equals(ATZ)) {
    envoi_rep = VERSION;
    envoi_reponse();
    ESP.restart();
  }

  else if (command.equals(ATI)) {
    envoi_rep = VERSION;
    envoi_reponse();
  }

  else if (command.equals(ATWS)) {
    envoi_rep = VERSION;
    envoi_reponse();
    Reset_atws();
  }

  else if (command.startsWith(ATSW)) {
    String sub_ATSW = "";
    String sub_ATSW_keep = "  ";
    String sub_ATSW_keep_alive = "";
    String sub_ATSW_keep_alive_ms = " ms ";
    sub_ATSW = command;  //ATSWFF
    length = command.length();
    length = length - 2;
    sub = command.substring(length);  //FF
    value0x = value0x + sub;
    uint8_t bin = strtol(value0x.c_str(), NULL, 0);
    delay_keep_alive = 20 * bin;
    sub_ATSW.concat(sub_ATSW_keep);
    sub_ATSW_keep_alive = String(delay_keep_alive);
    sub_ATSW.concat(sub_ATSW_keep_alive);
    sub_ATSW.concat(sub_ATSW_keep_alive_ms);
    value0x = "0x";
    envoi_rep = sub_ATSW;
    envoi_reponse();
  }

  else if (command.startsWith(ATWM)) {
    String sub_atwm = "";
    length_atwm = 4;
    sub_atwm = command.substring(length_atwm);
    // Serial.print("sub_atwm =");
    // Serial.println(sub_atwm);
    length_atwm = sub_atwm.length();
    buff_keep_alive_kline[sub_atwm.length() + 1];
    sub_atwm.toCharArray(buff_keep_alive_kline, sub_atwm.length() + 1);
    // for (int i = 0; i < sub_atwm.length() + 1; i++) {
    //   Serial.print(buff_keep_alive_kline[i]);
    //}
    //Serial.println("");
    length_atwm = sub_atwm.length() + 1;
    length_atwm = length_atwm / 2;
    // Serial.print("length_atwm =");
    // Serial.println(length_atwm);
    bool_trame_keep_alive = true;
    bool_init_trame_keep_alive = true;
    hex[length_atwm];
    convert_string_hex(hex, buff_keep_alive_kline);
    envoi_rep = command;
    envoi_reponse();
  }


  else if (command.startsWith(ATH)) {
    int index_ath;
    index_ath = command.indexOf("0");
    if (index_ath > -1) {
      bool_header_byte = false;
      envoi_rep = command;
    }
    index_ath = command.indexOf("1");
    if (index_ath > -1) {
      bool_header_byte = true;
      envoi_rep = command;
    }

    envoi_reponse();
  }

  else if (command.equals(ATIB10)) {
    BAUDERADE = 10400;
    // Serial.print(BAUDERADE);
    envoi_rep = BAUDERADE;
    envoi_reponse();
  }

  else if (command.equals(ATIB96)) {
    BAUDERADE = 9600;
    envoi_rep = BAUDERADE;
    envoi_reponse();
  }

  else if (command.equals(ATIB48)) {
    BAUDERADE = 4800;
    envoi_rep = BAUDERADE;
    envoi_reponse();
  }

  else if (command.startsWith(ATMODU)) {
    int index_atmodu;
    index_atmodu = command.indexOf("256");
    if (index_atmodu > -1) {
      bool_checksum_modulo_256 = true;
      bool_checksum_modulo_100 = false;
      envoi_rep = command;
    }
    index_atmodu = command.indexOf("100");
    if (index_atmodu > -1) {
      bool_checksum_modulo_256 = false;
      bool_checksum_modulo_100 = true;
      envoi_rep = command;
    }

    envoi_reponse();
  }

  else if (command.equals(ATPPS)) {
    if (bool_delay_fast_init_1A) {
      sub_ATPPS = "1A ";
    } else {
      sub_ATPPS = "1A ";
    }
    if (bool_delay_fast_init_1A_ON) {
      sub_ATPPS_sub = "ON ";
      sub_ATPPS.concat(sub_ATPPS_sub);
      sub_ATPPS_sub = String(delay_fast_init_1A_on);
      sub_ATPPS.concat(sub_ATPPS_sub);
      sub_ATPPS_sub = " ms ";
      sub_ATPPS.concat(sub_ATPPS_sub);
    } else {
      sub_ATPPS_sub = "OFF ";
      sub_ATPPS.concat(sub_ATPPS_sub);
      sub_ATPPS_sub = String(delay_fast_init_1A);
      sub_ATPPS.concat(sub_ATPPS_sub);
      sub_ATPPS_sub = " ms ";
      sub_ATPPS.concat(sub_ATPPS_sub);
    }
    if (bool_delay_fast_init_1B) {
      sub_ATPPS_sub = "1B ";
      sub_ATPPS.concat(sub_ATPPS_sub);
    } else {
      sub_ATPPS_sub = "1B ";
      sub_ATPPS.concat(sub_ATPPS_sub);
    }
    if (bool_delay_fast_init_1B_ON) {
      sub_ATPPS_sub = "ON ";
      sub_ATPPS.concat(sub_ATPPS_sub);
      //sub_ATPPS_sub = "";
      sub_ATPPS_sub = String(delay_fast_init_1B_on);
      sub_ATPPS.concat(sub_ATPPS_sub);
      sub_ATPPS_sub = " ms ";
      sub_ATPPS.concat(sub_ATPPS_sub);
    } else {
      sub_ATPPS_sub = "OFF ";
      sub_ATPPS.concat(sub_ATPPS_sub);
      sub_ATPPS_sub = String(delay_fast_init_1B);
      sub_ATPPS.concat(sub_ATPPS_sub);
      sub_ATPPS_sub = " ms ";
      sub_ATPPS.concat(sub_ATPPS_sub);
    }
    envoi_rep = sub_ATPPS;
    envoi_reponse();
  }

  else if (command.equals(ATSP3)) {
    init_slow = true;
    BAUDERADE = 10400;
    envoi_rep = command;
    envoi_reponse();
  }

  else if (command.equals(ATSP4)) {
    init_slow = true;
    BAUDERADE = 10400;
    envoi_rep = command;
    envoi_reponse();
  }

  else if (command.equals(ATSP5)) {
    init_fast = true;
    BAUDERADE = 10400;
    Serial.print("init_fast");
    envoi_rep = command;
    envoi_reponse();
  }

  else if (command.equals(ATSPH)) {
    bool_init_bike_honda = true;
    bool_bike_honda = true;
    bool_checksum_modulo_256 = false;
    BAUDERADE = 10400;
    Serial.print("init_bike_honda");
    envoi_rep = command;
    envoi_reponse();
  }

  else if (command.startsWith(ATPP)) {

    index_atpp = command.indexOf("1AON");
    if (index_atpp > -1) {
      delay_fast_init_1A = delay_fast_init_1A_on;
      bool_delay_fast_init_1A_ON = true;
      envoi_rep = command;
      envoi_reponse();
    }
    index_atpp = command.indexOf("1BON");
    if (index_atpp > -1) {
      delay_fast_init_1B = delay_fast_init_1B_on;
      bool_delay_fast_init_1B_ON = true;
      envoi_rep = command;
      envoi_reponse();
    }
    index_atpp = command.indexOf("1AOFF");
    if (index_atpp > -1) {
      delay_fast_init_1A = 25;
      delay_fast_init_1A_on = 0;
      bool_delay_fast_init_1A_ON = false;
      envoi_rep = command;
      envoi_reponse();
    }
    index_atpp = command.indexOf("1BOFF");
    if (index_atpp > -1) {
      delay_fast_init_1B = 25;
      delay_fast_init_1B_on = 0;
      bool_delay_fast_init_1B_ON = false;
      envoi_rep = command;
      envoi_reponse();
    }
    index_atpp = command.indexOf("SV");
    // Serial.print("index SV =");
    // Serial.println(index_atpp);
    if (index_atpp > -1) {
      index_atpp = command.indexOf("1A");
      //   Serial.print("index 1A =");
      //  Serial.println(index_atpp);
      if (index_atpp > -1) {
        string_delay_fast_init = command.substring(8);
        //     Serial.print("index 1A string_delay_fast_init =");
        //     Serial.println(string_delay_fast_init);

        value0x = value0x + string_delay_fast_init;
        uint8_t bin = strtol(value0x.c_str(), NULL, 0);
        //     Serial.print("1A myInt =");
        //     Serial.println(bin);
        delay_fast_init_1A_on = 2.5 * bin;
        //     Serial.print("index 1A string_delay_fast_init =");
        //    Serial.println(delay_fast_init_1A_on);
        value0x = "0x";
        bool_delay_fast_init_1A = true;
        envoi_rep = command;
        envoi_reponse();
      }
      index_atpp = command.indexOf("1B");
      //  Serial.print("index 1B =");
      //  Serial.println(index_atpp);
      if (index_atpp > -1) {
        string_delay_fast_init = command.substring(8);
        //  Serial.print("index 1B string_delay_fast_init =");
        //  Serial.println(string_delay_fast_init);
        value0x = value0x + string_delay_fast_init;
        uint8_t bin = strtol(value0x.c_str(), NULL, 0);
        //  Serial.print("1B myInt =");
        //  Serial.println(bin);
        delay_fast_init_1B_on = 2.5 * bin;
        //  Serial.print("index 1B string_delay_fast_init =");
        //  Serial.println(delay_fast_init_1B_on);
        value0x = "0x";
        bool_delay_fast_init_1B = true;
        envoi_rep = command;
        envoi_reponse();
      }
    }
  }

  else if (command.startsWith(ATIIA)) {
    length = command.length();
    length = length - 2;
    sub = command.substring(length);
    value0x = value0x + sub;
    uint8_t bin = strtol(value0x.c_str(), NULL, 0);
    // Serial.println(bin, HEX);
    value0x = "0x";
    init_atiia = true;
    envoi_rep = command;
    envoi_reponse();
  }

  /*
  else if (command.startsWith(ATFI)) {
    // length = command.length();
    // length = length - 2;
    sub_ATFI = "81";
    // envoi_rep = command;
    command.concat(sub_ATFI);
    envoi_rep = command;
    envoi_reponse();
    // value0x = value0x + sub_ATFI;
    // uint8_t bin = strtol(value0x.c_str(), NULL, 0);
    // value0x = "0x";
    init_atfi = true;
  }
*/


  else if (command.startsWith(ATSH)) {
    length_atsh = 4;
    init_atsh = true;
    sub_atsh = command.substring(length_atsh);
    //    Serial.print("sub_atsh = ");
    //    Serial.println(sub_atsh);
    length_atsh = sub_atsh.length();
    buffer[sub_atsh.length() + 1];
    sub_atsh.toCharArray(buffer, sub_atsh.length() + 1);
    length_atsh = sub_atsh.length() + 1;
    length_atsh = length_atsh / 2;
    envoi_rep = command;
    envoi_reponse();

  } else if (init_atsh) {  ////////////////////
  if (command.startsWith(ATFI)) {
    command = "81";
  }
    envoi_rep = command;
    sub_atsh_numb = sub_atsh;
    sub_number = command;
   // Serial.print("command =");
    //Serial.println(sub_number);
    length_kline = sub_number.length();
    // Serial.print("length_kline =");
    // Serial.println(length_kline);
    if (length_kline > 2) {
      length_kline = length_kline / 2;
      if (bool_bike_honda) {
        length_kline = length_kline + 3;
      }
      sub_number_add.concat(length_kline);
     // Serial.print("length_kline > 2sub_number_add =");
     // Serial.println(sub_number_add);
      sub_atsh_numb.concat(sub_number_add);
     // Serial.print("sub_atsh_numb =");
     // Serial.println(sub_atsh_numb);
      sub_number_add = "0";
    } else if (bool_init_bus) {
      //if(init_atfi){
      //  sub_atsh_numb = sub_ATFI;
      //  init_atfi = false;
      //}
      if (length_kline <= 2) {
        length_kline = length_kline / 2;
        if (bool_bike_honda) {
          length_kline = length_kline + 3;
        }
        sub_number_add.concat(length_kline);
       // Serial.print("length_kline <= 2sub_number_add =");
       // Serial.println(sub_number_add);
        sub_atsh_numb.concat(sub_number_add);
        sub_number_add = "0";
      }
    } 


    //  else if (init_atfi) {
    //    sub_atsh_numb = sub_ATFI;
    // init_atfi = false;
    // }

    sub_concat = sub_atsh_numb;
   // Serial.print("sub_concat =");
   // Serial.println(sub_concat);

    sub_concat.concat(command);
   // Serial.print("sub_concat =");
   // Serial.println(sub_concat);


   // Serial.print("buffer =");
    length = sub_concat.length();

    buffer[sub_concat.length() + 1];
    sub_concat.toCharArray(buffer, sub_concat.length() + 1);
   // for (int i = 0; i < sub_concat.length() + 1; i++) {
    //  Serial.print(buffer[i]);
   // }

    // Serial.println("");

    length = sub_concat.length() + 1;
    length = length / 2;

    length_kline = length - 3;

    // Serial.print("length_kline = ");
    // Serial.print(length_kline);
    // Serial.println("");

    // if (length_kline > 1) {
    // length_kline_string = length_kline;
    // }

    hex[length];
    convert_string_hex(hex, buffer);

    if (init_fast) {
      Serial.println("init_fast");
      INIT_FAST();
      init_fast = false;
      bool_start = true;
    }
    if (init_slow) {
      Serial.println("init_fast");
      INIT_SLOW();
      init_slow = false;
      bool_start = true;
    }
    if (bool_init_bike_honda) {
      Serial.println("init_bike_honda");
      INIT_BIKE_HONDA();
      bool_init_bike_honda = false;
      //bool_start = true;
    }

    if (bool_header_byte) {
      // string_header = command;
      SerialBT.print(command);
      SerialBT.print(LR);
    }

    envoi_trame_kline();
    sub_atsh_numb = "";
    sub_concat = "";
  }
}

void convert_string_hex(byte hex[], char buffer[]) {
  for (size_t i = 0; buffer[i] and buffer[i + 1]; i += 2) {
    char slice[] = { 0, 0, 0 };
    strncpy(slice, buffer + i, 2);
    hex[i / 2] = strtol(slice, nullptr, 16);
  }
  check_sum();
}

void envoi_reponse() {
  SerialBT.print(envoi_rep);
  SerialBT.print(LR);
  SerialBT.print(OK);
  SerialBT.print(PROMPT);
}

void BAUDERADE_SELECTION() {
  K_LINE.begin(BAUDERADE, SERIAL_8N1, RxKline, TxKline);
}

/*
void INIT_SLOW() {
  digitalWrite(TxKline, LOW);
  delay(200);
  digitalWrite(TxKline, HIGH);
  delay(400);
  digitalWrite(TxKline, LOW);
  delay(400);
  digitalWrite(TxKline, HIGH);
  delay(400);
  digitalWrite(TxKline, LOW);
  delay(400);
  digitalWrite(TxKline, HIGH);
  delay(200);
  BAUDERADE_SELECTION();
  //K_LINE.begin(BAUDERADE, SERIAL_8N1, RxKline, TxKline);
}

void INIT_FAST() {
  digitalWrite(TxKline, HIGH);
  delay(300);
  digitalWrite(TxKline, LOW);
  delay(delay_fast_init_1A);
  digitalWrite(TxKline, HIGH);
  delay(delay_fast_init_1B);
  BAUDERADE_SELECTION();
  //K_LINE.begin(10400, SERIAL_8N1, RxKline, TxKline);
}
*/
void check_sum() {
  byte checksum = 0;
  String checksum_hex = "";
  int length_checksum = 0;

  if (bool_trame_keep_alive) {
    length_checksum = length_atwm;
  } else {
    length_checksum = length;
  }

  if (bool_checksum_modulo_256) {
    for (int x = 0; x < length_checksum; x++) {
      checksum = checksum + hex[x];
    }
    checksum_ok = checksum % 256;
    hex[length_checksum] = checksum_ok;
    //  for (byte x = 0; x <= length; x++) {
    //    buff_envoi[x] = hex[x];
    //   }
  }

  if (bool_bike_honda) {
    for (int x = 0; x < length_checksum; x++) {
      checksum -= hex[x];
    }
    hex[length_checksum] = checksum;
    //  for (byte x = 0; x <= length; x++) {
    //    buff_envoi[x] = hex[x];
    //  }
  }
  if (bool_trame_keep_alive) {
    //  Serial.print("bool_trame_keep_alive length_checksum = ");
    //  Serial.println(length_checksum);
    for (int x = 0; x <= length_checksum; x++) {
      buff_alive_kline_trame[x] = hex[x];
      // Serial.print(buff_alive_kline_trame[x], HEX);
    }
    bool_trame_keep_alive = false;
    // Serial.println("");
  } else {
    for (int x = 0; x <= length_checksum; x++) {
      buff_envoi[x] = hex[x];
     // Serial.print(buff_envoi[x], HEX);
    }
   // Serial.println("");
  }
}

// SerialBT.flush();
