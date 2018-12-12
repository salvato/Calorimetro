// CalorimetroDlg.cpp : file di implementazione
//

#include "stdafx.h"
#include "resource.h"
#include "math.h"
#include "float.h"
#include <fstream>

#include "Includes/LMheader.h"
#include "Includes/LMfcn.h"

#include "ni488.h"
#include "GpibNotify.h"

#include "EasterDlg.h"
#include "SplashDlg.h"
#include "WarningOverwriteDlg.h"

#include "BolReader.h"
#include "CurrGen.h"
#include "Pulser.h"
#include "TempController.h"
//#include "Sms10.h"

#include "Keithley2001.h"
#include "Keithley2002.h"
#include "Keithley2010.h"
#include "HP34401.h"
#include "Keithley263.h"
#include "LakeShore370.h"

#include "MsgWindow.h"
#include "Plot3.h"
#include "CalibPoint.h"

#include "MinuitDlg.h"
#include "DoFitDlg.h"

#include "CalorimetroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


double pw;
int    nprob;
int    njev;
int    nfev;

double *datax;
double *datay;
double *germx;
double *germy;

/// Per il Fit //////////////
double *xFit;
double *yFit;
double *yTheo;
int    nDati;
double pulW;
////////////////////////////

#define IDT_MEASURE     1
#define IDT_DELAY       2

#define BOL_PLOT_NUM    0
#define BOL_PLOT_ID     0
#define BOL_PEN         1
#define BOL_COLOR       RGB(255,255,0)
#define BOL_SYMB        CPlotWindow::ipoint

#define GE_PLOT_NUM     1
#define GE_PLOT_ID      0
#define GE_PEN          1
#define GE_COLOR        RGB(255,255,0)
#define GE_SYMB         CPlotWindow::ipoint

#define BOLRUN_PLOT_NUM 2
#define BOLRUN_PLOT_ID  0
#define BOLRUN_PEN      1
#define BOLRUN_COLOR    RGB(255,255,0)
#define BOLRUN_SYMB     CPlotWindow::ipoint

#define GERUN_PLOT_NUM  3
#define GERUN_PLOT_ID   0
#define GERUN_PEN       1
#define GERUN_COLOR     RGB(255,255,0)
#define GERUN_SYMB      CPlotWindow::ipoint

#define CP_T3_PLOT_NUM  4
#define CP_T3_PLOT_ID   0
#define CP_T3_PEN       1
#define CP_T3_COLOR     RGB(255,255,0)
#define CP_T3_SYMB      CPlotWindow::iplus

#define CP_T3_T_PLOT_NUM 4
#define CP_T3_TEMP_ID    1
#define CP_T3_T_PEN      1
#define CP_T3_T_COLOR    RGB(0,0,255)
#define CP_T3_T_SYMB     CPlotWindow::iper

#define CALIB_PLOT_NUM  5
#define CALIB_PLOT_ID   0
#define TMP_PLOT_ID     1
#define CALIB_PEN       1
#define CALIB_COLOR     RGB(255,255,0)
#define CALIB_SYMB      CPlotWindow::iplus

#define FIT_PLOT_ID     1
#define FIT_PEN         1
#define FIT_COLOR       RGB(255,255,255)
#define FIT_SYMB        CPlotWindow::iline


// finestra di dialogo CCalorimetroDlg




CCalorimetroDlg::CCalorimetroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalorimetroDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  strcpy(szFileBol, "");

  xControl = 0;
  yControl = 0;

  pDurationDlg          = NULL;
  pDoFitDlg             = NULL;
  pSettingsDlg          = NULL;
  pApiezonSettingsDlg   = NULL;
  pBolReaderSettingsDlg = NULL;
  pGeReaderSettingsDlg  = NULL;
  pCurrGenSettingsDlg   = NULL;
  pTControlSettingsDlg  = NULL;
	pConfigureDlg         = NULL;
	pPlotsDlg             = NULL;
	pPulserDlg            = NULL;
	pGeReaderDlg          = NULL;
	pCurrGenDlg           = NULL;
	pBolReaderDlg         = NULL;
  pTControlDlg          = NULL;
  pLakeShoreSetDlg      = NULL;
  pMinuitDlg            = NULL;

 	pTempCtrl  = NULL;
	pPulser    = NULL;
	pCurrGen   = NULL;
	pBolReader = NULL;
	pGeReader  = NULL;
	pMsgWindow = NULL;
//pSms10     = NULL;

  pCurrGenNotify     = NULL;
  pBolReaderNotify   = NULL;
  pGeReaderNotify    = NULL;
  pTControllerNotify = NULL;
  pSms10Notify       = NULL;

  datax = NULL;
  datay = NULL;
  germx = NULL;
  germy = NULL;
  xFit  = NULL;
  yFit  = NULL;
  yTheo = NULL;
  param = NULL;

  char* 
    Names[] = {"Bolometer", 
               "Germanium", 
               "Bol-Run",
               "Ge-Run",
               "Cp/T^3",
               "Bol-Calib"
              };

  int 
    Ids[] = {BOL_PLOT_ID,
             GE_PLOT_ID,
             BOLRUN_PLOT_ID,
             GERUN_PLOT_ID,
             CP_T3_PLOT_ID,
             CALIB_PLOT_ID
            };

  COLORREF 
    Colors[] = {BOL_COLOR,
                GE_COLOR,
                BOLRUN_COLOR,
                GERUN_COLOR,
                CP_T3_COLOR,
                CALIB_COLOR
               };

  int 
    Symbols[] = {BOL_SYMB,
                 GE_SYMB,
                 BOLRUN_SYMB,
                 GERUN_SYMB,
                 CP_T3_SYMB,
                 CALIB_SYMB
                };

  int 
    Pens[] = {BOL_PEN,
              GE_PEN,
              BOLRUN_PEN,
              GERUN_PEN,
              CP_T3_PEN,
              CALIB_PEN
             };

  nPlot = sizeof(Names)/sizeof(char*);
  pPlot = new CPlotWindow*[nPlot];
  pProperties = new CDataSetProperties*[nPlot];

  for(int i=0; i<nPlot; i++) {
    pPlot[i] = NULL;
    pProperties[i] = new CDataSetProperties(Ids[i], Pens[i], Colors[i], Symbols[i], Names[i]);
  }
}


CCalorimetroDlg::~CCalorimetroDlg() {

  if(datax != NULL) delete[] datax;
  if(datay != NULL) delete[] datay;
  if(germx != NULL) delete[] germx;
  if(germy != NULL) delete[] germy;
  if(xFit  != NULL) delete[] xFit;
  if(yFit  != NULL) delete[] yFit;
  if(yTheo != NULL) delete[] yTheo;
  if(param != NULL) delete[] param;

 	if(pTempCtrl          != NULL) delete pTempCtrl;
	if(pPulser            != NULL) delete pPulser;
	if(pCurrGen           != NULL) delete pCurrGen;
	if(pBolReader         != NULL) delete pBolReader;
	if(pGeReader          != NULL) delete pGeReader;
	if(pMsgWindow         != NULL) delete pMsgWindow;
  if(pSms10Notify       != NULL) delete pSms10Notify;
  if(pCurrGenNotify     != NULL) delete pCurrGenNotify;
  if(pBolReaderNotify   != NULL) delete pBolReaderNotify;
  if(pGeReaderNotify    != NULL) delete pGeReaderNotify;
  if(pTControllerNotify != NULL) delete pTControllerNotify;

//if(pSms10           != NULL) delete pSms10;
  if(pMinuitDlg            != NULL) delete pMinuitDlg;
  if(pDoFitDlg             != NULL) delete pDoFitDlg;
  if(pSettingsDlg          != NULL) delete pSettingsDlg;
  if(pApiezonSettingsDlg   != NULL) delete pApiezonSettingsDlg;
  if(pBolReaderSettingsDlg != NULL) delete pBolReaderSettingsDlg;
  if(pGeReaderSettingsDlg  != NULL) delete pGeReaderSettingsDlg;
  if(pCurrGenSettingsDlg   != NULL) delete pCurrGenSettingsDlg;
  if(pTControlSettingsDlg  != NULL) delete pTControlSettingsDlg;
	if(pConfigureDlg         != NULL) delete pConfigureDlg;
	if(pPlotsDlg             != NULL) delete pPlotsDlg;
	if(pPulserDlg            != NULL) delete pPulserDlg;
	if(pGeReaderDlg          != NULL) delete pGeReaderDlg;
	if(pCurrGenDlg           != NULL) delete pCurrGenDlg;
	if(pBolReaderDlg         != NULL) delete pBolReaderDlg;
	if(pTControlDlg          != NULL) delete pTControlDlg;
	if(pLakeShoreSetDlg      != NULL) delete pLakeShoreSetDlg;
	if(pDurationDlg          != NULL) delete pDurationDlg;

  for(int i=0; i<nPlot; i++) {
    if(pPlot[i] != NULL) delete pPlot[i];
    delete pProperties[i];
  }
  delete[] pPlot;
  delete[] pProperties;

}


void
CCalorimetroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROCESS_DATA, ButtonProcess);
	DDX_Control(pDX, IDC_STARTSTOP, ButtonStartStop);
	DDX_Control(pDX, IDC_SAVE, ButtonSave);
	DDX_Control(pDX, IDC_FIT, ButtonFit);
	DDX_Control(pDX, IDC_CONFIGURE, ButtonConfigure);
}


BEGIN_MESSAGE_MAP(CCalorimetroDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONFIGURE, OnConfigure)
	ON_WM_CREATE()
  ON_MESSAGE(GPIB_MSG, OnGPIBMsg)
  ON_MESSAGE(GPIB_DATA, OnGPIBData)
  ON_MESSAGE(BOL_READER_RUN_DATA, OnBolReaderRunData)
  ON_MESSAGE(BOL_READER_DATA, OnBolReaderData)
  ON_MESSAGE(GE_READER_RUN_DATA, OnGeReaderRunData)
  ON_MESSAGE(GE_READER_DATA, OnGeReaderData)
  ON_MESSAGE(FIT_DONE, OnFitDone)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_FIT, OnFitClicked)
	ON_BN_CLICKED(IDC_STARTSTOP, OnStartStop)
	ON_BN_CLICKED(IDC_BITMAP, OnBitmap)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_PROCESS_DATA, OnProcessData)
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CCalorimetroDlg, CDialog)
  ON_EVENT(CCalorimetroDlg, ID_CURR_GEN_NOTIFY,   1, OnCurrGenNotify,       VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4)
  ON_EVENT(CCalorimetroDlg, ID_BOL_READER_NOTIFY, 1, OnBolReaderNotify,     VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4)
  ON_EVENT(CCalorimetroDlg, ID_GE_READER_NOTIFY,  1, OnGeReaderNotify,      VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4)
  ON_EVENT(CCalorimetroDlg, ID_TCONTROL_NOTIFY,   1, OnLakeShore370Notify,  VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4)
//ON_EVENT(CCalorimetroDlg, ID_SMS10NOTIFY,       1, OnSms10Notify,     VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_PI4)
END_EVENTSINK_MAP()


