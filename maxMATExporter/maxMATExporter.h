/**********************************************************************
 *<
	FILE: maxMATExporter.h

	DESCRIPTION:	Includes for Plugins

	CREATED BY:

	HISTORY:

 *>	Copyright (c) 2003, All Rights Reserved.
 **********************************************************************/

#ifndef __maxMATExporter__H
#define __maxMATExporter__H

#include "stdafx.h"


#if _MSC_VER > 1000


#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


#include "Max.h"
#include "resource.h"
#include "istdplug.h"
#include "iparamb2.h"
#include "iparamm2.h"
#include "stdmat.h"
#include "decomp.h"
#include "shape.h"
#include "interpik.h"
#include "bmmlib.h"	
#include "utilapi.h"
#include "igame.h"
#include "igameobject.h"

typedef unsigned int uint;

struct FileName_
{
	const TCHAR * File_Name;
};

unsigned int fl_crc32(char *);

struct MMESH
{
	bool IsOpac;
	bool IsDblSided;
	bool IsSelfIlluminate;
	int nVerts;
	int nTris;
	float OpacityVal;
	Point3 DiffuseVal;
	
	TCHAR *  nname;
	TCHAR *  SIname;
	TCHAR *  MatType;
	TCHAR *  material;	// material name
	TCHAR * pFilePath;
	TCHAR * pSIFilePath;
	IGameMesh *pMesh; // 3ds max mesh object
};

class CMaxPlugInApp : public CWinApp
{

public:
	CMaxPlugInApp();

	//{{AFX_VIRTUAL(CMsPlugInApp)
	//}}AFX_VIRTUAL
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	//{{AFX_MSG(CMsPlugInApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class PlugPanel : public UtilityObj {
	public:
		HINSTANCE		hInstance;
		IUtil*			iu;
		Interface*		ip;
		HWND			hPanel;

	public:
		// Constructor & Destructor
		PlugPanel();
		virtual ~PlugPanel();

		// Overides of the UtilityObj class
		void BeginEditParams(Interface* ip, IUtil* iu);
		void EndEditParams(Interface* ip, IUtil* iu);
		void DeleteThis()						{}
		void Init(HWND hWnd);
		void Destroy(HWND hWnd);

		//Specific Methods
		void Pick();
};

extern PlugPanel thePlugPanel;	

extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;

#endif
