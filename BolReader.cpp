// BolReader.cpp: implementation of the CBolReader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "BolReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBolReader::CBolReader(CWnd* Cal, int Addr)
  :CGpibInstrument(Cal, Addr) {
}


CBolReader::~CBolReader() {

}


bool  
CBolReader::ChangeScale(int iScale) {
  return false;
}


bool
CBolReader::ChangeDigits(int iDigits) {
  return false;
}


bool
CBolReader::ChangePlc(int iPlc) {
  return false;
}


bool
CBolReader::ChangeAutoZero(int iAutoZero) {
  return false;
}


bool
CBolReader::myConfigure(CString sConf) {
  return false;
}


bool
CBolReader::myInit() {
  return false;
}


bool
CBolReader::myDisconnect() {
  return false;
}


bool
CBolReader::myConnect() {
  return false;
}


void
CBolReader::SRQService(long, long, long, long, long FAR*) {

}


bool
CBolReader::StartRun() {
  return false;
}


bool
CBolReader::StopRun() {
	return false;
}
