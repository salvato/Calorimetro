//////////////////////////////////////////////////////////////////////
// CalibPoint.cpp: implementation of the CCalibPoint class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CalibPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCalibPoint::CCalibPoint(double new_Tg, double new_Rb, double new_sTg, double new_sRb) 
: Tg(new_Tg), Rb(new_Rb), sTg(new_sTg), sRb(new_sRb){
}

CCalibPoint::~CCalibPoint() {

}

