/*
* ASSALAMUALAIKUM WR. WB
* ======================
* RFID SCAN, ADD WITH NODEMCU ESP8266 SKETCH
* Copyright 2020 by Abdul Hakim Ghaniy
* 
* Follow me on Instagram @kaa.noy
* Follow my microblog on Instagram @kodein.web.id
* Read my latest article at https://blog.kodein.web.id
* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* Seluruh kode program yang berada dalam folder project ini merupakan 
* hak cipta dari Abdul Hakim Ghaniy.
* Kode program ini dapat digunakan secara GRATIS dengan syarat dan ketentuan.
* Tidak diperkenankan menggunakan kode ini untuk tujuan komersil pribadi.
* Seluruh kode program ini akan disumbangkan untuk pengembangan teknologi di Pondok Pesantren Daarul Rahman,
* Universitas Nahdlatul Ulama Indonesia, dan lembaga pendidikan atau non-profit yang membutuhkan lainnya.
* ============================================================================
*
* //////////////////////////////////
* //         FILE BEEP.h         //
* ////////////////////////////////
*
*
* ~ Updated at 15 Juni 2020 ~
*/

class BEEP {

public:
    unsigned long previousMillis = 0;
    unsigned long beepOn, beepOff;
    char beepPin;

    int setBeepPin(char);

    // bool state = false;

    void beep(byte beeps, ulong beepOn, ulong beepOff) {
        for (byte beep=0; beep<beeps; beep++) {
            digitalWrite(beepPin, !digitalRead(beepPin));
            delay(beepOn);
            digitalWrite(beepPin, !digitalRead(beepPin));
            delay(beepOff);
        }
    }
};

int BEEP::setBeepPin(char pin) {
    beepPin = pin;

    return beepPin;
}

// TODO:
// Using millis to control buzzer beeps...