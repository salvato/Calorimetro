// CbPoint.h: interface for the CCbPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBPOINT_H__B1121B22_CB47_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_CBPOINT_H__B1121B22_CB47_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class 
CCbPoint {
public:
	CCbPoint(double T=0.0, double Cb=0.0);
	virtual ~CCbPoint();
  double T, C;
};

#endif // !defined(AFX_CBPOINT_H__B1121B22_CB47_11D8_9B27_00801E0328BA__INCLUDED_)
