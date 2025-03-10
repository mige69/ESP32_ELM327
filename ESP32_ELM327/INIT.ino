
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

void INIT_BIKE_HONDA() {
  digitalWrite(TxKline, HIGH);
  delay(300);
  digitalWrite(TxKline, LOW);
  delay(70);
  digitalWrite(TxKline, HIGH);
  delay(120);
  BAUDERADE_SELECTION();
  //K_LINE.begin(10400, SERIAL_8N1, RxKline, TxKline);
}