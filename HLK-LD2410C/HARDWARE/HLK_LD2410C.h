#ifndef __HLK_LD2410C_H_
#define __HLK_LD2410C_H_	 
#include "stm32f10x.h"
#include "stdbool.h"


#define BUFF_MAX_LEN_LD2410C 			300 	/*对接串口，接收最大长度*/

#define RECEIVE_MAX_LEN_LD2410C		1024	//对接数据处理，接收最大长度


/*用户数据处理*/
typedef struct
{
    uint8_t rx_buff[BUFF_MAX_LEN_LD2410C]; /*接收缓存，对接串口*/
    bool rx_ok;           /*接收完成标志 1:完成 0:还没，对接串口*/
    uint16_t rx_len;       /*接收缓存的长度，对接串口*/

} _RX_Data_LD2410C;


typedef struct
{
    uint8_t RECEIVE_BUF[RECEIVE_MAX_LEN_LD2410C]; /*接收缓存，对接数据处理*/
    //bool Receive_OK;           /*接收完成标志 1:完成 0:还没，对接数据处理*/
    uint16_t Receive_len;       /*接收缓存的长度，对接数据处理*/

} _Receive_Data_LD2410C;


typedef struct
{
    uint8_t STATE_target; 
	
    uint8_t MOTION_target_distance;
	  uint8_t MOTION_target_energy; 
	
    uint8_t STATIC_target_distance; 		
		uint8_t STATIC_target_energy; 
    
		uint8_t Detection_target_distance; 	
	
    bool rx_ok;           /*接收完成标志 1:完成 0:还没，对接串口*/
    uint16_t len;       

} _Detection_Target_LD2410C;

extern	_RX_Data_LD2410C 							RX_Data_LD2410C;
extern	_Receive_Data_LD2410C 				Receive_Data_LD2410C;
extern  _Detection_Target_LD2410C			Detection_Target_LD2410C;

void DataGet_LD2410C(void);



#endif













