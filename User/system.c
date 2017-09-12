#include "system.h"
//#include "stm32f4xx.h"
#include "stm32f10x.h"


uint32_t runtime = 0;

// 系统滴答时钟使能
void Systick_Init(void)
{
 /*   if (SysTick_Config(SystemCoreClock / 1000))
    { 
        
        while (1);
    }
*/
	
  /* Setup SysTick Timer for 10 msec interrupts  */
  /*
	处理器在初始化时会调用SystemInit（），把系统频率设为72Mhz，
	即SystemCoreClock=72000000；
	那么如果我需要1ms的定时周期，只需要让重载数为72000
	*/
  if (SysTick_Config(SystemCoreClock / 1000))                //SysTick配置函数
  {
  /* Capture error */
    while (1);
  } 
 
  
}

// ms延时函数
void delay_ms(uint16_t msec)
{
    uint32_t target_time = runtime + msec;
    while(runtime <= target_time);
}

// NVIC向量表配置
void NVIC_Configuration(void)
{
	//定义NVIC结构体
	NVIC_InitTypeDef nvic;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	//配置nvic寄存器强占位（第几组）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
//    
/*	
//    配置DMA中断
//    nvic.NVIC_IRQChannel = USART3_IRQn;
	  nvic.NVIC_IRQChannel = DMA1_Channel2_IRQn;
	  //强占优先级，数字越小越高
//    nvic.NVIC_IRQChannelPreemptionPriority = 0;
	  nvic.NVIC_IRQChannelPreemptionPriority = 2;
	  //响应优先级
//    nvic.NVIC_IRQChannelSubPriority = 0;
	  nvic.NVIC_IRQChannelSubPriority = 1;
      nvic.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&nvic);
*/	
	  //    配置串口中断
      nvic.NVIC_IRQChannel = USART1_IRQn;	  
	  //强占优先级，数字越小越高
	  nvic.NVIC_IRQChannelPreemptionPriority = 2;	  
	  //响应优先级
      nvic.NVIC_IRQChannelSubPriority = 0;	  
      nvic.NVIC_IRQChannelCmd = ENABLE;
      NVIC_Init(&nvic);
	
	
	  /* Configure the SysTick handler priority */
	  NVIC_SetPriority(SysTick_IRQn, 0x0);                       //SysTick中断优先级设置

}


void System_Init(void)
{
    NVIC_Configuration();
	
    Systick_Init();
}

// systick函数 1ms自加一次
extern "C" void SysTick_Handler(void)
{
    runtime++;
}



uint32_t System_GetTime(void)
{
    return runtime;
}
