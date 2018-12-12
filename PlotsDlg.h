/////////////////////////////////////////////////////////////////////////////
// PlotsDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLOTSDLG_H__BD512B8C_E4E7_11D6_9B26_00801E0328BA__INCLUDED_)
#define AFX_PLOTSDLG_H__BD512B8C_E4E7_11D6_9B26_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct pLimits {
  CString name;
  double
    xmin,
    xmax,
    ymin,
    ymax;
  BOOL
    active,
    autorangeX,
    autorangeY,
    logX,
    logY;
};

class CPlotWindow;
class CDataSetProperties;

/////////////////////////////////////////////////////////////////////////////
// CPlotsDlg dialog
/////////////////////////////////////////////////////////////////////////////

class 
CPlotsDlg : public CPropertyPage {
	DECLARE_DYNCREATE(CPlotsDlg)

// Construction
public:
	CPlotsDlg();
	~CPlotsDlg();

// Dialog Data
	//{{AFX_DATA(CPlotsDlg)
	enum { IDD = IDD_PLOTS };
	CButton	m_ckLogY;
	CButton	m_ckLogX;
	CButton	m_ckAutoX;
	CButton	m_ckAutoY;
	CEdit	m_edYmin;
	CEdit	m_edYmax;
	CEdit	m_edXmin;
	CEdit	m_edXmax;
	CTabCtrl	m_Plots;
	CString	m_Xmin;
	CString	m_Xmax;
	CString	m_Ymax;
	CString	m_Ymin;
	BOOL	m_AutorangeX;
	BOOL	m_AutorangeY;
	BOOL	m_LogX;
	BOOL	m_LogY;
	BOOL	m_Active;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPlotsDlg)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPlotsDlg)
	afx_msg void OnSelchangePlots(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAutorangeX();
	afx_msg void OnAutorangeY();
	virtual BOOL OnInitDialog();
	afx_msg void OnPlotactive();
	afx_msg void OnLogx();
	afx_msg void OnLogy();
	afx_msg void OnChangeXmin();
	afx_msg void OnChangeYmin();
	afx_msg void OnChangeXmax();
	afx_msg void OnChangeYmax();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SetPlots(CPlotWindow** pPlots, CDataSetProperties** pProperties, int nP);
	int nPlots;
  pLimits* axLimits;
private:
	int previousSel;
  CPlotWindow** pPlot;
  CDataSetProperties** pProperties;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTSDLG_H__BD512B8C_E4E7_11D6_9B26_00801E0328BA__INCLUDED_)
