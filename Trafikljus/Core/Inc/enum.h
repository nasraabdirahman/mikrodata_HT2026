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
	//this state is when B1 is pushed
	s_car_go,
	/* others go here */
	s_car_drive, //greed
	s_car_about_to_drive, // red yellow
	s_car_stopped, //red
	s_people_walk,
	s_people_stop
};
#endif /* INC_ENUM_H_ */
