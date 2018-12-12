#if !defined(AFX_TCONTROLDLG_H__BD512B8B_E4E7_11D6_9B26_00801E0328BA__INCLUDED_)
#define AFX_TCONTROLDLG_H__BD512B8B_E4E7_11D6_9B26_00801E0328BA__INCLUDED_

#include "Tempctrl.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TControlDlg.h : header file
//

class CTempController;

/////////////////////////////////////////////////////////////////////////////
// CTControlDlg dialog

class CTControlDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CTControlDlg)

// Construction
public:
	void SetDevice(CTempController* pTempCtrl);
	CTControlDlg();
	~CTControlDlg();

// Dialog Data
	//{{AFX_DATA(CTControlDlg)
	enum { IDD = IDD_TCONTROL };
	double	m_Resistance;
	int		m_SensorCurrent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTControlDlg)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTControlDlg)
	afx_msg void OnSelchangeSensorcurrent();
	afx_msg void OnChangeResistance();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CTempController* pTempCtrl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCONTROLDLG_H__BD512B8B_E4E7_11D6_9B26_00801E0328BA__INCLUDED_)
