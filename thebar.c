/*
 * TheBar.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();

/**
 * Main function
 */
int main(int argc, char **argv)
{
	printBanner();
	init(); // initialize semaphores
	num_threads = atoi(argv[1]);

	pthread_t custThreads[num_threads];
	// fire off customer thread
	int i;
	for(i=0; i<num_threads;i++){
		pthread_create(&custThreads[i], NULL, customer, (void *)&i);
	}

	// fire off bartender thread
	pthread_t barThread;
	pthread_create(&barThread, NULL, bartender, NULL);

	// wait for all threads to finish
	for(i=0; i<num_threads;i++){ // joining customer threads
		pthread_join(custThreads[i], NULL);
	}
	pthread_join(barThread, NULL); // joining bartender thread

	cleanup(); // cleanup and destroy semaphores
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner()
{
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init()
{
	// unlink semaphores
	sem_unlink("/bar_empty");
	sem_unlink("/customer_inside");
	sem_unlink("/bartender_available");
	sem_unlink("/customer_places_order");
	sem_unlink("/bartender_made_drink");
	sem_unlink("/customer_paid");
	sem_unlink("/bartender_confirms_payment");
	sem_unlink("/customer_leaves");
	sem_unlink("/customer_browsing_art");
	sem_unlink("/customer_at_register");
	sem_unlink("/bartender_at_register");


	// create semaphores
	bar_empty = sem_open("/bar_empty", O_CREAT, 0600, 1);
	customer_inside = sem_open("/customer_outside", O_CREAT, 0600, 0);
	bartender_available = sem_open("/bartender_available", O_CREAT, 0600, 0);
	customer_places_order = sem_open("/customer_places_order", O_CREAT, 0600, 0);
	bartender_made_drink = sem_open("/bartender_made_drink", O_CREAT, 0600, 0);
	customer_paid = sem_open("/customer_paid", O_CREAT, 0600, 0);
	bartender_confirms_payment = sem_open("/bartender_confirms_payment", O_CREAT, 0600, 0);
	customer_leaves = sem_open("/customer_leaves", O_CREAT, 0600, 0);
	customer_browsing_art = sem_open("/customer_browsing_art", O_CREAT, 0600, 0);
	customer_at_register = sem_open("/customer_at_register", O_CREAT, 0600, 0);
	bartender_at_register = sem_open("/bartender_at_register", O_CREAT, 0600, 0);
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{
	// close semaphores
	sem_close(bar_empty);
	sem_close(customer_inside);
	sem_close(bartender_available);
	sem_close(customer_places_order);
	sem_close(bartender_made_drink);
	sem_close(customer_paid);
	sem_close(bartender_confirms_payment);
	sem_close(customer_leaves);
	sem_close(customer_browsing_art);
	sem_close(customer_at_register);
	sem_close(bartender_at_register);
}
