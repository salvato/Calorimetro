// CpPoint.h: interface for the CCpPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPPOINT_H__61B08481_CB75_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_CPPOINT_H__61B08481_CB75_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CbPoint.h"

class CCpPoint : public CCbPoint  
{
public:
	CCpPoint(double T=0.0, double Cp=0.0);
	virtual ~CCpPoint();

};

#endif // !defined(AFX_CPPOINT_H__61B08481_CB75_11D8_9B27_00801E0328BA__INCLUDED_)
