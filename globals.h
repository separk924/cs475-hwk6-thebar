/*
 * globals.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int num_threads;	// number of customer threads
int now_serving;	// customer's ID who is being served

/*  semaphores  */
sem_t* bar_empty;
sem_t* customer_inside;
sem_t* bartender_available;
sem_t* customer_places_order;
sem_t* bartender_made_drink;
sem_t* customer_paid;
sem_t* bartender_confirms_payment;
sem_t* customer_leaves;

#endif /* GLOBALS_H_ */
