/////////////////////////////////////////////////////////////////////////////
// DurationDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <fstream>
#include "resource.h"
#include "WarningOverwriteDlg.h"
#include "DurationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDurationDlg dialog
/////////////////////////////////////////////////////////////////////////////

CDurationDlg::CDurationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDurationDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CDurationDlg)
	sAMass1   = _T("6.0e-4");
	sAMass2   = _T("6.0e-4");
	sAMass3   = _T("6.0e-4");
	sAMass4   = _T("6.0e-4");
	sMass1    = _T("35.0E-3");
	sMass2    = _T("35.0E-3");
	sMass3    = _T("35.0E-3");
	sMass4    = _T("35.0E-3");
	sRFili1   = _T("6.0");
	sRFili2   = _T("6.0");
	sRFili3   = _T("6.0");
	sRFili4   = _T("6.0");
	sRTot1    = _T("132.5");
	sRTot2    = _T("132.5");
	sRTot3    = _T("132.5");
	sRTot4    = _T("132.5");
	sFileT1   = _T("");
	sFileT2   = _T("");
	sFileT3   = _T("");
	sFileT4   = _T("");
	sFileC1   = _T("");
	sFileC2   = _T("");
	sFileC3   = _T("");
	sFileC4   = _T("");
	iDuration = 0;
	//}}AFX_DATA_INIT
  Checked1 = true;
  Checked2 = false;
  Checked3 = false;
  Checked4 = false;

  int iArg1;
  double dArg1, dArg2, dArg3, dArg4;
  CString strValue, sTempT, sTempC;
  CWinApp* pApp = AfxGetApp();
  CString strStringItem = "MeasurementDlg";

  CString strSection = "Duration";
  iArg1 = iDuration;    
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    try {
      iArg1 = atoi(strValue);
    } catch(...) {
      iArg1 = iDuration;    
    }
  }
  strValue.Format("%d", iArg1);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 1";
  dArg1 = atof(sRFili1);    
  dArg2 = atof(sRTot1);    
  dArg3 = atof(sMass1); 
  dArg4 = atof(sAMass1);
  sTempT = sFileT1;
  sTempC = sFileC1;
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    try {
      dArg1 = atof(strtok(buf, ","));
      dArg2 = atof(strtok(0, ","));
      dArg3 = atof(strtok(0, ","));
      dArg4 = atof(strtok(0, ","));
      sTempT = strtok(0, ",");
      sTempC = strtok(0, "\0");
      sRFili1.Format("%.3g", dArg1);
      sRTot1.Format("%.3g", dArg2); 
      sMass1.Format("%.3g", dArg3);
      sAMass1.Format("%.3g", dArg4);
      sFileT1 = sTempT;
      sFileC1 = sTempC;
    } catch(...) {
      dArg1 = atof(sRFili1);    
      dArg2 = atof(sRTot1);    
      dArg3 = atof(sMass1); 
      dArg4 = atof(sAMass1);
      sTempT = sFileT1;
      sTempC = sFileC1;
    }
    delete[] buf;    
  }
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 2";
  dArg1 = atof(sRFili2);    
  dArg2 = atof(sRTot2);    
  dArg3 = atof(sMass2); 
  dArg4 = atof(sAMass2);
  sTempT = sFileT2;
  sTempC = sFileC2;
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    try {
      dArg1 = atof(strtok(buf, ","));
      dArg2 = atof(strtok(0, ","));
      dArg3 = atof(strtok(0, ","));
      dArg4 = atof(strtok(0, ","));
      sTempT = strtok(0, ",");
      sTempC = strtok(0, "\0");
      sRFili2.Format("%.3g", dArg1);
      sRTot2.Format("%.3g", dArg2); 
      sMass2.Format("%.3g", dArg3);
      sAMass2.Format("%.3g", dArg4);
      sFileT2 = sTempT;
      sFileC2 = sTempC;
    } catch(...) {
      dArg1 = atof(sRFili2);    
      dArg2 = atof(sRTot2);    
      dArg3 = atof(sMass2); 
      dArg4 = atof(sAMass2);
      sTempT= sFileT2;
      sTempC= sFileC2;
    }
    delete[] buf;    
  }
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 3";
  dArg1 = atof(sRFili3);    
  dArg2 = atof(sRTot3);    
  dArg3 = atof(sMass3); 
  dArg4 = atof(sAMass3);
  sTempT = sFileT3;
  sTempC = sFileC3;
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    try {
      dArg1 = atof(strtok(buf, ","));
      dArg2 = atof(strtok(0, ","));
      dArg3 = atof(strtok(0, ","));
      dArg4 = atof(strtok(0, ","));
      sTempT = strtok(0, ",");
      sTempC = strtok(0, "\0");
      sRFili3.Format("%.3g", dArg1);
      sRTot3.Format("%.3g", dArg2); 
      sMass3.Format("%.3g", dArg3);
      sAMass3.Format("%.3g", dArg4);
      sFileT3 = sTempT;
      sFileC3 = sTempC;
    } catch(...) {
      dArg1 = atof(sRFili3);    
      dArg2 = atof(sRTot3);    
      dArg3 = atof(sMass3); 
      dArg4 = atof(sAMass3);
      sTempT = sFileT3;
      sTempC = sFileC3;
    }
    delete[] buf;    
  }
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 4";
  dArg1 = atof(sRFili4);    
  dArg2 = atof(sRTot4);    
  dArg3 = atof(sMass4); 
  dArg4 = atof(sAMass4);
  sTempC = sFileT4;
  sTempT = sFileC4;
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    try {
      dArg1 = atof(strtok(buf, ","));
      dArg2 = atof(strtok(0, ","));
      dArg3 = atof(strtok(0, ","));
      dArg4 = atof(strtok(0, ","));
      sTempT = strtok(0, ",");
      sTempC = strtok(0, "\0");
      sRFili4.Format("%.3g", dArg1);
      sRTot4.Format("%.3g", dArg2); 
      sMass4.Format("%.3g", dArg3);
      sAMass4.Format("%.3g", dArg4);
      sFileT4 = sTempT;
      sFileC4 = sTempC;
    } catch(...) {
      dArg1 = atof(sRFili4);    
      dArg2 = atof(sRTot4);    
      dArg3 = atof(sMass4); 
      dArg4 = atof(sAMass4);
      sTempT = sFileT4;
      sTempC = sFileC4;
    }
    delete[] buf;    
  }
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CDurationDlg::~CDurationDlg() {
  double dArg1, dArg2, dArg3, dArg4;
  CString strValue, sTempT, sTempC;
  CWinApp* pApp = AfxGetApp();
  CString strStringItem = "MeasurementDlg";

  CString strSection = "Duration";
  strValue.Format("%d", iDuration);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 1";
  dArg1 = atof(sRFili1);    
  dArg2 = atof(sRTot1);    
  dArg3 = atof(sMass1); 
  dArg4 = atof(sAMass1);
  sTempT = sFileT1;
  sTempC = sFileC1;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 2";
  dArg1 = atof(sRFili2);    
  dArg2 = atof(sRTot2);    
  dArg3 = atof(sMass2); 
  dArg4 = atof(sAMass2);
  sTempT = sFileT2;
  sTempC = sFileC2;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 3";
  dArg1 = atof(sRFili3);    
  dArg2 = atof(sRTot3);    
  dArg3 = atof(sMass3); 
  dArg4 = atof(sAMass3);
  sTempT = sFileT3;
  sTempC = sFileC3;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 4";
  dArg1 = atof(sRFili4);    
  dArg2 = atof(sRTot4);    
  dArg3 = atof(sMass4); 
  dArg4 = atof(sAMass4);
  sTempT = sFileT4;
  sTempC = sFileC4;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


void
CDurationDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDurationDlg)
	DDX_Control(pDX, IDC_H1, bH1);
	DDX_Control(pDX, IDC_H2, bH2);
	DDX_Control(pDX, IDC_H3, bH3);
	DDX_Control(pDX, IDC_H4, bH4);
	DDX_Control(pDX, IDC_RTOT4, eRTot4);
	DDX_Control(pDX, IDC_RTOT3, eRTot3);
	DDX_Control(pDX, IDC_RTOT2, eRTot2);
	DDX_Control(pDX, IDC_RTOT1, eRTot1);
	DDX_Control(pDX, IDC_RFILI4, eRFili4);
	DDX_Control(pDX, IDC_RFILI3, eRFili3);
	DDX_Control(pDX, IDC_RFILI2, eRFili2);
	DDX_Control(pDX, IDC_RFILI1, eRFili1);
	DDX_Control(pDX, IDC_MASS_4, eMass4);
	DDX_Control(pDX, IDC_MASS_3, eMass3);
	DDX_Control(pDX, IDC_MASS_2, eMass2);
	DDX_Control(pDX, IDC_MASS_1, eMass1);
	DDX_Control(pDX, IDC_APIEZON_4, eAMass4);
	DDX_Control(pDX, IDC_APIEZON_3, eAMass3);
	DDX_Control(pDX, IDC_APIEZON_2, eAMass2);
	DDX_Control(pDX, IDC_APIEZON_1, eAMass1);
	DDX_Text(pDX, IDC_APIEZON_1, sAMass1);
	DDX_Text(pDX, IDC_APIEZON_2, sAMass2);
	DDX_Text(pDX, IDC_APIEZON_3, sAMass3);
	DDX_Text(pDX, IDC_APIEZON_4, sAMass4);
	DDX_Text(pDX, IDC_MASS_1, sMass1);
	DDX_Text(pDX, IDC_MASS_2, sMass2);
	DDX_Text(pDX, IDC_MASS_3, sMass3);
	DDX_Text(pDX, IDC_MASS_4, sMass4);
	DDX_Text(pDX, IDC_RFILI1, sRFili1);
	DDX_Text(pDX, IDC_RFILI2, sRFili2);
	DDX_Text(pDX, IDC_RFILI3, sRFili3);
	DDX_Text(pDX, IDC_RFILI4, sRFili4);
	DDX_Text(pDX, IDC_RTOT1, sRTot1);
	DDX_Text(pDX, IDC_RTOT2, sRTot2);
	DDX_Text(pDX, IDC_RTOT3, sRTot3);
	DDX_Text(pDX, IDC_RTOT4, sRTot4);
	DDX_Text(pDX, IDC_FILET1, sFileT1);
	DDX_Text(pDX, IDC_FILET2, sFileT2);
	DDX_Text(pDX, IDC_FILET3, sFileT3);
	DDX_Text(pDX, IDC_FILET4, sFileT4);
	DDX_Text(pDX, IDC_FILEC1, sFileC1);
	DDX_Text(pDX, IDC_FILEC2, sFileC2);
	DDX_Text(pDX, IDC_FILEC3, sFileC3);
	DDX_Text(pDX, IDC_FILEC4, sFileC4);
	DDX_Text(pDX, IDC_DURATION, iDuration);
	DDV_MinMaxInt(pDX, iDuration, 1, 6000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDurationDlg, CDialog)
	//{{AFX_MSG_MAP(CDurationDlg)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_H1, OnH1)
	ON_BN_CLICKED(IDC_H2, OnH2)
	ON_BN_CLICKED(IDC_H3, OnH3)
	ON_BN_CLICKED(IDC_H4, OnH4)
	ON_BN_CLICKED(IDC_CHANGET1, OnChangeFileT1)
	ON_BN_CLICKED(IDC_CHANGET2, OnChangeFileT2)
	ON_BN_CLICKED(IDC_CHANGET3, OnChangeFileT3)
	ON_BN_CLICKED(IDC_CHANGET4, OnChangeFileT4)
	ON_BN_CLICKED(IDC_CHANGEC1, OnChangeFileC1)
	ON_BN_CLICKED(IDC_CHANGEC2, OnChangeFileC2)
	ON_BN_CLICKED(IDC_CHANGEC3, OnChangeFileC3)
	ON_BN_CLICKED(IDC_CHANGEC4, OnChangeFileC4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDurationDlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL
CDurationDlg::OnInitDialog() {
	CDialog::OnInitDialog();
  UpdateData(false);
  if(Checked1) {
    OnH1();
  } else if(Checked2) {
    OnH2();
  } else if(Checked3) {
    OnH3();
  } else {
    OnH4();
  }
  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void 
CDurationDlg::OnOK() {
  if (!UpdateData(true)) return;
  double dArg1, dArg2, dArg3, dArg4;
  CString strValue, sTempT, sTempC;
  CWinApp* pApp = AfxGetApp();
  CString strStringItem = "MeasurementDlg";

  CString strSection = "Duration";
  strValue.Format("%d", iDuration);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 1";
  dArg1 = atof(sRFili1);    
  dArg2 = atof(sRTot1);    
  dArg3 = atof(sMass1); 
  dArg4 = atof(sAMass1);
  sTempT = sFileT1;
  sTempC = sFileC1;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 2";
  dArg1 = atof(sRFili2);    
  dArg2 = atof(sRTot2);    
  dArg3 = atof(sMass2); 
  dArg4 = atof(sAMass2);
  sTempT = sFileT2;
  sTempC = sFileC2;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 3";
  dArg1 = atof(sRFili3);    
  dArg2 = atof(sRTot3);    
  dArg3 = atof(sMass3); 
  dArg4 = atof(sAMass3);
  sTempT = sFileT3;
  sTempC = sFileC3;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 4";
  dArg1 = atof(sRFili4);    
  dArg2 = atof(sRTot4);    
  dArg3 = atof(sMass4); 
  dArg4 = atof(sAMass4);
  sTempT = sFileT4;
  sTempC = sFileC4;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s,%s", dArg1, dArg2, dArg3, dArg4, sTempT, sTempC);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  CDialog::OnOK();
}


int
CDurationDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


void 
CDurationDlg::OnH1() {
  UpdateData(true);
  Checked1 = true;
  Checked2 = false;
  Checked3 = false;
  Checked4 = false;

  eRFili1.EnableWindow(true);	
  eRTot1.EnableWindow(true);	
  eMass1.EnableWindow(true);
  eAMass1.EnableWindow(true);

  eRFili2.EnableWindow(false);	
  eRTot2.EnableWindow(false);	
  eMass2.EnableWindow(false);
  eAMass2.EnableWindow(false);

  eRFili3.EnableWindow(false);	
  eRTot3.EnableWindow(false);	
  eMass3.EnableWindow(false);
  eAMass3.EnableWindow(false);

  eRFili4.EnableWindow(false);	
  eRTot4.EnableWindow(false);	
  eMass4.EnableWindow(false);
  eAMass4.EnableWindow(false);

  bH1.SetCheck(1);
  bH2.SetCheck(0);
  bH3.SetCheck(0);
  bH4.SetCheck(0);
  UpdateData(false);
}


void
CDurationDlg::OnH2() {
  UpdateData(true);
  Checked1 = false;
  Checked2 = true;
  Checked3 = false;
  Checked4 = false;

  eRFili1.EnableWindow(false);	
  eRTot1.EnableWindow(false);	
  eMass1.EnableWindow(false);
  eAMass1.EnableWindow(false);

  eRFili2.EnableWindow(true);	
  eRTot2.EnableWindow(true);	
  eMass2.EnableWindow(true);
  eAMass2.EnableWindow(true);

  eRFili3.EnableWindow(false);	
  eRTot3.EnableWindow(false);	
  eMass3.EnableWindow(false);
  eAMass3.EnableWindow(false);

  eRFili4.EnableWindow(false);	
  eRTot4.EnableWindow(false);	
  eMass4.EnableWindow(false);
  eAMass4.EnableWindow(false);

  bH1.SetCheck(0);
  bH2.SetCheck(1);
  bH3.SetCheck(0);
  bH4.SetCheck(0);
  UpdateData(false);
}


void
CDurationDlg::OnH3() {
  UpdateData(true);
  Checked1 = false;
  Checked2 = false;
  Checked3 = true;
  Checked4 = false;

  eRFili1.EnableWindow(false);	
  eRTot1.EnableWindow(false);	
  eMass1.EnableWindow(false);
  eAMass1.EnableWindow(false);

  eRFili2.EnableWindow(false);	
  eRTot2.EnableWindow(false);	
  eMass2.EnableWindow(false);
  eAMass2.EnableWindow(false);

  eRFili3.EnableWindow(true);	
  eRTot3.EnableWindow(true);	
  eMass3.EnableWindow(true);
  eAMass3.EnableWindow(true);

  eRFili4.EnableWindow(false);	
  eRTot4.EnableWindow(false);	
  eMass4.EnableWindow(false);
  eAMass4.EnableWindow(false);

  bH1.SetCheck(0);
  bH2.SetCheck(0);
  bH3.SetCheck(3);
  bH4.SetCheck(0);
  UpdateData(false);
}


void
CDurationDlg::OnH4() {
  UpdateData(true);
  Checked1 = false;
  Checked2 = false;
  Checked3 = false;
  Checked4 = true;

  eRFili1.EnableWindow(false);	
  eRTot1.EnableWindow(false);	
  eMass1.EnableWindow(false);
  eAMass1.EnableWindow(false);

  eRFili2.EnableWindow(false);	
  eRTot2.EnableWindow(false);	
  eMass2.EnableWindow(false);
  eAMass2.EnableWindow(false);

  eRFili3.EnableWindow(false);	
  eRTot3.EnableWindow(false);	
  eMass3.EnableWindow(false);
  eAMass3.EnableWindow(false);

  eRFili4.EnableWindow(true);	
  eRTot4.EnableWindow(true);	
  eMass4.EnableWindow(true);
  eAMass4.EnableWindow(true);

  bH1.SetCheck(0);
  bH2.SetCheck(0);
  bH3.SetCheck(0);
  bH4.SetCheck(1);
  UpdateData(false);
}


void
CDurationDlg::OnChangeFileT1() {
  UpdateData(true);
  ChangeFileT(&sFileT1);
  UpdateData(false);
}


void
CDurationDlg::OnChangeFileT2() {
  UpdateData(true);
  ChangeFileT(&sFileT2);
  UpdateData(false);
}


void
CDurationDlg::OnChangeFileT3() {
  UpdateData(true);
  ChangeFileT(&sFileT3);
  UpdateData(false);
}


void
CDurationDlg::OnChangeFileT4() {
  UpdateData(true);
  ChangeFileT(&sFileT4);
  UpdateData(false);
}


void
CDurationDlg::OnCancel() {
  double dArg1, dArg2, dArg3, dArg4;
  CString strValue, sTemp;
  CWinApp* pApp = AfxGetApp();
  CString strStringItem = "MeasurementDlg";

  CString strSection = "Duration";
  strValue.Format("%d", iDuration);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 1";
  dArg1 = atof(sRFili1);    
  dArg2 = atof(sRTot1);    
  dArg3 = atof(sMass1); 
  dArg4 = atof(sAMass1);
  sTemp = sFileT1;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s", dArg1, dArg2, dArg3, dArg4, sTemp);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 2";
  dArg1 = atof(sRFili2);    
  dArg2 = atof(sRTot2);    
  dArg3 = atof(sMass2); 
  dArg4 = atof(sAMass2);
  sTemp = sFileT2;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s", dArg1, dArg2, dArg3, dArg4, sTemp);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 3";
  dArg1 = atof(sRFili3);    
  dArg2 = atof(sRTot3);    
  dArg3 = atof(sMass3); 
  dArg4 = atof(sAMass3);
  sTemp = sFileT3;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s", dArg1, dArg2, dArg3, dArg4, sTemp);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  strSection = "Heater 4";
  dArg1 = atof(sRFili4);    
  dArg2 = atof(sRTot4);    
  dArg3 = atof(sMass4); 
  dArg4 = atof(sAMass4);
  sTemp = sFileT4;
  strValue.Format("%.2f,%.2f,%.2f,%.2f,%s", dArg1, dArg2, dArg3, dArg4, sTemp);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
	
	CDialog::OnCancel();
}



void
CDurationDlg::OnChangeFileC1() {
  UpdateData(true);
  ChangeFileC(&sFileC1);
  UpdateData(false);
}


void
CDurationDlg::OnChangeFileC2() {
  UpdateData(true);
  ChangeFileC(&sFileC2);
  UpdateData(false);
}


void
CDurationDlg::OnChangeFileC3() {
  UpdateData(true);
  ChangeFileC(&sFileC3);
  UpdateData(false);
}


void
CDurationDlg::OnChangeFileC4() {
  UpdateData(true);
  ChangeFileC(&sFileC4);
  UpdateData(false);
}

void
CDurationDlg::ChangeFileC(CString* sFileC) {
  std::ifstream is;
  CString BolCFile = *sFileC;
	char szFilter[] = "File Cte Bol Data (*.Cte)|*.Cte|All Files (*.*)|*.*||";
  char szDefExt[] = "Cte";
  CString Prompt = "File Containing Bolometer Cte Data";

  CFileDialog FileDialog(true, szDefExt, BolCFile, OFN_HIDEREADONLY, szFilter);
  FileDialog.m_ofn.lpstrTitle = LPCTSTR(Prompt);

retry:
	if(FileDialog.DoModal() == IDOK) {
    BolCFile = FileDialog.GetPathName();
    is.open(BolCFile, std::ios::in);
    if(is.fail()) {
      AfxMessageBox("File Error: Retry");
      is.close();
      BolCFile = *sFileC;
      goto retry;
    } else {
      is.close();
    }
  }
  *sFileC = BolCFile;
}


void
CDurationDlg::ChangeFileT(CString* sFileT) {
  std::ifstream is;
  CString BolTFile = *sFileT;
	char szFilter[] = "File R-T Bolometro (*.bol)|*.bol|All Files (*.*)|*.*||";
  char szDefExt[] = "bol";
  CString Prompt = "File for Saving R-T Bolometer Calibration Data";

  CFileDialog FileDialog(FALSE, szDefExt, BolTFile, OFN_HIDEREADONLY, szFilter);
  FileDialog.m_ofn.lpstrTitle = LPCTSTR(Prompt);

	if(FileDialog.DoModal() == IDOK) {
    BolTFile = FileDialog.GetPathName();
    is.open(BolTFile, std::ios::in);
    if(!is.fail()) {
      CWarningOverwriteDlg WarningOverwriteDlg;
      INT_PTR iRes = WarningOverwriteDlg.DoModal();
      if(iRes == IDCANCEL) {
        is.close();
        return;
      } else if(iRes == IDC_OVERWRITE) {// Truncate File
        is.close();
        is.open(BolTFile, std::ios::out);
        is.close();
      } else {// Merge Do nothing
        is.close();
      }
    } else {// File does Not exists;
      is.close();
    }
  }
  *sFileT = BolTFile;
}