/* my GA program #1 */
#include "headers.h"

unsigned char **p; /* the whole population lives here */
int	*fitness;
int MAX_HERO;
int fitness_evals = 0;
int	individual_length;
int trial, hero;
int	random_int();
/*===========================================================*/
main( argc, argv ) int argc; char **argv;
{
	void tournament();
	int who, c1, c2, p1, p2;

	params( argc, argv );
	init();

	for( who = 0; who < POP_SIZE; who++ ) {
			fitness[who] = fv(who);
	}
	printf( "End of initial population. . . . Now evolve!\n" );

	for( trial = 0; trial < LOOPS; trial++ ) {

		tournament( tournament_size, &p1, &c1 );
		tournament( tournament_size, &p2, &c2 );

		if( hero >= MAX_HERO ) {
			printf( "Maximum hero goal reached: %d\n", hero );
			break;
		}
		make_children( p1, p2, c1, c2 );
		if( MUT_RATE > 0.0 ) {
			mutate( c1 );
			mutate( c2 );
		}
		fitness[c1] = fv(c1);
		fitness[c2] = fv(c2);
	}
	printf( "\t\t\tStopped after %d fitness evaluations. Hero = %d\n",
		fitness_evals, hero );
	exit( 0 );
}
/*===========================================================*/
void tournament( size, winner, loser )
int *winner, *loser;
{
	int i;
	int winfit = -99999, losefit = 99999;

	for( i = 0; i < size; i++ ) {
		int j = random_int( POP_SIZE );;
		if( fitness[j] > winfit ) {
			winfit = fitness[j];
			*winner = j;
		}
		if( fitness[j] < losefit ) {
			losefit = fitness[j];
			*loser = j;
		}
	}
}
/*===========================================================*/
init()
{
	int i, j;

	srand48( seed );
	hero = 0;
	individual_length = N;

	p = unchar_matrix( 0, POP_SIZE-1, 0, individual_length - 1 );
	fitness = ivector( 0, POP_SIZE-1 );

	switch( problem_number) {
	case 1:
		MAX_HERO = N; /* for problem #1 */
		break;
	case 2:
		MAX_HERO = N/2;  /* for problem #2 */
		break;
	case 3:
		MAX_HERO = N/2;  /* for problem #3 */
		break;
	default:
		printf( "What problem? problem number = %d\n", problem_number );
		exit( 1 );
	}

	for( i = 0; i < POP_SIZE; i++ ) {
		for( j = 0; j < individual_length; j++ ) {
			p[i][j] = random_int( 2 );
		}
	}
}
/*================================================================*/
/* fitness value of individual who */
/* Baby problem #1: sum the bits   */
/* Baby problem #2: want col agreement on Mx2 array */
/* Baby problem #3: want row agreement on 2xM array */

int fv( who ) int who;
{
	int	i;
	int	the_fitness = 0;

	fitness_evals++;

	/* problem_number	should be 1, 2, or 3 */
	switch( problem_number) {

	case 1:
		for( i = 0; i < N; i++ ) the_fitness += p[who][i];
		break;

	case 2:
		for( i = 0; i < N; i+=2 )
			the_fitness += (p[who][i] == p[who][i+1]);
		break;

	case 3:
		for( i = 0; i < N/2; i++ )
			the_fitness += (p[who][i] == p[who][i+N/2]);
		break;

	default:
		printf( "What problem? problem number = %d\n", problem_number );
		exit( 1 );
	}


	if( print_every_fitness )
		printf( "%4d fitness: %d\n", fitness_evals, the_fitness );

	if( the_fitness > hero ) {
		hero = the_fitness;
		if( print_every_hero )
			printf( "New hero %4d %d %6.2f%%\n",
			    fitness_evals, the_fitness,
			    100.0*(float)the_fitness/MAX_HERO );
	}

	return( the_fitness );
}
/*================================================================*/
/*  Two individuals, with subscripts p1 and p2, share genetic       */
/*  material, two children are produced, and the two children       */
/*  have subscripts c1 and c2.                                      */

make_children( p1, p2, c1, c2 )
int p1, p2, c1, c2;
{
	int i, left, right;

	if( uniform ) {
		for( i = 0; i < individual_length; i++ ) {
			if( random_int(2) ) {
				p[c1][i] = p[p1][i]; p[c2][i] = p[p2][i];
			} else {
				p[c1][i] = p[p2][i]; p[c2][i] = p[p1][i];
			}
		}
	} else if( two_point ) {

		left = random_int( individual_length -1 );
		right = left + 1 + random_int( individual_length - left - 1 );

		BUG {
			printf( "Cut points: 0 <= %d < %d <= %d\n",
				left, right, individual_length-1 );
		}

		for( i = 0; i <= left; i++ ) {
			p[c1][i] = p[p1][i]; p[c2][i] = p[p2][i];
		}

		for( i = left+1; i <= right; i++ ) {
			p[c1][i] = p[p2][i]; p[c2][i] = p[p1][i];
		}
		for( i = right+1; i < individual_length; i++ ) {
			p[c1][i] = p[p1][i]; p[c2][i] = p[p2][i];
		}
	} else if( one_point ) {

		left = random_int( individual_length );

		BUG {
			printf( "Cut points: 0 <= %d <= %d\n",
				left, individual_length-1 );
		}

		for( i = 0; i <= left; i++ ) {
			p[c1][i] = p[p1][i]; p[c2][i] = p[p2][i];
		}
		for( i = left+1; i < individual_length; i++ ) {
			p[c1][i] = p[p2][i]; p[c2][i] = p[p1][i];
		}
	} else {
		printf( "Which child-maker?\n" );
		exit( 1 );
	}
}
/*================================================================*/
#if 0
mutate( who ) int who;
{
	int k, j;

	if( totally_random ) {
		for( j = 0; j < N; j++ ) {
			p[who][j] = random_int( 2 );

		}
	} else {
		for( j = 0; j < mut_count; j++ ) {
			k = random_int(individual_length);
			p[who][k] = ( drand48() < 0.5 ) ? 1 : 0;
		}
	}
}
#endif
/*=================================================================*/
/* returns integer in range 0 <= r < n  */
int random_int( n ) int n;
{ return( (int) ( n * drand48() ) ); }
/*=================================================================*/
mutate( who ) int who;
{
        int j;

        for( j = 0; j < individual_length; j++ ) {
                if( drand48() < MUT_RATE ) {
                        p[who][j] = random_int( 2 );
                }
        }
}
/*=================================================================*/
