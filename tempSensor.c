/*
 * tempSensor.c
 *
 *  Created on: Feb 19, 2020
 *      Author: thatts2
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "tempSensor.h"


#include <stdio.h>
//#include "inc/tm4c123gh6pm.h"
#include "inc/tm4c1294ncpdt.h"


void delayMs(int n);

//int main(void)
void tempSensor(int *clientfd)
{
    int temperature;
    char buffer[18];
    char buffert[1024];
    //int clientfd;




    /* initialize UART0 for output */


    /* enable clocks */
    SYSCTL_RCGCGPIO_R |= 0x10;      /* enable clock to GPIO_PORTE */
    SYSCTL_RCGCADC_R |= 1;          /* enable clock to ADC0 */

    /* initialize PE3 for AIN0 input */
    //GPIO_PORTE_AFSEL_R |= 8;        /* enable alternate function */
    GPIO_PORTE_AHB_AFSEL_R|= 8;
    //GPIO_PORTE_DEN_R &= ~8;         /* disable digital function */
    GPIO_PORTE_AHB_DEN_R &= ~8;
    //GPIO_PORTE_AMSEL_R |= 8;        /* enable analog function */
    GPIO_PORTE_AHB_AMSEL_R |= 8;
    /* initialize ADC0 */
    ADC0_ACTSS_R &= ~8;             /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;         /* software trigger conversion */
    ADC0_SSMUX3_R = 0;              /* get input from channel 0 */
    ADC0_SSCTL3_R |= 6;             /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= 8;              /* enable ADC0 sequencer 3 */

    //lED
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);

 //   while(1) {   try for IOT
        ADC0_PSSI_R |= 8;           /* start a conversion sequence 3 */
        while((ADC0_RIS_R & 0x08) == 0)
            ;                       /* wait for conversion to complete */
        temperature = ((ADC0_SSFIFO3_R * 330) / 4096);
        ADC0_ISC_R = 8;             /* clear completion flag  */
        sprintf(buffer, "\r\nTemp = %d", temperature);
        //System_printf("\r\nTemp = %dF", temperature);
        //System_flush();
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);

        if(temperature >90)
        {

            GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
        }
         else
         {
             GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);
        }


        //UART0_puts(buffer); removed for IOT
      //  delayMs(1000);

        //char result = (char)temperature;
        //memset(buffert,0,sizeof(buffert));


        //sprintf(buffert,result);
       // sprintf(buffert, result);
       // sendData(buffert,clientfd);
        sendData(buffer,clientfd);
        //System_printf("Temperature is ","%d",temperature);
        //System_flush();
  //  } Try for IOT
        //return();
}

