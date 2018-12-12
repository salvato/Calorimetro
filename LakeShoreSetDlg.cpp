/////////////////////////////////////////////////////////////////////////////
// LakeShoreSetDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "TempController.h"
#include "LakeShoreSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _BASE     1
#define _NOCHANGE 0

const int CLakeShoreSetDlg::_R    = _BASE;
const int CLakeShoreSetDlg::_K    = _BASE << 1;
const int CLakeShoreSetDlg::_CUR  = _BASE << 2;
const int CLakeShoreSetDlg::_HEAT = _BASE << 3;
const int CLakeShoreSetDlg::_PID  = _BASE << 4;

/////////////////////////////////////////////////////////////////////////////
// CLakeShoreSetDlg property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CLakeShoreSetDlg, CPropertyPage)

CLakeShoreSetDlg::CLakeShoreSetDlg()
  : CPropertyPage(CLakeShoreSetDlg::IDD) {
	//{{AFX_DATA_INIT(CLakeShoreSetDlg)
	SetPoint  = _T("25000");
	iHeater   = 0;
	sDVal = _T("");
	sIVal = _T("");
	sPVal = _T("");
	iSensCurr = 0;
	//}}AFX_DATA_INIT
  double Arg1;
  CString strStringItem;
  CString strValue;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  strStringItem = "LakeShore 370";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  Arg1 = atof(SetPoint);
  if(strValue != "") {
    Arg1 = atof(strValue);
    SetPoint.Format("%g", Arg1);
  }
  strValue.Format("%g", Arg1);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  iValChngd = 0;
}


CLakeShoreSetDlg::~CLakeShoreSetDlg() {
}


void
CLakeShoreSetDlg::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLakeShoreSetDlg)
	DDX_Text(pDX, IDC_SETP, SetPoint);
	DDX_CBIndex(pDX, IDC_HEATER, iHeater);
	DDX_Text(pDX, IDC_EDIT_D, sDVal);
	DDX_Text(pDX, IDC_EDIT_I, sIVal);
	DDX_Text(pDX, IDC_EDIT_P, sPVal);
	DDX_CBIndex(pDX, IDC_SENSCUR, iSensCurr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLakeShoreSetDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CLakeShoreSetDlg)
	ON_EN_CHANGE(IDC_SETP, OnChangeSetp)
	ON_CBN_EDITCHANGE(IDC_HEATER, OnEditchangeHeater)
	ON_CBN_SELCHANGE(IDC_HEATER, OnSelchangeHeater)
	ON_EN_CHANGE(IDC_EDIT_P, OnChangeEditP)
	ON_EN_CHANGE(IDC_EDIT_D, OnChangeEditD)
	ON_EN_CHANGE(IDC_EDIT_I, OnChangeEditI)
	ON_CBN_EDITCHANGE(IDC_SENSCUR, OnEditChangeSenscur)
	ON_CBN_SELCHANGE(IDC_SENSCUR, OnSelchangeSenscur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void 
CLakeShoreSetDlg::SetDevice(CTempController *pmyTempCtrl) {
  pTempCtrl = pmyTempCtrl;
}


double
CLakeShoreSetDlg::GetSetPoint() {
  return atof(SetPoint);
}


/////////////////////////////////////////////////////////////////////////////
// CLakeShoreSetDlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL 
CLakeShoreSetDlg::OnApply() {
  double dSetPoint = atof(SetPoint);

  if(iValChngd & _CUR)  pTempCtrl->ChangeCurrent(iSensCurr);
  if(iValChngd & _R)    pTempCtrl->ChangeRSetPoint(dSetPoint);
  if(iValChngd & _HEAT) pTempCtrl->Heater(iHeater);
  if(iValChngd & _PID)  pTempCtrl->SetPID(atof(sPVal), atof(sIVal), atof(sDVal));
  iValChngd = _NOCHANGE;

  double Arg1;
  CString strValue;
  CString strStringItem;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  strStringItem = "LakeShore 370";
  Arg1 = atof(SetPoint);
  strValue.Format("%g", Arg1);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
  
	return CPropertyPage::OnApply();
}


BOOL
CLakeShoreSetDlg::OnInitDialog() {
	CPropertyPage::OnInitDialog();
  double P_Val, I_Val, D_Val;
  if(pTempCtrl->GetPID(&P_Val, &I_Val, &D_Val)) {
    sPVal.Format("%.3f", P_Val);
    sIVal.Format("%.0f", I_Val);
    sDVal.Format("%.0f", D_Val);
  } else {
    sPVal = "?";
    sIVal = "?";
    sDVal = "?";
  }

  if(!pTempCtrl->GetCurrent(&iSensCurr)) {
    iSensCurr = 0;
  }
  if(!pTempCtrl->GetHeater(&iHeater)) {
    iHeater = 0;
  }

  UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CLakeShoreSetDlg::OnChangeSetp() {
  iValChngd |= _R;
  SetModified(true);	
}


void
CLakeShoreSetDlg::OnEditchangeHeater() {
  iValChngd |= _HEAT;
  SetModified(true);	
}


void
CLakeShoreSetDlg::OnSelchangeHeater() {
  iValChngd |= _HEAT;
  SetModified(true);	
}


void
CLakeShoreSetDlg::OnChangeEditP() {
  iValChngd |= _PID;
  SetModified(true);	
}


void
CLakeShoreSetDlg::OnChangeEditD() {
  iValChngd |= _PID;
  SetModified(true);	
}


void
CLakeShoreSetDlg::OnChangeEditI() {
  iValChngd |= _PID;
  SetModified(true);	
}


void 
CLakeShoreSetDlg::OnEditChangeSenscur() {
  iValChngd |= _CUR;
  SetModified(true);	
}


void
CLakeShoreSetDlg::OnSelchangeSenscur() {
  iValChngd |= _CUR;
  SetModified(true);	
}

