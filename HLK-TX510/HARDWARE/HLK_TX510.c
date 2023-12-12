
#include "HLK_TX510.h"


unsigned char HLK_TX510_Face_IdentifyCmd[8] =  			{0xEF, 0xAA, 0x12, 0x00, 0x00, 0x00, 0x00, 0x12};							//	ʶ��ָ��						12
unsigned char HLK_TX510_Face_EnrollCmd[8] =					{0xEF, 0xAA, 0x13, 0x00, 0x00, 0x00, 0x00, 0x13};							//	ע��ָ��						12

unsigned char HLK_TX510_Delete_FaceCmd[10] =				{0xEF, 0xAA, 0x20, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01,0x23}; 	//	ɾ���û�ָ��				10
unsigned char HLK_TX510_Delete_FaceALLCmd[8] =    	{0xEF, 0xAA, 0x21, 0x00, 0x00, 0x00, 0x00, 0x21};  						// 	ɾ��ȫ��ָ��				10

unsigned char HLK_TX510_LightON[9] =          			{0xEF, 0xAA, 0xC0, 0x00, 0x00, 0x00, 0x01, 0x01, 0xC2}; 			//	�������ָ��				10
unsigned char HLK_TX510_LightOFF[9] = 				 			{0xEF, 0xAA, 0xC0, 0x00, 0x00, 0x00, 0x01, 0x00, 0xC1};  			//	�ر����ָ��				10
unsigned char HLK_TX510_Control_DisplayON[9] = 			{0xEF, 0xAA, 0xC1, 0x00, 0x00, 0x00, 0x01, 0x01, 0xC3};  			//	����ʾ�ͱ����ָ��	10
unsigned char HLK_TX510_Control_DisplayOFF[9] = 		{0xEF, 0xAA, 0xC1, 0x00, 0x00, 0x00, 0x01, 0x00, 0xC2};  			//	����ʾ�ͱ����ָ��	10
unsigned char HLK_TX510_WhiteLightON[9] =         	{0xEF, 0xAA, 0xC2, 0x00, 0x00, 0x00, 0x01, 0x01, 0xC4};  			//	���׹��ָ��				10
unsigned char HLK_TX510_WhiteLightOFF[9] = 					{0xEF, 0xAA, 0xC2, 0x00, 0x00, 0x00, 0x01, 0x00, 0xC3};  			//	�ذ׹��ָ��				10

unsigned char HLK_TX510_Version_InquireCmd[8] =			{0xEF, 0xAA, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30};  						//	�汾��ѯָ��
unsigned char HLK_TX510_RebootCmd[8] =							{0xEF, 0xAA, 0xC3, 0x00, 0x00, 0x00, 0x01, 0xC3};  						//	����ָ��						10
unsigned char HLK_TX510_Baudrate_SetCmd[9] =				{0xEF, 0xAA, 0x51, 0x00, 0x00, 0x00, 0x01, 0x04, 0x56}; 			//	����������ָ��			10
unsigned char HLK_TX510_Read_Face_QuantityCmd[8] =	{0xEF, 0xAA, 0xC4, 0x00, 0x00, 0x00, 0x00, 0xC4};  						//	��ȡ��ע���û�����

//unsigned char HLK_TX510_Write_Face_EigenvalueCmd[8] =	{0xEF, 0xAA, 0xC0, 0x00, 0x00, 0x00, 0x01, 0x01, 0xC2};  				//д������ֵָ��
//unsigned char HLK_TX510_Read_Face_EigenvalueCmd[12] =	{0xEF, 0xAA, 0xC6, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01,};  //��ȡ����ֵָ��



_HLK_TX510							HLK_TX510;
_RX_Data_TX510 					RX_Data_TX510;
_Receive_Data_TX510 		Receive_Data_TX510;


uint8_t flag_start_TX510 = 0;
uint8_t flag_stop_TX510 = 0;
u8 i;

