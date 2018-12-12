// CpPoint.cpp: implementation of the CCpPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "CpPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCpPoint::CCpPoint(double _T, double _Cp) 
: CCbPoint(_T, _Cp) {
}

CCpPoint::~CCpPoint() {

}
