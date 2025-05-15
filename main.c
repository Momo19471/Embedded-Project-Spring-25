#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "systick.h"
#include "lcd_test.h"
#include "gps.h"

// Coordinates definitions
#define hall_AB_lat         3003.86481
#define hall_AB_long        3116.81067
#define hall_CD_lat         3003.83248
#define hall_CD_long        3116.82769
//#define Mosque_lat          3003.8807
//#define Mosque_long         3116.8217
//#define Eemara_lat          3003.8444
//#define Eemara_long         3116.8408
#define Modarag_lat         3003.84044
#define Modarag_long        3116.74049
//#define Ml3b_lat            3003.8317
//#define Ml3b_long           3116.7600
#define Luban_lat           3003.80487
#define Luban_long          3116.77473
#define library_lat         3003.91201 
#define library_long        3116.79727 
#define Credit_lat 					3003.81823 
#define Credit_long 				3116.70878 
#define madany_lat          3003.86202 
#define madany_long         3116.66303 
#define nafora_lat          3003.94670 
#define nafora_long         3116.68987 
//#define palestine_hall_lat  3003.9124
//#define palestine_hall_long 3116.7175
//#define gate2_lat           3003.8776
//#define gate2_long          3116.6411
//#define gate6_lat           3003.8931
//#define gate6_long          3116.8289



// Dummy SystemInit for Keil
void SystemInit(void) { }

int main(void) {
    SysTick_Init();
    LCD_Init();
    UART0_Init();   // For debug messages (optional)
    UART3_Init();   // For GPS module
		GPIO_init_port(PORT_F,OUTPUT);
		GPIO_init_port(PORT_E,OUTPUT);
	
		GPIO_write(PORT_E,(0<<2)); 

    float current_lat = 0.0f;
    float current_long = 0.0f;
    float min_distance = 0;
    int closest_index = 0;
		int x = 0;
		char buffer77[20];
	
    LCD_Print("Waiting GPS...");
    SysTick_msDelay(3000);
    LCD_Clear();

//		UART_Forward(3,0);
	
    while (1) {
//			LCD_Print("before GPS read");
//		UART_Forward(3,0);
		GPS_read();
//				/*
if (!flag_Validity) {
		LCD_Clear();
		SysTick_msDelay(500);
    LCD_Print("Fixing");
    SysTick_msDelay(1000);
    continue;
}

current_lat = currentLat;
current_long = currentlong;
//			LCD_Print("after GPS read");

        // Read current GPS location


        min_distance = haversine(hall_AB_lat, hall_AB_long, current_lat, current_long);
        closest_index = 0;

        float temp;

        temp = haversine(hall_CD_lat, hall_CD_long, current_lat, current_long);
        if (temp < min_distance) { min_distance = temp; closest_index = 1; }

//        temp = haversine(Mosque_lat, Mosque_long, current_lat, current_long);
//        if (temp < min_distance) { min_distance = temp; closest_index = 2; }

//        temp = haversine(Eemara_lat, Eemara_long, current_lat, current_long);
//        if (temp < min_distance) { min_distance = temp; closest_index = 3; }

        temp = haversine(Modarag_lat, Modarag_long, current_lat, current_long);
        if (temp < min_distance) { min_distance = temp; closest_index = 4; }

//        temp = haversine(Ml3b_lat, Ml3b_long, current_lat, current_long);
//        if (temp < min_distance) { min_distance = temp; closest_index = 5; }

        temp = haversine(Luban_lat, Luban_long, current_lat, current_long);
        if (temp < min_distance) { min_distance = temp; closest_index = 6; }

        temp = haversine(library_lat, library_long, current_lat, current_long);
        if (temp < min_distance) { min_distance = temp; closest_index = 7; }

        temp = haversine(Credit_lat, Credit_long, current_lat, current_long);
        if (temp < min_distance) { min_distance = temp; closest_index = 8; }

//        temp = haversine(madany_lat, /.madany_long, current_lat, current_long);
//        if (temp < min_distance) { min_distance = temp; closest_index = 9; }

        temp = haversine(nafora_lat, nafora_long, current_lat, current_long);
        if (temp < min_distance) { min_distance = temp; closest_index = 10; }

//        temp = haversine(palestine_hall_lat, palestine_hall_long, current_lat, current_long);
//        if (temp < min_distance) { min_distance = temp; closest_index = 11; }

//        temp = haversine(gate2_lat, gate2_long, current_lat, current_long);
//        if (temp < min_distance) { min_distance = temp; closest_index = 12; }

//        temp = haversine(gate6_lat, gate6_long, current_lat, current_long);
//        if (temp < min_distance) { min_distance = temp; closest_index = 13; }

        if (min_distance > 25.0f) { closest_index = 14; }
				x = min_distance;
				sprintf(buffer77,"%d",x);
				LCD_Print(buffer77);
        LCD_Clear();
        switch (closest_index) {
           
					case 0: LCD_Print("Hall AB"); 
						LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Distance = ");
						LCD_Print(buffer77);
						LCD_Print("m");					
						GPIO_write(PORT_F,(1<<3));	GPIO_write(PORT_E,(3<<2)); 	break;
            
					case 1: LCD_Print("Hall CD"); 		
						LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Distance = ");
						LCD_Print(buffer77);
					
					
						LCD_Print("m");		
						GPIO_write(PORT_F,(1<<3));	GPIO_write(PORT_E,(3<<2)); 	break;
           

					case 4: LCD_Print("Moadarag");
						LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Distance = ");
						LCD_Print(buffer77);
						LCD_Print("m");
						GPIO_write(PORT_F,(1<<3));	GPIO_write(PORT_E,(3<<2)); 	break;
 
				
					case 6: LCD_Print("Luban"); 				
					LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Distance = ");
						LCD_Print(buffer77);
						LCD_Print("m");		
						GPIO_write(PORT_F,(1<<3));	GPIO_write(PORT_E,(3<<2)); 	break;
						
					case 7: LCD_Print("Library"); 			
					LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Distance = ");
						LCD_Print(buffer77);
						LCD_Print("m");		
						GPIO_write(PORT_F,(1<<3));	GPIO_write(PORT_E,(3<<2)); 	break;

					case 8: LCD_Print("Credit"); 				
					LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Distance = ");
						LCD_Print(buffer77);
						LCD_Print("m");		
						GPIO_write(PORT_F,(1<<3));	GPIO_write(PORT_E,(3<<2)); 	break;

					case 9: LCD_Print("Madany"); 				
					LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Distance = ");
						LCD_Print(buffer77);
						LCD_Print("m");		
						GPIO_write(PORT_F,(1<<3));	GPIO_write(PORT_E,(3<<2)); 	break;

					case 10: LCD_Print("Nafora"); 		
					LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Distance = ");
						LCD_Print(buffer77);
						LCD_Print("m");		
						GPIO_write(PORT_F,(1<<3));	GPIO_write(PORT_E,(3<<2)); 	break;



				case 14: LCD_Print("Out of range"); 	
				LCD_SetCursor(1, 0);  // Move to second row, first column
						LCD_Print("Nearest ");
						LCD_Print(buffer77);
						LCD_Print("m away");	GPIO_write(PORT_F,(1<<1)); GPIO_write(PORT_E,1<<1);	break; 
        }
			//	LCD_Print("GG");
        SysTick_msDelay(1000);
				
// 			*/
    }

    return 0;
}


// buzzer E2     green led E3        red led E1