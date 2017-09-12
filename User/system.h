#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stdint.h>

extern uint32_t runtime;

//自己编写的启动初始化函数，区别于SystemInit（）
void System_Init(void);

void delay_ms(uint16_t msec);
//通过滴答定时器返回系统运行时间，毫秒
uint32_t System_GetTime(void);

#endif
