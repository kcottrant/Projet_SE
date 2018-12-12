#ifndef _SPI_H_
#define _SPI_H_

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void SPI_MasterInit(void);
void SPI_MasterTransmit(uint8_t cData);
void allumeLed(uint16_t chiffre);

#endif
