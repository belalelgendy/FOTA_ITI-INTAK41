

#ifndef PARSE_H_
#define PARSE_H_


#include "UART.h"


#define CODE_SIZE  350
#define FINAL_ARR_SIZE   256 //from array tool


void UART_Receive_Str (unsigned char* str);
void Parsing_Data(unsigned char* str,unsigned char *str_data);
void parsing_with_address(unsigned char* str,unsigned char *str_data,unsigned char *crc_recevied);

void char2num(unsigned char *str);
void num2hex(unsigned char *str,unsigned char*str_last,int size_str);

char crc_each_record(unsigned char*str_data , unsigned char* rece_crc);

void final_array_of_data(unsigned char *str,unsigned char *our_array);
void crc_final(unsigned char * str,unsigned char * data_add, unsigned char* rece_crc);


#endif 
