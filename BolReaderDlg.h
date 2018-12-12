/////////////////////////////////////////////////////////////////////////////
// BolReaderDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOLREADERDLG_H__83FFF9A0_B976_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_BOLREADERDLG_H__83FFF9A0_B976_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBolReader;

/////////////////////////////////////////////////////////////////////////////
// CBolReaderDlg dialog
/////////////////////////////////////////////////////////////////////////////

class 
CBolReaderDlg : public CPropertyPage {
	DECLARE_DYNCREATE(CBolReaderDlg)

// Construction
public:
	CBolReaderDlg();
	~CBolReaderDlg();

// Dialog Data
	//{{AFX_DATA(CBolReaderDlg)
	enum { IDD = IDD_BOL_READER };
	CComboBox	cScale;
	CComboBox	cPlc;
	CComboBox	cDigits;
	CButton	cAZero;
	BOOL	m_AZero;
	int		m_Scale;
	int		m_Plc;
	int		m_Digits;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBolReaderDlg)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	int modelNumber;
  void SetDevice(CBolReader* Device);

protected:
	// Generated message map functions
	//{{AFX_MSG(CBolReaderDlg)
	afx_msg void OnAzero();
	afx_msg void OnSelchangeDigits();
	afx_msg void OnSelchangePlc();
	afx_msg void OnSelchangeScale();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  CBolReader* pBolReader;
	bool	bAZeroChanged;
	bool	bDigitsChanged;
	bool	bScaleChanged;
	bool	bPlcChanged;

	BOOL	AZeroOld;
	int		DigitsOld;
	int		ScaleOld;
	int		PlcOld;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOLREADERDLG_H__83FFF9A0_B976_11D8_9B27_00801E0328BA__INCLUDED_)