void HLK_TX510_ClearDate(void)
{
    memset(RX_Data_TX510.RX_BUF, 0, USART_RECEIVE_LEN_TX510);      //���
    memset(Receive_Data_TX510.Receive_BUF, 0, USART_RECEIVE_LEN_TX510);      //���

    RX_Data_TX510.RX_len = 0;
    Receive_Data_TX510.Receive_len = 0;

	
    HLK_TX510.CmdDataLen = 12;
    HLK_TX510.ifGetData = FALSE;
    HLK_TX510.ifParseData = FALSE;
    HLK_TX510.ifUsable =  FALSE;
    HLK_TX510.CurrentMode = NORMAL;

    HLK_TX510.TimeCount = 0;
    HLK_TX510.Illegal_PersonTime=0;
    HLK_TX510.Illegal_PersonWarn = FALSE;
}



void HLK_TX510_Receive_Byte(u8 Res)
{

    if( Res == 0xEF || flag_start_TX510 == 1)
    {
        flag_start_TX510 = 1;

				if ( RX_Data_TX510.RX_len != HLK_TX510.CmdDataLen - 1 )
				{
						RX_Data_TX510.RX_BUF[RX_Data_TX510.RX_len] = Res;/*��������*/
						RX_Data_TX510.RX_len ++; /*���ճ����ۼ�*/
						if ( RX_Data_TX510.RX_BUF[8] == 0x01 || RX_Data_TX510.RX_BUF[8] == 0x06\
																								 || RX_Data_TX510.RX_BUF[8] == 0x07\
																								 || RX_Data_TX510.RX_BUF[8] == 0x08\
																								 || RX_Data_TX510.RX_BUF[8] == 0x09\
																								 || RX_Data_TX510.RX_BUF[8] == 0x0a\
																								 || RX_Data_TX510.RX_BUF[8] == 0x03\
								)
            {
								HLK_TX510.ifGetData = TRUE;
								flag_start_TX510 = 0;
								for(i=0; i < RX_Data_TX510.RX_len; i++)
								{
										printf("%c",RX_Data_TX510.RX_BUF[i]);
								}
            }

				}
				else if (RX_Data_TX510.RX_len == HLK_TX510.CmdDataLen - 1 )
				{

						RX_Data_TX510.RX_BUF[RX_Data_TX510.RX_len] = Res;

						memset(Receive_Data_TX510.Receive_BUF, 0, USART_RECEIVE_LEN_TX510);      //���
						memcpy(Receive_Data_TX510.Receive_BUF, RX_Data_TX510.RX_BUF, RX_Data_TX510.RX_len); 	//��������

						Receive_Data_TX510.Receive_len = RX_Data_TX510.RX_len;
					
						flag_start_TX510 = 0;
						RX_Data_TX510.RX_len = 0;
						memset(RX_Data_TX510.RX_BUF, 0, USART_RECEIVE_LEN_TX510);      //���

						for(i=0; i < Receive_Data_TX510.Receive_len+1; i++)
						{
								printf("%c",Receive_Data_TX510.Receive_BUF[i]);
						}
						HLK_TX510.ifGetData = TRUE;
				}   
    }
		
		


}



void HLK_TX510_Send_FaceCmd(u8 *cmd)
{
    u8 i=0;
    for(i=0; i<8; i++)
    {
        HLK_TX510_SendByte(*cmd++);  // == *(cmd++) ȡcmd��ָ��Ԫ��ֵ��cmdָ����һ��Ԫ����cmd�Լ�1
    }
}


void HLK_TX510_Send_DeleteCmd(u8 *cmd)
{
    u8 i=0;
    for(i=0; i<8; i++)
    {
        HLK_TX510_SendByte(*cmd++);  // == *(cmd++) ȡcmd��ָ��Ԫ��ֵ��cmdָ����һ��Ԫ����cmd�Լ�1
    }
}
void HLK_TX510_Send_DeleteAllCmd(u8 *cmd)
{
    u8 i=0;
    for(i=0; i<10; i++)
    {
        HLK_TX510_SendByte(*cmd++);  // == *(cmd++) ȡcmd��ָ��Ԫ��ֵ��cmdָ����һ��Ԫ����cmd�Լ�1
    }
}

void HLK_TX510_Send_ControlCmd(u8 *cmd)
{
    u8 i=0;
    for(i=0; i<9; i++)
    {
        HLK_TX510_SendByte(*cmd++);  // == *(cmd++) ȡcmd��ָ��Ԫ��ֵ��cmdָ����һ��Ԫ����cmd�Լ�1
    }
}






