#ifndef __UART4_H
#define __UART4_H	 
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����2��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/29
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

#define UART4_MAX_RECV_LEN		1024				//�����ջ����ֽ���
#define UART4_MAX_SEND_LEN		600				//����ͻ����ֽ���
#define UART4_RX_EN 			1					//0,������;1,����.

extern u8  UART4_RX_BUF[UART4_MAX_RECV_LEN]; 		//���ջ���,���UART4_MAX_RECV_LEN�ֽ�
extern u8  UART4_TX_BUF[UART4_MAX_SEND_LEN]; 		//���ͻ���,���UART4_MAX_SEND_LEN�ֽ�
extern u16 UART4_RX_STA;   						//��������״̬

void uart4_init(u32 bound);				//����2��ʼ�� 
void u4_printf(char* fmt, ...);
void uart4_send(uint8_t *data, uint8_t len);

#endif













