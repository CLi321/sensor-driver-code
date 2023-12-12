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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{

    uart_init(115200); //���ڳ�ʼ��Ϊ115200
    delay_init();	   //��ʱ������ʼ��
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//    printf("��ӭʹ��Ұ��STM32������\n\n\n\n");

	
		NVICPriority_Structure.Usart3 = 2;
    USART3_Init();
	
		LED_GPIO_Config();
		EXTI_Key_Config(); //��ʼ��EXTI�жϣ����°����ᴥ���жϣ������жϻ����stm32f1xx_it.c�ļ��еĺ���	
	
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
