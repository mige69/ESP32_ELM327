
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
}

void INIT_FAST() {
  digitalWrite(TxKline, HIGH);
  delay(300);
  digitalWrite(TxKline, LOW);
  delay(delay_fast_init_1A);
  digitalWrite(TxKline, HIGH);
  delay(delay_fast_init_1B);
  BAUDERADE_SELECTION();
}

void INIT_BIKE_HONDA() {
  digitalWrite(TxKline, HIGH);
  delay(300);
  digitalWrite(TxKline, LOW);
  delay(70);
  digitalWrite(TxKline, HIGH);
  delay(120);
  BAUDERADE_SELECTION();
}