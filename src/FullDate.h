// Time Library
#include <NTPClient.h>
#include <WiFiUdp.h>

// TIME
const long utcOffsetInSeconds = 25200;  // +7 * 60 * 60 (UTC +7 ASIA/JAKARTA)
char daysOfTheWeek[7][12] = { "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu" };
char monthsOfTheYear[12][12]= { "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "3.id.pool.ntp.org", utcOffsetInSeconds);

class FullDate {
public:
    int getYear() {
        time_t rawtime = timeClient.getEpochTime();
        struct tm* ti;
        ti = localtime(&rawtime);
        int year = ti->tm_year + 1900;

        return year;
    }

    int getMonth() {
        time_t rawtime = timeClient.getEpochTime();
        struct tm* ti;
        ti = localtime(&rawtime);
        int month = (ti->tm_mon + 1) < 10 ? 0 + (ti->tm_mon + 1) : (ti->tm_mon + 1) - 1; // Gunakan Array Nama2 Bulan...

        return month;
    }

    int getDate() {
        time_t rawtime = timeClient.getEpochTime();
        struct tm* ti;
        ti = localtime(&rawtime);
        int date = (ti->tm_mday) < 10 ? 0 + (ti->tm_mday) : (ti->tm_mday);
        //String day = daysOfTheWeek[day];

        return date;
    }

}fullDate;