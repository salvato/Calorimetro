/////////////////////////////////////////////////////////////////////////////
// DoFitDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "resource.h"
#include "DoFitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDoFitDlg dialog
/////////////////////////////////////////////////////////////////////////////

CDoFitDlg::CDoFitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoFitDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CDoFitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_iFitType = 0;//0 = Single Exp; 1 = Double Exp; 2 = Linear.
  m_iDataSet = 1;//0 = Germanio; 1 = Bolometro.
}


void
CDoFitDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoFitDlg)
	DDX_Control(pDX, IDOK, m_b_OK);
	DDX_Control(pDX, IDC_EXP1, m_bSingle);
	DDX_Control(pDX, IDC_EXP2, m_bDouble);
	DDX_Control(pDX, IDC_LIN, m_bLinear);
	DDX_Control(pDX, IDC_GER, m_bGer);
	DDX_Control(pDX, IDC_BOL, m_bBol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoFitDlg, CDialog)
	//{{AFX_MSG_MAP(CDoFitDlg)
	ON_BN_CLICKED(IDC_BOL, OnBolClicked)
	ON_BN_CLICKED(IDC_EXP1, OnExp1Clicked)
	ON_BN_CLICKED(IDC_EXP2, OnExp2Clicked)
	ON_BN_CLICKED(IDC_GER, OnGerClicked)
	ON_BN_CLICKED(IDC_LIN, OnLinClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoFitDlg message handlers
/////////////////////////////////////////////////////////////////////////////

void
CDoFitDlg::OnGerClicked() {
  m_iDataSet = 1;
  m_bSingle.SetCheck(0);
  m_bDouble.SetCheck(0);
  m_bSingle.EnableWindow(FALSE);
  m_bDouble.EnableWindow(FALSE);
  m_bLinear.EnableWindow(TRUE);
  m_bLinear.SetCheck(1);
  OnLinClicked();
}


void
CDoFitDlg::OnBolClicked() {
  m_iDataSet = 0;
  m_bSingle.EnableWindow(TRUE);
  m_bDouble.EnableWindow(TRUE);
  m_bLinear.EnableWindow(FALSE);
  m_bSingle.SetCheck(1);
  m_bDouble.SetCheck(0);
  m_bLinear.SetCheck(0);
  OnExp1Clicked();
}


void
CDoFitDlg::OnExp1Clicked() {
  if(m_iFitType == 0)
    return;
  if(m_iFitType == 1) {
    FitExp2Dlg.DestroyWindow();
  } else {
    FitLinDlg.DestroyWindow();
  }
  FitExp1Dlg.Create(IDD_EXP1, this);
  m_iFitType = 0;
}


void
CDoFitDlg::OnExp2Clicked() {
  if(m_iFitType == 1)
    return;
  if(m_iFitType == 0) {
    FitExp1Dlg.DestroyWindow();
  } else {
    FitLinDlg.DestroyWindow();
  }
  FitExp2Dlg.Create(IDD_EXP2, this);
  m_iFitType = 1;
}


void
CDoFitDlg::OnLinClicked() {
  if(m_iFitType == 2)
    return;
  if(m_iFitType == 0) {
    FitExp1Dlg.DestroyWindow();
  } else {
    FitExp2Dlg.DestroyWindow();
  }
  FitLinDlg.Create(IDD_LIN, this);
  m_iFitType = 2;
}


BOOL
CDoFitDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	m_b_OK.EnableWindow(FALSE);
  switch(m_iFitType) {
    case 0: {
      FitExp1Dlg.Create(IDD_EXP1, this);
      m_bSingle.SetCheck(1);
      break;
    }
    case 1: {
      FitExp2Dlg.Create(IDD_EXP2, this);
      m_bDouble.SetCheck(1);
      break;
    }
    case 2: {
      FitLinDlg.Create(IDD_LIN, this);
      m_bLinear.SetCheck(1);
      break;
    }
  }
  switch(m_iDataSet) {
    case 0: {
      OnGerClicked();
      m_bGer.SetCheck(1);
      break;
    }
    case 1: {
      OnBolClicked();
      m_bBol.SetCheck(1);
      break;
    }
  }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void
CDoFitDlg::OnOK() {
  if(!FitLinDlg.fitDone) {
    AfxMessageBox("Germanium Data not yet fitted !");
    return;
  }
  if(!FitExp1Dlg.fitDone && !FitExp2Dlg.fitDone) {
    AfxMessageBox("Bolometer Data not yet fitted !");
    return;
  }
  switch(m_iFitType	) {
    case 0: {
      FitExp1Dlg.DestroyWindow();
      break;
    }
    case 1: {
      FitExp2Dlg.DestroyWindow();
      break;
    }
    case 2: {
      FitLinDlg.DestroyWindow();
      break;
    }
  }
  CDialog::OnOK();
}

void
CDoFitDlg::OnCancel() {
  switch(m_iFitType	) {
    case 0: {
      FitExp1Dlg.DestroyWindow();
      break;
    }
    case 1: {
      FitExp2Dlg.DestroyWindow();
      break;
    }
    case 2: {
      FitLinDlg.DestroyWindow();
      break;
    }
  }
  CDialog::OnCancel();
}

