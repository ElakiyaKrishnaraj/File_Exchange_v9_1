/*
 *
 *	This is a simple program that illustrates how to call the MATLAB
 *	Engine functions from NetSim C Code.
 *
 */
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "mat.h"
#include "mex.h"

char buf[100];
Engine *ep;
int status;
mxArray *h=NULL, *i=NULL, *j=NULL,*k=NULL;
mxArray *out;
double *result;
int test;

double fn_matlab_init()
{
	/*
	 * Start the MATLAB engine 
	 */
	if (!(ep = engOpen(NULL))) {
		MessageBox ((HWND)NULL, (LPCWSTR)"Can't start MATLAB engine", 
			(LPCWSTR) "MATLAB_Interface.c", MB_OK);
		exit(-1);
	}
	engEvalString(ep,"desktop");

	return 0;
}

double fn_netsim_matlab()
{

	//write your own implementation here

	int nakagami_shape=5,nakagami_scale=2;
	
	engPutVariable(ep,"h",h);
	sprintf(buf,"h=ProbDistUnivParam('nakagami',[%d %d])",nakagami_shape,nakagami_scale);
	status=engEvalString(ep,buf);
	 
	engPutVariable(ep,"i",i);
	sprintf(buf,"i=random(h,1)");
	
	status=engEvalString(ep,buf);
	out=engGetVariable(ep,"i");
	result=mxGetPr(out);

	return *result;
}

double fn_netsim_matlab_Finish()
{
	status=engEvalString(ep,"exit");
	return 0;
}

