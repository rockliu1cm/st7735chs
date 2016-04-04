/*
 * Lcd128xyColor.cpp
 *
 *  Created on: 2016��4��3��
 *      Author: rock
 */

#include "Lcd128xyColor.h"
#include <avr/pgmspace.h>
#include "font.h"
#include "SPI.h"
#include  "SD.h"

Lcd128xyColor::Lcd128xyColor(int sd, int cs, int reset, int a0) {
	this->_sd = sd;
	this->_cs = cs;
	this->_a0 = a0;
	this->_reset = reset;

//	pinMode(_sd, OUTPUT);
	pinMode(_cs, OUTPUT);
	pinMode(_a0, OUTPUT);
	pinMode(_reset, OUTPUT);
	this->BACK_COLOR = WHITE;
	this->POINT_COLOR = BLACK;
}
void Lcd128xyColor::setColor(u16 bgc, u16 fc) {
	this->BACK_COLOR = bgc;
	this->POINT_COLOR = fc;
}
void Lcd128xyColor::setBackgroundColor(u16 bgc) {
	this->BACK_COLOR = bgc;
}
void Lcd128xyColor::setFrontColor(u16 fc) {
	this->POINT_COLOR = fc;
}
void Lcd128xyColor::init(u16 bgc, u16 fc) {
	this->setColor(bgc, fc);

	//digitalWrite(_sd, 1);
	SPI.begin();
	SD.begin(_sd);
//	digitalWrite(_sd, 0);

	digitalWrite(_cs, 1);
	digitalWrite(_reset, 1);
	delay(5);
	digitalWrite(_reset, 0);
	delay(5);
	digitalWrite(_reset, 1);
	digitalWrite(_cs, 1);
	delay(5);
	digitalWrite(_cs, 0);

	writeReg(0x11); //Sleep out
	delay(120); //Delay 120ms
	//------------------------------------ST7735S Frame Rate-----------------------------------------//
	writeReg(0xB1);
	write8bit(0x05);

	writeReg(0x11);		//Sleep exit
	delay(120);

	//ST7735R Frame Rate
	writeReg(0xB1);
	write8bit(0x01);

	write8bit(0x2C);
	write8bit(0x2D);
	writeReg(0xB2);
	write8bit(0x01);
	write8bit(0x2C);
	write8bit(0x2D);
	writeReg(0xB3);
	write8bit(0x01);
	write8bit(0x2C);
	write8bit(0x2D);
	write8bit(0x01);
	write8bit(0x2C);
	write8bit(0x2D);

	writeReg(0xB4); //Column inversion
	write8bit(0x07);

	//ST7735R Power Sequence
	writeReg(0xC0);
	write8bit(0xA2);
	write8bit(0x02);
	write8bit(0x84);
	writeReg(0xC1);
	write8bit(0xC5);
	writeReg(0xC2);
	write8bit(0x0A);
	write8bit(0x00);
	writeReg(0xC3);
	write8bit(0x8A);
	write8bit(0x2A);
	writeReg(0xC4);
	write8bit(0x8A);
	write8bit(0xEE);

	writeReg(0xC5); //VCOM
	write8bit(0x0E);

	writeReg(0x36); //MX, MY, RGB mode
	write8bit(0xC8);

	//ST7735R Gamma Sequence
	writeReg(0xe0);
	write8bit(0x0f);
	write8bit(0x1a);
	write8bit(0x0f);
	write8bit(0x18);
	write8bit(0x2f);
	write8bit(0x28);
	write8bit(0x20);
	write8bit(0x22);
	write8bit(0x1f);
	write8bit(0x1b);
	write8bit(0x23);
	write8bit(0x37);
	write8bit(0x00);

	write8bit(0x07);
	write8bit(0x02);
	write8bit(0x10);
	writeReg(0xe1);
	write8bit(0x0f);
	write8bit(0x1b);
	write8bit(0x0f);
	write8bit(0x17);
	write8bit(0x33);
	write8bit(0x2c);
	write8bit(0x29);
	write8bit(0x2e);
	write8bit(0x30);
	write8bit(0x30);
	write8bit(0x39);
	write8bit(0x3f);
	write8bit(0x00);
	write8bit(0x07);
	write8bit(0x03);
	write8bit(0x10);

	writeReg(0x2a);
	write8bit(0x00);
	write8bit(0x00);
	write8bit(0x00);
	write8bit(0x7f);
	writeReg(0x2b);
	write8bit(0x00);
	write8bit(0x00);
	write8bit(0x00);
	write8bit(0x9f);
	//Enable test command
	writeReg(0xF0);
	write8bit(0x01);
	//Disable ram power save mode
	writeReg(0xF6);
	write8bit(0x00);

	// ����Ϊ3�ߴ���ģʽ��ֻ�ܶ�ȡ���ߵ�����65kɫrgb=565ģʽ
	writeReg(0x3A);
	write8bit(0x05);
	// ��ʾ��
	writeReg(0x29);
	digitalWrite(_cs, 1);
}
void Lcd128xyColor::clear() {
	digitalWrite(_cs, 0);
	//	u8 VH, VL;
	u16 i, j;
	//	VH = this->BACK_COLOR >> 8;
	//	VL = this->BACK_COLOR;
	address_set(0, 0, 127, 127);
	for (i = 0; i < 128; i++) {
		for (j = 0; j < 128; j++) {
			write16bit(BACK_COLOR);
		}
	}
	digitalWrite(_cs, 1);
}

