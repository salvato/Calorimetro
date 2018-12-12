#if !defined(AFX_FITEXP1DLG_H__FFE19362_F312_11D2_88DD_444553540000__INCLUDED_)
#define AFX_FITEXP1DLG_H__FFE19362_F312_11D2_88DD_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FitExp1Dlg.h : header file
//
class CDoFitDlg;

/////////////////////////////////////////////////////////////////////////////
// CFitExp1Dlg dialog

class
CFitExp1Dlg : public CDialog {
// Construction
public:
	bool fitDone;
	CFitExp1Dlg(CDoFitDlg* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFitExp1Dlg)
	enum { IDD = IDD_EXP1 };
	CEdit	m_eChi2;
	CButton	m_b_ok;
	CEdit	m_e_y1;
	CEdit	m_e_y0;
	CEdit	m_e_t0;
	CEdit	m_e_tau;
	CButton	m_bOverflow;
	CButton	m_bConverged;
	double	m_tau;
	double	m_t0;
	double	m_y0;
	double	m_y1;
	double	m_Chi2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFitExp1Dlg)
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
	//{{AFX_MSG(CFitExp1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDoFitClicked();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void FitData();
	CDoFitDlg* myParent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FITEXP1DLG_H__FFE19362_F312_11D2_88DD_444553540000__INCLUDED_)
