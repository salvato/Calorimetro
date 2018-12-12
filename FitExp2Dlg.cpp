/////////////////////////////////////////////////////////////////////////////
// FitExp2Dlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Includes/LMheader.h"
#include "Includes/LMfcn.h"
#include "resource.h"
#include "DoFitDlg.h"
#include "FitExp2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern double *datax;
extern double *datay;
extern double *germx;
extern double *germy;
extern double pw;
extern int    nprob;
extern int    njev;
extern int    nfev;


/////////////////////////////////////////////////////////////////////////////
// CFitExp2Dlg dialog
/////////////////////////////////////////////////////////////////////////////


CFitExp2Dlg::CFitExp2Dlg(CDoFitDlg* pParent /*=NULL*/)
	: CDialog(CFitExp2Dlg::IDD, (CDialog*)pParent) {
	//{{AFX_DATA_INIT(CFitExp2Dlg)
	m_tau1 = 0.0;
	m_tau2 = 0.0;
	m_t0   = 0.0;
	m_y0   = 0.0;
	m_y1   = 0.0;
	m_y2   = 0.0;
	m_Chi2 = 0.0;
	//}}AFX_DATA_INIT
  myParent = pParent;
  fitDone = false;
}


void
CFitExp2Dlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFitExp2Dlg)
	DDX_Control(pDX, IDC_T0, m_e_t0);
	DDX_Control(pDX, IDC_F2, m_e_tau2);
	DDX_Control(pDX, IDC_F1, m_e_tau1);
	DDX_Control(pDX, IDC_Y2, m_e_y2);
	DDX_Control(pDX, IDC_Y1, m_e_y1);
	DDX_Control(pDX, IDC_Y0, m_e_y0);
	DDX_Control(pDX, IDOK, m_b_ok);
	DDX_Control(pDX, IDC_CHI2, m_eChi2);
	DDX_Control(pDX, IDC_OVERFLOW, m_bOverflow);
	DDX_Control(pDX, IDC_CONVERGED, m_bConverged);
	DDX_Text(pDX, IDC_F1, m_tau1);
	DDX_Text(pDX, IDC_F2, m_tau2);
	DDX_Text(pDX, IDC_T0, m_t0);
	DDX_Text(pDX, IDC_Y0, m_y0);
	DDX_Text(pDX, IDC_Y1, m_y1);
	DDX_Text(pDX, IDC_Y2, m_y2);
	DDX_Text(pDX, IDC_CHI2, m_Chi2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFitExp2Dlg, CDialog)
	//{{AFX_MSG_MAP(CFitExp2Dlg)
	ON_BN_CLICKED(IDOK, OnDoFitClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFitExp2Dlg message handlers
/////////////////////////////////////////////////////////////////////////////

BOOL CFitExp2Dlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void
CFitExp2Dlg::OnDoFitClicked() {
  UpdateData(TRUE);
  m_b_ok.EnableWindow(FALSE);
  m_e_y0.EnableWindow(FALSE);
  m_e_y1.EnableWindow(FALSE);
  m_e_y2.EnableWindow(FALSE);
  m_e_t0.EnableWindow(FALSE);
  m_e_tau1.EnableWindow(FALSE);
  m_e_tau2.EnableWindow(FALSE);
  FitData();
  UpdateData(FALSE);
  m_b_ok.EnableWindow(TRUE);
  m_e_y0.EnableWindow(TRUE);
  m_e_y1.EnableWindow(TRUE);
  m_e_y2.EnableWindow(TRUE);
  m_e_t0.EnableWindow(TRUE);
  m_e_tau1.EnableWindow(TRUE);
  m_e_tau2.EnableWindow(TRUE);
}


BOOL
CFitExp2Dlg::OnCommand(WPARAM wParam, LPARAM lParam) {
  if(wParam == 2 && lParam == 0)
    return TRUE;
	
	return CDialog::OnCommand(wParam, lParam);
}


BOOL
CFitExp2Dlg::DestroyWindow() {
  UpdateData(TRUE);
  return CDialog::DestroyWindow();
}


BOOL
CFitExp2Dlg::Create(UINT nID, CDoFitDlg* pParent) {
  myParent = pParent;	
	return CDialog::Create(IDD, pParent);
}


void
CFitExp2Dlg::FitData() {
  int info, n, m;
  double tol = 1.0e-6;
  double* par;

  fitDone = false;
  myParent->m_b_OK.EnableWindow(FALSE);
  n = 6;
  par = new double[n];
  par[0] = m_y1;
  par[1] = m_tau1;
  par[2] = m_y0;
  par[3] = m_t0;
  par[4] = m_y2;
  par[5] = m_tau2;
  
  nprob = 2;
  m = myParent->m_Bol; 

  double* fvec = new double[m];

  lm_dif(LMfcn, m, n, par, fvec, tol, &info);
  
  m_y1   = par[0];
  m_tau1 = par[1];
  m_y0   = par[2];
  m_t0   = par[3];
  m_y2   = par[4];
  m_tau2 = par[5];
  UpdateData(false);
  if(info < 0 || (info/16) !=0) {
    m_eChi2.EnableWindow(FALSE);
    m_bOverflow.EnableWindow(TRUE);
    m_bOverflow.SetCheck(1);
    m_bConverged.EnableWindow(FALSE);
    m_bConverged.SetCheck(0);
  } else {
    m_bOverflow.EnableWindow(FALSE);
    m_bOverflow.SetCheck(0);
    info &= 0xF;
    m_eChi2.EnableWindow(TRUE);
    m_Chi2 = eunorm(m, fvec);
    if(info>0 && info<5) {
      m_bConverged.EnableWindow(TRUE);
      m_bConverged.SetCheck(1);
      fitDone = true;
      if(myParent->FitExp2Dlg.fitDone)
        myParent->m_b_OK.EnableWindow(TRUE);
    }
  }

  delete[] par;
  delete[] fvec;
}