void Lcd128xyColor::drawPoint(u8 x, u8 y) {
	digitalWrite(_cs, 0);
	_drawPoint(x, y);
	digitalWrite(_cs, 1);
}
void Lcd128xyColor::drawCircle(u8 x0, u8 y0, u8 r) {
	digitalWrite(_cs, 0);
	int a, b;
	int di;
	a = 0;
	b = r;
	di = 3 - (r << 1);             //�ж��¸���λ�õı�־
	while (a <= b) {
		_drawPoint(x0 - b, y0 - a);             //3
		_drawPoint(x0 + b, y0 - a);             //0
		_drawPoint(x0 - a, y0 + b);             //1
		_drawPoint(x0 - b, y0 - a);             //7
		_drawPoint(x0 - a, y0 - b);             //2
		_drawPoint(x0 + b, y0 + a);             //4
		_drawPoint(x0 + a, y0 - b);             //5
		_drawPoint(x0 + a, y0 + b);             //6
		_drawPoint(x0 - b, y0 + a);
		a++;
		//ʹ��Bresenham�㷨��Բ
		if (di < 0)
			di += 4 * a + 6;
		else {
			di += 10 + 4 * (a - b);
			b--;
		}
		_drawPoint(x0 + a, y0 + b);
	}
	digitalWrite(_cs, 1);
}
void Lcd128xyColor::drawLine(u8 x1, u8 y1, u8 x2, u8 y2) {
	digitalWrite(_cs, 0);
	u16 t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;

	delta_x = x2 - x1; //������������
	delta_y = y2 - y1;
	uRow = x1;
	uCol = y1;
	if (delta_x > 0)
		incx = 1; //���õ�������
	else if (delta_x == 0)
		incx = 0; //��ֱ��
	else {
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0; //ˮƽ��
	else {
		incy = -1;
		delta_y = -delta_y;
	}
	if (delta_x > delta_y)
		distance = delta_x; //ѡȡ��������������
	else
		distance = delta_y;
	for (t = 0; t <= distance + 1; t++) //�������
			{
		_drawPoint(uRow, uCol); //����
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance) {
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance) {
			yerr -= distance;
			uCol += incy;
		}
	}
	digitalWrite(_cs, 1);
}
void Lcd128xyColor::drawRectangle(u8 x1, u8 y1, u8 x2, u8 y2) {
	drawLine(x1, y1, x2, y1);
	drawLine(x1, y1, x1, y2);
	drawLine(x1, y2, x2, y2);
	drawLine(x2, y1, x2, y2);
}
void Lcd128xyColor::drawImage(u8 x, u8 y, u8 width, u8 height, const u8 *img) {
	digitalWrite(_cs, 0);
	address_set(x, y, x + width - 1, y + height - 1); //�������ã������±��0��ʼ�����Կ��Ҫ����-1
	for (int i = 0; i < width * height; i++) {
		//������ɫ����,һ����ɫ��2�ֽڣ�����������pgm_read_word����ȡ16λ
		write16bit(pgm_read_word(&img[i * 2]));
	}
	digitalWrite(_cs, 1);
}
void Lcd128xyColor::printChar(u8 x, u8 y, u8 num, u8 mode) {
	digitalWrite(_cs, 0);
	_showChar(x, y, num, mode);
	digitalWrite(_cs, 1);
}
// ��ʾ�ֿ��ļ�
int Lcd128xyColor::print(u8 x, u8 y, char* px) {
	u8 *p=(u8*)px;
	u32 qm = 0L, wm = 0L;
	u32 idx = 0;
	u8 font[32];
	Serial.println("printing...");
	while (*p != '\0') {
		// �ȸ����ַ��ж����<A1��ASCii
		Serial.println(*p, HEX);
		if (*p < 0xA1) {
			digitalWrite(_cs, 0);
			//asc
			_showChar(x, y, *p, 0);
			cursor(&x, &y, 8);
			digitalWrite(_cs, 1);
		} else {
			digitalWrite(_cs, 1);
			// ����Gb2312-80�ı������ÿ��������94���֣���һ�ֽ������룬(������-A1)x94xÿ���ֵ���ռ�ֽ�������ǰ��16x16��С��32�ֽڣ�
//	��ôÿ���ֵ���ģδ֪����(����-A1)x94x32+�ڶ��ֽ�λ��-A1
			qm = *p;
//			qm = qm & 0xFF;
			p++;
			wm = *p; //& 0xff;
			idx = (qm - 0xA1) * 0xBC0;
			idx += ((wm - 0xA1) * 32);
			Serial.print("index = ");
			Serial.println(idx, HEX);
			// ���������SD���ж�ȡ��ģ���ݵ�������
			// SD���ɶ�
			digitalWrite(_sd, 0);
			File f = SD.open("CHS16.FON", FILE_READ);
			if (f) {
				f.seek(idx);
				f.readBytes(font, 32);
				f.close();
			} else {
				// �����SD������
				digitalWrite(_sd, 1);
				return 100;
			}
			digitalWrite(_sd, 1);
			// ����Һ������׼��д����
			digitalWrite(_cs, 0);
			address_set(x, y, x + 15, y + 15); //������ʾ����
			// 4��tile0,8,16,24��ÿ��64bit��8�ֽ�
			for (int i = 0; i < 32; i++) {
				// ÿ�ֽڰ�λ���
				for (int b = 7; b >= 0; b--) {
					if (bitRead(font[i], b))
						write16bit(POINT_COLOR);
					else
						write16bit(BACK_COLOR);
				}
			}
			digitalWrite(_cs, 1);
			cursor(&x, &y, 16);
		}
		p++;
	}
//	Serial.println("display done.");
	digitalWrite(_cs, 1);
	return 0;
}
void Lcd128xyColor::cursor(u8* x, u8* y, u8 width) {
	u8 xx = *x, yy = *y;
	if (xx + width >= 128) {
		*x = 0;
		if (yy + 16 >= 128) {
			*y = 0;
		} else
			*y += 16;
	} else {
		*x += width;
	}
}
//  --------------------------------------------------------------------------------------------------------------
// private method
void Lcd128xyColor::_showChar(u8 x, u8 y, u8 num, u8 mode) {
	u8 temp;
	u8 pos, t;
	u16 x0 = x;
	u16 colortemp = POINT_COLOR;

	//���ô���
	num = num - ' ';      //�õ�ƫ�ƺ��ֵ
	address_set(x, y, x + 8 - 1, y + 16 - 1);      //���ù��λ��

	if (!mode) //�ǵ��ӷ�ʽ
	{
		for (pos = 0; pos < 16; pos++) {
			temp = pgm_read_byte(&asc2_1608[(u16 ) num * 16 + pos]); //����1608����
			for (t = 0; t < 8; t++) {
				if (temp & 0x01)
					POINT_COLOR = colortemp;
				else
					POINT_COLOR = BACK_COLOR;
				write16bit(POINT_COLOR);
				temp >>= 1;
				x++;
			}
			x = x0;
			y++;
		}
	} else		 //���ӷ�ʽ
	{
		for (pos = 0; pos < 16; pos++) {
			temp = pgm_read_byte(&asc2_1608[(u16 ) num * 16 + pos]);//����1608����
			for (t = 0; t < 8; t++) {
				if (temp & 0x01)
					_drawPoint(x + t, y + pos);		 //��һ����
				temp >>= 1;
			}
		}
	}
	POINT_COLOR = colortemp;
}
void Lcd128xyColor::_drawPoint(u8 x, u8 y) {
	address_set(x, y, x, y); //���ù��λ��
	write16bit(POINT_COLOR);
}
u8 Lcd128xyColor::offsetX(u8 x) {
	return x % 128;
}
u8 Lcd128xyColor::offsetY(u8 y) {
	return (y % 128) + 32;
}
void Lcd128xyColor::address_set(u16 x1, u16 y1, u16 x2, u16 y2) {
	writeReg(0x2a);
	write16bit(this->offsetX(x1));
	write16bit(this->offsetX(x2));

	writeReg(0x2b);
	// ������ƫ������
	write16bit(this->offsetY(y1));
	write16bit(this->offsetY(y2));

	writeReg(0x2C);
}
void Lcd128xyColor::write8bit(u8 da) {
	digitalWrite(_a0, 1);
	SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
	//  shiftOut(_sda, _sck, MSBFIRST, da);
	SPI.transfer(da);
	SPI.endTransaction();
}
void Lcd128xyColor::write16bit(u16 da) {
	digitalWrite(_a0, 1);
	SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
	//  shiftOut(_sda, _sck, MSBFIRST, da >> 8);
	//  shiftOut(_sda, _sck, MSBFIRST, da);
	SPI.transfer(da >> 8);
	SPI.transfer(da);
	SPI.endTransaction();
}
void Lcd128xyColor::writeReg(u8 da) {
	digitalWrite(_a0, 0);
	//  shiftOut(_sda, _sck, MSBFIRST, da);
	SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
	//  shiftOut(_sda, _sck, MSBFIRST, da);
	SPI.transfer(da);
	SPI.endTransaction();
}
