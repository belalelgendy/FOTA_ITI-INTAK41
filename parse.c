#include "parse.h"

void UART_Receive_Str (unsigned char* str)
{
	unsigned short i=0;
	str[i]=UART_Receive();


	for (i=0;str[i]!='*';)
	{
		i++;
		str[i]=UART_Receive();
	}

	str[i]='\0';
}
	/*						350			256		*/
void Parsing_Data(unsigned char* str,unsigned char *str_data)
{
	int i=0,j=0,k=0;
	for (i=0;str[i];i++)
	{
		if (str[i]==':')
		{

			if (str[i+8]=='1')
			{

				//crc_recevied[m]='\0';
				break;
			}

			if (str[i+8]=='0')
			{
				for (k=(i+9);k<(i+32+9);k++)
				{
					str_data[j]=str[k];
					j++;
				}
			}
		}
	}
	str_data[j]='\0';

}


void parsing_with_address(unsigned char* str,unsigned char *str_data,unsigned char *crc_recevied)
{
	int i=0,j=0,k=0,m=0;
	for (i=0;str[i];i++)
	{
		if (str[i]==':')
		{
			if (str[i+8]=='1' && str[i+7]=='0')
			{

				//str_data[j]='\0';
				//crc_recevied[m]='\0';
				break;
			}
			for (k=(i+1);k<(i+32+9);k++)
			{
				str_data[j]=str[k];
				j++;
			}
			crc_recevied[m]=str[k];
			crc_recevied[m+1]=str[k+1];
			m=m+2;
		}
	}
	str_data[j]='\0';
	crc_recevied[m]='\0';
}


void char2num(unsigned char *str)
{
	int i=0;
	for (i=0;str[i];i++)
	{
		if (str[i]>='A' && str[i]<='Z')
		{
			str[i]=(str[i]-'A')+10;
		}
		if (str[i]>='0' && str[i]<='9')
		{
			str[i]=str[i]-'0';
		}
	}


}

void num2hex(unsigned char *str,unsigned char *str_last,int size_str)
{
	int i=0,j=0;
	int num=0,rem=0;

	for (i=0;i<size_str;)
	{	
		str_last[j]=(str[i]*16)+str[i+1];
		j++;
		i=i+2;
	}
	str_last[j]='\0';
}

char crc_each_record(unsigned char*str_data , unsigned char* rece_crc)
{
	int i=0,j=0,k=0,t=20;
	long int crc_record_calc=0;
	int rec_crc_size=strlen(rece_crc);
	int str_data_size=strlen(str_data);

	unsigned char crc_in_hex[(rec_crc_size/2)];
	unsigned char data_in_hex[(str_data_size/2)];

	char2num(rece_crc);
	num2hex(rece_crc,crc_in_hex,rec_crc_size);

	char2num(str_data);
	num2hex(str_data,data_in_hex,str_data_size);

	for (j=0;j<=str_data_size/2;j++)
	{
		if (j==t)
		{       t=t+20;
		crc_record_calc=(~(crc_record_calc))+1;
		if (crc_record_calc=!crc_in_hex[k])
		{

			//jmp 0
			/*LCD_WriteString("wrong : ");
				LCD_WriteNumber(k+1);*/
			UART_Send('c');
			return 0;
		}
		k++;
		crc_record_calc=0;
		}
		crc_record_calc=crc_record_calc+data_in_hex[j];


	}
	return 1;
}

				/*		345-->350			128-->256				*/
void final_array_of_data(unsigned char *str,unsigned char *our_array)
{
	int temp_ch_size=0,finial_data_size=0,i=0;
	unsigned char temp_ch[FINAL_ARR_SIZE];
	Parsing_Data(str,temp_ch);
	temp_ch_size=strlen(temp_ch);
	finial_data_size=temp_ch_size/2;
	char2num(temp_ch);
	num2hex(temp_ch,our_array,temp_ch_size);


	//filling with 0xff
	for (i=finial_data_size+1;i<FINAL_ARR_SIZE;i++)
	{
		our_array[i]=0xff;
	}

}

void crc_final(unsigned char * str,unsigned char * data_add, unsigned char* rece_crc)
{
	char crc_check=0;
	parsing_with_address(str,data_add,rece_crc);

	crc_check=crc_each_record(data_add,rece_crc);

	if (crc_check==0)
	{
		UART_Send('a');

	}
	else if (crc_check==1)
	{
		UART_Send('b');
	}
}
