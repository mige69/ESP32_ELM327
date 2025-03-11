// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESP2SOTA.h>

#include "BluetoothSerial.h"
#include <Streaming.h>


const char* ssid = "ESP32_ELM327_OTA";
const char* password = "123456789abc";
WebServer server(80);

#define K_LINE Serial2
#define RxKline 16
#define TxKline 17

uint16_t BAUDERADE = 48000;

const unsigned long TIME_INTERVAL_KLINE = 135;
unsigned long previousMillis;
unsigned long previousMillisKline;
unsigned long previousMillisupdate;

byte const startinit[5] = { 0x81, 0x12, 0xF1, 0x81, 0x05 };

byte monitorsensordata[7] = { 0x80, 0x12, 0xF1, 0x02, 0x21, 0x08, 0xAE };

const byte buffSize = 128;  //255
char lineOne[buffSize];
int line1count;

char buffer[] = {};
char buffer_hex[] = {};
char buff_keep_alive_kline[] = {};

byte hex[] = {};
byte hex_recoit[] = {};
byte buff_envoi[] = {};
byte buff_recoit[133] = {};
byte buff_envoi_BT[] = {};
byte buff_alive_kline[6] = {};
byte buff_alive_kline_trame[] = {};


byte count = 0;
byte checksum_ok = 0;

byte format = 0x80;
byte format_init = 0x81;
byte ecuadrr = 0x12;
byte testaddr = 0xF1;
byte bus_init = 0xC1;
byte checksum_result = 0;
byte result = 0;
byte rec_hex = 0;
byte keep_alive = 0x3E;
byte keep_alive_somme = 0x01;

bool monitor = false;
String sub_hex = "";
bool check = false;
bool format_ok = false;
bool testformat_ok = false;
bool ecuadrr_ok = false;
bool envoi_ok = false;
bool recoit_ok = false;
bool testaddr_ok = false;
bool bool_alive_kline = false;
bool bool_alive_kline_ok = false;
bool init_fast = false;
bool init_slow = false;
bool bool_init_bike_honda = false;
bool init_atiia = false;
bool init_atsh = false;
bool init_atfi = false;
bool trame_kline = false;
bool mode_kline = false;
bool bool_start = false;
bool bool_init_bus = false;
bool bool_delay_fast_init_1A = false;
bool bool_delay_fast_init_1B = false;
bool bool_delay_fast_init_1A_ON = false;
bool bool_delay_fast_init_1B_ON = false;
bool bool_checksum_modulo_256 = true;
bool bool_checksum_modulo_100 = false;
bool bool_bike_honda = false;
bool bool_header_byte = true;
bool bool_trame_ok = false;
bool bool_trame_keep_alive = false;
bool bool_init_trame_keep_alive = false;
bool bool_stop_wifi = false;
bool bool_format = false;




String device_name = "ESP32_ELM327";


// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;



const String VERSION = "ESP32_ELM327";

String value0x = "0x";

String INTERPRETATION;
String at_command = "";


const String AT = "AT";    // Echo off/on
const String ATE = "ATE";  // Echo off/on
const String ATI = "ATI";  // Version id
const String ATZ = "ATZ";  // Reset harware
const String ATS = "ATS";  // Set protocol X
const String ATH = "ATH";  // Headers off / on
const String ATL = "ATL";  // Linefeeds off/on
const String ATM = "ATM";  // Memory off/on
const String ATDPN = "ATDPN";
const String ATDESC = "AT@1";
const String ATAT = "ATAT";

const String ATIIA = "ATIIA";    // INIT Adress
const String ATIB10 = "ATIB10";  // BAUDE 10400
const String ATIB48 = "ATIB48";  // BAUDE 4800
const String ATIB96 = "ATIB96";  // BAUDE 9600
const String ATSH = "ATSH";      // EN TETE
const String ATSP = "ATSP";      // PROTOCOLE
const String ATW = "ATW";
const String ATWS = "ATWS";  // reset logiciel
const String ATSP3 = "ATSP3";
const String ATSP4 = "ATSP4";
const String ATSP5 = "ATSP5";
const String ATSPH = "ATSPH";
const String ATPP = "ATPP";
const String ATPPS = "ATPPS";
const String ATMODU = "ATMODU";
const String ATFI = "ATFI";
const String ATSW = "ATSW";  //time keep alive
const String ATWM = "ATWM";  //trame keep alive
const String PROMPT = ">";
const String LF = "\n";
const String LR = "\r";  // REPEAT LAST COMMAND
//const String OK = "OK";


String sub_ATPPS = "";
String sub_ATPPS_sub = "";
String sub_ATPPS_1A = "";
String sub_ATPPS_1B = "";
String sub = "";
String sub_atsh = "";
String sub_atsh_numb = "";
String sub_concat = "";
String envoi_rep = "";
String sub_number = "";
String sub_number_add = "0";
String string_delay_fast_init = "";
String string_header = "";
String sub_ATFI = "";

int length_atsh;
int length;
int length_alive_kline;
int length_kline;
int length_BT;
int delay_fast_init_1A = 25;
int delay_fast_init_1B = 25;
int delay_fast_init_1A_on = 0;
int delay_fast_init_1B_on = 0;
int length_atwm;
int index_atpp;

unsigned long delay_keep_alive = 3000;


int mode = 0;

void setup() {
 // Serial.begin(115200);


  pinMode(TxKline, OUTPUT);


  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  delay(1000);
  IPAddress IP = IPAddress(10, 10, 10, 1);
  IPAddress NMask = IPAddress(255, 255, 255, 0);
  WiFi.softAPConfig(IP, IP, NMask);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  SerialBT.begin(device_name);  //Bluetooth device name
  
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());

  /* SETUP YOR WEB OWN ENTRY POINTS */
  server.on("/myurl", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "Hello there!");
  });

  server.on("/", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/html", "<head><meta http-equiv=\"refresh\" content=\"1;URL=/update\" /></head>");
  });




  /* INITIALIZE ESP2SOTA LIBRARY */
  ESP2SOTA.begin(&server);
  server.begin();

  previousMillis = millis();
  previousMillisKline = millis();
  previousMillisupdate = millis();
}

void loop() {

  if (!bool_stop_wifi) {
    if (millis() - previousMillisupdate >= 600000) {
      WiFi.mode(WIFI_OFF);
      Serial.println("WIFI_OFF");
      bool_stop_wifi = true;
    }
  }

  /* HANDLE UPDATE REQUESTS */
  server.handleClient();

  if (SerialBT.available()) {
    char c = SerialBT.read();
    if ((c == '\n' || c == '\r') && at_command.length() > 0) {
      at_command.toUpperCase();
      AT_COMMANDS_INT(at_command);
      at_command = "";
    } else if (c != ' ' && c != '\n' && c != '\r') {
      at_command += c;
    }
  }

  if (millis() - previousMillis >= delay_keep_alive) {
    previousMillis = millis();
    if (bool_init_bus) {
      if (bool_init_trame_keep_alive) {
        Serial.print("length_atwm = ");
        Serial.println(length_atwm);
        for (int x = 0; x <= length_atwm; x++) {
          buff_envoi[x] = buff_alive_kline_trame[x];
          length = length_atwm;
        }
        bool_alive_kline = false;
        Serial.println("");
      }
      if (bool_alive_kline) {
        length = 5;
        for (int x = 0; x <= length; x++) {
          buff_envoi[x] = buff_alive_kline[x];
        }
        bool_alive_kline_ok = true;
        bool_init_trame_keep_alive = false;
      }
      envoi_trame_kline();
    }
  }
}
