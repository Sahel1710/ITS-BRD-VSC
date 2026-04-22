/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "init.h"
#include "LCD_Touch.h"
#include "display.h"
#include "rpn.h"


extern void initDisplay(void);

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	initDisplay();
	
	TP_Init(false);

  runCalculator();
  
	return 0;
}
