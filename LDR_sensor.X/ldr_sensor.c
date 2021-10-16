/*
 * File:   ldr_sensor.c
 * Author: vedan
 *
 * Created on June 23, 2021, 12:28 PM
 */


#include "config.h"
void ADC_init(){
    ADCON0 = 0x41;
    ADCON1 = 0xC0;
}

double ADC_readChannel(unsigned int channel){
    if(channel > 13){
        return 0;
    }
    ADCON0 &= 0xC5;
    ADCON0 |= channel << 3;
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((ADRESH << 8) + ADRESL);
}
void main(void) {
    double adc_input = 0, vout = 0;
    TRISD = 0;
    PORTDbits.RD0 = 0;
    TRISAbits.TRISA0 = 1;
    ADC_init();
    while(1){
        adc_input = ADC_readChannel(0);
        vout = adc_input * 5000.0f / 1023;
        if(vout > 4500){
            PORTDbits.RD0 = 1;
        } else {
            PORTDbits.RD0 = 0;
        }
    }
    
    return;
}

