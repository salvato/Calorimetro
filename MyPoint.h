// MyPoint.h: interface for the CMyPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPOINT_H__2CCA07D3_BAE2_11D4_88DD_00801E0328BA__INCLUDED_)
#define AFX_MYPOINT_H__2CCA07D3_BAE2_11D4_88DD_00801E0328BA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMyPoint  
{
public:
	double x;
	double y;
	CMyPoint(double, double);
	CMyPoint();
	virtual ~CMyPoint();

};

#endif // !defined(AFX_MYPOINT_H__2CCA07D3_BAE2_11D4_88DD_00801E0328BA__INCLUDED_)
