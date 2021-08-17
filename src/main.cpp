#include <Arduino.h>
#include "DefinedNecessaries.h"
#include "FlashingViaOTA.h"

void setup() {
    // initialize the Serial
    Serial.begin(115200);
    Serial.println("Starting TelegramBot...");

    // connect the ESP8266 to the desired access point
    // WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
    // WiFi.config(staticIP, subnet, gateway, dns);
    WiFi.begin(ssid, pass);

    //WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
  
    // Wait for connection
    while ( WiFi.status() != WL_CONNECTED ) {
        delay( 500 );
        Serial.print(".");
    }

    // USING wifiMulti
    // if (wifiMulti.run(5000) == WL_CONNECTED) {
    //     Serial.print("Wifi Connected");        
    // } else {
    //     Serial.print("Wifi Not Connected");
    //     ESP.restart();
    // }
    
    

    // set the pin connected to the LED to act as output pin
    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);
    pinMode(RELAY_3, OUTPUT);
    pinMode(RELAY_4, OUTPUT);
    pinMode(RELAY_5, OUTPUT);
    pinMode(RELAY_6, OUTPUT);
    pinMode(RELAY_7, OUTPUT);
    pinMode(RELAY_8, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    digitalWrite(RELAY_1, HIGH); // turn off the led (inverted logic!)
    digitalWrite(RELAY_2, HIGH); // turn off the led (inverted logic!)
    digitalWrite(RELAY_3, HIGH); // turn off the led (inverted logic!)
    digitalWrite(RELAY_4, HIGH); // turn off the led (inverted logic!)
    digitalWrite(RELAY_5, HIGH); // turn off the led (inverted logic!)
    digitalWrite(RELAY_6, HIGH); // turn off the led (inverted logic!)
    digitalWrite(RELAY_7, HIGH); // turn off the led (inverted logic!)
    digitalWrite(RELAY_8, HIGH); // turn off the led (inverted logic!)

    // set the telegram bot token
    fallenWaterBot.setTelegramToken(token);
    fallenWaterBot.useDNS(true);

    // check if all things are ok
    if (fallenWaterBot.testConnection()) {
        Serial.println("\ntest Connection OK\n");
    }
    else {
        Serial.println("\ntest Connection Failed\n");
        ESP.restart();
    }

    FlashingViaOTA();
    timeClient.begin();

    LAMPU_TERAS.setTimeOn(18, 15); // (Jam, Menit)
    LAMPU_TERAS.setTimeOff(5, 30);

    LAMPU_LORONG.setTimeOn(17, 40);
    LAMPU_LORONG.setTimeOff(6, 0);

    // ALARM.setTimeOn(5, 0);

    BUZZER.setBeepPin(BUZZER_PIN);
    // alarm.setBeepPin(RELAY_4);
}

