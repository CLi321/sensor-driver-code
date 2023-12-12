/******************************************************************************/

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"


#include "HLK_TX510.h"
#include "usart3.h"
#include "led_test.h"  
#include "key_exti.h"
#include "stm32f10x_it.h"

STRUCT_NVICPriority NVICPriority_Structure;

uint8_t KEY1_flag = 0, KEY2_flag = 0;

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{

    uart_init(115200); //串口初始化为115200
    delay_init();	   //延时函数初始化
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
//    printf("欢迎使用野火STM32开发板\n\n\n\n");

	
		NVICPriority_Structure.Usart3 = 2;
    USART3_Init();
	
		LED_GPIO_Config();
		EXTI_Key_Config(); //初始化EXTI中断，按下按键会触发中断，触发中断会进入stm32f1xx_it.c文件中的函数	
	
    while(1)
    {		
				if ( KEY1_flag == 1)
        {
						HLK_TX510_Enroll_FaceID();	
						Dealwith_HLK_TX510();
						delay_s(2);
						KEY1_flag = 0;
        }
				else if ( KEY2_flag == 1)
        {
						HLK_TX510_DeleteAll_FaceID();	
						Dealwith_HLK_TX510();
						delay_s(2);	
						KEY2_flag = 0;
        }
				else
				{
						HLK_TX510_Identify_FaceID();
						Dealwith_HLK_TX510();
						delay_s(2);					
				}
    }
}


/*********************************************END OF FILE**********************/
