//////////////////////////////////////////////////////////////////////
// CalibPoint.h: interface for the CCalibPoint class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALIBPOINT_H__693C16C1_BEEA_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_CALIBPOINT_H__693C16C1_BEEA_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class 
CCalibPoint {
public:
	double Tg;
	double Rb;
	double sTg;
	double sRb;
	CCalibPoint(double new_Tg=0.0, double new_Rb=0.0, double new_sTg=0.0, double new_sRb=0.0);
	virtual ~CCalibPoint();
};

#endif // !defined(AFX_CALIBPOINT_H__693C16C1_BEEA_11D8_9B27_00801E0328BA__INCLUDED_)
