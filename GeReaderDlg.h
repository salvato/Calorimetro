/////////////////////////////////////////////////////////////////////////////
// GeReaderDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEREADERDLG_H__68B43541_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
#define AFX_GEREADERDLG_H__68B43541_B95C_11D8_9B27_00801E0328BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGeReader;

/////////////////////////////////////////////////////////////////////////////
// CGeReaderDlg dialog
/////////////////////////////////////////////////////////////////////////////

class 
CGeReaderDlg : public CPropertyPage {
	DECLARE_DYNCREATE(CGeReaderDlg)

// Construction
public:
	CGeReaderDlg();   // standard constructor
	~CGeReaderDlg();

// Dialog Data
	//{{AFX_DATA(CGeReaderDlg)
	enum { IDD = IDD_GE_READER };
	CComboBox	cRange;
	int		m_Range;
	CString	m_FilePar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeReaderDlg)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
  void SetDevice(CGeReader* Device);

protected:

	// Generated message map functions
	//{{AFX_MSG(CGeReaderDlg)
	afx_msg void OnChangeFile();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchangeRange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  CString strSection;
  CString strStringItem;
  CString strValue;
  CGeReader* pGeReader;

	bool	bRangeChanged;
	bool	bFileChanged;

  int     RangeOld;
  CString FileOld;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GEREADERDLG_H__68B43541_B95C_11D8_9B27_00801E0328BA__INCLUDED_)
