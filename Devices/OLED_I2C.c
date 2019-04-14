/************************************************************************************
Ӳ��IIC
*************************************************************************************/

//��ϸ���ܿɲο���
//http://www.eeworld.com.cn/mcu/article_2018041538734.html

#include "OLED_I2C.h"
#include "delay.h"
#include <stm32f10x.h>
#include "codetab.h"
#include "myiic.h"



void I2C_Configuration(void)
{
	IIC_Init();
	
	
//	I2C_InitTypeDef  I2C_InitStructure;
//	GPIO_InitTypeDef  GPIO_InitStructure; 

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

//	/*STM32F103C8T6оƬ��Ӳ��I2C: PB6 -- SCL; PB7 -- SDA */
//	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//I2C���뿪©���
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	I2C_DeInit(I2C1);//ʹ��I2C1
//	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;	//����ΪIICģʽ
//	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;//����IICռ�ձȣII2C fast mode Tlow/Thigh = 2�
//	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//������I2C��ַ,���д��
//	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//ʹ��ASK�ź�
//	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//ָ��7λ��ַ
//	I2C_InitStructure.I2C_ClockSpeed = 400000;//400K��ʱ��Ƶ�ʣ�����С�ڵ���400KHz

//	I2C_Cmd(I2C1, ENABLE);
//	I2C_Init(I2C1, &I2C_InitStructure);
}

void I2C_WriteByte(uint8_t addr,uint8_t data)
{


//	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
//	
//	I2C_GenerateSTART(I2C1, ENABLE);//����I2C1
//	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

//	I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);//������ַ -- Ĭ��0x78
//	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

//	I2C_SendData(I2C1, addr);//�Ĵ�����ַ
//	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

//	I2C_SendData(I2C1, data);//��������
//	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
//	
//	I2C_GenerateSTOP(I2C1, ENABLE);//�ر�I2C1����
}




void WriteCmd(unsigned char I2C_Command)//д����
{
	IIC_Start();
    IIC_Send_Byte(OLED_ADDRESS);//OLED��ַ
    IIC_Ack();
    IIC_Send_Byte(0x00);//�Ĵ�����ַ
    IIC_Ack();
    IIC_Send_Byte(I2C_Command);
    IIC_Ack();
    IIC_Stop();
	
	//I2C_WriteByte(0x00, I2C_Command);
}

void WriteDat(unsigned char I2C_Data)//д����
{
	IIC_Start();
    IIC_Send_Byte(OLED_ADDRESS);//OLED��ַ
    IIC_Ack();
    IIC_Send_Byte(0x40);//�Ĵ�����ַ
    IIC_Ack();
    IIC_Send_Byte(I2C_Data);
    IIC_Ack();
    IIC_Stop();
	//I2C_WriteByte(0x40, I2C_Data);
}

void OLED_Init(void)
{
	DelayMs(100); //�������ʱ����Ҫ
	
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //���ȵ��� 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
	
}

void OLED_SetPos(unsigned char x, unsigned char y) //������ʼ�����꣬��ȷ��x/2*2 y
{ 
	WriteCmd(0xb0+y);
	WriteCmd(((x&0xf0)>>4)|0x10);
	WriteCmd((x&0x0f)|0x00);  //ԭ���ǣ�WriteCmd((x&0x0f)|0x01);������
}

//void OLED_SetPos_Curr(unsigned char x, unsigned char y) //������ʼ������,��ȷ��xy
//{ 
//	WriteCmd(0xb0+y);
//	WriteCmd(((x&0xf0)>>4)|0x10);
//	WriteCmd((x&0x0f)|0x00);
//}


void OLED_Fill(unsigned char fill_Data)//ȫ�����
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		WriteCmd(0xb0+m);		//page0-page1
		WriteCmd(0x00);		//low column start address
		WriteCmd(0x10);		//high column start address
		for(n=0;n<128;n++)
		{
			WriteDat(fill_Data);
		}
	}
}

void OLED_CLS(void)//����
{
	OLED_Fill(0x00);
}

void OLED_CLE_part()
{
	//�����Ļ
	unsigned char m,n;
	for(m=2;m<8;m++)
	{
		WriteCmd(0xb0+m);	//page0-page1
//		WriteCmd(0x00);		//low column start address
//		WriteCmd(0x10);		//high column start address
		
		WriteCmd(((0&0xf0)>>4)|0x10);
		WriteCmd((0&0x0f)|0x00);  //ԭ���ǣ�WriteCmd((x&0x0f)|0x01);������
		for(n=0;n<128;n++)
		{
			WriteDat(0x00);
		}
	}	
}


