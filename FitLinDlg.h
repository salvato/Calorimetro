/////////////////////////////////////////////////////////////////////////////
// FitLinDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FITLINDLG_H__71A71002_F346_11D2_88DD_444553540000__INCLUDED_)
#define AFX_FITLINDLG_H__71A71002_F346_11D2_88DD_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDoFitDlg;


/////////////////////////////////////////////////////////////////////////////
// CFitLinDlg dialog
/////////////////////////////////////////////////////////////////////////////

class
CFitLinDlg : public CDialog {
// Construction
public:
	bool fitDone;
	void FitData();
	CFitLinDlg(CDoFitDlg* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFitLinDlg)
	enum { IDD = IDD_LIN };
	CButton	m_b_ok;
	CEdit	m_e_b;
	CEdit	m_e_a;
	CEdit	m_eChi2;
	CButton	m_bOverflow;
	CButton	m_bConverged;
	double	m_a;
	double	m_b;
	double	m_Chi2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFitLinDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL Create(UINT nID, CDoFitDlg* pParent = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFitLinDlg)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnDoFitClicked();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDoFitDlg* myParent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FITLINDLG_H__71A71002_F346_11D2_88DD_444553540000__INCLUDED_)
