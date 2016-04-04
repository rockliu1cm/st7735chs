#include "SD.h"
#include "SPI.h"
#include "font.h"
#include "Lcd128xyColor.h"

// pin setting
const int SDCS = 4;
const int LCDCS = 5;
const int LCDRST = 6;
const int LCDEN = 7;
// inctence LCD
Lcd128xyColor lcd(SDCS, LCDCS, LCDRST, LCDEN);

char x[] =  "asdf老刘的程序，就是要这么写。";

void setup() {

	Serial.begin(9600);
	Serial.println("start....");
	lcd.init(WHITE, BLACK);
	lcd.clear();
	lcd.drawLine(0, 0, 255, 255);
	lcd.drawImage(50, 50, 40, 40, image);

	Serial.println(lcd.print(0, 0,x));
	lcd.setFrontColor(RED);
	lcd.drawLine(127, 0, 0, 127);

}

void loop() {

}
