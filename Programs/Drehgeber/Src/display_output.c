/**
* @file display_output.c
* @author Mihai Dicusar
* @date Dec 2025
* @brief This module is used to display the angle and the angular velocity,
*		 as well as the text for start screen.
*/

#include <stdio.h>
#include "lcd.h"
#include <string.h>
#include "display_output.h"

char bufAngle[20] = "";
char bufVelocity[20] = "";
char lastBufAngle[20] = "";
char lastBufVelocity[20] = "";

int last_done = 0;
int current_done = 0;

void display_init()
{
    lcdGotoXY(ANGLE_TEXT_POS_X, ANGLE_TEXT_POS_Y);
	lcdPrintlnS("Angle:            ");
	lcdGotoXY(ANGLE_NR_POS_X, ANGLE_NR_POS_Y);
	lcdPrintS("0.00");
	lcdGotoXY(DEG_POS_X, DEG_POS_Y);
	lcdPrintS("DEG");

	lcdGotoXY(ANG_VEL_TEXT_POS_X, ANG_VEL_TEXT_POS_Y);
	lcdPrintlnS("Angular velocity: ");
	lcdGotoXY(ANG_VEL_NR_POS_X, ANG_VEL_NR_POS_Y);
	lcdPrintS("0.00");
	lcdGotoXY(DEG_S_POS_X, DEG_S_POX_Y);
	lcdPrintS("DEG/S");
}

void display_angle(double angle)
{
	sprintf(bufAngle, "%-6.2f", angle);

	int angleMaxLen = (strlen(bufAngle) > strlen(lastBufAngle)) ? strlen(bufAngle) : strlen(lastBufAngle);
	for (int i = 0; i < angleMaxLen; i++)
	{
		char current_char = (i < strlen(bufAngle)) ? bufAngle[i] : ' ';

		if (lastBufAngle[i] != current_char)
		{
			lcdGotoXY(ANGLE_NR_POS_X + i, ANGLE_NR_POS_Y);
			lcdPrintC(current_char);
			lastBufAngle[i] = current_char;
		}
	}
}

void display_velocity(double velocity)
{
    sprintf(bufVelocity, "%-6.2f", velocity);

	int velocityMaxLen = (strlen(bufVelocity) > strlen(lastBufVelocity)) ? strlen(bufVelocity) : strlen(lastBufVelocity);
	for (int i = 0; i < velocityMaxLen; i++)
	{
		char current_char = (i < strlen(bufVelocity)) ? bufVelocity[i] : ' ';

		if (lastBufVelocity[i] != current_char)
		{
			lcdGotoXY(ANG_VEL_NR_POS_X + i, ANG_VEL_NR_POS_Y);
			lcdPrintC(current_char);
			lastBufVelocity[i] = current_char;
		}
	}
}