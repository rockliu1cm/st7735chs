/*
 * Lcd128xyColor.h
 *
 *  Created on: 2016年4月3日
 *      Author: rock
 */

#ifndef LCD128XYCOLOR_H_
#define LCD128XYCOLOR_H_

#include <USBAPI.h>

typedef unsigned char u8;
//typedef unsigned int u16;
typedef unsigned long u32;
//定义LCD的尺寸
#define LCD_W 128
#define LCD_H 160

//画笔颜色
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
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色

#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

/**
 * 1.44寸SPI液晶模块
 * IC = ST7735
 * BUS = SPI
 */
class Lcd128xyColor {
public:
	/**
	 *对象构建，确认引脚
	 */
//    Lcd128xyColor(int cs, int reset, int a0, int sda, int sck);
	Lcd128xyColor(int sd, int cs, int reset, int a0);
	// 设置前景色和背景色
	void setColor(u16 bgc, u16 fc);
	//	设置背景色
	void setBackgroundColor(u16 bgc);
	//	设置前景色
	void setFrontColor(u16 fc);
	//	屏幕初始化
	void init(u16 bgc, u16 fc);
	//	清屏
	void clear();
	//画点
	void drawPoint(u8 x, u8 y);
	// 画圈
	void drawCircle(u8 x, u8 y, u8 r);
	//	画线
	void drawLine(u8 x1, u8 y1, u8 x2, u8 y2);
	//	画方块
	void drawRectangle(u8 x1, u8 y1, u8 x2, u8 y2);
	//	画图
	void drawImage(u8 x, u8 y, u8 width, u8 height, const u8 *img);
	//	显示字符
	void printChar(u8 x, u8 y, u8 num, u8 mode);
	// 显示根据SD卡中字库文件转换而成的中文GB2312的16x16字模，同时支持8x16的内部ASCII字库
	int print(u8, u8, char *);

private:
	//	由于IC地址是128x160的，而屏幕是128x128的，在y轴上会有128x32像素是看不到的，所以需做一个偏移量，即所有的y轴地址要+32才行否则会偏或者看不到哦
	u8 offsetX(u8 x);
	u8 offsetY(u8 y);
	void cursor(u8* x, u8* y, u8 width);
	void _showChar(u8 x, u8 y, u8 num, u8 mode);
	void _drawPoint(u8 x, u8 y);
	//	地址位置范围设置
	void address_set(u16 x1, u16 y1, u16 x2, u16 y2);
	//	传输1字节
	void write8bit(u8 da);
	//	传输2字节
	void write16bit(u16 da);
	//	设置寄存器
	void writeReg(u8 da);
	//	u32 mypow(u8 m, u8 n);
	int _sd;
	int _cs;
	int _reset;
	int _a0;
//    int _sda;
//    int _sck;
	u16 BACK_COLOR, POINT_COLOR;   //背景色，画笔色
};

#endif /* LCD128XYCOLOR_H_ */
