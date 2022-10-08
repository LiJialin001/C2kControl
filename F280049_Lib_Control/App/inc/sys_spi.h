/*
 * sys_spi.h
 *
 *  Created on: 2022年10月8日
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_SPI_H_
#define APP_INC_SYS_SPI_H_

#include "driverlib.h"
#include "device.h"


//函数声明
void SPI_init();
uint8_t SPI_RW(uint8_t data);



#endif /* APP_INC_SYS_SPI_H_ */
