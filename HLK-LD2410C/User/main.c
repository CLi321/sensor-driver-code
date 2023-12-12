/******************************************************************************/ 

#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"

#include "uart4.h"
#include "HLK_LD2410C.h"



extern _Detection_Target_LD2410C		Detection_Target_LD2410C;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	
	uart_init(256000); //���ڳ�ʼ��Ϊ115200
	uart4_init(256000);
	delay_init();	   //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	
  while(1)
	{	
			printf("Ŀ��״̬:%x\r\n",Detection_Target_LD2410C.STATE_target);
			printf("�˶�Ŀ�����:%dcm\r\n",Detection_Target_LD2410C.MOTION_target_distance);
			printf("�˶�Ŀ������ֵ:%d\r\n",Detection_Target_LD2410C.MOTION_target_energy);
			printf("��ֹĿ�����:%dcm\r\n",Detection_Target_LD2410C.STATIC_target_distance);
			printf("��ֹĿ������ֵ:%d\r\n",Detection_Target_LD2410C.STATIC_target_energy);
			printf("̽�����:%dcm\r\n",Detection_Target_LD2410C.Detection_target_distance);
			printf("\n\r");
			
			delay_s(1);
		
		
		
	}	
}


/*********************************************END OF FILE**********************/
