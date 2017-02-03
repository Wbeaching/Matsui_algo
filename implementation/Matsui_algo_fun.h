#ifndef _MEMORY_H_
#define _MEMORY_H_

#define k 64			//key size
#define size 256		//state size
#define no_of_time 10	//How many number of colliding key pairs you need.

typedef unsigned char UC;

UC iSwap( UC *a,UC *b );
UC MaxcolStep( UC *Key5 );
void Print_key( UC *arr );
UC Search( UC Key1[] );
void key_generation();
void avg_time();

#endif
