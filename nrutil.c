/* nrutil.c -- from Numerical Recipes */
#include <malloc.h>
#include <stdio.h>
#include "headers.h"

void nrerror(error_text)
char error_text[];
{
	fprintf(stderr,"Numerical Recipes run-time error...\n");
	fprintf(stderr,"%s\n",error_text);
	fprintf(stderr,"...now exiting to system...\n");
	exit(1);
}

unsigned char *ucvector(nl,nh)
int nl,nh;
{
	unsigned char *v;

	v = (unsigned char *)malloc((unsigned) (nh-nl+1)*sizeof(unsigned char));
	if (!v) nrerror("allocation failure in ucvector()");
	return v-nl;
}

char *cvector(nl,nh)
int nl,nh;
{
	char *v;

	v = (char *)malloc((unsigned) (nh-nl+1)*sizeof(char));
	if (!v) nrerror("allocation failure in cvector()");
	return v-nl;
}

float *vector(nl,nh)
int nl,nh;
{
	float *v;

	v=(float *)malloc((unsigned) (nh-nl+1)*sizeof(float));
	if (!v) nrerror("allocation failure in vector()");
	return v-nl;
}

int *ivector(nl,nh)
int nl,nh;
{
	int *v;

	v=(int *)malloc((unsigned) (nh-nl+1)*sizeof(int));
	if (!v) nrerror("allocation failure in ivector()");
	return v-nl;
}

short int *sivector(nl,nh)
int nl,nh;
{
	short int *v;

	v=(short int *)malloc((unsigned) (nh-nl+1)*sizeof(short int));
	if (!v) nrerror("allocation failure in sivector()");
	return v-nl;
}

double *dvector(nl,nh)
int nl,nh;
{
	double *v;

	v=(double *)malloc((unsigned) (nh-nl+1)*sizeof(double));
	if (!v) nrerror("allocation failure in dvector()");
	return v-nl;
}

char **cmatrix(nrl,nrh,ncl,nch) int nrl,nrh,ncl,nch;
{
	int i; 
	char **m;

	m=(char **) malloc((unsigned) (nrh-nrl+1)*sizeof(char*));
	if (!m) nrerror("allocation failure 1 in cmatrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(char *) malloc((unsigned) (nch-ncl+1)*sizeof(char));
		if (!m[i]) nrerror("allocation failure 2 in cmatrix()");
		m[i] -= ncl;
	}
	return m;
}

float **matrix(nrl,nrh,ncl,nch) int nrl,nrh,ncl,nch;
{
	int i; 
	float **m;

	m=(float **) malloc((unsigned) (nrh-nrl+1)*sizeof(float*));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(float *) malloc((unsigned) (nch-ncl+1)*sizeof(float));
		if (!m[i]) nrerror("allocation failure 2 in matrix()");
		m[i] -= ncl;
	}
	return m;
}

double **dmatrix(nrl,nrh,ncl,nch) int nrl,nrh,ncl,nch;
{
	int i; 
	double **m;

	m=(double **) malloc((unsigned) (nrh-nrl+1)*sizeof(double*));
	if (!m) nrerror("allocation failure 1 in dmatrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(double *) malloc((unsigned) (nch-ncl+1)*sizeof(double));
		if (!m[i]) nrerror("allocation failure 2 in dmatrix()");
		m[i] -= ncl;
	}
	return m;
}

short int **simatrix(nrl,nrh,ncl,nch)
int nrl,nrh,ncl,nch;
{
	int i;
	short int **m;

	m=(short int **)malloc((unsigned) (nrh-nrl+1)*sizeof(short int*));
	if (!m) nrerror("allocation failure 1 in simatrix()");
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(short int *)malloc((unsigned) (nch-ncl+1)*sizeof(short int));
		if (!m[i]) nrerror("allocation failure 2 in simatrix()");
		m[i] -= ncl;
	}
	return m;
}

unsigned char **unchar_matrix( nrl, nrh, ncl, nch )
int nrl, nrh, ncl, nch;
{
	int i;
	unsigned char *tmp, **m;

	m = (unsigned char **) calloc( nrh - nrl + 1, sizeof(unsigned char*) );
	if( !m ) nrerror( "allocation failure 1 in unchar_matrix()" );
	m -= nrl;

	for( i=nrl; i<=nrh; i++ ) {
		tmp = (unsigned char *) calloc( nch - ncl + 1, sizeof(unsigned char) );
		if( ! tmp ) nrerror( "allocation failure 2 in imatrix()" );
		m[i] = tmp - ncl;
	}
	return m;
}

int **imatrix( nrl, nrh, ncl, nch )
int nrl, nrh, ncl, nch;
{
	int i, *tmp, **m;

	m = (int **) calloc( nrh - nrl + 1, sizeof(int*) );
	if( !m ) nrerror( "allocation failure 1 in imatrix()" );
	m -= nrl;

	for( i=nrl; i<=nrh; i++ ) {
		tmp = (int *) calloc( nch - ncl + 1, sizeof(int) );
		if( ! tmp ) nrerror( "allocation failure 2 in imatrix()" );
		m[i] = tmp - ncl;
	}
	return m;
}

float **submatrix(a,oldrl,oldrh,oldcl,oldch,newrl,newcl)
float **a;
int oldrl,oldrh,oldcl,oldch,newrl,newcl;
{
	int i,j;
	float **m;

	m=(float **) malloc((unsigned) (oldrh-oldrl+1)*sizeof(float*));
	if (!m) nrerror("allocation failure in submatrix()");
	m -= newrl;

	for(i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j]=a[i]+oldcl-newcl;

	return m;
}

void free_vector(v,nl,nh)
float *v;
int nl,nh;
{
	free((char*) (v+nl));
}

void free_ivector(v,nl,nh)
int *v,nl,nh;
{
	free((char*) (v+nl));
}

void free_sivector(v,nl,nh)
short int *v; int nl,nh;
{
	free((char*) (v+nl));
}

void free_dvector(v,nl,nh)
double *v;
int nl,nh;
{
	free((char*) (v+nl));
}

void free_cmatrix(m,nrl,nrh,ncl,nch)
char **m;
int nrl,nrh,ncl,nch;
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

void free_matrix(m,nrl,nrh,ncl,nch)
float **m;
int nrl,nrh,ncl,nch;
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

void free_dmatrix(m,nrl,nrh,ncl,nch)
double **m;
int nrl,nrh,ncl,nch;
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

void free_simatrix(m,nrl,nrh,ncl,nch)
short int **m;
int nrl,nrh,ncl,nch;
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

void free_imatrix(m,nrl,nrh,ncl,nch)
int **m;
int nrl,nrh,ncl,nch;
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

void free_submatrix(b,nrl,nrh,ncl,nch)
float **b;
int nrl,nrh,ncl,nch;
{
	free((char*) (b+nrl));
}

float **convert_matrix(a,nrl,nrh,ncl,nch)
float *a;
int nrl,nrh,ncl,nch;
{
	int i,j,nrow,ncol;
	float **m;

	nrow=nrh-nrl+1;
	ncol=nch-ncl+1;
	m = (float **) malloc((unsigned) (nrow)*sizeof(float*));
	if (!m) nrerror("allocation failure in convert_matrix()");
	m -= nrl;
	for(i=0,j=nrl;i<=nrow-1;i++,j++) m[j]=a+ncol*i-ncl;
	return m;
}

void free_convert_matrix(b,nrl,nrh,ncl,nch)
float **b;
int nrl,nrh,ncl,nch;
{
	free((char*) (b+nrl));
}

