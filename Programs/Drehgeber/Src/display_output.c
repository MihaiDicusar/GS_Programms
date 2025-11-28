#include <stdio.h>
#include "lcd.h"
#include <string.h>

char bufAngle[20] = "";
char bufVelocity[20] = "";
char lastBufAngle[20] = "";
char lastBufVelocity[20] = "";

int last_done = 0;
int current_done = 0;

void display_init()
{
    lcdGotoXY(1, 1);
	lcdPrintlnS("Angle: ");
	lcdGotoXY(1, 3);
	lcdPrintlnS("Angular velocity: ");
}

char resetBufAngle()
{
    bufAngle[0] = '\0';
}

char resetBufVelocity()
{
    bufVelocity[0] = '\0';
}

void display_angle(double angle)
{
	sprintf(bufAngle, "%-5.2f", angle);

	last_done = 0;
	current_done = 0;

	int angleMaxLen = (strlen(bufAngle) > strlen(lastBufAngle)) ? strlen(bufAngle) : strlen(lastBufAngle);
	for (int i = 0; i < angleMaxLen; i++)
	{
		char last_char = lastBufAngle[i];
		char current_char = bufAngle[i];

		if (last_char == '\0') {last_done = 1;}
		if (current_char == '\0') {current_done = 1;}

    	if (last_done && current_done)
		{
			lastBufAngle[i] = '\0';
			break;
		}

		if (last_char != current_char)
		{
			lcdGotoXY(8 + i, 1);
			char print_char = (current_done) ? ' ' : current_char;
			lcdPrintC(print_char);
			lastBufAngle[i] = current_char;
		}
	}
}

void display_velocity(double velocity)
{
    sprintf(bufVelocity, "%-5.2f", velocity);

    last_done = 0;
	current_done = 0;

	int velocityMaxLen = (strlen(bufVelocity) > strlen(lastBufVelocity)) ? strlen(bufVelocity) : strlen(lastBufVelocity);
	for (int i = 0; i < velocityMaxLen; i++)
	{
		char last_char = lastBufVelocity[i];
		char current_char = bufVelocity[i];

		if (last_char == '\0') {last_done = 1;}
		if (current_char == '\0') {current_done = 1;}

		if (last_done && current_done)
		{
			lastBufVelocity[i] = '\0';
			break;
		}

		if (last_char != current_char)
		{
			lcdGotoXY(19 + i, 3);
			char print_char = (current_done) ? ' ' : current_char;
			lcdPrintC(print_char);
			lastBufVelocity[i] = current_char;
		}
	}
}