/*
 * main.hpp
 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */

#ifndef __ROSMAIN_H_
#define __ROSMAIN_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

void setup(void);
void loop(void);
void cdc_receive_put(uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* __ROSMAIN_H_ */