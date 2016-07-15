#pragma once

//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Includes for Plugins
// AUTHOR: 
//***************************************************************************/

#include "stdafx.h"

#include "3dsmaxsdk_preinclude.h"
#include "resource.h"
#include <istdplug.h>
#include <iparamb2.h>
#include <iparamm2.h>
#include <maxtypes.h>
#include <impexp.h>

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
#include <IGame\IGame.h>
#include <IGame\IGameObject.h>

#include <string>

using namespace std;

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

	string  nname;
	string  SIname;
	string  MatType;
	string  material;	// material name
	string  pFilePath;
	string  pSIFilePath;
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
	void DeleteThis() {}
	void Init(HWND hWnd);
	void Destroy(HWND hWnd);

	//Specific Methods
	void Pick();
};

extern PlugPanel thePlugPanel;

extern TCHAR *GetString(int id);

extern HINSTANCE hInstance;

#include <cctype>

inline bool icompare_pred(unsigned char a, unsigned char b)
{
	return std::tolower(a) == std::tolower(b);
}

inline bool icompare(std::string const& a, std::string const& b)
{
	if (a.length() == b.length()) {
		return std::equal(b.begin(), b.end(),
			a.begin(), icompare_pred);
	}
	else {
		return false;
	}
}