#include "uart4.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "HLK_LD2410C.h"



//���ڷ��ͻ�����
__align(8) u8 UART4_TX_BUF[UART4_MAX_SEND_LEN]; //���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
u8 UART4_RX_BUF[UART4_MAX_RECV_LEN]; 				//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.

extern void DataGet_LD2410C(void);
u8 flag_start_LD2410C = 0;

/*UART4�жϷ�����*/
void UART4_IRQHandler(void)
{
    u8 res;
	
    if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) //���յ�����
    {
        res = USART_ReceiveData(UART4);
				
				if (res == 0xf4 || flag_start_LD2410C == 1)
        {
						flag_start_LD2410C = 1;
						if(res != 0xf5) 
						{
								 RX_Data_LD2410C.rx_buff[RX_Data_LD2410C.rx_len] = res;/*��������*/
								 RX_Data_LD2410C.rx_len++; /*���ճ����ۼ�*/
						}
						else if(res == 0xf5) 
						{						
								RX_Data_LD2410C.rx_buff[RX_Data_LD2410C.rx_len] = res;
							
								memset(Receive_Data_LD2410C.RECEIVE_BUF, 0, RECEIVE_MAX_LEN_LD2410C);      //���
								memcpy(Receive_Data_LD2410C.RECEIVE_BUF, RX_Data_LD2410C.rx_buff, RX_Data_LD2410C.rx_len); 	//��������
							
								Receive_Data_LD2410C.Receive_len = RX_Data_LD2410C.rx_len;	
								flag_start_LD2410C = 0;		
								RX_Data_LD2410C.rx_len = 0;
							
								DataGet_LD2410C();
						}					
        }
    }
		
		
    if (USART_GetITStatus(UART4, USART_IT_IDLE) != RESET) //�����ж�
    {
         res = USART_ReceiveData(UART4); /*������ж�*/
        
         if ((RX_Data_LD2410C.rx_len != 0) && !RX_Data_LD2410C.rx_ok)
         {
            RX_Data_LD2410C.rx_ok = 1;/*��־������*/
         }
    }
    
}

USART_InitTypeDef USART_InitStructure;

//��ʼ��IO ����4
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������
void uart4_init(u32 bound)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);// GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    USART_DeInit(UART4);                                //��λ����4
    //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;            //PA.2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     //�����������
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ��PA2

    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;            //PA.3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //��������
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //��ʼ��PA3

    USART_InitStructure.USART_BaudRate = bound;                                    //һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                            //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //�շ�ģʽ

    USART_Init(UART4, &USART_InitStructure); //��ʼ������2
    
    USART_Cmd(UART4, ENABLE);                                         //ʹ�ܴ���

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//���������ж�
    USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);//���������ж�

    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2 ; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

    RX_Data_LD2410C.rx_ok = 0;				  //����
}



//����4,printf ����
//ȷ��һ�η������ݲ�����USART2_MAX_SEND_LEN�ֽ�
void u4_printf(char *fmt, ...)
{
    u16 i, j;
    va_list ap;
    va_start(ap, fmt);
    vsprintf((char *)UART4_TX_BUF, fmt, ap);
    va_end(ap);

    for (j = 0; j < i; j++) //ѭ����������
    {
        while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET); //ѭ������,ֱ���������

        USART_SendData(UART4, UART4_TX_BUF[j]);
    }
}

//����4���ݷ���
//*date:���ݻ����ַ
//len:���ݳ���
void uart4_send(uint8_t *data, uint8_t len)
{

    uint8_t i = 0;

    for (i = 0; i < len; i++) //ѭ����������
    {
        while ((UART4->SR & 0X40) == 0); //ѭ������,ֱ���������

        UART4->DR = *(data + i);
    }

}



 
