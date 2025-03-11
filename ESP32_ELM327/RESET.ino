void Reset_atws() {

  K_LINE.flush();
  if (K_LINE.available()) {
    while (K_LINE.available()) {
      K_LINE.read();
    }
  }
  K_LINE.end();

  init_atiia = false;
  init_fast = false;
  init_slow = false;
  init_atsh = false;
  init_atfi = false;
  bool_start = false;
  bool_alive_kline = false;
  trame_kline = false;
  bool_init_bus = false;
  bool_delay_fast_init_1B = false;
  bool_delay_fast_init_1A = false;
  bool_delay_fast_init_1A_ON = false;
  bool_delay_fast_init_1B_ON = false;
  bool_init_bike_honda = false;
  bool_bike_honda = false;
  bool_checksum_modulo_256 = true;
  bool_checksum_modulo_100 = false;
  bool_header_byte = true;
  delay_fast_init_1A_on = 0;
  delay_fast_init_1B_on = 0;
  delay_fast_init_1A = 25;
  delay_fast_init_1B = 25;
}