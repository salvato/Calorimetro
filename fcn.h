#ifndef __FCN_H
#define __FCN_H
extern "C"
void __stdcall fcn(int* npar, double* g, double* f, double* par, int* iflag, void ( __stdcall* util)(void));
#endif