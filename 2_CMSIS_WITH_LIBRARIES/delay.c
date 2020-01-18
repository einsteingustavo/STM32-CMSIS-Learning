#include "delay.h"

void delay(int time){
	int volatile delay;
	delay = 0;
		while(delay<time){
			
			 delay++;
			}
}
