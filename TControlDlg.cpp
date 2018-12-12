/////////////////////////////////////////////////////////////////////////////
// TControlDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "TempController.h"
#include "TControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTControlDlg property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CTControlDlg, CPropertyPage)

CTControlDlg::CTControlDlg() 
: CPropertyPage(CTControlDlg::IDD) {
	//{{AFX_DATA_INIT(CTControlDlg)
	m_Resistance = 10000.0;
	m_SensorCurrent = 0;
	//}}AFX_DATA_INIT
  int iArg1;
  double Arg2;
  CString strStringItem;
  CString strValue;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  strStringItem = "TCONTROL";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  iArg1 = m_SensorCurrent + 1;
  Arg2 = m_Resistance;
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    iArg1 = atoi(strtok(buf, ","));
    Arg2 = atof(strtok(0, ","));
    m_SensorCurrent = iArg1 - 1;
    m_Resistance    = Arg2;
    delete[] buf;
  }
  strValue.Format("%d,%g", iArg1, Arg2);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CTControlDlg::~CTControlDlg() {
}


void 
CTControlDlg::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTControlDlg)
	DDX_Text(pDX, IDC_RESISTANCE, m_Resistance);
	DDV_MinMaxDouble(pDX, m_Resistance, 0., 200000.);
	DDX_CBIndex(pDX, IDC_SENSORCURRENT, m_SensorCurrent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTControlDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CTControlDlg)
	ON_CBN_SELCHANGE(IDC_SENSORCURRENT, OnSelchangeSensorcurrent)
	ON_EN_CHANGE(IDC_RESISTANCE, OnChangeResistance)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTControlDlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL 
CTControlDlg::OnApply() {
	pTempCtrl->ChangeCurrent(m_SensorCurrent + 1);
  pTempCtrl->ChangeRSetPoint(m_Resistance);

  int iArg1;
  double dArg2;
  CString strValue;
  CString strStringItem;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  strStringItem = "TCONTROL";

  iArg1 = m_SensorCurrent + 1;
  dArg2 = m_Resistance;

  strValue.Format("%d,%g", iArg1, dArg2);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
	
	return CPropertyPage::OnApply();
}


void 
CTControlDlg::OnSelchangeSensorcurrent() {
  SetModified(TRUE);
}


void 
CTControlDlg::SetDevice(CTempController *pmyTempCtrl) {
  pTempCtrl = pmyTempCtrl;
}


void 
CTControlDlg::OnChangeResistance() {
    SetModified(TRUE);
}


BOOL
CTControlDlg::OnInitDialog() {
	CPropertyPage::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