void HLK_TX510_Enroll_FaceID(void)
{

    HLK_TX510_ClearDate();
    HLK_TX510.CmdDataLen = HLK_TX510_Face_AnswerLEN;
    HLK_TX510.CurrentMode = EnrollFaceID;

    HLK_TX510_Send_FaceCmd(HLK_TX510_Face_EnrollCmd); //������ָ��
    while(HLK_TX510.ifGetData == FALSE); //�ȴ�������Ӧ������


}
void HLK_TX510_Identify_FaceID(void)
{

    HLK_TX510_ClearDate();
    HLK_TX510.CmdDataLen = HLK_TX510_Face_AnswerLEN;
    HLK_TX510.CurrentMode = IdentifyFaceID;

    HLK_TX510_Send_FaceCmd(HLK_TX510_Face_IdentifyCmd);
	  while(HLK_TX510.ifGetData == FALSE); //�ȴ�������Ӧ������
				

}

void HLK_TX510_Delete_FaceID(void)
{

    HLK_TX510_ClearDate();
    HLK_TX510.CmdDataLen = HLK_TX510_Operate_AnswerLEN;
    HLK_TX510.CurrentMode = DeleteFaceID;

    HLK_TX510_Send_DeleteCmd(HLK_TX510_Delete_FaceCmd);
    while(HLK_TX510.ifGetData == FALSE); //�ȴ�������Ӧ������

}

void HLK_TX510_DeleteAll_FaceID(void)
{

    HLK_TX510_ClearDate();
    HLK_TX510.CmdDataLen = HLK_TX510_Operate_AnswerLEN;
    HLK_TX510.CurrentMode = DeleteAllFaceID;

    HLK_TX510_Send_DeleteAllCmd(HLK_TX510_Delete_FaceALLCmd);
    while(HLK_TX510.ifGetData == FALSE); //�ȴ�������Ӧ������

}

void Dealwith_HLK_TX510(void)
{

		if ( HLK_TX510.ifGetData == TRUE )
    {
				HLK_TX510.ifGetData = FALSE;
			
				if( HLK_TX510.CurrentMode == EnrollFaceID )
				{
						HLK_TX510.TimeCount = 0;

						if(Receive_Data_TX510.Receive_BUF[7]==0x13 && Receive_Data_TX510.Receive_BUF[8]==0x00)
						{
								perform_EnrollFace();
						}
				}
				else if( HLK_TX510.CurrentMode == IdentifyFaceID )
				{	
						HLK_TX510.TimeCount = 0;
					
						if(Receive_Data_TX510.Receive_BUF[6]==0x04 && Receive_Data_TX510.Receive_BUF[7]==0x12 && Receive_Data_TX510.Receive_BUF[8]==0x00)
						{
								perform_IdentifyFace();
						}
				}
				else if( HLK_TX510.CurrentMode == DeleteFaceID )
				{
						HLK_TX510.TimeCount = 0;

						if(Receive_Data_TX510.Receive_BUF[6]==0x02 && Receive_Data_TX510.Receive_BUF[7]==0x20 && Receive_Data_TX510.Receive_BUF[8]==0x00)
						{
								perform_DeleteFace();
						}
				}
				else if( HLK_TX510.CurrentMode == DeleteAllFaceID )
				{
						HLK_TX510.TimeCount = 0;

						if(Receive_Data_TX510.Receive_BUF[6]==0x02 && Receive_Data_TX510.Receive_BUF[7]==0x21 && Receive_Data_TX510.Receive_BUF[8]==0x00)
						{
								perform_DeleteAllFace();									
						}
				}	
    }

}

void perform_EnrollFace(void)
{
		LED1(LED_ON);	
		delay_s(1);
		LED1(LED_OFF);	
		delay_s(1);
}
void perform_IdentifyFace(void)
{
		LED2(LED_ON);	
		delay_s(1);	
		LED2(LED_OFF);
		delay_s(1);	
}
void perform_DeleteFace(void)
{
		LED3(LED_ON);	
		delay_s(1);
		LED3(LED_OFF);	
		delay_s(1);	
}
void perform_DeleteAllFace(void)
{
		LED3(LED_ON);	
		delay_s(1);
		LED3(LED_OFF);	
		delay_s(1);	
}

