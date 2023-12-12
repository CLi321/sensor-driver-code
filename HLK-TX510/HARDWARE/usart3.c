#include "usart3.h"
#include <stdio.h>
#include <string.h>

#include "HLK_TX510.h"





static void USART3_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVICPriority_Structure.Usart3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��

    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}


static void USART3_GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure USARTy Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USARTy Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

static void USART3_Configuration(void)
{

    USART_InitTypeDef USART_InitStructure;

    USART_DeInit(USART3);                                //��λ����3
    /* USARTy and USARTz configuration ------------------------------------------------------*/
    /* USARTy and USARTz configured as follow:
          - BaudRate = 9600 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Hardware flow control disabled (RTS and CTS signals)
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;//����������;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ


    USART_Init(USART3, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//���������ж�
    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//���������ж�
    USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���
}

static void USART3_RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    /* Enable USARTy Clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);  //��ʹ�ô��ڸ��ù��ܵ�ʱ��Ҫ������Ӧ�Ĺ���ʱ��USART ���Ҵ�ʱ��Դ��APB1�ϣ�����
}

void USART3_Init(void)
{
    USART3_RCC_Configuration();
    USART3_GPIO_Configuration();
    USART3_Configuration();
    USART3_NVIC_Configuration();

    HLK_TX510_ClearDate();
}



void USART3_SendByte(u8 date)
{
    USART_SendData(USART3,date);
    while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) == RESET);
}

void USART3_IRQHandler(void)                	//����1�жϷ������
{
    u8 Res=0;
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        Res =USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
        HLK_TX510_Receive_Byte(Res);
//				printf("%c",Res);
    }
		
		
		if (USART_GetITStatus(USART3, USART_IT_IDLE) != RESET) //�����ж�
    {
         Res = USART_ReceiveData(USART3); /*������ж�*/
        
         if ((RX_Data_TX510.RX_len != 0) && !RX_Data_TX510.RX_ok)
         {
            RX_Data_TX510.RX_ok = 1;/*��־������*/
         }
    }

}


