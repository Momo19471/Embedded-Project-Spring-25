//#include "Io.h"
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "stdio.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>
#include "gps.h"
#include "lcd_test.h"

//float LATs[1000] = {0}, LONGs[1000] = {0}, DIST[1000] = {0};
float nmea_coord=0;

	
float start_time = 0, end_time = 0, max_speed = 0, SPEED = 0, first_lat = 0, first_long = 0;
uint8_t coordinate_index = 1;
uint8_t flag_Validity = 0;
char dis[15] = {0};
volatile float distance_acc = 0;
char noOfTokenStrings = 0;
char Valid = 0;
char Lat[15] = {0};
char Long[15] = {0};
char speed[15] = {0};
char time[6] = {0};
char North = 0;
char East = 0;
char recieved_char = 0;
volatile char fish = 1;
uint8_t is_first = 1;
char i = 0;
uint8_t No_commas = 0;
uint8_t comma_index = 0;
char flag = 1;
//char GPS_logname[] = { '$', 'G', 'P', 'R', 'M', 'C', ',', '\0' };
char GPS[80] = {0};
float currentlong = 0, currentLat = 0, currentspeed = 0;
float Firstlong = 0, FirstLat = 0;
float previouslat = 0, previouslong =0;

char hoda[80];
int x = 0;

//GPS_logname[4];
//buffer[10];

void RecieveString(char *buffer, char stop_char) {
    char c;
    int i = 0;
//    LCD_Print("inside receive string");
    do {
        c = UART_RX(3);
        buffer[i++] = c;
    } while (c != stop_char && i < 79); // leave space for null terminator

    buffer[i] = '\0';
}

/*
int GPS_read1(float *latitude, float *longitude) {
    char buffer[100];
    if (read_GPRMC(buffer)) {
        parse_GPRMC(buffer, latitude, longitude);
        return 1;  // Success
    }
    return 0;  // Failed
}
*/

void GPS_read() {
    char ch;
    int match = 0;
    int index = 0;

    // Wait for $GPRMC,
    while (1) {
        ch = UART_RX(3);
        if (match == 0 && ch == '$') match++;
        else if (match == 1 && ch == 'G') match++;
        else if (match == 2 && ch == 'P') match++;
        else if (match == 3 && ch == 'R') match++;
        else if (match == 4 && ch == 'M') match++;
        else if (match == 5 && ch == 'C') match++;
        else if (match == 6 && ch == ',') break;
        else match = 0;
    }

    RecieveString(GPS, '*'); // read rest of sentence

    // Reset buffers
    memset(Lat, 0, sizeof(Lat));
    memset(Long, 0, sizeof(Long));
    memset(speed, 0, sizeof(speed));

    uint8_t comma_count = 0, i_lat = 0, i_long = 0, i_speed = 0;
    Valid = 0;

    for (uint8_t i = 0; GPS[i] != '\0'; i++) {
        if (GPS[i] == ',') {
            comma_count++;
            continue;
        }

        switch (comma_count) {
            case 1:
                // Validity flag
                Valid = GPS[i]; // should be 'A'
                break;
            case 2:
                if (i_lat < sizeof(Lat) - 1) Lat[i_lat++] = GPS[i];
                break;
            case 3:
                North = GPS[i];
                break;
            case 4:
                if (i_long < sizeof(Long) - 1) Long[i_long++] = GPS[i];
                break;
            case 5:
                East = GPS[i];
                break;
            case 6:
                if (i_speed < sizeof(speed) - 1) speed[i_speed++] = GPS[i];
                break;
        }
    }

    Lat[i_lat] = '\0';
    Long[i_long] = '\0';
    speed[i_speed] = '\0';

    if (Valid == 'A') {
        currentLat = atof(Lat);
        currentlong = atof(Long);
        currentspeed = atof(speed);
        flag_Validity = 1;
    } else {
        flag_Validity = 0;
    }
}

    // Convert to float
//    currentLat = atof(Lat);
//    currentlong = atof(Long);


// Convert NMEA format (ddmm.mmmm or dddmm.mmmm) to decimal degrees
float nmea_to_decimal(float nmea_coord)
{
    int degrees = (int)(nmea_coord / 100.0f);
    float minutes = nmea_coord - (degrees * 100.0f);
    return degrees + (minutes / 60.0f);
}

// Convert degrees to radians
float to_radians(float degrees) {
    return degrees * (pi/ 180.0f);
}

// Haversine function using NMEA input
float haversine(float lat1_nmea, float lon1_nmea, float lat2_nmea, float lon2_nmea) {
    float lat1 = to_radians(nmea_to_decimal(lat1_nmea));
    float lon1 = to_radians(nmea_to_decimal(lon1_nmea));
    float lat2 = to_radians(nmea_to_decimal(lat2_nmea));
    float lon2 = to_radians(nmea_to_decimal(lon2_nmea));

    float dlat = lat2 - lat1;
    float dlon = lon2 - lon1;

    float a = sinf(dlat / 2.0f) * sinf(dlat / 2.0f) +
              cosf(lat1) * cosf(lat2) *
              sinf(dlon / 2.0f) * sinf(dlon / 2.0f);
    float c = 2.0f * atan2f(sqrtf(a), sqrtf(1.0f - a));

    return EARTH_RADIUS_M * c;
}