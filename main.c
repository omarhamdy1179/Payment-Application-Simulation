/*
 * main.c
 *
 *  Created on: Oct 25, 2022
 *      Author: omar hamdii
 */

#include "Application/Application.h"

void main ()
{
	setvbuf (stdout, NULL, _IONBF, 0);
	setvbuf (stderr, NULL, _IONBF, 0);
	appStart() ;
}
