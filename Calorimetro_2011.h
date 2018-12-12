// Calorimetro_2011.h : file di intestazione principale per l'applicazione PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "includere 'stdafx.h' prima di includere questo file per PCH"
#endif

#include "resource.h"		// simboli principali


// CCalorimetroApp:
// Vedere Calorimetro_2011.cpp per l'implementazione di questa classe
//

class CCalorimetroApp : public CWinApp
{
public:
	CCalorimetroApp();

// Override
	public:
	virtual BOOL InitInstance();

// Implementazione

	DECLARE_MESSAGE_MAP()
};

extern CCalorimetroApp theApp;