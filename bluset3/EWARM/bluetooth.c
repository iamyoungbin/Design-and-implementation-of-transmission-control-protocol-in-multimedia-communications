/* 
bluetooth.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //for strncmp
#include "stm32f4xx_hal.h"
#include "bluetooth.h"

unsigned char bt_mac_addr[8];
unsigned char bt_broadcast_addr[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char bt_state;
unsigned char bt_index;
unsigned char bt_count;
unsigned char bt_dis_count;
unsigned char btBuf[100];
unsigned char bt_enable_flag;



//AT_COMMAND
uint8_t AT[] = "AT";
uint8_t OK[3];

//SET BAUD 115200
uint8_t SET_BAUD[] = "AT+BAUD0";
uint8_t BAUD[8];

//MAC QURRY
uint8_t QR_MAC_ADDRESS[] = "AT+ADDR?";
uint8_t SAVE_ADDRESS[20];
uint8_t MAC1[] = "OK+ADDR:A810871D1386";
uint8_t MAC2[] = "OK+ADDR:A810871B48F5";

//SET MODE
uint8_t SET_MODE[] = "AT+MODE0";
uint8_t MODE[8];

//FACTORY SETUP
uint8_t SET_RENEW[] = "AT+RENEW";
uint8_t RENEW[8];

//RESET MODULE
uint8_t SET_RESET[] = "AT+RESET";
uint8_t BT_RESET[8];

// START DISC
uint8_t SET_SCAN[] = "AT+DISC?";

//MASTER & SLAVE
uint8_t SET_MASTER[] = "AT+ROLE1";
uint8_t SET_SLAVE[] = "AT+ROLE0";
uint8_t RESULT_ROLE[8];
uint8_t QR_ROLE[] = "AT+ROLE?";
uint8_t ROLE[8];

//SET IMME(CENTRAL)
//IMME0 = AUTO  SCAN - CONNECT
//IMME1 = COMMAND - SCAN - CONNECT
uint8_t SET_IMME0[] = "AT+IMME0";
uint8_t SET_IMME1[] = "AT+IMME1";
uint8_t IMME[8];
//START
uint8_t BT_START1[] = "AT+START";
uint8_t START1[8];

//CONN RESULT
uint8_t NOTI[] = "AT+NOTP1";
uint8_t NOTI1[8];
uint8_t CONN_RESULT[8];
uint8_t CON_MAC1[] = "AT+CONA810871D1386"; //연결 주소 입력
uint8_t CON_MAC2[] = "AT+CONA810871B48F5";

uint8_t CONNL[] = "AT+CONNL";

/* 블루투스 모듈 모드 설정 */
// BlueTooth Init
// Master
void BT_M_Init()
{  
  // BAUD
  HAL_UART_Transmit(&huart6, SET_BAUD, 8, 1000);
  HAL_Delay(100);
  
  // AT
  HAL_UART_Transmit(&huart6, AT, 2, 1000);
  HAL_Delay(100);  
  
  // MODE 0
  HAL_UART_Transmit(&huart6, SET_MODE, 8, 1000);
  HAL_Delay(100);
  
  // notp
  HAL_UART_Transmit(&huart6, NOTI, 8, 1000);
  HAL_Delay(300);
  
  // SET IMME1
  HAL_UART_Transmit(&huart6, SET_IMME1, 8, 1000);
  HAL_Delay(10);
  
  // SET ROLE1
  HAL_UART_Transmit(&huart6, SET_MASTER, 8, 1000);
  HAL_Delay(10);
  
  // SET_RESET
  HAL_UART_Transmit(&huart6, SET_RESET, 8, 1000);
  HAL_Delay(100);
  
  // SET START
  HAL_UART_Transmit(&huart6, BT_START1, 8, 1000);
  HAL_Delay(100);
  
  // QR_MAC
  HAL_UART_Transmit(&huart6, QR_MAC_ADDRESS, 8, 1000);
  HAL_Delay(100);
  
  // DISC
  HAL_UART_Transmit(&huart6, SET_SCAN, 8, 1000);
  HAL_Delay(100);
  
  // BT_CONNET()
  HAL_UART_Transmit(&huart6, CON_MAC2, 18, 1000);
  HAL_Delay(100);
}
//Slave
void BT_S_Init()
{
  // RENEW
  //HAL_UART_Transmit(&huart2, SET_RENEW, 8, 1000);
  HAL_Delay(1000);
  
  // BAUD
  HAL_UART_Transmit(&huart6, SET_BAUD, 8, 1000);
  HAL_Delay(100);
  
  // AT
  HAL_UART_Transmit(&huart6, AT, 2, 1000);
  HAL_Delay(100);
  
  // MODE 0
  HAL_UART_Transmit(&huart6, SET_MODE, 8, 1000);
  HAL_Delay(300);
  
  // notp
  HAL_UART_Transmit(&huart6, NOTI, 8, 1000);
  HAL_Delay(100);
  
  // SET IMME1
  HAL_UART_Transmit(&huart6, SET_IMME0, 8, 1000);
  HAL_Delay(10);
  
  // ROLE0 : SLAVE
  HAL_UART_Transmit(&huart6, SET_SLAVE, 8, 1000);
  HAL_Delay(10);
  
  // SET_RESET
  HAL_UART_Transmit(&huart6, SET_RESET, 8, 1000);
  HAL_Delay(10);
  
  // SET START
  //HAL_UART_Transmit(&huart6, BT_START1, 8, 1000);
  HAL_Delay(100);
  
  // DISC
  // HAL_UART_Transmit(&huart6, SET_SCAN, 8, 1000);
  HAL_Delay(100);
  
  // QR_MAC
  HAL_UART_Transmit(&huart6, QR_MAC_ADDRESS, 8, 1000);
  HAL_Delay(100);
}
