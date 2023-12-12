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


//模组返回的消息类型说明
#define HLK_TX510_SUCC           				0x00 // 成功
#define HLK_TX510_No_Face     					0x01 // 检测无人脸
#define HLK_TX510_Face_angle_ERROR     	0x03 // 人脸姿态角度过大
#define HLK_TX510_2D_ERROR        			0x06 // 2D 活体未通过
#define HLK_TX510_3D_ERROR       				0x07 // 3D 活体未通过
#define HLK_TX510_Match_RERROR     	  	0x08 // 匹配未通过
#define HLK_TX510_Repeat_ERROR       		0x09 // 重复注册
#define HLK_TX510_Save_ID_failed       	0x0a // 保存 ID 失败


#define HLK_TX510_Face_AnswerLEN     					12  //人脸录入、识别，       反馈字节长度
#define HLK_TX510_Operate_AnswerLEN 					10  //删除操作、控制操作，   反馈字节长度


#define USART_RECEIVE_LEN_TX510					50


/*用户数据处理*/
typedef struct
{
    unsigned char RX_BUF[USART_RECEIVE_LEN_TX510]; /*接收缓存，对接串口*/
    bool RX_ok;           /*接收完成标志 1:完成 0:还没，对接串口*/
    uint16_t RX_len;       /*接收缓存的长度，对接串口*/

} _RX_Data_TX510;


typedef struct
{
    unsigned char Receive_BUF[USART_RECEIVE_LEN_TX510]; /*接收缓存，对接数据处理*/
    bool Receive_OK;           /*接收完成标志 1:完成 0:还没，对接数据处理*/
    uint16_t Receive_len;       /*接收缓存的长度，对接数据处理*/

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
    ENUM_Judge ifGetData;		//是否获取到数据
    ENUM_Judge ifParseData;	//是否解析完成
    ENUM_Judge ifUsable;		//信息是否可用
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