bool
CCalorimetroDlg::ReadCbFile(CString BolCFile) {
  std::ifstream is;
  is.open(BolCFile, std::ios::in);
  if(is.fail()) {
    AfxMessageBox("File Not Found or File Error", MB_ICONQUESTION);
    is.close();
    return false;
  }
  char Line[256];
  CString sToken = " \t,\0";
  CString sTemp, sMsg;
  double x, y;
  int iLine = 0;
  while(!is.eof()) {
    try{
      is.getline(Line, sizeof(Line)-1);
      iLine++;
      if(Line != "") {
        sTemp = Line;
        x  = atof(strtok(Line, sToken));
        y  = atof(strtok(0, sToken));
        CbPoints.Add(CCbPoint(x, y));
      }
    } catch(...) {
      sMsg.Format("Problems in Bolometer Cb File:\nLine Number %d Read:\n", iLine);
      AfxMessageBox(sMsg + "\""+ sTemp + "\"");
      is.close();
      return false;
    }
  }
  is.close();
  //Ensure Cb is Sorted in Ascending Temperature Order
  CCbPoint tmp;

  for(int i=0; i<CbPoints.GetSize(); i++) {
    for(int j=0; j<CbPoints.GetSize()-1-i; j++) {
      if(CbPoints[j+1].T < CbPoints[j].T) {
        tmp = CbPoints[j];
        CbPoints[j] = CbPoints[j+1];
        CbPoints[j+1] = tmp;
      }
    }
  }
  return true;
}


// Restituisce il Calore Specifico del Bolometro alla temperatura T
double
CCalorimetroDlg::Cb(double T) {
  double T1=-1, T2=-1, C1=-1, C2=-1;
  double dMin1=FLT_MAX, dMin2=FLT_MAX, dMax1=-FLT_MAX, dMax2=-FLT_MAX;
  int i;
  for(i=0; i<CbPoints.GetSize(); i++) {
    if(CbPoints[i].T > T)
      break;
  }
  if(i==0) {// No points Cooler exists
    T1 = CbPoints[0].T;
    T2 = CbPoints[1].T;
    C1 = CbPoints[0].C;
    C2 = CbPoints[1].C;
  } else if(i==CbPoints.GetSize()) {// No Point Hotter exists
    T1 = CbPoints[i-2].T;
    T2 = CbPoints[i-1].T;
    C1 = CbPoints[i-2].C;
    C2 = CbPoints[i-1].C;
  } else {
    T1 = CbPoints[i-1].T;
    T2 = CbPoints[i].T;
    C1 = CbPoints[i-1].C;
    C2 = CbPoints[i].C;
  }
  return ((C2-C1)/(T2-T1) * (T-T1) + C1);
}


bool
CCalorimetroDlg::ComputeCp(double Tau, double deltaT, double *Cp) {
  if(FileInfo.GetUndef()) return false;
  *Cp = (pow(FileInfo.Current, 2)*FileInfo.RHeater*Tau) / deltaT;
//  if(FileInfo.PulseDuration > 3.0*Tau) {// Caso "a Regime"
//    *Cp = (pow(FileInfo.Current, 2)*FileInfo.RHeater*Tau) / deltaT;
//  } else {// Caso ad Impulso
//    *Cp = (pow(FileInfo.Current, 2)*FileInfo.RHeater*FileInfo.PulseDuration) / deltaT;
//  }
  double C1 = Cb(FileInfo.TGer);
  double C2 = CsAp(FileInfo.TGer)*FileInfo.ApiezonMass;
  *Cp = *Cp - C1 - C2;
  *Cp = *Cp / FileInfo.SampleMass;
  return true;
}


bool
CCalorimetroDlg::ReadBolCalFile(CString BolCalFile) {
  std::ifstream is;
  is.open(BolCalFile, std::ios::in);
  if(is.fail()) {
    is.close();
    return true;
  }
  char Line[256];
  CString sToken = " \t,\0";
  CString sTemp, sMsg;
  double x, y, sx, sy;
  int iLine = 0;
  while(!is.eof()) {
    try{
     is.getline(Line, sizeof(Line)-1);
      iLine++;
      if(Line != "") {
        sTemp = Line;
        x  = atof(strtok(Line, sToken));
        y  = atof(strtok(0, sToken));
        sx = atof(strtok(0, sToken));
        sy = atof(strtok(0, sToken));
        CalibPoints.Add(CCalibPoint(x, y, sx, sy));
      }
    } catch(...) {
      return false;
    }
  }
  is.close();
  return true;
}


void 
CCalorimetroDlg::bSort(double *val, int* ind, int n) {
  int i,j;
  double tmp;
  int itmp;

  for (i=0; i<n-1; i++) {
    for (j=0; j<n-1-i; j++)
      if (val[j+1] < val[j]) {
        tmp = val[j];
        val[j] = val[j+1];
        val[j+1] = tmp;
        itmp = ind[j];
        ind[j] = ind[j+1];
        ind[j+1] = itmp;
    }
  }
}


