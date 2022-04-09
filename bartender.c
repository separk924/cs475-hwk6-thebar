/*
 * bartender.c
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
#include "bartender.h"

/**
 * Code for bartender thread.
 * Do not touch.
 */
void* bartender(void* args)
{
	int i;
	for (i = 0; i<num_threads; i++)
	{
		waitForCustomer();
		makeDrink();
		receivePayment();
	}
	return NULL;
}

/**
 * Waits in a closet until a customer enters.
 */
void waitForCustomer()
{
	sem_wait(customer_inside);
	// synchronize
	printf("\t\t\t\t\t\t\t\t\t\t\t| Bartender\n");
	sem_post(bartender_available);
}


/**
 * When a customer places an order it takes the Bartender
 * a random amount of time between 5 ms and 1000 ms to make the drink.
 */
void makeDrink()
{
	sem_wait(customer_places_order);
	// synchronize
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\tBartender\n");
	srand(time(0));
	int num = rand() % 1000000 + 5000;
	usleep(num); // bartender making drink
	sem_post(bartender_made_drink); // signals that drink was made
}


/**
 * Gets payment from the correct customer
 */
void receivePayment()
{
	// synchronize
	// at the register waiting for customer to pay
	sem_wait(customer_at_register);
	sem_wait(customer_browsing_art);
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\tBartender\n");
	sem_post(bartender_at_register);
	sem_wait(customer_paid);
	//got the payment from the right customer!
	printf("\t\t\t\t\t\t\t\t\t\t\t| \t\t\t\t\t\tBartender\n");
	sem_post(bartender_confirms_payment);
}
