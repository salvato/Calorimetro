/////////////////////////////////////////////////////////////////////////////
// LakeShoreSetDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAKESHORESETDLG_H__BE208BA1_C109_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_LAKESHORESETDLG_H__BE208BA1_C109_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTempController;

/////////////////////////////////////////////////////////////////////////////
// CLakeShoreSetDlg dialog
/////////////////////////////////////////////////////////////////////////////

class 
CLakeShoreSetDlg : public CPropertyPage {
	DECLARE_DYNCREATE(CLakeShoreSetDlg)

// Construction
public:
	CLakeShoreSetDlg();
	~CLakeShoreSetDlg();

// Dialog Data
	//{{AFX_DATA(CLakeShoreSetDlg)
	enum { IDD = IDD_LAKESHORE_370 };
	CString	SetPoint;
	int		iHeater;
	CString	sDVal;
	CString	sIVal;
	CString	sPVal;
	int		iSensCurr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLakeShoreSetDlg)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	double GetSetPoint();
	void SetDevice(CTempController* pTempCtrl);

protected:
	// Generated message map functions
	//{{AFX_MSG(CLakeShoreSetDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSetp();
	afx_msg void OnEditchangeHeater();
	afx_msg void OnSelchangeHeater();
	afx_msg void OnChangeEditP();
	afx_msg void OnChangeEditD();
	afx_msg void OnChangeEditI();
	afx_msg void OnEditChangeSenscur();
	afx_msg void OnSelchangeSenscur();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int iValChngd;
	CTempController* pTempCtrl;

  static const int _R;
  static const int _K;
  static const int _CUR;
  static const int _HEAT;
  static const int _PID;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAKESHORESETDLG_H__BE208BA1_C109_11D8_9B27_00801E0328BA__INCLUDED_)
