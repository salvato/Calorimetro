//{{AFX_INCLUDES()
#include "editgrid.h"
//}}AFX_INCLUDES
#if !defined(AFX_PARDLG_H__C8CDAC0F_D3F5_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_PARDLG_H__C8CDAC0F_D3F5_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParDlg dialog
/////////////////////////////////////////////////////////////////////////////

class
CParDlg : public CDialog {
// Construction
public:
	CParDlg(CWnd* pParent = NULL);   // standard constructor
  ~	CParDlg();

// Dialog Data
	//{{AFX_DATA(CParDlg)
	enum { IDD = IDD_PARDLG };
	CEditGrid	myGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool UpdatePar(CParInfo ParInfo);
	CParInfo GetParInfo(int num);
	bool AddPar(int num, CString name, double val, double err, double min, double max, bool fixed=false);
	bool AddPar(CParInfo Parinfo);
	void UpdateWindow();
	void ClearAll();

protected:

	// Generated message map functions
	//{{AFX_MSG(CParDlg)
  LRESULT OnFixUnfix(WPARAM wParam, LPARAM lParam);
  LRESULT OnParUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CWnd* pParent;
  int x0;
  int y0;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARDLG_H__C8CDAC0F_D3F5_11D8_9B27_00801E0328BA__INCLUDED_)
