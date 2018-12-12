//////////////////////////////////////////////////////////////////////
// CurrGen.cpp: implementation of the CCurrGen class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CurrGen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCurrGen::CCurrGen(CWnd* Cal, int Addr)
  :CGpibInstrument(Cal, Addr) {
}


CCurrGen::~CCurrGen() {
}


bool
CCurrGen::myConfigure(CString sConf) {
  return false;
}


bool
CCurrGen::myInit() {
  return false;
}


bool
CCurrGen::myDisconnect() {
  return false;
}


bool
CCurrGen::myConnect() {
  return false;
}


void
CCurrGen::SRQService(long, long, long, long, long FAR*) {
}


bool 
CCurrGen::ChangeCurrent(double dCurrent) {
  return false;
}
