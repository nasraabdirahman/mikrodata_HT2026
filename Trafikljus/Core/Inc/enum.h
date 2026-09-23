/*
 * enum.h
 *
 *  Created on: 17 sep. 2026
 *      Author: nasra
 */

#ifndef INC_ENUM_H_
#define INC_ENUM_H_


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
#endif /* INC_ENUM_H_ */

void evq_push_back(enum event e);
enum event evq_pop_front();
