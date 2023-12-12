#ifndef _HLK_TX510_H_
#define _HLK_TX510_H_

#include "stm32f10x.h"
#include "string.h"
#include "stdio.h"
#include "def_config.h"
#include "delay.h"
#include "usart3.h"
#include "stdbool.h"

#include "led_test.h"


#define HLK_TX510_SendByte  USART3_SendByte


//ģ�鷵�ص���Ϣ����˵��
#define HLK_TX510_SUCC           				0x00 // �ɹ�
#define HLK_TX510_No_Face     					0x01 // ���������
#define HLK_TX510_Face_angle_ERROR     	0x03 // ������̬�Ƕȹ���
#define HLK_TX510_2D_ERROR        			0x06 // 2D ����δͨ��
#define HLK_TX510_3D_ERROR       				0x07 // 3D ����δͨ��
#define HLK_TX510_Match_RERROR     	  	0x08 // ƥ��δͨ��
#define HLK_TX510_Repeat_ERROR       		0x09 // �ظ�ע��
#define HLK_TX510_Save_ID_failed       	0x0a // ���� ID ʧ��


#define HLK_TX510_Face_AnswerLEN     					12  //����¼�롢ʶ��       �����ֽڳ���
#define HLK_TX510_Operate_AnswerLEN 					10  //ɾ�����������Ʋ�����   �����ֽڳ���


#define USART_RECEIVE_LEN_TX510					50


/*�û����ݴ���*/
typedef struct
{
    unsigned char RX_BUF[USART_RECEIVE_LEN_TX510]; /*���ջ��棬�ԽӴ���*/
    bool RX_ok;           /*������ɱ�־ 1:��� 0:��û���ԽӴ���*/
    uint16_t RX_len;       /*���ջ���ĳ��ȣ��ԽӴ���*/

} _RX_Data_TX510;


typedef struct
{
    unsigned char Receive_BUF[USART_RECEIVE_LEN_TX510]; /*���ջ��棬�Խ����ݴ���*/
    bool Receive_OK;           /*������ɱ�־ 1:��� 0:��û���Խ����ݴ���*/
    uint16_t Receive_len;       /*���ջ���ĳ��ȣ��Խ����ݴ���*/

} _Receive_Data_TX510;




typedef enum
{
    NORMAL,
    EnrollFaceID,
    IdentifyFaceID,
    DeleteFaceID,
    DeleteAllFaceID,
    Control

} ENUM_HLK_TX510;


typedef struct SaveData
{


    char CmdDataLen;
    ENUM_Judge ifGetData;		//�Ƿ��ȡ������
    ENUM_Judge ifParseData;	//�Ƿ�������
    ENUM_Judge ifUsable;		//��Ϣ�Ƿ����
    ENUM_HLK_TX510 CurrentMode;

    ENUM_Judge Illegal_PersonWarn;
    char Illegal_PersonTime;
    char TimeCount;

} _HLK_TX510;


extern _HLK_TX510 HLK_TX510;
extern _RX_Data_TX510 					RX_Data_TX510;
extern _Receive_Data_TX510 			Receive_Data_TX510;




void HLK_TX510_ClearDate(void);
void HLK_TX510_Receive_Byte(u8 res);


void HLK_TX510_Send_FaceCmd(u8 *cmd);
void HLK_TX510_Send_DeleteCmd(u8 *cmd);
void HLK_TX510_Send_DeleteAllCmd(u8 *cmd);
void HLK_TX510_Send_ControlCmd(u8 *cmd);

void HLK_TX510_Enroll_FaceID(void);
void HLK_TX510_Identify_FaceID(void);
void HLK_TX510_Delete_FaceID(void);
void HLK_TX510_DeleteAll_FaceID(void);


void Dealwith_HLK_TX510(void);


void perform_EnrollFace(void);
void perform_IdentifyFace(void);
void perform_DeleteFace(void);
void perform_DeleteAllFace(void);


#endif
