/*
 * main.cpp
 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */
#include "ROSMain.h"
#include "stm32f4xx_hal.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Bool.h>
#include "ringbuffer.h"

void messageCb(const std_msgs::Bool& msg);

extern uint8_t RxBuffer[RxBufferSize];
struct ringbuffer rb;

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);
ros::Subscriber<std_msgs::Bool> sub("ledState", &messageCb);

char hello[40];
int s;
uint8_t u8Counter = 0;
uint32_t u32LastUpdate = 0;

void cdc_receive_put(uint8_t value) {
	ringbuffer_putchar(&rb, value);
}

void messageCb(const std_msgs::Bool& msg) {
  if(msg.data == 1) {
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
  }
}

void setup(void) {
  ringbuffer_init(&rb, RxBuffer, RxBufferSize);
  nh.initNode();
  nh.advertise(chatter);
  
  HAL_Delay(100);
  nh.subscribe(sub);
}

void loop(void)
{
  if(HAL_GetTick() - u32LastUpdate > 100) {
    s = snprintf(hello, sizeof(hello), "Counter = %d", u8Counter);
    str_msg.data = hello;
    chatter.publish(&str_msg);
    u32LastUpdate = HAL_GetTick();
    u8Counter++; 
  }
  
  nh.spinOnce();
}