//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED�������л���
//--------------------------------------------------------------
void OLED_ON(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X14);  //������ɱ�
	WriteCmd(0XAF);  //OLED����
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : ��OLED���� -- ����ģʽ��,OLED���Ĳ���10uA
//--------------------------------------------------------------
void OLED_OFF(void)
{
	WriteCmd(0X8D);  //���õ�ɱ�
	WriteCmd(0X10);  //�رյ�ɱ�
	WriteCmd(0XAE);  //OLED����
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- ��ʼ������(x:0~127, y:0~7); ch[] -- Ҫ��ʾ���ַ���; TextSize -- �ַ���С(1:6*8 ; 2:8*16)
// Description    : ��ʾcodetab.h�е�ASCII�ַ�,��6*8��8*16��ѡ��
//--------------------------------------------------------------
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize, unsigned char flag)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
				{
					if (flag == 0)
						WriteDat(F6x8[c][i]);
					else
						WriteDat(~F6x8[c][i]);
				}
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
				{
					if (flag == 0)
						WriteDat(F8X16[c*16+i]);
					else 
						WriteDat(~F8X16[c*16+i]);
				}
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
				{
					if (flag == 0)
						WriteDat(F8X16[c*16+i+8]);
					else
						WriteDat(~F8X16[c*16+i+8]);
				}
				x += 8;
				j++;
			}
		}break;
	}
}

//��ʾָ�����е��ַ���
void OLED_ShowStr_xix(unsigned char x, unsigned char y, unsigned char ch[], unsigned char num, unsigned char TextSize, unsigned char flag)
{
	unsigned char c = 0,i = 0,j = 0;
	
	switch(TextSize)
	{
		case 1:
		{
			while(j < num)
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<6;i++)
				{
					if (flag == 0)
						WriteDat(F6x8[c][i]);
					else
						WriteDat(~F6x8[c][i]);
				}
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(j < num)
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(x,y);
				for(i=0;i<8;i++)
				{
					if (flag == 0)
						WriteDat(F8X16[c*16+i]);
					else 
						WriteDat(~F8X16[c*16+i]);
				}
				OLED_SetPos(x,y+1);
				for(i=0;i<8;i++)
				{
					if (flag == 0)
						WriteDat(F8X16[c*16+i+8]);
					else
						WriteDat(~F8X16[c*16+i+8]);
				}
				x += 8;
				j++;
			}
		}break;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- ��ʼ������(x0:0~127, y0:0~7); x1,y1 -- ���Խ���(������)������(x1:1~128,y1:1~8)
// Description    : ��ʾBMPλͼ
//--------------------------------------------------------------
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[], unsigned char flag)
{
	unsigned int j=0;
	unsigned char x,y;

	if(y1%8==0)
		y = y1/8;
	else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
		for(x=x0;x<x1;x++)
		{
			if (flag == 0)
				WriteDat(BMP[j++]);
			else
				WriteDat(~BMP[j++]);
		}
	}
}

void OLED_DrawSpace(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1)
{
	unsigned char x,y;

	if(y1%8==0)
		y = y1/8;
	else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(x0,y);
		for(x=x0;x<x1;x++)
		{
			WriteDat(0x00);
		}
	}	
}


/****************************/
//��ʾ��ص���
void battery_show(unsigned char grade)
{
	int k = 0;
	
	for (k = 126 - grade * 6; k < 126; k += 6)
	{
		OLED_SetPos(k, 0);
		WriteDat(0xfa); //1111 0101 ��->��
		WriteDat(0xfa);
		WriteDat(0xfa);
		OLED_SetPos(k, 1);
		WriteDat(0x5f);	//1010 ffff ��->��
		WriteDat(0x5f);
		WriteDat(0x5f);
	}
}

//x:80-127
//y:4-7
void gif_show(unsigned char i)
{
	switch(i)
	{
		case 0: OLED_DrawBMP(80, 2, 128, 8, (unsigned char *)BMP_gif1, 0); break;
		case 1: OLED_DrawBMP(80, 2, 128, 8, (unsigned char *)BMP_gif2, 0); break;
		case 2: OLED_DrawBMP(80, 2, 128, 8, (unsigned char *)BMP_gif3, 0); break;
		case 3: OLED_DrawBMP(80, 2, 128, 8, (unsigned char *)BMP_gif4, 0); break;
		case 4: OLED_DrawSpace(80, 2, 128, 8); break;
		default: break;
	}
}
