/////////////////////////////////////////////////////////////////////////////
// MinuitDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MINUITDLG_H__C10A76AD_B2DB_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_MINUITDLG_H__C10A76AD_B2DB_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "math.h"
#include "Includes/fcn.h"
#include "MinuitDecl.h"

class CPlotWindow;
class CMsgWindow;
class CParDlg;

extern CPlotWindow* pPlotA;

/////////////////////////////////////////////////////////////////////////////
// CMinuitDlg dialog
/////////////////////////////////////////////////////////////////////////////

class
CMinuitDlg : public CDialog {
// Construction
public:
	CMinuitDlg(CWnd* pParent=NULL, CMsgWindow* pMsg=NULL);
  virtual ~CMinuitDlg();

// Dialog Data
	//{{AFX_DATA(CMinuitDlg)
	enum { IDD = IDD_MINUIT_DIALOG };
	CComboBox	cCommand;
	CString	Command;
	CString	Filename;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMinuitDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

public:
	void SetFilename(CString File);
	void GetPars(double *par, int nPar);
	bool SetPars(double* par, int nPar);

private:
	CWnd* myParent;
	int yControl;
	int xControl;
	int nPar;
  int iErr, narg;
	double xEnd;
	double xStart;
  double arglis[10];

	CFont*      pmyFont;
  CParDlg*    pParDlg;
  CMsgWindow* pMsgWindow;
  CString     strValue;
  CString     strSection;
  CString     strStringItem;
  CString     line;
  CString     szFilter;
  CString     szDefExt;

	void SendUpdatedPar();
 	void GetUpdatedPar();

	// Generated message map functions
	//{{AFX_MSG(CMinuitDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnGoCom();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  LRESULT OnNewText(WPARAM wParam, LPARAM lParam);
  LRESULT OnFixUnfix(WPARAM wParam, LPARAM lParam);
  LRESULT OnParUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDone();
	virtual void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINUITDLG_H__C10A76AD_B2DB_11D8_9B27_00801E0328BA__INCLUDED_)
