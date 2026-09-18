/*
 * EventQueue.c
 *
 *  Created on: 18 sep. 2026
 *      Author: nasra
 */


/*
 * eventQueue.c
 *
 *  Created on: 18 sep. 2026
 *      Author: nasra
 */


#include "eventQueue.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#define EVQ_SIZE 10

enum event evq[ EVQ_SIZE ];
int evq_count = 0;
int evq_front_ix = 0;
int evq_rear_ix = 0;
int ev_error = -99;
void evq_push_back(enum event e)
{
	//check if queue is full
	if(evq_count == EVQ_SIZE)
	{
		return;
	}
	//put event in queue
	evq[evq_rear_ix] = e;
	//increment rear
	if(evq_rear_ix == EVQ_SIZE - 1)
	{
		evq_rear_ix = 0;
	}
	else
	{
		evq_rear_ix++;
	}
	//increment event count
	evq_count++;
}
enum event evq_pop_front()
{
	// check if event queue is empty
	if(evq_count == 0)
	{
		return ev_none;
	}
	//get event at the front
	enum event e = evq[evq_front_ix];
	// if front is at the end den move it to the front
	if(evq_front_ix == EVQ_SIZE - 1)
	{
		evq_front_ix = 0;
	}
	//move front forward
	else
	{
		evq_front_ix++;
	}
	//decrease event
	evq_count--;
	//return event
	return e;
}
