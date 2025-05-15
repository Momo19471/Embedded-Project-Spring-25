#ifndef gps_h
#define gps_h

#include "tm4c123gh6pm.h"
#include "UART.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

#define pi 3.14159265358979323846
#define EARTH_RADIUS_M 6371000

float nmea_to_decimal(float nmea_coord);

float haversine(float lat1_nmea, float lon1_nmea, float lat2_nmea, float lon2_nmea);
float to_radians(float degrees);



extern float LATs[1000];
extern float LONGs[1000];
extern float DIST[1000];

extern float start_time, end_time, max_speed, SPEED, first_lat, first_long;
extern uint8_t coordinate_index;
extern uint8_t flag_Validity;
extern char dis[15];
extern volatile float distance_acc;
extern char noOfTokenStrings;
extern char Valid;
extern char Lat[15];
extern char Long[15];
extern char speed[15];
extern char time[6];
extern char North;
extern char East;
extern char recieved_char;
extern volatile char fish;
extern uint8_t is_first;
extern char i;
extern uint8_t No_commas;
extern uint8_t comma_index;
extern char flag;
//extern char GPS_logname[20];
extern char GPS[80];
extern float currentlong, currentLat, currentspeed;
extern float Firstlong, FirstLat;
extern float previouslat, previouslong;

void RecieveString(char *token, char stop_char);
void GPS_read();

//int GPS_read1(float *latitude, float *longitude);

float toDegrees(float angle);
float toRadians(float angle);
//float haversine(float lat1, float lon1, float lat2, float lon2);

#endif