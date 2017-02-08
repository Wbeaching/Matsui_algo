#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include "Matsui_algo_fun.h"

UC N, d, b;
UC Statevector1[size];

UC iSwap( UC *a,UC *b )
{
	UC temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

UC MaxcolStep( UC *Key5 )
{
	UC  l, j1 = 0, m = 0, p, t, flag = 0, flag1 = 0;
	short i;
	
	for( i = 0 ; i < size ; i++ )
		Statevector1[i] = i;

	p = d+(N-1)*k;
	for( i = 0 ; i < p ; i++ )
	{
		j1 = ( j1 + Statevector1[i] + Key5[i%k] ) % size ;
		l++;
		t = d+m*k;
		if( i == t && i < p )
		{
			if( flag == 0 )
			{
				if( (j1 != d) )
					return i; 
				flag = 1;
			}
			else if( i < p-k )
			{
				if( ( j1 != t+k) )
					return i; 
			}
			else
			{
				if( j1 != t+k - 1 )
					return i; 
			}
		}
		else if( i < p-2 )
		{
			if( i < d )
			{
				if( ( j1 == d || j1 == d+1) )
					return i; 
			}
			else if( i == d+1 )
			{
				if( j1 != d+k )
					return i; 
			}
			else if( i < d+k )
			{
				if( j1 == d+k || j1 == d)
					return i; 
			}
			else if( i < p-k )
			{
				if( j1 == t+k || j1 == d )
					return i; 
			}
			else
			{
				if( j1 == t+k-1 || j1 == d)
					return i; 
			}
		}
		
		else
		{
			if( i == ( p-2 ) )
			{
				if( j1 != d )
					return i; 
			}
			
			else if( i == ( p-1 ) )
			{
				if( j1 != ( p-1 ) )
					return i; 
			}
		}
		if( i > d+k-2 )
		{
			if( flag1 == 0 )
			{
				m = 1;
				l = -1;
			}
			flag1 = 1;
			if( l == k-1 )
			{
				m++;
				l = -1;
			}
		}
		iSwap( &Statevector1[i] , &Statevector1[j1] );
	}
	return 255;
}

void Print_key( UC *arr )
{
	short k1;
	
	printf("keys are::\n");
	printf("\n");
	for( k1 = 0 ; k1 < k ; k1++ )
		printf("%d ,",arr[k1]);
	printf("\n");
}


UC Search( UC Key1[] )
{
	UC Key3[ k ], S , MaxS = 0 , temp = 0 , x ,y, C;
	short i , j;
	
	S = MaxcolStep( Key1 );
	if( S == 255 )
	{
		printf("b = %d\n", b);
		++b;
		//printf("Colliding pair::\n");
		//Print_key(Key1);
		return 1;
	}
	
	MaxS = S;
	for( i = 0 ; i < k ; i++ )
	{
			for( j = 1 ; j <= size ; j++ )
			{
				if( ( (i%k) == d-1 ) || ( (i%k) == d ) || ( ( i %k ) == d+1 ) )
					break;
					
				Key1[i%k] = ( Key1[i%k] + 1 + 256)%256;
				Key1[(i+1)%k] = ( Key1[(i+1)%k] - 1 + 256 )%256;
				
				temp = MaxcolStep( Key1 );

				if( temp > MaxS )
					MaxS = temp;
			}
	}
	
	if( MaxS <= S )
		return 0;

	C = 0;
	for(i = 0; i < k; ++i)
		Key3[i] = Key1[i];
		
	for(i = 0 ; i < k ; i++)
	{
		for(j = 1; j <= size ; j++)
		{
			if( ( (i%k) == d ) || ( (i%k) == d ) || ( ( i %k ) == d+1 ) )
					break;
					
			Key3[i%k] = ( Key3[i%k] + 1 + 256)%256;
			Key3[(i+1)%k] = ( Key3[(i+1)%k] - 1 + 256 )%256;
			temp = MaxcolStep( Key3 );
			if(temp == MaxS)
			{
				Search( Key3 );
				 C++;
				 if(C == N)
				 	return 0;
			}
		}
	}
	return 0;
}


void key_generation()
{
	UC i , j, q; 
	UC Key1[ k ], Key2[ k ];
	
	srand(time(NULL));
	while(1)
	{
		for( i = 0 ; i < k ; i++ )
			Key1[ i ] = rand() % size;
			
		Key1[d+1] = k-d-1;
		b = 0;
		Search( Key1 );
		if(b >= 1)
			break;
			
		//printf("Generate new key:\n\n");
	}
	return;		
}

void Number_of_round()
{
	d = k-3;
	if( ( size % k ) == 0 )
		N = size/k;
	else
		N = ( size + k - d -1 )/k;
	printf("Matsui no_of_time = %d N = %d k = %d\n", no_of_time, N, k);
}

void avg_time()
{
	short i, count = 0;
	double time = 0;
	
	for(i = 0; i < no_of_time; ++i)
	{
		clock_t tic = clock();
		key_generation();
		clock_t toc = clock();
		time = time+(double)(toc - tic) / (CLOCKS_PER_SEC);
		count = count+b;
		printf("no_of_time = %d  count = %d\n", i, count);
	}
	printf("AVG TIME: %f seconds\n", time/count);
}
