// MyPoint.cpp: implementation of the CMyPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMyPoint::CMyPoint(double newx=0.0, double newy=0.0) :
  x(newx), y(newy) {
}


 CMyPoint::CMyPoint() :
  x(0.0), y(0.0) {
}

CMyPoint::~CMyPoint() {
}
