#if !defined(AFX_FITEXP2DLG_H__71A71001_F346_11D2_88DD_444553540000__INCLUDED_)
#define AFX_FITEXP2DLG_H__71A71001_F346_11D2_88DD_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FitExp2Dlg.h : header file
//
class CDoFitDlg;

/////////////////////////////////////////////////////////////////////////////
// CFitExp2Dlg dialog

class CFitExp2Dlg : public CDialog
{
// Construction
public:
	bool fitDone;
	void FitData();
	CFitExp2Dlg(CDoFitDlg* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFitExp2Dlg)
	enum { IDD = IDD_EXP2 };
	CEdit	m_e_t0;
	CEdit	m_e_tau2;
	CEdit	m_e_tau1;
	CEdit	m_e_y2;
	CEdit	m_e_y1;
	CEdit	m_e_y0;
	CButton	m_b_ok;
	CEdit	m_eChi2;
	CButton	m_bOverflow;
	CButton	m_bConverged;
	double	m_tau1;
	double	m_tau2;
	double	m_t0;
	double	m_y0;
	double	m_y1;
	double	m_y2;
	double	m_Chi2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFitExp2Dlg)
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
	//{{AFX_MSG(CFitExp2Dlg)
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

#endif // !defined(AFX_FITEXP2DLG_H__71A71001_F346_11D2_88DD_444553540000__INCLUDED_)
