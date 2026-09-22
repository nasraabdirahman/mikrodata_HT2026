/*
 * EventQueue.h
 *
 *  Created on: 18 sep. 2026
 *      Author: nasra
 */

#ifndef INC_EVENTQUEUE_H_
#define INC_EVENTQUEUE_H_

enum event
{
	ev_none,
	ev_button_push,
	ev_state_timeout
};

enum state
 {
	 s_init,
	 s_people_walk,
	 s_car_standing_by,
	 s_people_stop,
	 s_car_go,
	 s_pushed_wait,
	 s_car_is_stopping,
	 s_car_stop,
	 /* others go here */
 };
void evq_push_back(enum event e);
enum event evq_pop_front();

#endif /* INC_EVENTQUEUE_H_ */
