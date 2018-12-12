#if !defined(AFX_APIEZONSETTINGSDLG_H__F92EDE01_D97C_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_APIEZONSETTINGSDLG_H__F92EDE01_D97C_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/////////////////////////////////////////////////////////////////////////////
// ApiezonSettingsDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CApiezonSettingsDlg dialog
/////////////////////////////////////////////////////////////////////////////

class
CApiezonSettingsDlg : public CPropertyPage {
	DECLARE_DYNCREATE(CApiezonSettingsDlg)

// Construction
public:
	bool bSettingChanged;
	CApiezonSettingsDlg();
	~CApiezonSettingsDlg();

// Dialog Data
	//{{AFX_DATA(CApiezonSettingsDlg)
	enum { IDD = IDD_APIEZON_SETTINGS };
	CString	sFileCApiezon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CApiezonSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CApiezonSettingsDlg)
	afx_msg void OnChangeFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APIEZONSETTINGSDLG_H__F92EDE01_D97C_11D8_9B27_00801E0328BA__INCLUDED_)
