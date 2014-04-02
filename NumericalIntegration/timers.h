
// vim: ai:si:ts=2:st=2:sw=2:tw=0:nobk:nowrap:noic:nocp
// timers.h [c] piotao, @venona, @maon, somewhen in 201002
// 20100925 - refactoring, used for cgm measurements
// 20110307 - given as an example of time measurement for students at ZONKG
// this lib is for time measurements, by independent timers
// time is measured in seconds with high precision.
/* simple usage:

	 pTimer zegar = newTimer(); // make new timer
   ...
	 startTimer(zegar); // store first timestamp
	 // some long taking actions
	 stopTimer(zegar);  // store second timestamp
	 printTimer(zegar); // show time difference
	 freeTimer(zegar);  // free occupied ram
*/

#ifndef TIMERS_H_
#define TIMERS_H_

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "defs.h"

#define TIMER_SCALE 1000000000

typedef struct timespec TimeSpec;
typedef TimeSpec* pTimeSpec;

// simple timer for keeping time records in multiple instances
typedef struct Timer {
	TimeSpec start; // starting time
	TimeSpec end;   // stopping time
	long int time;  // period time (calculated during stop)
} Timer;

// pointer to Timer structure for passing by in functions
typedef Timer* pTimer;

// create new, 0-filled timer structure
pTimer newTimer() {
	pTimer pT = (pTimer) malloc(sizeof(Timer));
	memset(pT, 0, sizeof(Timer));
	return pT;
}

// free timer memory
void freeTimer(pTimer pT) {
	if (pT) free(pT);
}

// launch timer by storing time in its starting register
void startTimer(pTimer pT) {
	if (pT) clock_gettime(CLOCK_MONOTONIC, &(pT->start));
}

// set any used timer to 0-state
void resetTimer(pTimer pT) {
	if (pT) memset(pT, 0, sizeof(Timer));
}

// calculate time difference between two given times
long int timespecDiff(pTimeSpec A, pTimeSpec B) {
	return ((A->tv_sec * TIMER_SCALE) + A->tv_nsec) - ((B->tv_sec * TIMER_SCALE) + B->tv_nsec);
}

// launch time measure by storing current time in ending register
// then calculate time period since start time and add to overall time
void stopTimer(pTimer pT) {
	if (pT) {
		clock_gettime(CLOCK_MONOTONIC, &(pT->end));
		pT->time += timespecDiff(&(pT->end), &(pT->start));
	}
}

// return real time as a double value
double getTime(pTimer pT){
	if(pT){
		return (double) pT->time / (double) TIMER_SCALE;
	}
	else{
		return -1.0;
	}
}

// print time in seconds, using scientific format
void printTimer(pTimer pT) {
	if (pT) printf("%e", getTime(pT));
	else printf("NULL");
}

// print time in seconds, using given format
void printTimerFmt(const char* fmt, pTimer pT) {
	if (pT) printf(fmt, getTime(pT));
	else printf("NULL");
}

/*
char* formatTimer(const char *fmt, pTimer pT){
	char* string = (char*) malloc(128);  // due to this limitation, here can an overflow occur if buffer too small
	if(pT){
		int len = 0;
		len = sprintf(string, fmt, getTime(pT));
		if(len <= 0) sprintf(string,"Error: %i chars returned from sprintf",len);
		return string;
	}
	else{
		strcpy(string,"NULL");
		return string;
	}
}
*/
#endif /* timers.h */
