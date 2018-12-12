/////////////////////////////////////////////////////////////////////////////
// CurrGenDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "CurrGen.h"
#include "CurrGenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrGenDlg property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CCurrGenDlg, CPropertyPage)

CCurrGenDlg::CCurrGenDlg() : CPropertyPage(CCurrGenDlg::IDD) {
	//{{AFX_DATA_INIT(CCurrGenDlg)
	Current = 1.0e-12;
	//}}AFX_DATA_INIT
  pCurrGen = NULL;

  double Arg1;
  CString strStringItem;
  CString strValue;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  strStringItem = "Current Generator";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  Arg1 = Current;            // Current
  if(strValue != "") {
    Arg1 = atof(strValue);
    Current = Arg1;
  }
  strValue.Format("%g", Arg1);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CCurrGenDlg::~CCurrGenDlg() {
}


void 
CCurrGenDlg::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurrGenDlg)
	DDX_Text(pDX, IDC_CURRENT, Current);
	DDV_MinMaxDouble(pDX, Current, 0.0, 1.e-001);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurrGenDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CCurrGenDlg)
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_CURRENT, OnChangeCurrent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void 
CCurrGenDlg::SetDevice(CCurrGen* Device) {
  pCurrGen = Device;
}


/////////////////////////////////////////////////////////////////////////////
// CCurrGenDlg message handlers
/////////////////////////////////////////////////////////////////////////////

int 
CCurrGenDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


BOOL 
CCurrGenDlg::OnApply() {
	// TODO: Add your specialized code here and/or call the base class
	if(!UpdateData(true)) return FALSE;
	SetCurrent(Current);
  
  double Arg1;
  CString strStringItem;
  CString strValue;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();
  
  strStringItem = "Current Generator";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  
  Arg1 = Current;
  strValue.Format("%g", Arg1);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

	return CPropertyPage::OnApply();
}


bool 
CCurrGenDlg::SetCurrent(double Current) {
  CString sConf;
	if(Current < 2.0E-12)
		sConf ="F1R1Z1X";
	else if(Current < 20.0E-12)
		sConf ="F1R2Z1X";
	else if(Current < 200.0E-12)
		sConf ="F1R3Z1X";
	else if(Current < 2.0E-9)
		sConf ="F1R4Z1X";
	else if(Current < 20.0E-9)
		sConf ="F1R5Z1X";
	else if(Current < 200.0E-9)
		sConf ="F1R6Z1X";
	else if(Current < 2.0E-6)
		sConf ="F1R7Z1X";
	else if(Current < 20.0E-6)
		sConf ="F1R8Z1X";
	else if(Current < 200.0E-6)
		sConf ="F1R9Z1X";
	else if(Current < 2.0E-3)
		sConf ="F1R10Z1X";
	else if(Current < 20.0E-3)
		sConf ="F1R11Z1X";
	else {
		sConf ="F1R1Z1X";
    Current = 1.0E-12;
	}
	pCurrGen->Configure(sConf);
 	sConf.Format("V%g O1X", Current);
	return pCurrGen->Configure(sConf);

}


void
CCurrGenDlg::OnChangeCurrent() {
  SetModified(TRUE);
}
