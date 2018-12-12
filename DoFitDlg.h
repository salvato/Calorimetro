/////////////////////////////////////////////////////////////////////////////
// DoFitDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOFIT_H__FFE19361_F312_11D2_88DD_444553540000__INCLUDED_)
#define AFX_DOFIT_H__FFE19361_F312_11D2_88DD_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "FitExp1Dlg.h"
#include "FitExp2Dlg.h"
#include "FitLinDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CDoFitDlg dialog
/////////////////////////////////////////////////////////////////////////////

class
CDoFitDlg : public CDialog {
// Construction
public:
	CDoFitDlg(CWnd* pParent = NULL);   // standard constructor
  int m_iFitType;
  int m_iDataSet;
  CFitExp1Dlg FitExp1Dlg;
  CFitExp2Dlg FitExp2Dlg;
  CFitLinDlg  FitLinDlg;
// Dialog Data
	//{{AFX_DATA(CDoFitDlg)
	enum { IDD = IDD_DOFIT };
	CButton	m_b_OK;
  CButton m_bSingle;
  CButton m_bDouble;
  CButton m_bLinear;
  CButton m_bGer;
  CButton m_bBol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDoFitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
public:
	int m_Ger;
	int m_Bol;
	// Generated message map functions
	//{{AFX_MSG(CDoFitDlg)
	afx_msg void OnBolClicked();
	afx_msg void OnExp1Clicked();
	afx_msg void OnExp2Clicked();
	afx_msg void OnGerClicked();
	afx_msg void OnLinClicked();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOFIT_H__FFE19361_F312_11D2_88DD_444553540000__INCLUDED_)
