// CalorimetroDlg.h : file di intestazione
//

#pragma once


#include "CpPoint.h"
#include "CbPoint.h"
#include "CalibPoint.h"
#include "MyPoint.h"
#include "DoFitDlg.h"
//********************#include "MagnetDlg.h"
#include "ApiezonSettingsDlg.h"
#include "BolReaderSettings.h"
#include "GeReaderSettings.h"
#include "CurrGenSettings.h"
#include "TControlSettings.h"
#include "LakeShoreSetDlg.h"
#include "LowLevelSettings.h"
#include "GeReaderDlg.h"
#include "BolReaderDlg.h"
#include "CurrGenDlg.h"
#include "GeReaderDlg.h"
#include "PulserDlg.h"
#include "TControlDlg.h"
#include "PlotsDlg.h"
#include "GpibNotify.h"
#include "FileHeader.h"
#include "ConfigureDlg.h"
#include "MinuitDlg.h"
#include "FileInfo.h"	// Added by ClassView
#include "DurationDlg.h"

class	CTempCtrl;
class CPulser;
class CKei263;
class CBolReader;
class CGeReader;
class CTempController;
//********************class CSms10;

class CDataSetProperties;
class CPlotWindow;
class CMsgWindow;

// finestra di dialogo CCalorimetroDlg
class CCalorimetroDlg : public CDialog
{
// Costruzione
public:
	CCalorimetroDlg(CWnd* pParent = NULL);	// costruttore standard
	virtual ~CCalorimetroDlg();

// Dati della finestra di dialogo
	enum { IDD = IDD_CONTROLPANEL };
	CButton	ButtonProcess;
	CButton	ButtonStartStop;
	CButton	ButtonSave;
	CButton	ButtonFit;
	CButton	ButtonConfigure;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// supporto DDX/DDV
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);


// Implementazione
public:
	void CreateTControl();

protected:
	HICON m_hIcon;

	// Funzioni generate per la mappa dei messaggi
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConfigure();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnGPIBMsg(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGPIBData(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnBolReaderRunData(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnBolReaderData(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGeReaderRunData(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnGeReaderData(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnFitDone(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSave();
	afx_msg void OnFitClicked();
	afx_msg void OnStartStop();
	afx_msg void OnBitmap();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnProcessData();

  DECLARE_EVENTSINK_MAP()
	DECLARE_MESSAGE_MAP()


private:
	double CsAp(double T);
	bool ReadApFile(CString ApFile);
  bool ReadCbFile(CString BolCFile);
	double Cb(double T);
	bool ComputeCp(double tau, double deltaT, double *Cp);
	CFileInfo FileInfo;
	CString FileInProcess;
	double* param;
  CMinuitDlg* pMinuitDlg;
	int FitData(double* BolPar, double* GePar);
	bool ReadBolCalFile(CString BolCalFile);
	double BolMax;
	double BolMin;
  bool FindCoef(double *a, double *b, double tg);
	bool ProcessFile(CString FileDati);
	void ShowFitLin(double* par);
	void ShowFitExp1(double* par);
	void ShowFitExp2(double* par);
	HCURSOR myCursor;
	CCalibPoint LastCalibPoint;
	void AddCalibPoint(double Rb, double Rg, double sRb, double sRg);
	bool CalibrateBolometer(double *Rb, double *Rg, double *sRb, double *sRg);
  void bSort(double *val, int* ind, int n);
	void CreatePulser();
	void CreateCurrGen();
	void CreateGeReader();
	void CreateBolReader();
	char szFileBol[256];
  CFileHeader hdr;
	bool IsRunning;
	bool StartRun();
	bool IsDirty;
	int xControl, yControl;

  CDurationDlg*        pDurationDlg;
  CDoFitDlg*           pDoFitDlg;
  CLowLevelSettings*   pSettingsDlg;
  CApiezonSettingsDlg* pApiezonSettingsDlg;
  CBolReaderSettings*  pBolReaderSettingsDlg;
  CGeReaderSettings*   pGeReaderSettingsDlg;
  CCurrGenSettings*    pCurrGenSettingsDlg;
  CTControlSettings*   pTControlSettingsDlg;
  CLakeShoreSetDlg*    pLakeShoreSetDlg;
	CConfigureDlg*       pConfigureDlg;
	CPlotsDlg*           pPlotsDlg;
	CPulserDlg*          pPulserDlg;
	CGeReaderDlg*        pGeReaderDlg;
	CCurrGenDlg*         pCurrGenDlg;
	CBolReaderDlg*       pBolReaderDlg;
	CTControlDlg*        pTControlDlg;
//********************CMagnetDlg* pMagnetDlg;

  CPlotWindow** pPlot;
  CDataSetProperties** pProperties;

	CPulser*         pPulser;
	CCurrGen*        pCurrGen;
	CBolReader*      pBolReader;
	CGeReader*       pGeReader;
 	CTempController* pTempCtrl;
//********************	CSms10*     pSms10;

	CMsgWindow*        pMsgWindow;

  CGpibNotify* pSms10Notify;
  CGpibNotify* pCurrGenNotify;
  CGpibNotify* pBolReaderNotify;
  CGpibNotify* pGeReaderNotify;
  CGpibNotify* pTControllerNotify;

	CArray<CMyPoint,CMyPoint&> BolData;
	CArray<CMyPoint,CMyPoint&> GeData;

	CArray<CCalibPoint,CCalibPoint&> CalibPoints;

	CArray<CCbPoint,CCbPoint&> AsPoints;
	CArray<CCbPoint,CCbPoint&> CbPoints;
	CArray<CCpPoint,CCpPoint&> CpPoints;
	CArray<CCpPoint,CCpPoint&> CpPoints_Temp;
/////////////////////////////////////////////////////////	CArray<CString,CString>    FileDati;

	void ClearGeData();
	void ClearBolData();
	void AddGeData(double x, double y);
	void AddBolData(double x, double y);

protected:
//********************	afx_msg void OnSms10Notify(long, long, long, long, long FAR*);
	afx_msg void OnCurrGenNotify(long, long, long, long, long FAR*);
	afx_msg void OnBolReaderNotify(long, long, long, long, long FAR*);
	afx_msg void OnGeReaderNotify(long, long, long, long, long FAR*);
	afx_msg void OnLakeShore370Notify(long, long, long, long, long FAR*);

  int nPlot;

};