void loop() {

    ArduinoOTA.handle();
    timeClient.update();

    if (fullDate.getYear() == 1970) {
        Serial.println("Tanggal dan Waktu salah, koneksi ke Server NTP terputus...");
        Serial.println("Merestart ulang\n");
        delay(100);
        ESP.restart();
    }

    if (timeClient.getHours() == LAMPU_TERAS.onHour && timeClient.getMinutes() == LAMPU_TERAS.onMinute) {
        if(lampuTerasState == false) {
            LAMPU_TERAS.timerOn(RELAY_7);
            lampuTerasState = !lampuTerasState;
        }
        else {
            Serial.println("Lampu sudah dinyalakan.");
        }
    }

    if (timeClient.getHours() == LAMPU_TERAS.offHour && timeClient.getMinutes() == LAMPU_TERAS.offMinute) {
        if(lampuTerasState == true) {
            LAMPU_TERAS.timerOff(RELAY_7);
            lampuTerasState = !lampuTerasState;
        }
        else {
            Serial.println("Lampu sudah dimatikan.");
        }
    }

    if (timeClient.getHours() == LAMPU_LORONG.onHour && timeClient.getMinutes() == LAMPU_LORONG.onMinute) {
        if(lampuLorongState == false) {
            LAMPU_LORONG.timerOn(RELAY_8);
            lampuLorongState = !lampuLorongState;
        }
        else {
            Serial.println("Lampu sudah dinyalakan.");
        }
    }

    if (timeClient.getHours() == LAMPU_LORONG.offHour && timeClient.getMinutes() == LAMPU_LORONG.offMinute) {
        if(lampuLorongState == true) {
            LAMPU_LORONG.timerOff(RELAY_8);
            lampuLorongState = !lampuLorongState;
        }
        else {
            Serial.println("Lampu sudah dimatikan.");
        }
    }

    //  if (timeClient.getHours() == ALARM.onHour && timeClient.getMinutes() == ALARM.onMinute) {
    //      alarm.beep(4, 200, 200);
    //  }


    // if there is an incoming message...
    if (fallenWaterBot.getNewMessage(msg)) {
        if (msg.text.equalsIgnoreCase("/stopkontak_komputer_nyala")) {
            if (komputerState == false) {
                BUZZER.beep(1, 200, 200);
                digitalWrite(RELAY_1, LOW);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "StopKontak khusus komputer dinyalakan");
                Serial.println("Relay 1 Menyala");
                komputerState = !komputerState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "StopKontak khusus Komputer sudah dinyalakan.");
            }
        }
        else if (msg.text.equalsIgnoreCase("/stopkontak_komputer_mati")) {
            if (komputerState == true) {
                BUZZER.beep(2, 200, 200);
                digitalWrite(RELAY_1, HIGH);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "StopKontak khusus komputer dimatikan");
                Serial.println("Relay 1 Mati");
                komputerState = !komputerState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "StopKontak khusus Komputer sudah dimatikan.");
            }
        }
        else if (msg.text.equalsIgnoreCase("/kipas_ac_nyala")) {
            if (kipasACState == false) {
                BUZZER.beep(1, 200, 200);
                digitalWrite(RELAY_2, LOW);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "Kipas atau AC dinyalakan");
                Serial.println("Relay 2 Menyala");
                kipasACState = !kipasACState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "Kipas atau AC sudah dinyalakan.");
            }
        }
        else if (msg.text.equalsIgnoreCase("/kipas_ac_mati")) {
            if (kipasACState == true) {
                BUZZER.beep(2, 200, 200);
                digitalWrite(RELAY_2, HIGH);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "Kipas atau AC dimatikan");
                Serial.println("Relay 2 Mati");
                kipasACState = !kipasACState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "Kipas atau AC sudah dimatikan.");
            }
        }
        else if (msg.text.equalsIgnoreCase("/stopkontak_bawah_nyala")) {
            if (stopKontakBawahState == false) {
                BUZZER.beep(1, 200, 200);
                digitalWrite(RELAY_3, LOW);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "StopKontak khusus bawah dinyalakan");
                Serial.println("Relay 3 Menyala");
                stopKontakBawahState = !stopKontakBawahState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "StopKontak khusus bawah sudah dinyalakan.");
            }
        }
        else if (msg.text.equalsIgnoreCase("/stopkontak_bawah_mati")) {
            if (stopKontakBawahState == true) {
                BUZZER.beep(2, 200, 200);
                digitalWrite(RELAY_3, HIGH);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "StopKontak khusus bawah dimatikan");
                Serial.println("Relay 3 Mati");
                stopKontakBawahState = !stopKontakBawahState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "StopKontak khusus bawah sudah dimatikan.");
            }

        }
        else if (msg.text.equalsIgnoreCase("/lampu_kamar_nyala")) {
            if (lampuKamarState == false) {
                BUZZER.beep(1, 200, 200);
                digitalWrite(RELAY_6, LOW);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "Lampu kamar dinyalakan");
                Serial.println("Relay 6 Menyala");
                lampuKamarState = !lampuKamarState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "Lampu kamar sudah dinyalakan...");
            }

        }
        else if (msg.text.equalsIgnoreCase("/lampu_kamar_mati")) {
            if (lampuKamarState == true) {
                BUZZER.beep(2, 200, 200);
                digitalWrite(RELAY_6, HIGH);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "Lampu kamar dimatikan");
                Serial.println("Relay 6 Mati");
                lampuKamarState = !lampuKamarState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "Lampu kamar sudah dimatikan...");
            }
        }
        else if (msg.text.equalsIgnoreCase("/lampu_teras_nyala")) {
            if (lampuTerasState == false) {
                BUZZER.beep(1, 200, 200);
                digitalWrite(RELAY_7, LOW);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "Lampu Teras dinyalakan");
                Serial.println("Relay 7 Menyala");
                lampuTerasState = !lampuTerasState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "Lampu Teras sudah dinyalakan...");
            }

        }
        else if (msg.text.equalsIgnoreCase("/lampu_teras_mati")) {
            if (lampuTerasState == true) {
                BUZZER.beep(2, 200, 200);
                digitalWrite(RELAY_7, HIGH);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "Lampu Teras dimatikan");
                Serial.println("Relay 7 Mati");
                lampuTerasState = !lampuTerasState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "Lampu Teras sudah dimatikan...");
            }
        }
        else if (msg.text.equalsIgnoreCase("/lampu_lorong_nyala")) {
            if (lampuLorongState == false) {
                BUZZER.beep(1, 200, 200);
                digitalWrite(RELAY_8, LOW);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "Lampu Lorong dinyalakan");
                Serial.println("Relay 8 Menyala");
                lampuLorongState = !lampuLorongState; // Return True with Not Gate logic.
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "Lampu Lorong sudah dinyalakan...");
            }
        }
        else if (msg.text.equalsIgnoreCase("/lampu_lorong_mati")) {
            if (lampuLorongState == true) {
                BUZZER.beep(2, 200, 200);
                digitalWrite(RELAY_8, HIGH);
                fallenWaterBot.sendMessage(msg.sender.id, "OK " + msg.sender.username + ", " + "Lampu Lorong dimatikan");
                Serial.println("Relay 8 Mati");
                lampuLorongState = !lampuLorongState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, "Lampu Lorong sudah dimatikan...");
            }
        }
        else if (msg.text.equalsIgnoreCase("/mode_tidur")) {
            if (lampuLorongState == true && lampuKamarState == true && komputerState == true) {
                BUZZER.beep(2, 200, 200);
                digitalWrite(RELAY_1, HIGH); // Stop Kontak Komputer
                digitalWrite(RELAY_6, HIGH); // Lampu Kamar
                digitalWrite(RELAY_8, HIGH); // Lampu Lorong
                fallenWaterBot.sendMessage(msg.sender.id, "Mode tidur: Lampu Kamar, Lorong, dan Stop Kontak Komputer dimatikan");
                Serial.println("Mode tidur: Lampu Kamar, Lorong, dan Stop Kontak Komputer dimatikan");
                komputerState = !komputerState;
                lampuKamarState = !lampuKamarState;
                lampuLorongState = !lampuLorongState;
            }
            else {
                fallenWaterBot.sendMessage(msg.sender.id, msg.sender.username + ", " + "Mode tidur dapat diaktifkan jika Lampu Kamar, Lorong dan Stop Kontak Komputer menyala.");
            }
            
        }
        else if (msg.text.equalsIgnoreCase("/tampilkan_waktu")) {
            String waktu;
            String tanggal;
            waktu = timeClient.getFormattedTime();
            tanggal = daysOfTheWeek[timeClient.getDay()] + String(", ") + fullDate.getDate() + " " + monthsOfTheYear[fullDate.getMonth()] + " " + fullDate.getYear();
            fallenWaterBot.sendMessage(msg.sender.id, "Sekarang Pukul " + waktu + " WIB");
            fallenWaterBot.sendMessage(msg.sender.id, tanggal);
        }
        else {
            String reply;
            reply = "Hay " + msg.sender.username + ". Coba perintah /lampu_kamar_nyala.";
            fallenWaterBot.sendMessage(msg.sender.id, reply);             // and send it
        }
   
    }

    // TODO:
    // Make algorithms for Alarm...
    // Make algorithms to control Exhaust Fan based on Humidity Level...

    // wait 500 milliseconds
    delay(500);

}
