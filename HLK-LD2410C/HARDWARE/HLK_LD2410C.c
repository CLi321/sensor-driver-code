#include "HLK_LD2410C.h"
#include "usart.h"
#include "string.h"

_RX_Data_LD2410C 				RX_Data_LD2410C;
_Receive_Data_LD2410C 	Receive_Data_LD2410C;


_Detection_Target_LD2410C		Detection_Target_LD2410C;

/**
  * @brief  数据获取
  * @param  
  * @retval  
  */
void DataGet_LD2410C(void)
{
//		u32 i;
//		u8 point = 0;

//		for(i=0;i < Receive_Data_LD2410C.Receive_len;i++)
//		{
//			if (i != Receive_Data_LD2410C.Receive_len-1)
//      {
//					printf("%x,",Receive_Data_LD2410C.RECEIVE_BUF[i]);
//      }
//      else if(i == Receive_Data_LD2410C.Receive_len-1)
//      {
//					printf("%x",Receive_Data_LD2410C.RECEIVE_BUF[i]);
//      }

//		}
//		printf(" \n\r");	
    
		if(Receive_Data_LD2410C.RECEIVE_BUF[0]==0xf4 && Receive_Data_LD2410C.RECEIVE_BUF[1]==0xf3 && Receive_Data_LD2410C.RECEIVE_BUF[2]==0xf2 && Receive_Data_LD2410C.RECEIVE_BUF[3]==0xf1 )
		{
				if (Receive_Data_LD2410C.RECEIVE_BUF[7]==0xaa && Receive_Data_LD2410C.RECEIVE_BUF[17]==0x55)
				{
						Detection_Target_LD2410C.STATE_target = Receive_Data_LD2410C.RECEIVE_BUF[8];
						Detection_Target_LD2410C.MOTION_target_distance = (Receive_Data_LD2410C.RECEIVE_BUF[10]<<8) + Receive_Data_LD2410C.RECEIVE_BUF[9];
						Detection_Target_LD2410C.MOTION_target_energy = Receive_Data_LD2410C.RECEIVE_BUF[11];
						Detection_Target_LD2410C.STATIC_target_distance = (Receive_Data_LD2410C.RECEIVE_BUF[13]<<8) + Receive_Data_LD2410C.RECEIVE_BUF[12];
						Detection_Target_LD2410C.STATIC_target_energy = Receive_Data_LD2410C.RECEIVE_BUF[14];
						Detection_Target_LD2410C.Detection_target_distance = (Receive_Data_LD2410C.RECEIVE_BUF[16]<<8) + Receive_Data_LD2410C.RECEIVE_BUF[15];
				}
				else
				{
						Detection_Target_LD2410C.STATE_target = 0;
						Detection_Target_LD2410C.MOTION_target_distance = 0;
						Detection_Target_LD2410C.MOTION_target_energy = 0;
						Detection_Target_LD2410C.STATIC_target_distance = 0;
						Detection_Target_LD2410C.STATIC_target_energy = 0;
						Detection_Target_LD2410C.Detection_target_distance = 0;
				}
		}
		else
		{
				Detection_Target_LD2410C.STATE_target = 0;
				Detection_Target_LD2410C.MOTION_target_distance = 0;
				Detection_Target_LD2410C.MOTION_target_energy = 0;
				Detection_Target_LD2410C.STATIC_target_distance = 0;
				Detection_Target_LD2410C.STATIC_target_energy = 0;
				Detection_Target_LD2410C.Detection_target_distance = 0;
		}

}

