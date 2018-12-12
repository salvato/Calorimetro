#if !defined(AFX_READINGS_H__D08402C1_DAD4_11D2_88DD_444553540000__INCLUDED_)
#define AFX_READINGS_H__D08402C1_DAD4_11D2_88DD_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Readings.h : header file
//
class CBitmap;

/////////////////////////////////////////////////////////////////////////////
// CReadings window

class CReadings : public CWnd
{
// Construction
public:
	CReadings(CString Title="Readings");

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReadings)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	void NewValue(CString value);
	void NewValue(double value);
	void NewValue(float value);
	void NewValue(int value);
	virtual ~CReadings();

	// Generated message map functions
protected:
	//{{AFX_MSG(CReadings)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CStatic* pBkgnd;
	CBitmap* pMyBitmap;
	CEdit* pValue;
	CRect myRect;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READINGS_H__D08402C1_DAD4_11D2_88DD_444553540000__INCLUDED_)
