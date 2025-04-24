#include "thermo.h"

// Called to update the thermometer display.  Makes use of
// set_temp_from_ports() and set_display_from_temp() to access
// temperature sensor then set the display. Always sets the display
// even if the other functions returns an error. Returns 0 if both
// functions complete successfully and return 0. Returns 1 if either
// function or both return a non-zero values.
// 
// CONSTRAINT: Does not allocate any heap memory as malloc() is NOT
// available on the target microcontroller.  Uses stack and global
// memory only.
int thermo_update(){
    temp_t temp;
    int set_check;
    int display_check;
    set_check = set_temp_from_ports(&temp);
    display_check = set_display_from_temp(temp, &THERMO_DISPLAY_PORT);
    if(set_check > 0 || display_check > 0){
        return 1;
    }
    else{
        return 0;
    }
}

// Uses the two global variables (ports) THERMO_SENSOR_PORT and
// THERMO_STATUS_PORT to set the fields of `temp`. If
// THERMO_SENSOR_PORT is negative or above its maximum trusted value
// (associated with +45.0 deg C), this function sets the
// tenths_degrees to 0 and the temp_mode to 3 for `temp` before
// returning 1.  Otherwise, converts the sensor value to deg C using
// shift operations.  Further converts to deg F if indicated from
// THERMO_STATUS_PORT. Sets the fields of `temp` to appropriate
// values. `temp_mode` is 1 for Celsius, and 2 for Fahrenheit. Returns
// 0 on success. This function DOES NOT modify any global variables
// but may access them.
//
// CONSTRAINTS: Uses only integer operations. No floating point
// operations are used as the target machine does not have a FPU. Does
// not use any math functions such as abs().
/*int set_temp_from_ports(temp_t *temp){
    int port_mask = 1;
    int port_shifted = port_mask << 2;
    if(THERMO_SENSOR_PORT < 0 || THERMO_SENSOR_PORT > 28800 || THERMO_STATUS_PORT & port_shifted){
        temp->tenths_degrees = 0;
        temp->temp_mode = 3;
        return 1;
    }
    short bit_temp = THERMO_SENSOR_PORT >> 5;
    short remainder = THERMO_SENSOR_PORT & 0b00011111;
    if(remainder >= 16){
       bit_temp += 1;
    }
    bit_temp -= 450;
    int mask = 1;
    int shifted = mask << 5;
    if(THERMO_STATUS_PORT & shifted){
        bit_temp = (bit_temp * 9) / 5 + 320;
        temp->tenths_degrees = bit_temp;
        temp->temp_mode = 2;
    }
    else{
        temp->tenths_degrees = bit_temp;
        temp->temp_mode = 1;
    }
    return 0;
}*/

// Alters the bits of integer pointed to by display to reflect the
// temperature in struct arg temp.  If temp has a temperature value
// that is below minimum or above maximum temperature allowable or if
// the temp_mode is not Celsius or Fahrenheit, sets the display to
// read "ERR" and returns 1. Otherwise, calculates each digit of the
// temperature and changes bits at display to show the temperature
// according to the pattern for each digit.  This function DOES NOT
// modify any global variables except if `display` points at one.
// 
// CONSTRAINTS: Uses only integer operations. No floating point
// operations are used as the target machine does not have a FPU. Does
// not use any math functions such as abs().
/*int set_display_from_temp(temp_t temp, int *display){
    //deref sets display to 0
    *display = 0;
    //array for displays ints 0-9
    //int dis_masks[10] = {123, 72, 61, 109, 78, 103, 119, 73, 127, 111};
    int dis_masks[10] = {0b1111011, 0b1001000, 0b0111101, 0b1101101, 0b1001110, 0b1100111, 0b1110111, 0b1001001, 0b1111111, 0b1101111};
    //array for negative sign, blank, letters E and R
    int other_masks[4] = {0b0000100, 0b0000000, 0b0110111, 0b1011111};
    //integer variable 0
    int num_display = 0;
    int total = temp.tenths_degrees;
    //check for temp_mode correct value
    if(temp.temp_mode != 1 && temp.temp_mode != 2){
        num_display |= other_masks[2];
        num_display = num_display << 7;
        num_display |= other_masks[3];
        num_display = num_display << 7;
        num_display |= other_masks[3];
        num_display = num_display << 7;
        num_display |= other_masks[1];
        *display = num_display;
        return 1;
    }
    //check for in range - celsius
    if(temp.temp_mode == 1){
        if(temp.tenths_degrees < -450 || temp.tenths_degrees > 450){
            num_display |= other_masks[2];
            num_display = num_display << 7;
            num_display |= other_masks[3];
            num_display = num_display << 7;
            num_display |= other_masks[3];
            num_display = num_display << 7;
            num_display |= other_masks[1];
            *display = num_display;
            return 1;
        }
    }
    //check in range - fahrenheight
    if(temp.temp_mode == 2){
        if(temp.tenths_degrees < -490 || temp.tenths_degrees > 1130){
            num_display |= other_masks[2];
            num_display = num_display << 7;
            num_display |= other_masks[3];
            num_display = num_display << 7;
            num_display |= other_masks[3];
            num_display = num_display << 7;
            num_display |= other_masks[1];
            *display = num_display;
            return 1;
        }
    }
    //check for negative
    int is_neg = 0;
    if(temp.tenths_degrees < 0){
        num_display |= other_masks[0];
        num_display = num_display << 7;
        total *= -1;
        is_neg = 1;
    }
    //modulo operations for determining
    int temp_tenths = 99;
    if(is_neg == 0){
        temp_tenths = total % 10;
        total /= 10;
    }
    int temp_ones = total % 10;
    total /= 10;
    int temp_tens = total % 10;
    total /= 10;
    int temp_hundreds = total % 10;
   //check for hundreds place
   if(temp_hundreds != 0){
       num_display |= dis_masks[temp_hundreds];
       num_display = num_display << 7;
   } 
    //check for tens place
    if(temp_tens != 0 || temp_hundreds != 0){
        num_display |= dis_masks[temp_tens];
        num_display = num_display << 7;
    }
    //put in ones place
    num_display |= dis_masks[temp_ones];

    //check for tenths place
    if(temp_tenths != 99){
        num_display = num_display << 7;
        num_display |= dis_masks[temp_tenths];
    }
    //check for farenheight or celsius
    int cf_mask;
    int num_places = 0;
    if(temp.temp_mode == 1){
        num_places = 28;
    }
    else{
        num_places = 29;
    }
    cf_mask = 1 << num_places;
    num_display |= cf_mask;
    *display = num_display;
    return 0;
}*/
