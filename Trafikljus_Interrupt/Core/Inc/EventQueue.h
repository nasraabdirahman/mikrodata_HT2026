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
	/* others go here */
	s_car_stop, //red
	s_car_standing_by, // Red Yellow
	s_people_walk, //green
	s_car_about_to_stop, //Yellow
	s_car_go, //greed
	s_people_stop, // red
	s_people_pushed_button
};

void evq_push_back(enum event e);
enum event evq_pop_front();

#endif /* INC_EVENTQUEUE_H_ */
