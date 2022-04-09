/*
 * customer.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"

/**
 * This is what the thread will call.
 * Do not touch.
 */
void* customer(void* args)
{
	unsigned int *custID = (unsigned int*) args;
	custTravelToBar(*custID);
	custArriveAtBar(*custID);
	custPlaceOrder();
	custBrowseArt();
	custAtRegister();
	custLeaveBar();
	return NULL;
}


/**
 * Each customer takes a random amount of time between 20 ms and 5000 ms to travel to the bar.
 */
void custTravelToBar(unsigned int custID)
{
	srand(time(0));
	int num = rand() % 5000000 + 20000;
	usleep(num); // traveling to bar
	// synchronize
	printf("Cust %u\t\t\t\t\t\t\t\t\t\t\t|\n", custID);
}


/**
 * If there is already another customer in the bar the current customer has
 * to wait until bar is empty before entering.
 */
void custArriveAtBar(unsigned int custID)
{
	sem_wait(bar_empty);
	// synchronize
	now_serving = custID;
	printf("\t\tCust %u\t\t\t\t\t\t\t\t\t|\n", custID);
	sem_post(customer_inside);
}


/**
 * The customer in the bar places an order
 */
void custPlaceOrder()
{
	sem_wait(bartender_available);
	
	// synchronize
	printf("\t\t\t\tCust %u\t\t\t\t\t\t\t|\n", now_serving);
	sem_post(customer_places_order);
}


/**
 * The customer in the bar can browse the wall art for a random amount of time between 3ms and 4000ms.
 */
void custBrowseArt()
{
	printf("\t\t\t\t\t\tCust %u\t\t\t\t\t|\n", now_serving);
	// synchronize
	srand(time(0));
	int num = rand() % 4000000 + 3000;
	usleep(num); // browsing wall art
	sem_post(customer_browsing_art);
}


/**
 * If their drink is not ready by the time they are done admiring the art they must wait
 * until the bartender has finished. When the bartender is finished, the customer pays.
 *
 */
void custAtRegister()
{
	
	sem_wait(bartender_made_drink);
	// synchronize
	printf("\t\t\t\t\t\t\t\tCust %u\t\t\t|\n", now_serving);
	sem_post(customer_at_register);
	sem_wait(bartender_at_register);
	sem_post(customer_paid);
}


/**
 * The customer in the bar leaves the bar.
 */
void custLeaveBar()
{
	sem_wait(bartender_confirms_payment);

	// synchronize
	printf("\t\t\t\t\t\t\t\t\t\tCust %u\t|\n", now_serving);
	sem_post(bar_empty);
}
