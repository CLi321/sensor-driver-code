/******************************************************************************/ 

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"

#include "uart4.h"
#include "HLK_LD2410C.h"



extern _Detection_Target_LD2410C		Detection_Target_LD2410C;

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	
	uart_init(256000); //串口初始化为115200
	uart4_init(256000);
	delay_init();	   //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	
  while(1)
	{	
			printf("目标状态:%x\r\n",Detection_Target_LD2410C.STATE_target);
			printf("运动目标距离:%dcm\r\n",Detection_Target_LD2410C.MOTION_target_distance);
			printf("运动目标能量值:%d\r\n",Detection_Target_LD2410C.MOTION_target_energy);
			printf("静止目标距离:%dcm\r\n",Detection_Target_LD2410C.STATIC_target_distance);
			printf("静止目标能量值:%d\r\n",Detection_Target_LD2410C.STATIC_target_energy);
			printf("探测距离:%dcm\r\n",Detection_Target_LD2410C.Detection_target_distance);
			printf("\n\r");
			
			delay_s(1);
		
		
		
	}	
}


/*********************************************END OF FILE**********************/
