/*
 * Lcd128xyColor.h
 *
 *  Created on: 2016��4��3��
 *      Author: rock
 */

#ifndef LCD128XYCOLOR_H_
#define LCD128XYCOLOR_H_

#include <USBAPI.h>

typedef unsigned char u8;
//typedef unsigned int u16;
typedef unsigned long u32;
//����LCD�ĳߴ�
#define LCD_W 128
#define LCD_H 160

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ

#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

/**
 * 1.44��SPIҺ��ģ��
 * IC = ST7735
 * BUS = SPI
 */
class Lcd128xyColor {
public:
	/**
	 *���󹹽���ȷ������
	 */
//    Lcd128xyColor(int cs, int reset, int a0, int sda, int sck);
	Lcd128xyColor(int sd, int cs, int reset, int a0);
	// ����ǰ��ɫ�ͱ���ɫ
	void setColor(u16 bgc, u16 fc);
	//	���ñ���ɫ
	void setBackgroundColor(u16 bgc);
	//	����ǰ��ɫ
	void setFrontColor(u16 fc);
	//	��Ļ��ʼ��
	void init(u16 bgc, u16 fc);
	//	����
	void clear();
	//����
	void drawPoint(u8 x, u8 y);
	// ��Ȧ
	void drawCircle(u8 x, u8 y, u8 r);
	//	����
	void drawLine(u8 x1, u8 y1, u8 x2, u8 y2);
	//	������
	void drawRectangle(u8 x1, u8 y1, u8 x2, u8 y2);
	//	��ͼ
	void drawImage(u8 x, u8 y, u8 width, u8 height, const u8 *img);
	//	��ʾ�ַ�
	void printChar(u8 x, u8 y, u8 num, u8 mode);
	// ��ʾ����SD�����ֿ��ļ�ת�����ɵ�����GB2312��16x16��ģ��ͬʱ֧��8x16���ڲ�ASCII�ֿ�
	int print(u8, u8, char *);

private:
	//	����IC��ַ��128x160�ģ�����Ļ��128x128�ģ���y���ϻ���128x32�����ǿ������ģ���������һ��ƫ�����������е�y���ַҪ+32���з����ƫ���߿�����Ŷ
	u8 offsetX(u8 x);
	u8 offsetY(u8 y);
	void cursor(u8* x, u8* y, u8 width);
	void _showChar(u8 x, u8 y, u8 num, u8 mode);
	void _drawPoint(u8 x, u8 y);
	//	��ַλ�÷�Χ����
	void address_set(u16 x1, u16 y1, u16 x2, u16 y2);
	//	����1�ֽ�
	void write8bit(u8 da);
	//	����2�ֽ�
	void write16bit(u16 da);
	//	���üĴ���
	void writeReg(u8 da);
	//	u32 mypow(u8 m, u8 n);
	int _sd;
	int _cs;
	int _reset;
	int _a0;
//    int _sda;
//    int _sck;
	u16 BACK_COLOR, POINT_COLOR;   //����ɫ������ɫ
};

#endif /* LCD128XYCOLOR_H_ */
