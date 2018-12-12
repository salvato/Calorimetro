// CbPoint.cpp: implementation of the CCbPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "CbPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCbPoint::CCbPoint(double _T, double _Cb)
: T(_T), C(_Cb) {
  
}

CCbPoint::~CCbPoint() {

}
