/*
 * sys_spi.h
 *
 *  Created on: 2022��10��8��
 *      Author: Lijialin001
 */

#ifndef APP_INC_SYS_SPI_H_
#define APP_INC_SYS_SPI_H_

#include "driverlib.h"
#include "device.h"


//��������
void SPI_init();
uint8_t SPI_RW(uint8_t data);



#endif /* APP_INC_SYS_SPI_H_ */
