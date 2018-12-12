/////////////////////////////////////////////////////////////////////////////
// BolReaderDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "BolReader.h"
#include "BolReaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBolReaderDlg property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CBolReaderDlg, CPropertyPage)

CBolReaderDlg::CBolReaderDlg() 
  : CPropertyPage(CBolReaderDlg::IDD) {
	//{{AFX_DATA_INIT(CBolReaderDlg)
	m_AZero  = TRUE;
	m_Scale  = 3;
	m_Plc    = 1;
	m_Digits = 0;
	//}}AFX_DATA_INIT

  pBolReader = NULL;

  int iArg1, iArg2, iArg3, iArg4;
  CString strStringItem;
  CString strValue;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();

  strStringItem = "Bolometer Reader";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  iArg1 = m_Scale;     // Scale
  iArg2 = m_Digits;    // Digits
  iArg3 = m_Plc;       // PLC
  iArg4 = m_AZero ? 1 : 0; // AutoZero
  if(strValue != "") {
    sscanf(strValue, "%d, %d, %d, %d", &iArg1, &iArg2, &iArg3, &iArg4);
    m_Scale  = iArg1;                 // Scale
    m_Digits = iArg2;                 // Digits
    m_Plc    = iArg3;                 // PLC
    m_AZero  = (iArg4==1) ? true : false; // AutoZero
  }
  strValue.Format("%1d,%1d,%1d,%1d", iArg1, iArg2, iArg3, iArg4);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CBolReaderDlg::~CBolReaderDlg() {
}


void
CBolReaderDlg::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBolReaderDlg)
	DDX_Control(pDX, IDC_SCALE, cScale);
	DDX_Control(pDX, IDC_PLC, cPlc);
	DDX_Control(pDX, IDC_DIGITS, cDigits);
	DDX_Control(pDX, IDC_AZERO, cAZero);
	DDX_Check(pDX, IDC_AZERO, m_AZero);
	DDX_CBIndex(pDX, IDC_SCALE, m_Scale);
	DDX_CBIndex(pDX, IDC_PLC, m_Plc);
	DDX_CBIndex(pDX, IDC_DIGITS, m_Digits);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBolReaderDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CBolReaderDlg)
	ON_BN_CLICKED(IDC_AZERO, OnAzero)
	ON_CBN_SELCHANGE(IDC_DIGITS, OnSelchangeDigits)
	ON_CBN_SELCHANGE(IDC_PLC, OnSelchangePlc)
	ON_CBN_SELCHANGE(IDC_SCALE, OnSelchangeScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBolReaderDlg message handlers
/////////////////////////////////////////////////////////////////////////////



void 
CBolReaderDlg::OnAzero() {
  if(cAZero.GetCheck() == AZeroOld) {
    bAZeroChanged = false;
  } else {
    bAZeroChanged = true;
  }
  SetModified(bAZeroChanged || bDigitsChanged || bScaleChanged || bPlcChanged);
}


void 
CBolReaderDlg::OnSelchangeDigits() {
  if(cDigits.GetCurSel() == DigitsOld) {
    bDigitsChanged = false;
  } else {
    bDigitsChanged = true;
  }
  SetModified(bAZeroChanged || bDigitsChanged || bScaleChanged || bPlcChanged);
}


void 
CBolReaderDlg::OnSelchangePlc() {
  if(cPlc.GetCurSel() == PlcOld) {
    bPlcChanged = false;
  } else {
    bPlcChanged = true;
  }
  SetModified(bAZeroChanged || bDigitsChanged || bScaleChanged || bPlcChanged);
}


void 
CBolReaderDlg::OnSelchangeScale() {
  if(cScale.GetCurSel() == ScaleOld) {
    bScaleChanged = false;
  } else {
    bScaleChanged = true;
  }
  SetModified(bAZeroChanged || bDigitsChanged || bScaleChanged || bPlcChanged);
}



BOOL 
CBolReaderDlg::OnApply() {
  if(!(bAZeroChanged || bDigitsChanged || bScaleChanged || bPlcChanged)) return true;
  if(!UpdateData(true)) return FALSE;

  int iArg1, iArg2, iArg3, iArg4;
  CString strValue;

  iArg1 = m_Scale;    // Scale
  iArg2 = m_Digits;    // Digits
  iArg3 = m_Plc;    // PLC
  iArg4 = m_AZero ? 1 : 0; // AutoZero

	if(ScaleOld  != m_Scale)  pBolReader->ChangeScale(m_Scale+1);
  if(DigitsOld != m_Digits) pBolReader->ChangeDigits(m_Digits+4);
  if(PlcOld    != m_Plc)    pBolReader->ChangePlc(m_Plc+1);
  if(AZeroOld  != m_AZero)  pBolReader->ChangeAutoZero(iArg4);

  strValue.Format("%1d,%1d,%1d,%1d", iArg1, iArg2, iArg3, iArg4);

  CString strStringItem;
  CString strSection = "Configuration";
  CWinApp* pApp = AfxGetApp();
  strStringItem = "Bolometer Reader";
  pApp->WriteProfileString(strSection, strStringItem, strValue);

	bAZeroChanged  = false;
	bDigitsChanged = false;
	bScaleChanged  = false;
	bPlcChanged    = false;
	
	AZeroOld  = m_AZero;
	DigitsOld = m_Digits;
	ScaleOld  = m_Scale;
	PlcOld    = m_Plc;
		
  SetModified(bAZeroChanged || bDigitsChanged || bScaleChanged || bPlcChanged);
	return CPropertyPage::OnApply();
}


void
CBolReaderDlg::SetDevice(CBolReader* Device) {
  pBolReader = Device;
}


BOOL
CBolReaderDlg::OnInitDialog() {
	CPropertyPage::OnInitDialog();
  UpdateData(false);
  CString buf;
  cDigits.ResetContent();
  int minDigits = 4;
  int maxDigits;
  switch(modelNumber) {
    case 0: {
      maxDigits = 7;
      break;
    }
    case 1: {
      maxDigits = 9;
      break;
    }
    case 2: {
      maxDigits = 7;
      break;
    }
    default: {
      maxDigits = 9;
      break;
    }
  }
  for(int i=minDigits; i<=maxDigits; i++) {
    buf.Format("%1d", i);
    cDigits.AddString(buf);
  }
  if(m_Digits+4 > maxDigits) {
    m_Digits = maxDigits;
  }
  if(m_Digits+4 < minDigits) {
    m_Digits = minDigits;
  }
  cDigits.SetCurSel(m_Digits);

	bAZeroChanged  = false;
	bDigitsChanged = false;
	bScaleChanged  = false;
	bPlcChanged    = false;
	
	AZeroOld  = m_AZero;
	DigitsOld = m_Digits;
	ScaleOld  = m_Scale;
	PlcOld    = m_Plc;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

