// Telegram Bot
#include "CTBot.h"

// NodeMCU Library
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>

// Flashing Over Air
#include <ArduinoOTA.h>
// #include <ESP8266WiFiMulti.h>

#include "DeviceTimer.h"
#include "BEEP.h"
#include "secret_key.h"

// ESP8266WiFiMulti wifiMulti;

// Initialize BOT Telegram
CTBot fallenWaterBot ;

// a variable to store telegram message data
TBMessage msg;
//TBLocation loc;

DeviceTimer LAMPU_TERAS;
DeviceTimer LAMPU_LORONG;
DeviceTimer ALARM;
bool lampuLorongState = false;
bool lampuTerasState = false;
bool lampuKamarState = false;
bool kipasACState = false;
bool alarmState = false;
bool komputerState = false;
bool stopKontakBawahState = false;

BEEP BUZZER;
BEEP alarm;

//Static IP address configuration
// IPAddress staticIP(192, 168, 1, 37); //ESP static ip
// IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
// IPAddress subnet(255, 255, 255, 0);  //Subnet mask
// IPAddress dns(8, 8, 8, 8);  //DNS

const char* deviceName = "My SmartHome";

String ssid  = "kaa.noy"; 
String pass  = "Paviliong4";

// String ssid  = "punya.ayah"; 
// String pass  = "123punya456ayah";

// Register multi WiFi networks
// wifiMulti.addAP("kaa.noy", "Paviliong4");
// wifiMulti.addAP("kaa.noy1", "Paviliong4");
String token = TELEGRAM_BOT_API;
                       
#define RELAY_1 D0  // StopKontak Meja Komputer
#define RELAY_2 D1  // Kipas atau AC
#define RELAY_3 D2  // StopKontak Bawah / Dekat Kasur
#define RELAY_4 D3  // Alarm
#define RELAY_5 D4  // StopKontak LED Atap
#define RELAY_6 D5  // Lampu Kamar Ghaniy
#define RELAY_7 D6  // Lampu Teras Atas dan Bawah
#define RELAY_8 D7  // Lampu Lorong Lantai 2
#define BUZZER_PIN D8
