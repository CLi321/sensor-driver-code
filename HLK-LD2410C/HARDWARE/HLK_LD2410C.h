#ifndef __HLK_LD2410C_H_
#define __HLK_LD2410C_H_	 
#include "stm32f10x.h"
#include "stdbool.h"


#define BUFF_MAX_LEN_LD2410C 			300 	/*�ԽӴ��ڣ�������󳤶�*/

#define RECEIVE_MAX_LEN_LD2410C		1024	//�Խ����ݴ���������󳤶�


/*�û����ݴ���*/
typedef struct
{
    uint8_t rx_buff[BUFF_MAX_LEN_LD2410C]; /*���ջ��棬�ԽӴ���*/
    bool rx_ok;           /*������ɱ�־ 1:��� 0:��û���ԽӴ���*/
    uint16_t rx_len;       /*���ջ���ĳ��ȣ��ԽӴ���*/

} _RX_Data_LD2410C;


typedef struct
{
    uint8_t RECEIVE_BUF[RECEIVE_MAX_LEN_LD2410C]; /*���ջ��棬�Խ����ݴ���*/
    //bool Receive_OK;           /*������ɱ�־ 1:��� 0:��û���Խ����ݴ���*/
    uint16_t Receive_len;       /*���ջ���ĳ��ȣ��Խ����ݴ���*/

} _Receive_Data_LD2410C;


typedef struct
{
    uint8_t STATE_target; 
	
    uint8_t MOTION_target_distance;
	  uint8_t MOTION_target_energy; 
	
    uint8_t STATIC_target_distance; 		
		uint8_t STATIC_target_energy; 
    
		uint8_t Detection_target_distance; 	
	
    bool rx_ok;           /*������ɱ�־ 1:��� 0:��û���ԽӴ���*/
    uint16_t len;       

} _Detection_Target_LD2410C;

extern	_RX_Data_LD2410C 							RX_Data_LD2410C;
extern	_Receive_Data_LD2410C 				Receive_Data_LD2410C;
extern  _Detection_Target_LD2410C			Detection_Target_LD2410C;

void DataGet_LD2410C(void);



#endif













