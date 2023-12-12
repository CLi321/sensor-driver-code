#ifndef __UART4_H
#define __UART4_H	 
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口2驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/29
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

#define UART4_MAX_RECV_LEN		1024				//最大接收缓存字节数
#define UART4_MAX_SEND_LEN		600				//最大发送缓存字节数
#define UART4_RX_EN 			1					//0,不接收;1,接收.

extern u8  UART4_RX_BUF[UART4_MAX_RECV_LEN]; 		//接收缓冲,最大UART4_MAX_RECV_LEN字节
extern u8  UART4_TX_BUF[UART4_MAX_SEND_LEN]; 		//发送缓冲,最大UART4_MAX_SEND_LEN字节
extern u16 UART4_RX_STA;   						//接收数据状态

void uart4_init(u32 bound);				//串口2初始化 
void u4_printf(char* fmt, ...);
void uart4_send(uint8_t *data, uint8_t len);

#endif













