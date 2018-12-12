#if !defined(AFX_DURATIONDLG_H__783B33A1_E69F_11D2_88DD_444553540000__INCLUDED_)
#define AFX_DURATIONDLG_H__783B33A1_E69F_11D2_88DD_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DurationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDurationDlg dialog

class CDurationDlg : public CDialog
{
// Construction
public:
	virtual  ~CDurationDlg();
	CDurationDlg(CWnd* pParent = NULL);   // standard constructor
  bool Checked1, Checked2, Checked3, Checked4;

// Dialog Data
	//{{AFX_DATA(CDurationDlg)
	enum { IDD = IDD_DURATION };
	CButton	bH1;
	CButton	bH2;
	CButton	bH3;
	CButton	bH4;
	CEdit	  eRTot4;
	CEdit	  eRTot3;
	CEdit	  eRTot2;
	CEdit	  eRTot1;
	CEdit	  eRFili4;
	CEdit	  eRFili3;
	CEdit	  eRFili2;
	CEdit	  eRFili1;
	CEdit	  eMass4;
	CEdit	  eMass3;
	CEdit	  eMass2;
	CEdit	  eMass1;
	CEdit	  eAMass4;
	CEdit	  eAMass3;
	CEdit	  eAMass2;
	CEdit	  eAMass1;
	CString	sAMass1;
	CString	sAMass2;
	CString	sAMass3;
	CString	sAMass4;
	CString	sMass1;
	CString	sMass2;
	CString	sMass3;
	CString	sMass4;
	CString	sRFili1;
	CString	sRFili2;
	CString	sRFili3;
	CString	sRFili4;
	CString	sRTot1;
	CString	sRTot2;
	CString	sRTot3;
	CString	sRTot4;
	CString	sFileT1;
	CString	sFileT2;
	CString	sFileT3;
	CString	sFileT4;
	CString	sFileC1;
	CString	sFileC2;
	CString	sFileC3;
	CString	sFileC4;
	int		iDuration;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDurationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDurationDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnH1();
	afx_msg void OnH2();
	afx_msg void OnH3();
	afx_msg void OnH4();
	afx_msg void OnChangeFileT1();
	afx_msg void OnChangeFileT2();
	afx_msg void OnChangeFileT3();
	afx_msg void OnChangeFileT4();
	afx_msg void OnChangeFileC1();
	afx_msg void OnChangeFileC2();
	afx_msg void OnChangeFileC3();
	afx_msg void OnChangeFileC4();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  void ChangeFileC(CString* sFileC);
  void ChangeFileT(CString* sFileT);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DURATIONDLG_H__783B33A1_E69F_11D2_88DD_444553540000__INCLUDED_)
