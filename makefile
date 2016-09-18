# Makefile for ga

CFLAGS	= -O -L/usr1/lib -I/usr1/include
LIBS	= -lm

INC	= nr.h nrutil.h params.h headers.h

MYOBJS = 	ga.o nrutil.o params.o

ga: $(MYOBJS) $(INC)
	cc $(CFLAGS) -o $@ $(MYOBJS) $(LIBS)

$(MYOBJS): $(INC)

params.h params.c:	params.d
	./make-params

clean:
	rm -f $(MYOBJS)
	rm -f ga params.[ch] mon.out core ,*
