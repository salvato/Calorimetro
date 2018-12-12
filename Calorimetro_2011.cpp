// Calorimetro_2011.cpp : definisce i comportamenti delle classi per l'applicazione.
//

#include "stdafx.h"
#include "Calorimetro_2011.h"
#include "CalorimetroDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalorimetroApp

BEGIN_MESSAGE_MAP(CCalorimetroApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// costruzione di CCalorimetroApp

CCalorimetroApp::CCalorimetroApp()
{
	// TODO: inserire qui il codice di costruzione.
	// Inserire l'inizializzazione significativa in InitInstance.
}


// L'unico e solo oggetto CCalorimetroApp

CCalorimetroApp theApp;


// Inizializzazione di CCalorimetroApp

BOOL CCalorimetroApp::InitInstance()
{
	// InitCommonControlsEx() è necessario in Windows XP se nel manifesto
	// di un'applicazione è specificato l'utilizzo di ComCtl32.dll versione 6 o successiva per attivare
	// gli stili visuali. In caso contrario, non sarà possibile creare finestre.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Effettuare questa impostazione in modo da includere tutte le classi di controlli comuni da utilizzare
	// nell'applicazione.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Inizializzazione standard
	// Se non si utilizzano queste funzionalità e si desidera ridurre la dimensione
	// dell'eseguibile finale, è necessario rimuovere dal seguente codice
	// le specifiche routine di inizializzazione che non sono necessarie.
	// Modificare la chiave del Registro di sistema in cui sono memorizzate le impostazioni
	// TODO: è necessario modificare questa stringa in modo appropriato,
	// inserendo ad esempio il nome della società o dell'organizzazione.
	SetRegistryKey(_T("Gabriele Salvato"));

	CCalorimetroDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: inserire qui il codice per gestire la chiusura della finestra di dialogo 
		//  tramite il pulsante OK.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: inserire qui il codice per gestire la chiusura della finestra di dialogo 
		//  tramite il pulsante Annulla.
	}

	// Poiché la finestra di dialogo è stata chiusa, restituisce FALSE in modo che l'applicazione
	//  venga terminata, anziché avviare il message pump dell'applicazione.
	return FALSE;
}