bool
CCalorimetroDlg::FindCoef(double *a, double *b, double tg) {
  double*  cPoints = new double[CalibPoints.GetSize()];
  int*    icPoints = new int[CalibPoints.GetSize()];
  double*  hPoints = new double[CalibPoints.GetSize()];
  int*    ihPoints = new int[CalibPoints.GetSize()];

  int nc = 0, nh = 0;
  double dist;

  // Divide Points Hotter and Colder of tg
  for(int i=0; i<CalibPoints.GetSize(); i++) {
    dist = CalibPoints[i].Tg - tg;
    if(dist < 0.0) {
      cPoints[nc] = fabs(dist);
      icPoints[nc] = i;
      nc++;
    } else {
      hPoints[nh] = fabs(dist);
      ihPoints[nh] = i;
      nh++;
    }
  }

  // Sort Calibration Points in Increasing Distance From the tg Point
  if(nc>1) bSort(cPoints, icPoints, nc);
  if(nh>1) bSort(hPoints, ihPoints, nh);

  int iCold = -1, iHott = -1;
  int ic, ih;
  double maxDist = 0.01*tg; // Clusters of Points no more the 5% of tg apart
	CArray<CCalibPoint,CCalibPoint&>  FitPoints;//Array Containing Points to Fit

  // Try to Find Clusters of Points Near tg
  for(ih=0; ih<nh; ih++) {
    if(hPoints[ih] > maxDist) break;
    FitPoints.Add(CalibPoints[ihPoints[ih]]);
  }
  for(ic=0; ic<nc; ic++) {
    if(cPoints[ic] > maxDist) break;
    FitPoints.Add(CalibPoints[icPoints[ic]]);
  }

  // Now Add One Point on the Hotter Side (if one exists)
  if(ih<nh) {
    FitPoints.Add(CalibPoints[ihPoints[ih]]);
    if(FitPoints.GetSize() < 2) {// We have yet Not enough Points to fit
      if(ic<nc) {
        FitPoints.Add(CalibPoints[icPoints[ic]]);
      } else {//Not enough points to fit...
        return false;
      }
    }
  } else {//Not Points Hotter exists
    if(ic<nc) {
      FitPoints.Add(CalibPoints[icPoints[ic]]);
      if(FitPoints.GetSize() < 2) {// We have yet Not enough Points to Fit
        return false;
      }
    } else {
      return false;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // Calcolo parametri della retta --> ln(Rb) = a*ln(Tg) + b
  // In questa scala la curva del sensore e' piu' simile ad una retta
  ////////////////////////////////////////////////////////////////////////////////

  //How Many Points We Got ?
  if(FitPoints.GetSize() < 2) { // Less than 2 ? Something wrong...
    delete[] cPoints;  cPoints  = NULL;
    delete[] hPoints;  hPoints  = NULL;
    delete[] icPoints; icPoints = NULL;
    delete[] ihPoints; ihPoints = NULL;
    return false;
  } else if(FitPoints.GetSize() > 2) { // More than 2 Points: we may do a Linear Regression
    double s1=0, sx=0, sy=0, sxy=0, sxx=0;
    for(int i=0; i<FitPoints.GetSize(); i++) {
      s1  = s1 + 1;
      sx  = sx + log(FitPoints[i].Tg);
      sy  = sy + log(FitPoints[i].Rb);
      sxy = sxy + log(FitPoints[i].Tg) * log(FitPoints[i].Rb);
      sxx = sxx + log(FitPoints[i].Tg) * log(FitPoints[i].Tg);
    }
    double den = s1*sxx - sx*sx;
    if(den != 0.0) {
      *a = (s1*sxy - sx*sy)  / den;
      *b = (sxx*sy - sx*sxy) / den;
    } else {// Revert to Straight Line
      double xa, xb, ya, yb;
      xa = log(FitPoints[0].Tg);
      ya = log(FitPoints[0].Rb);
      xb = log(FitPoints[1].Tg);
      yb = log(FitPoints[1].Rb);
      *a = (yb-ya)/(xb-xa);
      *b = yb - (*a)*xb;
    }
  } else {// Only 2 Points: Straight Line... what else ?
    double xa, xb, ya, yb;
    xa = log(FitPoints[0].Tg);
    ya = log(FitPoints[0].Rb);
    xb = log(FitPoints[1].Tg);
    yb = log(FitPoints[1].Rb);
    *a = (yb-ya)/(xb-xa);
    *b = yb - (*a) * xb;
  }
  delete[] cPoints;  cPoints  = NULL;
  delete[] hPoints;  hPoints  = NULL;
  delete[] icPoints; icPoints = NULL;
  delete[] ihPoints; ihPoints = NULL;

  return true;
}


bool 
CCalorimetroDlg::ProcessFile(CString FileDati) {
  if(!ReadApFile(pApiezonSettingsDlg->sFileCApiezon)) {
    AfxMessageBox("Error in Apiezon File");
    return false;
  }
  CString sTokens = " \t,\0";
  std::ifstream is;
  std::ofstream os;
  CString FileOut = FileDati.Left(FileDati.ReverseFind('.')) + ".ela";
  is.open(FileDati, std::ios::in);
  if(is.fail()) {
    is.close();
    return false;
  }
  //os.open(FileOut, std::ios::out, std::filebuf::sh_read);
  os.open(FileOut, std::ios::out);
  if(os.fail()) {
    AfxMessageBox("Could Not Open Output File");
    is.close();
    os.close();
    return false;
  }
  char cLine[256];
  CString sLine;
  double min, max, tg, pulseW, testC;
  double x, y, rMax=-FLT_MAX, rMin=FLT_MAX, r0=0;
  int np = -1;
  FileInfo.SetUndef();
  while(!is.eof()) {
    try{
	    is.getline(cLine, sizeof(cLine)-1);
      sLine = cLine;
      if(sLine.Find("=") == -1) {
        break;
      } else if(sLine.Find("BolMin") > -1) {
        min = atof(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("BolMax") > -1) {
        max = atof(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("Mean Temperature") > -1) {
        tg  = atof(sLine.Mid(sLine.Find("=")+1));
        FileInfo.TGer = tg;
      } else if(sLine.Find("PointNumber") > -1) {
        np  = atoi(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("Pulse Width") > -1) {
        pulseW  = atof(sLine.Mid(sLine.Find("=")+1));
        FileInfo.PulseDuration = pulseW;
      } else if(sLine.Find("Delay") > -1) {
        FileInfo.Delay = atof(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("Test Current") > -1) {
        testC  = atof(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("Pulse Current") > -1) {
        FileInfo.Current  = atof(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("Sample Mass") > -1) {
        FileInfo.SampleMass  = atof(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("Heater Res") > -1) {
        FileInfo.RHeater  = atof(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("Apiezon Mass") > -1) {
        FileInfo.ApiezonMass  = atof(sLine.Mid(sLine.Find("=")+1));
      } else if(sLine.Find("Bolometer T File") > -1) {
        FileInfo.BolTFile = sLine.Mid(sLine.Find("=")+1);
      } else if(sLine.Find("Bolometer C File") > -1) {
        FileInfo.BolCFile = sLine.Mid(sLine.Find("=")+1);
      }
    } catch(...) {
      AfxMessageBox("Error in File " + FileDati);
      is.close();
      os.close();
      return false;
    }
    os << sLine << std::endl;
  }
  if(np < 1) {
    AfxMessageBox("Error in File " + FileDati + " Incorrect Number of Points");
    is.close();
    os.close();
    return false;
  }
  if(FileInfo.GetUndef()) {
    AfxMessageBox("Error in File " + FileDati + "\n Maybe an Old Format File ?");
    is.close();
    os.close();
    return false;
  }
  if(!ReadCbFile(FileInfo.BolCFile)) {
    AfxMessageBox("Bolometer Cte File Corrupt !");
    return false;
  }
  CalibPoints.RemoveAll();// Rileggiamo da File i Punti di Calibrazione cosi' e'
                          // Possibile editarli e rimuovere eventuali misure non
                          // Valide o rumorose !
  if(!ReadBolCalFile(FileInfo.BolTFile) || CalibPoints.GetSize() < 1) {
    AfxMessageBox("Bolometer Calibration File Corrupt !");
    return false;
  }
  if(pPlot[CALIB_PLOT_NUM] != NULL) {
    pPlot[CALIB_PLOT_NUM]->DelDataSet(CALIB_PLOT_ID);
    pPlot[CALIB_PLOT_NUM]->NewDataSet(*pProperties[CALIB_PLOT_NUM]);
    for(int i=0; i<CalibPoints.GetSize(); i++) {
      pPlot[CALIB_PLOT_NUM]->NewPoint(CALIB_PLOT_ID, CalibPoints[i].Tg, CalibPoints[i].Rb);
    }
    pPlot[CALIB_PLOT_NUM]->SetShowDataSet(CALIB_PLOT_ID, true);
    pPlot[CALIB_PLOT_NUM]->UpdatePlot();
  }
  
  nDati = np;

  double a, b;
  if(!FindCoef(&a, &b, tg)) {
    AfxMessageBox("Not Enough Information to Fit " + FileDati);
    is.close();
    os.close();
    return false;
  }
  //Disegna la retta (nello spazio ln(X), ln(Y)) interpolante....
  if(pPlot[CALIB_PLOT_NUM] != NULL) {
    pPlot[CALIB_PLOT_NUM]->DelDataSet(TMP_PLOT_ID);
    double x1, x2, y1, y2;
    BOOL dummy;
    for(int i=0; i<CalibPoints.GetSize(); i++) {
      pPlot[CALIB_PLOT_NUM]->GetLimits(&x1, &x2, &y1, &y2, &dummy, &dummy, &dummy, &dummy);
      pPlot[CALIB_PLOT_NUM]->NewDataSet(TMP_PLOT_ID, 1, RGB(255,255,255), CPlotWindow::iline, "Temp");
      pPlot[CALIB_PLOT_NUM]->NewPoint(TMP_PLOT_ID, CalibPoints[i].Tg, exp(a*log(CalibPoints[i].Tg)+b));
      pPlot[CALIB_PLOT_NUM]->SetShowDataSet(TMP_PLOT_ID, true);
      pPlot[CALIB_PLOT_NUM]->SetMarkerPos(tg, exp(a*log(tg)+b));
      pPlot[CALIB_PLOT_NUM]->SetShowMarker(true);
      pPlot[CALIB_PLOT_NUM]->UpdatePlot();
    }
  }  
  
  xFit  = new double[nDati];
  yFit  = new double[nDati];
  yTheo = new double[nDati];
  param = new double[7];

  int i=0, nPunti=0;
  do{
    try{
      strcpy(cLine, sLine);
      x = atof(strtok(cLine, sTokens));
      y = atof(strtok(0, sTokens));
      y = exp((log(y)-b)/a);
      xFit[nPunti] = x;
      yFit[nPunti] = y;
      rMax = __max(rMax, yFit[nPunti]);
      rMin = __min(rMin, yFit[nPunti]);
      if(xFit[nPunti] < FileInfo.Delay) {
        r0 += yFit[i++];
      }
      nPunti++;
      sLine.Format("%f\t%f", x, y);
      os << sLine << std::endl;
	    is.getline(cLine, sizeof(cLine)-1);
      sLine = cLine;
    } catch(...) {
      AfxMessageBox("Error in File " + FileDati);
      is.close();
      os.close();
      delete[] param; param       = NULL;
      delete[] xFit; xFit         = NULL;
      delete[] yFit; yFit         = NULL;
      delete[] yTheo; yTheo       = NULL;
      return false;
    }
  } while(!is.eof());
  r0 /= (double)i; // Valor medio dei punti precedenti l'impulso


/////////////////////////////////////////////////////////////////////////////////
// Fit a Singolo Esponenziale                                                  //
//                                                                             //
//   par[0] = Variazione della Temperatura Dovuta all'Impulso di Corrente      //
//   par[1] = Costante di Tempo del Sistema                      //
//   par[2] = Baseline di Temperatura                                          //
//   par[3] = Istante di Inizio dell'Impulso di Corrente                       //
//   par[4] = Pendenza Fondo Lineare                                           //
//   par[5] = Temperatura Minima  da Cosiderare nel Fit -- Fissata dall'Utente //
//   par[6] = Temperatura Massima da Cosiderare nel Fit -- Fissata dall'Utente //
//                                                                             //
/////////////////////////////////////////////////////////////////////////////////
// Stima Iniziale
/////////////////////////////////////////////////////////////////////////////////

  param[0] = rMax - r0;
  param[1] = xFit[nPunti-1] / 10.0;
  param[2] = r0;
  param[3] = FileInfo.Delay;
  param[4] = 0.0;
  param[5] = xFit[0];
  param[6] = xFit[nPunti-1];

  pulW = pulseW;

  pMinuitDlg = new CMinuitDlg(this, pMsgWindow); 
  pMinuitDlg->Create(IDD_MINUIT_DIALOG, this);
  pMinuitDlg->SetFilename(FileInProcess);
  pMinuitDlg->SetPars(param, 7);

  is.close();
  os.close();
  return true;
}


/////////////////////////////////////////////////////////////////////////////
// Le Funzioni da Minimizzare:
//
// se: nprob == 0 Fitta i Dati del Germanio Con una Retta
//     nprob == 1 Fitta i Dati Grezzi del Bolometro Con Singolo Esponenziale
//                Sono ancora Valori Resistivi (NON in Temperatura !)
/////////////////////////////////////////////////////////////////////////////
int
CCalorimetroDlg::FitData(double* BolPar, double* GePar) {
  int i;
  int m = int(BolData.GetSize());
  int n = int(GeData.GetSize());

  if(m==0 && n==0) {
    AfxMessageBox("No Data to Fit");
    return -1;
  }

  datax = new double[m];
  datay = new double[m];
  germx = new double[n];
  germy = new double[n];

  double rMax = BolData[0].y;
  double rMin = BolData[0].y;
  for(i=0; i<m; i++) {
    datax[i] = BolData[i].x;
    datay[i] = BolData[i].y;
    rMax = __max(rMax, datay[i]);
    rMin = __min(rMin, datay[i]);
  }

  for(i=0; i<n; i++) {
    germx[i] = GeData[i].x;
    germy[i] = GeData[i].y;
  }

  pw        = hdr.PulseWidth;
  double ts = hdr.Delay;
  double r0 = datay[0];

  i = 1;
  while (i<m && datax[i]<ts) {
    r0 += datay[i];
    i++;
  }
  r0 /=(double)i; // Valor medio dei punti precedenti l'impulso

  int info;
  double tol = 1.0e-8;

  double* fvec = new double[m];

  ///////////////////////////////////////////////////////////////////////////// 
  // Fit a Singolo Esponenziale
  //
  //   BolPar[0] = Variazione resistiva dovuta all'impulso di corrente
  //   BolPar[1] = Costante di tempo del sistema
  //   BolPar[2] = Baseline di Resistenza
  //   BolPar[3] = Istante di inizio dell'impulso di corrente
  /////////////////////////////////////////////////////////////////////////////
  BolPar[0] = r0 - rMin;
  BolPar[1] = (datax[m-1] - (ts+pw))/3.0;//10.0 / datax[m-1];
  BolPar[2] = r0;
  BolPar[3] = ts;

  nprob = 1;
  try{
    lm_dif(LMfcn, m, 4, BolPar, fvec, tol, &info);
    if(!(info & 1)) lm_dif(LMfcn, m, 4, BolPar, fvec, tol, &info);
    ShowFitExp1(BolPar);
  } catch(...) {
    AfxMessageBox("Unable to Fit Bolometer Data");
  }

  int info1 = info;
  delete[] fvec; fvec = NULL;
  
  fvec = new double[n];

  /////////////////////////////////////////////////////////////////////////////
  // Fit Lineare
  //
  //   GePar[0] = Offset
  //   GePar[1] = Coefficiente Angolare
  /////////////////////////////////////////////////////////////////////////////
  GePar[1] = (germy[n-1] - germy[0])/(germx[n-1] - germx[0]);
  GePar[0] = germy[0] - GePar[1]*germx[n-1];

  nprob = 0;
  try{
    lm_dif(LMfcn, n, 2, GePar, fvec, tol, &info);
    ShowFitLin(GePar);
    if(!(info & 1)) lm_dif(LMfcn, n, 2, GePar, fvec, tol, &info);
  } catch(...) {
    AfxMessageBox("Unable to Fit Germanium Data");
  }

  delete[] fvec; fvec = NULL;

  delete[] datax; datax = NULL;
  delete[] datay; datay = NULL;
  delete[] germx; germx = NULL;
  delete[] germy; germy = NULL;

  return info*256+info1;
}


void
CCalorimetroDlg::ShowFitExp1(double* par) {
  if(pPlot[BOLRUN_PLOT_NUM] == NULL) return;

// Fit con Singolo esponenziale:
  double tau = par[1];
  double t0  = par[3];
  double y0  = par[2];
  double y1  = par[0];
  double t, y;
  double tend = t0 + pw;

  pPlot[BOLRUN_PLOT_NUM]->DelDataSet(FIT_PLOT_ID);
  pPlot[BOLRUN_PLOT_NUM]->NewDataSet(FIT_PLOT_ID, FIT_PEN, FIT_COLOR, FIT_SYMB, "Single Exp");
  for(int i=0; i<BolData.GetSize(); i++) {
    t = BolData[i].x;
    if(t <= t0) {
      y = y0;
    } else if(t <= tend) {
      y = y0 - y1*(1.0 - exp((t0-t)/tau));
    } else {
      y = y0 - y1*(1.0 - exp(-pw/tau)) * exp((tend-t)/tau);
    }
    pPlot[BOLRUN_PLOT_NUM]->NewPoint(FIT_PLOT_ID, t, y/pCurrGenDlg->Current);
  }  
  pPlot[BOLRUN_PLOT_NUM]->SetShowDataSet(FIT_PLOT_ID, true);
  pPlot[BOLRUN_PLOT_NUM]->UpdatePlot();
}


void
CCalorimetroDlg::ShowFitExp2(double* par) {
  if(pPlot[BOLRUN_PLOT_NUM] == NULL) return;

// Fit con Doppio esponenziale:
  double y1   = par[0];
  double tau1 = par[1];
  double y0   = par[2];
  double t0   = par[3];
  double y2   = par[4];
  double tau2 = par[5];
  double t, y;
  double tend = t0 + pw;

  pPlot[BOLRUN_PLOT_NUM]->DelDataSet(FIT_PLOT_ID);
  pPlot[BOLRUN_PLOT_NUM]->NewDataSet(FIT_PLOT_ID, FIT_PEN, FIT_COLOR, FIT_SYMB, "Single Exp");
  for(int i=0; i<BolData.GetSize(); i++) {
    t = BolData[i].x;
    if(t <= t0) {
      y = y0;
    } else if(t <= tend) {
      y = y0 - y1*(1.0 - exp((t0-t)/tau1)) - y2*(1.0 - exp((t0-t)/tau2));
    } else {
      y = y0 - y1*(1.0 - exp(-pw/tau1))*exp((tend-t)/tau1);
      y+=    - y2*(1.0 - exp(-pw/tau2))*exp((tend-t)/tau2);
    }
    pPlot[BOLRUN_PLOT_NUM]->NewPoint(FIT_PLOT_ID, t, y/pCurrGenDlg->Current);
  }  
  pPlot[BOLRUN_PLOT_NUM]->SetShowDataSet(FIT_PLOT_ID, true);
  pPlot[BOLRUN_PLOT_NUM]->UpdatePlot();
}


void
CCalorimetroDlg::ShowFitLin(double* par) {
  if(pPlot[GERUN_PLOT_NUM] == NULL) return;

  double a = par[1];
  double b = par[0];
  double t, y;

  pPlot[GERUN_PLOT_NUM]->DelDataSet(FIT_PLOT_ID);
  pPlot[GERUN_PLOT_NUM]->NewDataSet(FIT_PLOT_ID, FIT_PEN, FIT_COLOR, FIT_SYMB, "Single Exp");
  for(int i=0; i<GeData.GetSize(); i++) {
    t = GeData[i].x;
    y = a * t + b;
    pPlot[GERUN_PLOT_NUM]->NewPoint(FIT_PLOT_ID, t, y);
  }  
  pPlot[GERUN_PLOT_NUM]->SetShowDataSet(FIT_PLOT_ID, true);
  pPlot[GERUN_PLOT_NUM]->UpdatePlot();
}


void 
CCalorimetroDlg::CreateBolReader() {
  if(pBolReaderNotify != NULL) delete pBolReaderNotify;
    pBolReaderNotify = new CGpibNotify();

  if(!pBolReaderNotify->Create(NULL,0,CRect(CFrameWnd::rectDefault),this,ID_BOL_READER_NOTIFY)) {
    AfxMessageBox("Error: Could not Create Bol Reader Notify");
    PostQuitMessage(-1003);
    return;
  }
  if(pBolReader != NULL) delete pBolReader;

  switch(pBolReaderSettingsDlg->GetModelNumber()) {
    case 0: {
	    pBolReader = new CKeithley2001(this, pBolReaderSettingsDlg->GetAddress());
      break;
    }
    case 1: {
	    pBolReader = new CKeithley2002(this, pBolReaderSettingsDlg->GetAddress());
      break;
    }
    case 2: {
	    pBolReader = new CKeithley2010(this, pBolReaderSettingsDlg->GetAddress());
      break;
    }
    default: {
	    pBolReader = new CKeithley2002(this, pBolReaderSettingsDlg->GetAddress());
      break;
    }
  }
  pBolReaderDlg->SetDevice(pBolReader);
  int iAns;
retry:
  if(!pBolReader->Connect()) {
    iAns = AfxMessageBox("BolReader Not Connected or Switched OFF",MB_ABORTRETRYIGNORE);
    if (iAns == IDABORT) {
      PostQuitMessage(-1005);
      return;
    } else if(iAns == IDRETRY) {
      goto retry;
    } else {
      return;
    }
  }
  if(pBolReader->Connected) pBolReader->Init(pBolReaderNotify);
  if(pBolReader->Initialized) {
    pBolReader->ChangeScale(pBolReaderDlg->m_Scale+1);
    pBolReader->ChangeDigits(pBolReaderDlg->m_Digits+4);
    pBolReader->ChangePlc(pBolReaderDlg->m_Plc+1);
    pBolReader->ChangeAutoZero(pBolReaderDlg->m_AZero ? 1 : 0);
  }
}


void
CCalorimetroDlg::CreateGeReader() {
  if(pGeReaderNotify != NULL) delete pGeReaderNotify;
    pGeReaderNotify = new CGpibNotify();
  if(!pGeReaderNotify->Create(NULL,0,CRect(CFrameWnd::rectDefault),this,ID_GE_READER_NOTIFY)) {
    AfxMessageBox("Error: Could not Create Ge Reader Notify");
    PostQuitMessage(-1004);
    return;
  }

  if(pGeReader != NULL) delete pGeReader;

  switch(pGeReaderSettingsDlg->GetModelNumber()) {
    case 0: {
	    pGeReader = new CHP34401(this, pGeReaderSettingsDlg->GetAddress());
      break;
    }
    default: {
	    pGeReader = new CHP34401(this, pGeReaderSettingsDlg->GetAddress());
      break;
    }
  }

  int iAns;
  if(pGeReader != NULL) {
    pGeReaderDlg->SetDevice(pGeReader);
    retry:
    if(!pGeReader->Connect()) {
      iAns = AfxMessageBox("GeReader Not Connected or Switched OFF",MB_ABORTRETRYIGNORE);
      if (iAns == IDABORT) {
        PostQuitMessage(-1006);
        return;
      } else if(iAns == IDRETRY) {
        goto retry;
      } else {
        return;
      }
    }
retry2:
    if(!pGeReader->ReadChebCoef(pGeReaderDlg->m_FilePar)) {
      pConfigureDlg->SetActivePage(1);
      pConfigureDlg->DoModal();
      goto retry2;
    }
	  if(pGeReader->Connected) 
      pGeReader->Init(pGeReaderNotify);
	  if(pGeReader->Initialized) 
      pGeReader->ChangeScale(pGeReaderDlg->m_Range+1);
  }
}

void
CCalorimetroDlg::CreateCurrGen() {
  if(pCurrGenNotify != NULL) delete pCurrGenNotify;
    pCurrGenNotify= new CGpibNotify();
  if(!pCurrGenNotify->Create(NULL,0,CRect(CFrameWnd::rectDefault),this,ID_CURR_GEN_NOTIFY)) {
    AfxMessageBox("Error: Could not Create Current Generator Notify");
    PostQuitMessage(-1002);
    return;
  }

  if(pCurrGen != NULL) delete pCurrGen;

  switch(pCurrGenSettingsDlg->GetModelNumber()) {
    case 0: {
	    pCurrGen = new CKeithley263(this, pCurrGenSettingsDlg->GetAddress());
      break;
    }
    default: {
	    pCurrGen = new CKeithley263(this, pCurrGenSettingsDlg->GetAddress());
      break;
    }
  }
  pCurrGenDlg->SetDevice(pCurrGen);
  int iAns;
retry:
  if(!pCurrGen->Connect()) {
    iAns = AfxMessageBox("Current Generator Not Connected or Switched OFF",MB_ABORTRETRYIGNORE);
    if (iAns == IDABORT) {
      PostQuitMessage(-1007);
      return;
    } else if(iAns == IDRETRY) {
      goto retry;
    } else {
      return;
    }
  }
	if(pCurrGen->Connected)  pCurrGen->Init(pCurrGenNotify);
	if(pCurrGen->Initialized)  pCurrGen->ChangeCurrent(pCurrGenDlg->Current);
}


void
CCalorimetroDlg::CreateTControl() {

  if(pTControllerNotify != NULL) delete pTControllerNotify;
    pTControllerNotify= new CGpibNotify();

  if(!pTControllerNotify->Create(NULL,0,CRect(CFrameWnd::rectDefault),this,ID_TCONTROL_NOTIFY)) {
    AfxMessageBox("Error: Could not Create Temperature Control Notify");
    PostQuitMessage(-1002);
    return;
  }

  if(pTempCtrl != NULL) delete pTempCtrl;

  switch(pTControlSettingsDlg->GetModelNumber()) {
    case 0: {
	    pTempCtrl = new CTempCtrl(this, pTControlSettingsDlg->GetAddress());
      pTControlDlg->SetDevice(pTempCtrl);
      break;
    }
    case 1: {
	    pTempCtrl = new CLakeShore370(this, pTControlSettingsDlg->GetAddress());
      pLakeShoreSetDlg->SetDevice(pTempCtrl);
      break;
    }
    default: {
	    pTempCtrl = new CTempCtrl(this, pTControlSettingsDlg->GetAddress());
      pTControlDlg->SetDevice(pTempCtrl);
      break;
    }
  }
  int iAns;
retry:
  if(!pTempCtrl->Connect()) {
    iAns = AfxMessageBox("Temperature Control Not Connected or Switched OFF",MB_ABORTRETRYIGNORE);
    if (iAns == IDABORT) {
      PostQuitMessage(-1008);
      return;
    } else if(iAns == IDRETRY) {
      goto retry;
    } else {
      return;
    }
  }
  if(pTempCtrl->Connected) {
    switch(pTControlSettingsDlg->GetModelNumber()) {
      case 0: {
        pTempCtrl->Init(NULL);
        if(pTempCtrl->Initialized) pTempCtrl->Configure("\r\n");
	      pTempCtrl->ChangeCurrent(pTControlDlg->m_SensorCurrent+1);
        pTempCtrl->ChangeRSetPoint(pTControlDlg->m_Resistance);
        break;
      }
      case 1: {
        pTempCtrl->Init(pTControllerNotify);
        if(pTempCtrl->Initialized) {
          double SetPoint = pLakeShoreSetDlg->GetSetPoint();
	        pTempCtrl->ChangeRSetPoint(SetPoint);
        }
        break;
      }
      default: {
        pTempCtrl->Init(NULL);
        if(pTempCtrl->Initialized) pTempCtrl->Configure("\r\n");
	      pTempCtrl->ChangeCurrent(pTControlDlg->m_SensorCurrent+1);
        pTempCtrl->ChangeRSetPoint(pTControlDlg->m_Resistance);
        break;
      }
    }
  }
}


void
CCalorimetroDlg::CreatePulser() {
	pPulser    = new CPulser("PCI_82550001");
  pPulserDlg->SetDevice(pPulser);
  pPulser->Configure(pPulserDlg->m_Width, pPulserDlg->m_CurSel);
}


bool 
CCalorimetroDlg::CalibrateBolometer(double *Rb, double *Rg, double *sRb, double *sRg) {
  int n, nn, m, mm;
  
  m = int(BolData.GetSize());
  n = int(GeData.GetSize());
  
  double ts  = hdr.Delay;
  double cur = hdr.TestCurrent;

  if(cur < FLT_MIN) return false;

  double rb  = 0.0;//Bolometer Mean Value
  double rg  = 0.0;//Germanium Mean Value
  double srb = 0.0;//Bolometer Standard Deviation
  double srg = 0.0;//Germanium Standard Deviation

  if(n>0 && m>0) { //Get points before Pulse Start
    mm = 0;
    while (mm<m && BolData[mm].x<ts) {// Calculate Bolometer Mean Value
      rb += BolData[mm++].y;
    }
    if(mm==0) return false;
    rb = rb / (double(mm)*cur);

    nn = 0;
    while (nn<n && GeData[nn].x<ts) {// Calculate Germanium Mean Value
      rg += GeData[nn++].y;
    }
    if(nn==0) return false;
    rg /= double(nn);
    int i;
    for(i=0; i<mm; i++) {
      srb += pow(((BolData[i].y/cur)-rb), 2);
    }
    srb = pow(srb/double(mm), 0.5);

    for(i=0; i<nn; i++) {
      srg += pow((GeData[i].y-rg), 2);
    }
    srg = pow(srg/double(nn), 0.5);

    *Rb  = fabs(rb);
    *Rg  = fabs(rg);
    *sRb = srb;
    *sRg = srg;
    return true;
  }
  return false;
}


void
CCalorimetroDlg::AddCalibPoint(double Rb, double Rg, double sRb, double sRg) {
  LastCalibPoint = CCalibPoint(Rg, Rb, sRg, sRb);
  if(pPlot[CALIB_PLOT_NUM] != NULL) {
    pPlot[CALIB_PLOT_NUM]->DelDataSet(TMP_PLOT_ID);
    pPlot[CALIB_PLOT_NUM]->NewDataSet(TMP_PLOT_ID, 1, RGB(255,255,255), CPlotWindow::istar, "Temp");
    pPlot[CALIB_PLOT_NUM]->NewPoint(TMP_PLOT_ID, Rg, Rb);
    pPlot[CALIB_PLOT_NUM]->SetShowDataSet(TMP_PLOT_ID, true);
    pPlot[CALIB_PLOT_NUM]->UpdatePlot();
  }  
}


bool
CCalorimetroDlg::ReadApFile(CString ApFile) {
  std::ifstream is;
  is.open(ApFile, std::ios::in);
  if(is.fail()) {
    AfxMessageBox("File Not Found or File Error", MB_ICONQUESTION);
    is.close();
    return false;
  }
  AsPoints.RemoveAll();

  char Line[256];
  CString sToken = " \t,\0";
  CString sTemp, sMsg;
  double x, y;
  int iLine = 0;
  while(!is.eof()) {
    try{
      is.getline(Line, sizeof(Line)-1);
      iLine++;
      if(Line != "") {
        sTemp = Line;
        x  = atof(strtok(Line, sToken));
        y  = atof(strtok(0, sToken));
        AsPoints.Add(CCbPoint(x, y));
      }
    } catch(...) {
      sMsg.Format("Problems in Apiezon Cs File:\nLine Number %d Read:\n", iLine);
      AfxMessageBox(sMsg + "\""+ sTemp + "\"");
      is.close();
      return false;
    }
  }
  is.close();
  //Ensure As is Sorted in Ascending Temperature Order
  CCbPoint tmp;

  for(int i=0; i<AsPoints.GetSize(); i++) {
    for (int j=0; j<AsPoints.GetSize()-1-i; j++)
      if(AsPoints[j+1].T < AsPoints[j].T) {
        tmp = AsPoints[j];
        AsPoints[j] = AsPoints[j+1];
        AsPoints[j+1] = tmp;
    }
  }
  return true;
}


// Restituisce il Calore Specifico di un Grammo di Apiezon alla Temperatura T
double
CCalorimetroDlg::CsAp(double T) {
  double T1=-1, T2=-1, C1=-1, C2=-1;
  double dMin1=FLT_MAX, dMin2=FLT_MAX, dMax1=-FLT_MAX, dMax2=-FLT_MAX;
  int i;
  for(i=0; i<AsPoints.GetSize(); i++) {
    if(AsPoints[i].T > T)
      break;
  }
  if(i==0) {// No points Cooler exists
    T1 = AsPoints[0].T;
    T2 = AsPoints[1].T;
    C1 = AsPoints[0].C;
    C2 = AsPoints[1].C;
  } else if(i==AsPoints.GetSize()) {// No Point Hotter exists
    T1 = AsPoints[i-2].T;
    T2 = AsPoints[i-1].T;
    C1 = AsPoints[i-2].C;
    C2 = AsPoints[i-1].C;
  } else {
    T1 = AsPoints[i-1].T;
    T2 = AsPoints[i].T;
    C1 = AsPoints[i-1].C;
    C2 = AsPoints[i].C;
  }
  return ((C2-C1)/(T2-T1) * (T-T1) + C1);
}


void
CCalorimetroDlg::AddBolData(double x, double y) {
  BolData.Add(CMyPoint(x, y));
}


void
CCalorimetroDlg::AddGeData(double x, double y) {
  GeData.Add(CMyPoint(x, y));
}


void
CCalorimetroDlg::ClearBolData() {
  BolData.RemoveAll();
}


void
CCalorimetroDlg::ClearGeData() {
  GeData.RemoveAll();
}


// gestori di messaggi di CCalorimetroDlg

BOOL
CCalorimetroDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if(pSysMenu != NULL) {
  	pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_LOWLVLCNF, "Low Level Configuration");
	}
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	IsDirty   = false;
	IsRunning = false;
  
  CRect Rect;
  GetWindowRect(&Rect);
  Rect.SetRect(xControl, yControl, xControl+Rect.Width(), yControl+Rect.Height());
  MoveWindow(&Rect, true);

  ButtonSave.EnableWindow(IsDirty);
  ButtonFit.EnableWindow(false);
  ButtonProcess.EnableWindow(true);

  myCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
  SetCursor(myCursor);

	pMsgWindow = new CMsgWindow("Messages");
  SendIFC(0) ;
  
  CalibPoints.RemoveAll();

  pDurationDlg          = new CDurationDlg();
  pSettingsDlg          = new CLowLevelSettings("Low Level Configuration", this, 0);
	pConfigureDlg         = new CConfigureDlg("Configure");
  pDoFitDlg             = new CDoFitDlg();
  pApiezonSettingsDlg   = new CApiezonSettingsDlg();
  pBolReaderSettingsDlg = new CBolReaderSettings();
  pGeReaderSettingsDlg  = new CGeReaderSettings();
  pCurrGenSettingsDlg   = new CCurrGenSettings();
  pTControlSettingsDlg  = new CTControlSettings();
	pPlotsDlg             = new CPlotsDlg();
	pPulserDlg            = new CPulserDlg();
	pGeReaderDlg          = new CGeReaderDlg();
	pCurrGenDlg           = new CCurrGenDlg();
	pBolReaderDlg         = new CBolReaderDlg();
  pTControlDlg          = new CTControlDlg();
  pLakeShoreSetDlg      = new CLakeShoreSetDlg();
//********************* pMagnetDlg = new CMagnetDlg();

  pPlotsDlg->SetPlots(pPlot, pProperties, nPlot);

  pConfigureDlg->AddPage(pBolReaderDlg);
  pBolReaderDlg->modelNumber = pBolReaderSettingsDlg->GetModelNumber();
  pSettingsDlg->AddPage(pBolReaderSettingsDlg);
  CreateBolReader();

  pConfigureDlg->AddPage(pCurrGenDlg);
  pSettingsDlg->AddPage(pCurrGenSettingsDlg);
  CreateCurrGen();

  CreateTControl();
  if(pTControlSettingsDlg->GetModelNumber() == 0) {
    pConfigureDlg->AddPage(pTControlDlg);
  } else {
    pConfigureDlg->AddPage(pLakeShoreSetDlg);
  }
  pSettingsDlg->AddPage(pTControlSettingsDlg);

  pConfigureDlg->AddPage(pGeReaderDlg);
  pSettingsDlg->AddPage(pGeReaderSettingsDlg);
  if(!pTControlSettingsDlg->GetUseAsGeReader())
    CreateGeReader();
  else {
retry1:
    if(!pTempCtrl->ReadChebCoef(pGeReaderDlg->m_FilePar)) {
      pConfigureDlg->SetActivePage(1);
      pConfigureDlg->DoModal();
      goto retry1;
    }
	  if(pTempCtrl->Connected) 
      pTempCtrl->StartReadingR();
  }

  pConfigureDlg->AddPage(pPulserDlg);
  CreatePulser();

  pConfigureDlg->AddPage(pPlotsDlg);
  pSettingsDlg->AddPage(pApiezonSettingsDlg);

//pConfigureDlg->AddPage(pMagnetDlg);
//pSms10     = new CSms10(this, 21);
//pMagnetDlg->SetDevice(pSms10);

  if(pPlot[CALIB_PLOT_NUM] != NULL) {
    if(CalibPoints.GetSize() > 0) {
      for(int i=0; i<CalibPoints.GetSize(); i++) {
        pPlot[CALIB_PLOT_NUM]->NewPoint(CALIB_PLOT_ID, CalibPoints.ElementAt(i).Tg, CalibPoints.ElementAt(i).Rb);
      }
      pPlot[CALIB_PLOT_NUM]->UpdatePlot();
    }  
  }

  if(pPlot[CP_T3_PLOT_NUM] != NULL) {
    pPlot[CP_T3_PLOT_NUM]->DelDataSet(CP_T3_PLOT_ID);
    pPlot[CP_T3_PLOT_NUM]->NewDataSet(*pProperties[CP_T3_PLOT_NUM]);
    pPlot[CP_T3_PLOT_NUM]->SetShowDataSet(CP_T3_PLOT_ID, true);
    pPlot[CP_T3_T_PLOT_NUM]->DelDataSet(CP_T3_TEMP_ID);
    pPlot[CP_T3_T_PLOT_NUM]->SetShowDataSet(CP_T3_TEMP_ID, true);
    pPlot[CP_T3_T_PLOT_NUM]->NewDataSet(CP_T3_TEMP_ID, CP_T3_PEN, CP_T3_T_COLOR, CP_T3_T_SYMB, "On Run");;
    pPlot[CP_T3_PLOT_NUM]->UpdatePlot();
  }
  
	return TRUE;  // restituisce TRUE a meno che non venga impostato lo stato attivo su un controllo.
}


void
CCalorimetroDlg::OnProcessData() {
  ButtonStartStop.EnableWindow(false);
  ButtonConfigure.EnableWindow(false);
  ButtonFit.EnableWindow(false);
  ButtonSave.EnableWindow(false);
  char szFilter[] = "File Dati (*.dat)|*.dat|All Files (*.*)|*.*||";
  char szDefExt[] = "dat";
  CFileDialog FileDialog(TRUE, szDefExt, "", OFN_HIDEREADONLY, szFilter);
  CString Prompt = "Choose File to Process";
  FileDialog.m_ofn.lpstrTitle = LPCTSTR(Prompt);
	if(FileDialog.DoModal() == IDOK) {
    FileInProcess = FileDialog.GetPathName();
    if(ProcessFile(FileInProcess)) {// Il Fit !!
      ButtonProcess.EnableWindow(false);
    }
  }
  ButtonStartStop.EnableWindow(true);
  ButtonConfigure.EnableWindow(true);
  ButtonFit.EnableWindow(true);
  ButtonSave.EnableWindow(IsDirty);
}


void
CCalorimetroDlg::OnCurrGenNotify(long ud, long Ibsta, long Iberr, long Ibcntl, 
                      long FAR* RearmMask) {
    pCurrGen->SRQService(ud, Ibsta, Iberr, Ibcntl, RearmMask);
}


void
CCalorimetroDlg::OnBolReaderNotify(long ud, long Ibsta, long Iberr, long Ibcntl, 
                      long FAR* RearmMask) {
    pBolReader->SRQService(ud, Ibsta, Iberr, Ibcntl, RearmMask);
}


void
CCalorimetroDlg::OnGeReaderNotify(long ud, long Ibsta, long Iberr, long Ibcntl, 
                      long FAR* RearmMask) {
    pGeReader->SRQService(ud, Ibsta, Iberr, Ibcntl, RearmMask);
}


void
CCalorimetroDlg::OnLakeShore370Notify(long ud, long Ibsta, long Iberr, long Ibcntl, long FAR* RearmMask) {
  pTempCtrl->SRQService(ud, Ibsta, Iberr, Ibcntl, RearmMask);
}


void 
CCalorimetroDlg::OnSysCommand(UINT nID, LPARAM lParam) {
  if(nID == IDM_LOWLVLCNF) {
    if(!IsRunning) {
      pSettingsDlg->DoModal();
      if(pApiezonSettingsDlg->bSettingChanged) {
        if(!ReadApFile(pApiezonSettingsDlg->sFileCApiezon)) {
          AfxMessageBox("Error in Apiezon File");
        }
        pApiezonSettingsDlg->bSettingChanged = false;
      }
      if(pBolReaderSettingsDlg->bSettingChanged) {
        if(pBolReader != NULL)
          pBolReader->Disconnect();
        CreateBolReader();
        pBolReaderSettingsDlg->bSettingChanged = false;
      }
      if(pTControlSettingsDlg->bSettingChanged) {
        if(pTempCtrl != NULL)
          pTempCtrl->Disconnect();
        CreateTControl();
        pTControlSettingsDlg->bSettingChanged = false;
        if(pTControlSettingsDlg->GetModelNumber() == 0) {
          for(int i=0; i<pConfigureDlg->GetPageCount(); i++) {
            if(pConfigureDlg->GetPage(i) == pLakeShoreSetDlg) {
              pConfigureDlg->RemovePage(pLakeShoreSetDlg);
              pConfigureDlg->AddPage(pTControlDlg);
              break;
            }
          }
        } else {
          for(int i=0; i<pConfigureDlg->GetPageCount(); i++) {
            if(pConfigureDlg->GetPage(i) == pTControlDlg) {
              pConfigureDlg->RemovePage(pTControlDlg);
              pConfigureDlg->AddPage(pLakeShoreSetDlg);
              break;
            }
          }
        }
        if(!pTControlSettingsDlg->GetUseAsGeReader()) {
          if(pGeReader == NULL) {
             CreateGeReader();
          }
        } else {
          if(pGeReader != NULL) {
            pGeReader->Disconnect();
            delete pGeReader;
            pGeReader = NULL;
            if(pGeReaderNotify != NULL){
              delete pGeReaderNotify;
              pGeReaderNotify = NULL;
            }
          }
retry3:
          if(!pTempCtrl->ReadChebCoef(pGeReaderDlg->m_FilePar)) {
            pConfigureDlg->SetActivePage(1);
            pConfigureDlg->DoModal();
            goto retry3;
          }
	        if(pTempCtrl->Connected) 
            pTempCtrl->StartReadingR();
        }
      }
      if(pGeReaderSettingsDlg->bSettingChanged) {
        if(pGeReader != NULL)
          pGeReader->Disconnect();
        CreateGeReader();
        pGeReaderSettingsDlg->bSettingChanged = false;
      }
    }
  }
	CDialog::OnSysCommand(nID, lParam);
}


void
CCalorimetroDlg::OnPaint() {
	if(IsIconic()) {
		CPaintDC dc(this); // contesto di periferica per il disegno
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}


HCURSOR
CCalorimetroDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int 
CCalorimetroDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

  myCursor = AfxGetApp()->LoadStandardCursor(IDC_APPSTARTING);
  SetCursor(myCursor);

  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Dialog";
  GetWindowText(strStringItem);
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    xControl = atoi(strtok(buf, ","));
    yControl = atoi(strtok(0, "\0"));
    delete[] buf;
  }

  CSplashDlg SplashDlg;
  SplashDlg.DoModal();
	return 0;
}


void 
CCalorimetroDlg::OnConfigure() {
  pConfigureDlg->DoModal();
  if(pPlot[CALIB_PLOT_NUM] != NULL) {
    if(CalibPoints.GetSize() > 0) {
      pPlot[CALIB_PLOT_NUM]->DelDataSet(CALIB_PLOT_ID);
      pPlot[CALIB_PLOT_NUM]->NewDataSet(*pProperties[CALIB_PLOT_NUM]);
      for(int i=0; i<CalibPoints.GetSize(); i++) {
        pPlot[CALIB_PLOT_NUM]->NewPoint(CALIB_PLOT_ID, CalibPoints.ElementAt(i).Tg, CalibPoints.ElementAt(i).Rb);
      }
      pPlot[CALIB_PLOT_NUM]->SetShowDataSet(CALIB_PLOT_ID, true);
      pPlot[CALIB_PLOT_NUM]->UpdatePlot();
    }  
  }
  if(pPlot[CP_T3_PLOT_NUM] != NULL) {
    if(CpPoints.GetSize() > 0) {
      pPlot[CP_T3_PLOT_NUM]->DelDataSet(CP_T3_PLOT_ID);
      pPlot[CP_T3_PLOT_NUM]->NewDataSet(*pProperties[CP_T3_PLOT_NUM]);
      pPlot[CP_T3_T_PLOT_NUM]->DelDataSet(CP_T3_TEMP_ID);
      pPlot[CP_T3_T_PLOT_NUM]->NewDataSet(CP_T3_TEMP_ID, CP_T3_T_PEN, CP_T3_T_COLOR, CP_T3_T_SYMB, "On Run");;
      double t3;
      int i;
      for(i=0; i<CpPoints.GetSize(); i++) {
        t3 = pow(CpPoints.ElementAt(i).T, 3);
        pPlot[CP_T3_PLOT_NUM]->NewPoint(CP_T3_PLOT_ID, CpPoints.ElementAt(i).T, CpPoints.ElementAt(i).C/t3);
      }
      for(i=0; i<CpPoints_Temp.GetSize(); i++) {
        t3 = pow(CpPoints_Temp.ElementAt(i).T, 3);
        pPlot[CP_T3_T_PLOT_NUM]->NewPoint(CP_T3_PLOT_ID, CpPoints_Temp.ElementAt(i).T, CpPoints_Temp.ElementAt(i).C/t3);
      }
      pPlot[CP_T3_PLOT_NUM]->SetShowDataSet(CP_T3_PLOT_ID, true);
      pPlot[CP_T3_T_PLOT_NUM]->SetShowDataSet(CP_T3_TEMP_ID, true);
      pPlot[CP_T3_PLOT_NUM]->UpdatePlot();
    }  
  }
}


afx_msg LRESULT 
CCalorimetroDlg::OnGPIBMsg(WPARAM wParam, LPARAM lParam) {
  CString Msg = (char *)lParam;
  pMsgWindow->AddText(Msg+= "\r\n");
  return LRESULT(0);
}


afx_msg LRESULT 
CCalorimetroDlg::OnGPIBData(WPARAM wParam, LPARAM lParam) {
  CString Msg = (char *)lParam;
  pMsgWindow->AddText(Msg+= "\r\n");
  return LRESULT(0);
}


afx_msg LRESULT 
CCalorimetroDlg::OnBolReaderRunData(WPARAM wParam, LPARAM lParam) {
  IsDirty   = true;
  char* pMsg = (char *)lParam;
  double x, y;
  x = atof(strtok(pMsg, ";"));
  y = atof(strtok(0, "\0"));
  if(y > BolMax) BolMax = y;
  if(y < BolMin) BolMin = y;
  AddBolData(x, y);
  if(pPlot[BOLRUN_PLOT_NUM] != NULL) {
    pPlot[BOLRUN_PLOT_NUM]->NewPoint(BOLRUN_PLOT_ID, x, y/pCurrGenDlg->Current);
    pPlot[BOLRUN_PLOT_NUM]->UpdatePlot();
  }  
  return LRESULT(0);
}


afx_msg LRESULT 
CCalorimetroDlg::OnBolReaderData(WPARAM wParam, LPARAM lParam) {
  char* pMsg = (char *)lParam;
  double x, y;
  x = atof(strtok(pMsg, ";"));
  y = atof(strtok(0, "\0"));
  if(pPlot[BOL_PLOT_NUM] != NULL) {
    pPlot[BOL_PLOT_NUM]->NewPoint(BOL_PLOT_ID, x, y/pCurrGenDlg->Current);
    pPlot[BOL_PLOT_NUM]->UpdatePlot();
  }  
  return LRESULT(0);
}


afx_msg LRESULT 
CCalorimetroDlg::OnGeReaderRunData(WPARAM wParam, LPARAM lParam) {
  char* pMsg = (char *)lParam;
  double x, y;
  x = atof(strtok(pMsg, ";"));
  y = atof(strtok(0, "\0"));
  AddGeData(x, y);
  if(pPlot[GERUN_PLOT_NUM] != NULL) {
    pPlot[GERUN_PLOT_NUM]->NewPoint(GERUN_PLOT_ID, x, y);
    pPlot[GERUN_PLOT_NUM]->UpdatePlot();
  }  
  return LRESULT(0);
}


afx_msg LRESULT 
CCalorimetroDlg::OnGeReaderData(WPARAM wParam, LPARAM lParam) {
  char* pMsg = (char *)lParam;
  double x, y;
  x = atof(strtok(pMsg, ";"));
  y = atof(strtok(0, "\0"));
  if(pPlot[GE_PLOT_NUM] != NULL) {
    pPlot[GE_PLOT_NUM]->NewPoint(GE_PLOT_ID, x, y);
    pPlot[GE_PLOT_NUM]->UpdatePlot();
  }  
  return LRESULT(0);
}


void 
CCalorimetroDlg::OnStartStop() {
  CString Text;
  ButtonStartStop.GetWindowText(Text);
  if(Text == "Stop") {
    KillTimer(IDT_MEASURE);
    KillTimer(IDT_DELAY);
    IsRunning = false;
    myCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    SetCursor(myCursor);
  	pPulser->TriggerOff();
  	pPulser->SetPulseWidth(pPulser->PW);
    pBolReader->StopRun();
    if(pTControlSettingsDlg->GetUseAsGeReader()) {
      pTempCtrl->StopRun();
    } else {
      pGeReader->StopRun();
    }
    ButtonStartStop.SetWindowText("Start");
    ButtonConfigure.EnableWindow(true);
    ButtonFit.EnableWindow(true);
    ButtonSave.EnableWindow(IsDirty);
    ButtonProcess.EnableWindow(true);

    double Rb, Rg, sRb, sRg;
    if(CalibrateBolometer(&Rb, &Rg, &sRb, &sRg)) {
      AddCalibPoint(Rb, Rg, sRb, sRg);
    }
    return;
  }
	if(IsDirty){
		if(AfxMessageBox("Data Not Saved !\nDiscard Old Data ?",
					MB_YESNO | MB_ICONQUESTION) != IDYES){
      return;
    }
  }
  IsDirty = false;//No Data Yet
	if(!StartRun()) {
    ButtonConfigure.EnableWindow(true);
    ButtonFit.EnableWindow(true);
    ButtonSave.EnableWindow(IsDirty);
    ButtonProcess.EnableWindow(true);
  } else {
    BolMin = DBL_MAX;
    BolMax = -BolMin;
    ButtonStartStop.SetWindowText("Stop");
    ButtonConfigure.EnableWindow(false);
    ButtonProcess.EnableWindow(false);
    ButtonFit.EnableWindow(false);
    ButtonSave.EnableWindow(IsDirty);
    myCursor = AfxGetApp()->LoadStandardCursor(IDC_APPSTARTING);
    SetCursor(myCursor);
    IsRunning = true;
  }
}


bool 
CCalorimetroDlg::StartRun() {
  if(!ReadApFile(pApiezonSettingsDlg->sFileCApiezon)) {
    AfxMessageBox("Error in Apiezon File");
    return false;
  }
  if(pDurationDlg->iDuration < int((pPulserDlg->m_Delay+pPulserDlg->m_Width)*1.1)) {
    pDurationDlg->iDuration = int((pPulserDlg->m_Delay+pPulserDlg->m_Width)*1.1);
  }
  if(pDurationDlg->DoModal() != IDOK) 
    return false;

  hdr.Delay       = pPulserDlg->m_Delay;
  hdr.Current     = pPulserDlg->GetCurrent();
  hdr.PulseWidth  = pPulserDlg->m_Width;
  hdr.TestCurrent = pCurrGenDlg->Current;

  if(pDurationDlg->Checked1) {
    hdr.WireResistance = atof(pDurationDlg->sRFili1);
    hdr.HeaterResistance = atof(pDurationDlg->sRTot1) - hdr.WireResistance;
    hdr.SampleMass  = atof(pDurationDlg->sMass1);
    hdr.ApiezonMass = atof(pDurationDlg->sAMass1);
    hdr.BolTFile    = pDurationDlg->sFileT1;
    hdr.BolCFile    = pDurationDlg->sFileC1;
  } else if(pDurationDlg->Checked2){
    hdr.WireResistance = atof(pDurationDlg->sRFili2);
    hdr.HeaterResistance = atof(pDurationDlg->sRTot2) - hdr.WireResistance;
    hdr.SampleMass  = atof(pDurationDlg->sMass2);
    hdr.ApiezonMass = atof(pDurationDlg->sAMass2);
    hdr.BolTFile    = pDurationDlg->sFileT2;
    hdr.BolCFile    = pDurationDlg->sFileC2;
  } else if(pDurationDlg->Checked3){
    hdr.WireResistance = atof(pDurationDlg->sRFili3);
    hdr.HeaterResistance = atof(pDurationDlg->sRTot3) - hdr.WireResistance;
    hdr.SampleMass  = atof(pDurationDlg->sMass3);
    hdr.ApiezonMass = atof(pDurationDlg->sAMass3);
    hdr.BolTFile    = pDurationDlg->sFileT3;
    hdr.BolCFile    = pDurationDlg->sFileC3;
  } else {
    hdr.WireResistance = atof(pDurationDlg->sRFili4);
    hdr.HeaterResistance = atof(pDurationDlg->sRTot4) - hdr.WireResistance;
    hdr.SampleMass  = atof(pDurationDlg->sMass4);
    hdr.ApiezonMass = atof(pDurationDlg->sAMass4);
    hdr.BolTFile    = pDurationDlg->sFileT4;
    hdr.BolCFile    = pDurationDlg->sFileC4;
  }
  
  if(!ReadCbFile(hdr.BolCFile)) return false;

  CalibPoints.RemoveAll();// Rileggiamo da File i Punti di Calibrazione cosi' e'
                          // Possibile Editarli e Rimuovere eventuali Misure non
                          // Valide o Rumorose !
  if(!ReadBolCalFile(hdr.BolTFile)) {
    AfxMessageBox("Bolometer Calibration File Corrupt !");
    return false;
  }
  if(pPlot[CALIB_PLOT_NUM] != NULL) {
    pPlot[CALIB_PLOT_NUM]->DelDataSet(CALIB_PLOT_ID);
    pPlot[CALIB_PLOT_NUM]->NewDataSet(*pProperties[CALIB_PLOT_NUM]);
    for(int i=0; i<CalibPoints.GetSize(); i++) {
      pPlot[CALIB_PLOT_NUM]->NewPoint(CALIB_PLOT_ID, CalibPoints[i].Tg, CalibPoints[i].Rb);
    }
    pPlot[CALIB_PLOT_NUM]->SetShowDataSet(CALIB_PLOT_ID, true);
    pPlot[CALIB_PLOT_NUM]->UpdatePlot();
  }
  
  ClearBolData();
  ClearGeData();
  if(pPlot[BOLRUN_PLOT_NUM] != NULL) {
    pPlot[BOLRUN_PLOT_NUM]->ClearPlot();
    pPlot[BOLRUN_PLOT_NUM]->NewDataSet(*pProperties[BOLRUN_PLOT_NUM]);
    pPlot[BOLRUN_PLOT_NUM]->SetShowDataSet(pProperties[BOLRUN_PLOT_NUM]->GetId(), true);
    pPlot[BOLRUN_PLOT_NUM]->UpdatePlot();
  }
  if(pPlot[GERUN_PLOT_NUM] != NULL) {
    pPlot[GERUN_PLOT_NUM]->ClearPlot();
    pPlot[GERUN_PLOT_NUM]->NewDataSet(*pProperties[GERUN_PLOT_NUM]);
    pPlot[GERUN_PLOT_NUM]->SetShowDataSet(pProperties[GERUN_PLOT_NUM]->GetId(), true);
    pPlot[GERUN_PLOT_NUM]->UpdatePlot();
  }
  if(pPlot[CALIB_PLOT_NUM] != NULL) {
    pPlot[CALIB_PLOT_NUM]->DelDataSet(TMP_PLOT_ID);
    pPlot[CALIB_PLOT_NUM]->SetShowMarker(false);
    pPlot[CALIB_PLOT_NUM]->UpdatePlot();
  }

 	UINT MilliSec = pDurationDlg->iDuration * 1000;// In milliseconds
 	if(SetTimer(IDT_MEASURE, MilliSec, NULL) == 0) {
	  AfxMessageBox("Unable to set Timer 0", MB_ICONSTOP);
		return false;
	}

  UINT Delay = UINT(pPulserDlg->m_Delay * 1000.0);
	if(Delay == 0)
    pPulser->TriggerOn();
  else if (SetTimer(IDT_DELAY, Delay, NULL) == 0) {
    MessageBox("Unable to set Delay Timer", "Error", MB_ICONSTOP);
    return false;
  }

 	bool result = pBolReader->StartRun();
  if(!result) {
    pBolReader->StopRun();
  } else {
    if(pTControlSettingsDlg->GetUseAsGeReader())
      result &= pTempCtrl->StartRun();
    else
      result &= pGeReader->StartRun();
    if(!result) {
      pBolReader->StopRun();
      if(pTControlSettingsDlg->GetUseAsGeReader())
        pTempCtrl->StopRun();
      else
        pGeReader->StopRun();
    }
  }
  if(!result) {
    KillTimer(IDT_MEASURE);
    KillTimer(IDT_DELAY);
  }
  return result;
}


void 
CCalorimetroDlg::OnTimer(UINT nIDEvent) {
  switch(nIDEvent) {

  case IDT_MEASURE:

    KillTimer(IDT_MEASURE);
    KillTimer(IDT_DELAY);

    IsRunning = false;

    myCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    SetCursor(myCursor);

  	pPulser->TriggerOff();
  	pPulser->SetPulseWidth(pPulser->PW);

    pBolReader->StopRun();
    if(pTControlSettingsDlg->GetUseAsGeReader())
      pTempCtrl->StopRun();
    else
      pGeReader->StopRun();

    double Rb, Rg, sRb, sRg;
    if(CalibrateBolometer(&Rb, &Rg, &sRb, &sRg)) {
      AddCalibPoint(Rb, Rg, sRb, sRg);
    }

    AfxMessageBox("Measure Terminated:\nTime elapsed");

    ButtonStartStop.SetWindowText("Start");
    ButtonConfigure.EnableWindow(true);
    ButtonFit.EnableWindow(true);
    ButtonSave.EnableWindow(IsDirty);
    ButtonProcess.EnableWindow(true);
    break;

  case IDT_DELAY:
    KillTimer(nIDEvent);
    pPulser->TriggerOn();
    break;
  }	
	CDialog::OnTimer(nIDEvent);
}


void 
CCalorimetroDlg::OnSave() {
  if(!IsDirty) {
    AfxMessageBox("Nothing to Save");
    return;
  }

  double BolPar[4], GePar[2];

  int iRes = FitData(BolPar, GePar);
  if(iRes & 0x03) {
    double a, b, tg=LastCalibPoint.Tg;
    if(FindCoef(&a, &b, tg)) {
      //Disegna la retta (nello spazio ln(X), ln(Y)) interpolante....
      if(pPlot[CALIB_PLOT_NUM] != NULL) {
        pPlot[CALIB_PLOT_NUM]->DelDataSet(TMP_PLOT_ID);
        double x1, x2, y1, y2;
        BOOL dummy;
        for(int i=0; i<CalibPoints.GetSize(); i++) {
          pPlot[CALIB_PLOT_NUM]->GetLimits(&x1, &x2, &y1, &y2, &dummy, &dummy, &dummy, &dummy);
          pPlot[CALIB_PLOT_NUM]->NewDataSet(TMP_PLOT_ID, 1, RGB(255,255,255), CPlotWindow::iline, "Temp");
          pPlot[CALIB_PLOT_NUM]->NewPoint(TMP_PLOT_ID, CalibPoints[i].Tg, exp(a*log(CalibPoints[i].Tg)+b));
          pPlot[CALIB_PLOT_NUM]->SetShowDataSet(TMP_PLOT_ID, true);
          pPlot[CALIB_PLOT_NUM]->SetMarkerPos(tg, exp(a*log(tg)+b));
          pPlot[CALIB_PLOT_NUM]->SetShowMarker(true);
          pPlot[CALIB_PLOT_NUM]->UpdatePlot();
        }
      }
      double t1 = BolPar[2]/hdr.TestCurrent;
      double t2 = (BolPar[2]-BolPar[0])/hdr.TestCurrent;
      if(t1 > 0.0) t1 = exp((log(t1)-b)/a);
      if(t2 > 0.0) t2 = exp((log(t2)-b)/a);
      double DeltaT = t2-t1;
      if(DeltaT > 0.0) {
        double Cp;
        FileInfo.SetUndef();
        FileInfo.TGer          = tg;
        FileInfo.PulseDuration = hdr.PulseWidth;
        FileInfo.Delay         = hdr.Delay;
        FileInfo.Current       = hdr.Current;
        FileInfo.SampleMass    = hdr.SampleMass;
        FileInfo.ApiezonMass   = hdr.ApiezonMass;
        FileInfo.RHeater       = hdr.HeaterResistance;
        FileInfo.BolCFile      = hdr.BolCFile;
        FileInfo.BolTFile      = hdr.BolTFile;

        if(ComputeCp(BolPar[1], DeltaT, &Cp)) {
          CpPoints_Temp.Add(CCpPoint(FileInfo.TGer, Cp));
          if(pPlot[CP_T3_T_PLOT_NUM] != NULL) {
            pPlot[CP_T3_T_PLOT_NUM]->NewPoint(CP_T3_TEMP_ID, tg, Cp/pow(tg, 3));
            pPlot[CP_T3_T_PLOT_NUM]->UpdatePlot();
          }  
        }
        FileInfo.SetUndef();
      }
    }
  }

  int i;
  char szFilter[] = "Bolometer Data (*.dat)|*.dat|All Files (*.*)|*.*||";
  char szDefExt[] = "dat";
  CFileDialog FileDialog(FALSE, szDefExt, szFileBol, 
                         OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
  if(FileDialog.DoModal() == IDOK) {
    strcpy(szFileBol, FileDialog.GetFileTitle());

    std::ofstream os(FileDialog.GetPathName());

	  os	<< "Pulse Current    =" << hdr.Current                   << "\n"
		  	<< "Apiezon Mass [g] =" << hdr.ApiezonMass               << "\n"
			  << "PointNumber      =" << int(BolData.GetSize())        << "\n"
			  << "Pulse Width [s]  =" << hdr.PulseWidth                << "\n";
	  os	<< "BolStartValue    =" << LastCalibPoint.Rb             << "\n"
  			<< "BolStandardDev   =" << LastCalibPoint.sRb            << "\n"
  			<< "BolMin           =" << BolMin/hdr.TestCurrent        << "\n"
  			<< "BolMax           =" << BolMax/hdr.TestCurrent        << "\n";
  	os	<< "Mean Temperature =" << LastCalibPoint.Tg             << "\n"
  			<< "Sigma T          =" << LastCalibPoint.sTg            << "\n"
  			<< "Bolometer T File =" << hdr.BolTFile                  << "\n"
  			<< "Wire Resistance  =" << hdr.WireResistance            << "\n"
  			<< "Heater Res       =" << hdr.HeaterResistance          << "\n"
  			<< "Delay            =" << hdr.Delay                     << "\n";
  	os	<< "Bolometer C File =" << hdr.BolCFile                  << "\n"
  			<< "Tau              =" << BolPar[1]                     << "\n"
  			<< "Delta R          =" << BolPar[0]/hdr.TestCurrent     << "\n"
  			<< "Intercetta Ge    =" << GePar[0]                      << "\n"
  			<< "Pendenza Ge      =" << GePar[1]                      << "\n"
  			<< "Sample Mass      =" << hdr.SampleMass                << "\n"
  			<< "Test Current     =" << hdr.TestCurrent               << "\n";

  	for(i=0; i<BolData.GetSize(); i++) {
  		os << BolData[i].x << "\t" << BolData[i].y/hdr.TestCurrent << "\n";
  	}
  	os.close();

    std::ofstream fs;
    //fs.open(hdr.BolTFile, std::ios::out|std::ios::app, filebuf::sh_read);
    fs.open(hdr.BolTFile, std::ios::out|std::ios::app);
    if(fs.fail()) {
      AfxMessageBox("Could Not Save the Bolometer Calibration Data");
    } else {
      fs << std::endl << LastCalibPoint.Tg  // Temperatura del Germanio
         << "\t" << LastCalibPoint.Rb  // Resistenza del Bolometro
         << "\t" << LastCalibPoint.sTg // Deviazione Standard Temperatura Germanio
         << "\t" << LastCalibPoint.sRb;// Deviazione Standard Resistenza Bolometro
      fs.close();
    }
    CalibPoints.Add(LastCalibPoint);
    if(pPlot[CALIB_PLOT_NUM] != NULL) {
      pPlot[CALIB_PLOT_NUM]->DelDataSet(TMP_PLOT_ID);
      pPlot[CALIB_PLOT_NUM]->NewPoint(CALIB_PLOT_ID, LastCalibPoint.Tg, LastCalibPoint.Rb);
      pPlot[CALIB_PLOT_NUM]->UpdatePlot();
    }  
  	IsDirty = false;
    ButtonSave.EnableWindow(IsDirty);
  }
}


void 
CCalorimetroDlg::OnFitClicked() {
	int i;
  int m = int(BolData.GetSize());
  int n = int(GeData.GetSize());

  if(m==0 && n==0) {
    AfxMessageBox("No Data to Fit");
    return;
  }
  pDoFitDlg->m_Ger = n;
  pDoFitDlg->m_Bol = m;

  datax = new double[m];
  datay = new double[m];
  germx = new double[n];
  germy = new double[n];

  double rMax = BolData[0].y;
  double rMin = BolData[0].y;
  for(i=0; i<m; i++) {
    datax[i] = BolData[i].x;
    datay[i] = BolData[i].y;
    rMax = __max(rMax, datay[i]);
    rMin = __min(rMin, datay[i]);
  }
  for(i=0; i<n; i++) {
    germx[i] = GeData[i].x;
    germy[i] = GeData[i].y;
  }

  pw             = hdr.PulseWidth;
  double ts      = hdr.Delay;
  double current = hdr.TestCurrent;
  double wr      = hdr.WireResistance;
  double hr      = hdr.HeaterResistance;

  double r0;
  r0 = datay[0];
  i = 1;
  while (i<m && datax[i]<ts) {
    r0 += datay[i];
    i++;
  }
  r0 /=(double)i; // Valor medio dei punti precedenti l'impulso

// Fit con Singolo esponenziale: Stima Iniziale
  pDoFitDlg->FitExp1Dlg.m_tau = datax[m-1] / 10.0;
  pDoFitDlg->FitExp1Dlg.m_t0  = ts;
  pDoFitDlg->FitExp1Dlg.m_y0  = r0;
  pDoFitDlg->FitExp1Dlg.m_y1  = r0 - rMin;

// Fit con Doppio esponenziale: Stima Iniziale
  pDoFitDlg->FitExp2Dlg.m_tau1 = datax[m-1] / 100.0;
  pDoFitDlg->FitExp2Dlg.m_tau2 = pDoFitDlg->FitExp2Dlg.m_tau1/10.0;
  pDoFitDlg->FitExp2Dlg.m_t0 = ts;
  pDoFitDlg->FitExp2Dlg.m_y0 = r0;
  pDoFitDlg->FitExp2Dlg.m_y1 = 0.5 * (r0 - rMin);
  pDoFitDlg->FitExp2Dlg.m_y2 = 0.5 * (r0 - rMin);

// Fit Lineare: Stima Iniziale
  double a = (germy[n-1] - germy[0])/(germx[n-1] - germx[0]);
  r0 = germy[0];
  double tfin= germx[0];
  double b = r0 - a*tfin;
  pDoFitDlg->FitLinDlg.m_a = a;
  pDoFitDlg->FitLinDlg.m_b = b;

  double *par;
  par = NULL;
// Execute Fit Dialog
  pDoFitDlg->DoModal();
  if(pDoFitDlg->FitExp1Dlg.fitDone) {
    if(par != NULL) delete[] par;
    par = new double[4];
    par[0] = pDoFitDlg->FitExp1Dlg.m_y1;
    par[1] = pDoFitDlg->FitExp1Dlg.m_tau;
    par[2] = pDoFitDlg->FitExp1Dlg.m_y0;
    par[3] = pDoFitDlg->FitExp1Dlg.m_t0;
    ShowFitExp1(par);
  }
  if(pDoFitDlg->FitExp2Dlg.fitDone) {
    if(par != NULL) delete[] par;
    par = new double[6];
    par[0] = pDoFitDlg->FitExp2Dlg.m_y1;
    par[1] = pDoFitDlg->FitExp2Dlg.m_tau1;
    par[2] = pDoFitDlg->FitExp2Dlg.m_y0;
    par[3] = pDoFitDlg->FitExp2Dlg.m_t0;
    par[4] = pDoFitDlg->FitExp2Dlg.m_y2;
    par[5] = pDoFitDlg->FitExp2Dlg.m_tau2;
    ShowFitExp2(par);
  }
  if(pDoFitDlg->FitLinDlg.fitDone) {
    if(par != NULL) delete[] par;
    par = new double[2];
    par[0] = pDoFitDlg->FitLinDlg.m_b;
    par[1] = pDoFitDlg->FitLinDlg.m_a;
    ShowFitLin(par);
  }

  if(par != NULL) {
    delete[] par;
    par = NULL;
  }

  delete[] datax; datax = NULL;
  delete[] datay; datay = NULL;
  delete[] germx; germx = NULL;
  delete[] germy; germy = NULL;
}


BOOL
CCalorimetroDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
  if(wParam == 2 && lParam == 0) {
    if(AfxMessageBox("Terminate Program:\nAre you Sure?", MB_APPLMODAL|MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)== IDYES) {

      CString strValue;
      CString strSection;
      CString strStringItem;
      CWinApp* pApp = AfxGetApp();
      GetWindowText(strStringItem);
      if(!IsIconic()) {
        strSection = "Dialog";
        CRect Rect;
        GetWindowRect(&Rect);
        strValue.Format("%d,%d", Rect.left, Rect.top);  
        pApp->WriteProfileString(strSection, strStringItem, strValue);
      }
      return CDialog::OnCommand(wParam, lParam);
    }
    return TRUE;
  }
	return CDialog::OnCommand(wParam, lParam);
}


void 
CCalorimetroDlg::OnBitmap() {
  CEasterDlg EasterDlg;
  EasterDlg.DoModal();
}


BOOL 
CCalorimetroDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
  if(pWnd == this) {
    SetCursor(myCursor);
    return false;
  } else {
  	return CDialog::OnSetCursor(pWnd, nHitTest, message);
  }
}


LRESULT
CCalorimetroDlg::OnFitDone(WPARAM wParam, LPARAM lParam) {
  if(wParam == IDOK) {
    pMinuitDlg->GetPars(param, 7);
    if(pPlot[CALIB_PLOT_NUM] != NULL) {
      pPlot[CALIB_PLOT_NUM]->DelDataSet(TMP_PLOT_ID);
      pPlot[CALIB_PLOT_NUM]->SetShowMarker(false);
      pPlot[CALIB_PLOT_NUM]->UpdatePlot();
    }
    //Calcola Cp
    double Cp;
    if(ComputeCp(param[1], param[0], &Cp)) {
      CpPoints.Add(CCpPoint(FileInfo.TGer, Cp));
      double t3 = pow(FileInfo.TGer, 3);
      if(pPlot[CP_T3_PLOT_NUM] != NULL) {
        pPlot[CP_T3_PLOT_NUM]->NewPoint(CP_T3_PLOT_ID, FileInfo.TGer, Cp/t3);
        pPlot[CP_T3_PLOT_NUM]->UpdatePlot();
      }  
    }
  }

  delete pMinuitDlg; pMinuitDlg = NULL;
  delete[] xFit; xFit   = NULL;
  delete[] yFit; yFit   = NULL;
  delete[] yTheo; yTheo = NULL;
  delete[] param; param = NULL;

  ButtonProcess.EnableWindow(true);
  return LRESULT(0);
}
