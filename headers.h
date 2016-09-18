/* $HOME/headers.h -- for general C programming */

#include "params.h"
#include "nrutil.h"
#include "nr.h"
#include <math.h>
double drand48();

#define	BUG  	if(debug)
#define	NOBUG	if(0)

#define	BP(A)	if(debug)printf("A=%d\t", A);
#define	BF(A)	if(debug)printf("A=%f\t", A);

#define	SQR(A)	((A)*(A))
#define	LIMITS(i,lo,hi)	{if((i)<(lo)){printf("limit");BP(i);DIE };if((i)>(hi)){printf("limit");BP(i);exit(1);}}
