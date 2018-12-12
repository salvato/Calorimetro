/////////////////////////////////////////////////////////////////////////////
// GeReaderSettings.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "GeReaderSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeReaderSettings property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CGeReaderSettings, CPropertyPage)

CGeReaderSettings::CGeReaderSettings()
  : CPropertyPage(CGeReaderSettings::IDD) {
	//{{AFX_DATA_INIT(CGeReaderSettings)
	iAddress = 22;
	//}}AFX_DATA_INIT
  iModelNumber = 0;
	
  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Ge Reader";
  strStringItem = "Settings";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    iAddress     = atoi(strtok(buf, ","));
    iModelNumber = atoi(strtok(0, "\0"));
    delete[] buf;
  }
  strValue.Format("%d,%d", iAddress, iModelNumber);

  pApp->WriteProfileString(strSection, strStringItem, strValue);
  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  bSettingChanged  = false;
}


CGeReaderSettings::~CGeReaderSettings() {
}


void
CGeReaderSettings::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeReaderSettings)
	DDX_Control(pDX, IDC_ADDRESS, eAddress);
	DDX_Control(pDX, IDC_MODEL, cModelNumber);
	DDX_Text(pDX, IDC_ADDRESS, iAddress);
	DDV_MinMaxInt(pDX, iAddress, 1, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeReaderSettings, CPropertyPage)
	//{{AFX_MSG_MAP(CGeReaderSettings)
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_ADDRESS, OnChangeAddress)
	ON_CBN_SELCHANGE(IDC_MODEL, OnSelchangeModel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int
CGeReaderSettings::GetModelNumber() {
  return iModelNumber;
}


int
CGeReaderSettings::GetAddress() {
  return iAddress;
}


/////////////////////////////////////////////////////////////////////////////
// CGeReaderSettings message handlers
/////////////////////////////////////////////////////////////////////////////

int 
CGeReaderSettings::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  bSettingChanged  = false;
	
	return 0;
}


BOOL 
CGeReaderSettings::OnInitDialog() {
	CPropertyPage::OnInitDialog();
	
  cModelNumber.SetCurSel(iModelNumber);
  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  bSettingChanged  = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CGeReaderSettings::OnChangeAddress() {
  CString sText;
  eAddress.GetWindowText(sText);
  if(atoi(sText) == iOldAddress) {
    bAddressModified = false;
  } else {
    bAddressModified = true;
  }
  SetModified(bAddressModified || bModelModified);	
}


void
CGeReaderSettings::OnSelchangeModel() {
  if(cModelNumber.GetCurSel() == iOldModelNumber) {
    bModelModified = false;
  } else {
    bModelModified = true;
  }
  SetModified(bAddressModified || bModelModified);	
}


BOOL
CGeReaderSettings::OnApply() {
  if(!(bAddressModified || bModelModified)) return true;
	if(!UpdateData(true)) return false;

  iModelNumber = cModelNumber.GetCurSel();
  bSettingChanged = true;

  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Ge Reader";
  strStringItem = "Settings";
  strValue.Format("%d,%d", iAddress, iModelNumber);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  SetModified(bAddressModified || bModelModified);	
	return CPropertyPage::OnApply();
}
