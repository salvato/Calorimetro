#if !defined(AFX_PULSERDLG_H__BD512B8A_E4E7_11D6_9B26_00801E0328BA__INCLUDED_)
#define AFX_PULSERDLG_H__BD512B8A_E4E7_11D6_9B26_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// PulserDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#include <afxtempl.h>
class CPulser;

/////////////////////////////////////////////////////////////////////////////
// CPulserDlg dialog
/////////////////////////////////////////////////////////////////////////////

class 
CPulserDlg : public CPropertyPage {
	DECLARE_DYNCREATE(CPulserDlg)

// Construction
public:
	double GetCurrent();
	void SetDevice(CPulser* pmyPulser);
	CPulserDlg();
	~CPulserDlg();

// Dialog Data
	//{{AFX_DATA(CPulserDlg)
	enum { IDD = IDD_PULSER };
	CComboBox	m_CurrVals;
	double	m_Delay;
	double	m_Width;
	int		m_CurSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPulserDlg)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPulserDlg)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCurrents();
	afx_msg void OnChangeDelay();
	afx_msg void OnChangeWidth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CPulser* pPulser;
  CArray<double, double> tValues;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PULSERDLG_H__BD512B8A_E4E7_11D6_9B26_00801E0328BA__INCLUDED_)
