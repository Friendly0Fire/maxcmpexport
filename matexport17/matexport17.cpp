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
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

#include "matexport17.h"
#include "inode.h"
#include "max.h"
#include "iparamb2.h"
#include <IGame\IGame.h>
#include <IGame\IGameObject.h>
#include "DlgOptions.h"
#include "ExportOptions.h"

static BOOL showPrompts;
static BOOL exportSelected;

#define matexport17_CLASS_ID	Class_ID(0x9b3b98f6, 0x58b42903)

typedef unsigned int uint;

// FL CRC32 table
static unsigned int flcrc32tbl[] = {
	0x0,	0x9073096,	0x120E612C,	0x1B0951BA,
	0xFF6DC419,	0xF66AF48F,	0xED63A535,	0xE46495A3,
	0xFEDB8832,	0xF7DCB8A4,	0xECD5E91E,	0xE5D2D988,
	0x1B64C2B,	0x8B17CBD,	0x13B82D07,	0x1ABF1D91,
	0xFDB71064,	0xF4B020F2,	0xEFB97148,	0xE6BE41DE,
	0x2DAD47D,	0xBDDE4EB,	0x10D4B551,	0x19D385C7,
	0x36C9856,	0xA6BA8C0,	0x1162F97A,	0x1865C9EC,
	0xFC015C4F,	0xF5066CD9,	0xEE0F3D63,	0xE7080DF5,
	0xFB6E20C8,	0xF269105E,	0xE96041E4,	0xE0677172,
	0x403E4D1,	0xD04D447,	0x160D85FD,	0x1F0AB56B,
	0x5B5A8FA,	0xCB2986C,	0x17BBC9D6,	0x1EBCF940,
	0xFAD86CE3,	0xF3DF5C75,	0xE8D60DCF,	0xE1D13D59,
	0x6D930AC,	0xFDE003A,	0x14D75180,	0x1DD06116,
	0xF9B4F4B5,	0xF0B3C423,	0xEBBA9599,	0xE2BDA50F,
	0xF802B89E,	0xF1058808,	0xEA0CD9B2,	0xE30BE924,
	0x76F7C87,	0xE684C11,	0x15611DAB,	0x1C662D3D,
	0xF6DC4190,	0xFFDB7106,	0xE4D220BC,	0xEDD5102A,
	0x9B18589,	0xB6B51F,	0x1BBFE4A5,	0x12B8D433,
	0x807C9A2,	0x100F934,	0x1A09A88E,	0x130E9818,
	0xF76A0DBB,	0xFE6D3D2D,	0xE5646C97,	0xEC635C01,
	0xB6B51F4,	0x26C6162,	0x196530D8,	0x1062004E,
	0xF40695ED,	0xFD01A57B,	0xE608F4C1,	0xEF0FC457,
	0xF5B0D9C6,	0xFCB7E950,	0xE7BEB8EA,	0xEEB9887C,
	0xADD1DDF,	0x3DA2D49,	0x18D37CF3,	0x11D44C65,
	0xDB26158,	0x4B551CE,	0x1FBC0074,	0x16BB30E2,
	0xF2DFA541,	0xFBD895D7,	0xE0D1C46D,	0xE9D6F4FB,
	0xF369E96A,	0xFA6ED9FC,	0xE1678846,	0xE860B8D0,
	0xC042D73,	0x5031DE5,	0x1E0A4C5F,	0x170D7CC9,
	0xF005713C,	0xF90241AA,	0xE20B1010,	0xEB0C2086,
	0xF68B525,	0x66F85B3,	0x1D66D409,	0x1461E49F,
	0xEDEF90E,	0x7D9C998,	0x1CD09822,	0x15D7A8B4,
	0xF1B33D17,	0xF8B40D81,	0xE3BD5C3B,	0xEABA6CAD,
	0xEDB88320,	0xE4BFB3B6,	0xFFB6E20C,	0xF6B1D29A,
	0x12D54739,	0x1BD277AF,	0xDB2615,	0x9DC1683,
	0x13630B12,	0x1A643B84,	0x16D6A3E,	0x86A5AA8,
	0xEC0ECF0B,	0xE509FF9D,	0xFE00AE27,	0xF7079EB1,
	0x100F9344,	0x1908A3D2,	0x201F268,	0xB06C2FE,
	0xEF62575D,	0xE66567CB,	0xFD6C3671,	0xF46B06E7,
	0xEED41B76,	0xE7D32BE0,	0xFCDA7A5A,	0xF5DD4ACC,
	0x11B9DF6F,	0x18BEEFF9,	0x3B7BE43,	0xAB08ED5,
	0x16D6A3E8,	0x1FD1937E,	0x4D8C2C4,	0xDDFF252,
	0xE9BB67F1,	0xE0BC5767,	0xFBB506DD,	0xF2B2364B,
	0xE80D2BDA,	0xE10A1B4C,	0xFA034AF6,	0xF3047A60,
	0x1760EFC3,	0x1E67DF55,	0x56E8EEF,	0xC69BE79,
	0xEB61B38C,	0xE266831A,	0xF96FD2A0,	0xF068E236,
	0x140C7795,	0x1D0B4703,	0x60216B9,	0xF05262F,
	0x15BA3BBE,	0x1CBD0B28,	0x7B45A92,	0xEB36A04,
	0xEAD7FFA7,	0xE3D0CF31,	0xF8D99E8B,	0xF1DEAE1D,
	0x1B64C2B0,	0x1263F226,	0x96AA39C,	0x6D930A,
	0xE40906A9,	0xED0E363F,	0xF6076785,	0xFF005713,
	0xE5BF4A82,	0xECB87A14,	0xF7B12BAE,	0xFEB61B38,
	0x1AD28E9B,	0x13D5BE0D,	0x8DCEFB7,	0x1DBDF21,
	0xE6D3D2D4,	0xEFD4E242,	0xF4DDB3F8,	0xFDDA836E,
	0x19BE16CD,	0x10B9265B,	0xBB077E1,	0x2B74777,
	0x18085AE6,	0x110F6A70,	0xA063BCA,	0x3010B5C,
	0xE7659EFF,	0xEE62AE69,	0xF56BFFD3,	0xFC6CCF45,
	0xE00AE278,	0xE90DD2EE,	0xF2048354,	0xFB03B3C2,
	0x1F672661,	0x166016F7,	0xD69474D,	0x46E77DB,
	0x1ED16A4A,	0x17D65ADC,	0xCDF0B66,	0x5D83BF0,
	0xE1BCAE53,	0xE8BB9EC5,	0xF3B2CF7F,	0xFAB5FFE9,
	0x1DBDF21C,	0x14BAC28A,	0xFB39330,	0x6B4A3A6,
	0xE2D03605,	0xEBD70693,	0xF0DE5729,	0xF9D967BF,
	0xE3667A2E,	0xEA614AB8,	0xF1681B02,	0xF86F2B94,
	0x1C0BBE37,	0x150C8EA1,	0xE05DF1B,	0x702EF8D,
};

CMaxPlugInApp	theApp;
cDlgOptions     theDlgOptions;

BEGIN_MESSAGE_MAP(CMaxPlugInApp, CWinApp)
	//{{AFX_MSG_MAP(CMsPlugInApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

class matexport17 : public SceneExport {
public:

	static HWND hParams;

	//Constructor/Destructor
	matexport17();
	~matexport17();

	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
	void			ShowOptions(HWND hWnd);

	void ExportNodeInfo(IGameNode * pMesh, const TCHAR *name);
	void Test(Interface *ip);
	BOOL ExportGroup(IGameNode * pMesh, const TCHAR* name);
	BOOL ExportRootMesh(IGameNode * pMesh, const TCHAR *name);
	BOOL SupportsOptions(int ext, DWORD options);
	int  DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);

	Tab<IGameNode*>Meshes;

private:
	Interface*	ip;
};



class matexport17ClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new matexport17(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return matexport17_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("matexport17"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* Getmatexport17Desc() { 
	static matexport17ClassDesc matexport17Desc;
	return &matexport17Desc; 
}





INT_PTR CALLBACK matexport17OptionsDlgProc(HWND hWnd,UINT message,WPARAM,LPARAM lParam) {
	static matexport17* imp = nullptr;

	switch(message) {
		case WM_INITDIALOG:
			imp = (matexport17 *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
	}
	return 0;
}


INT_PTR CALLBACK OptionsBoxDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM /*lParam*/)
{
	switch (msg) {
	case WM_INITDIALOG:
		CenterWindow(hWnd, GetParent(hWnd));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hWnd, 1);
			break;
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
void matexport17::ShowOptions(HWND hWnd)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_OPTIONS), hWnd, OptionsBoxDlgProc, 0);
}
CMaxPlugInApp::CMaxPlugInApp()
{
}
int CMaxPlugInApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}


//--- matexport17 -------------------------------------------------------
#include <list>
using namespace std;

std::list<MMESH *> * meshList;
std::list<string> MaterialNames;
matexport17::matexport17()
{

}

matexport17::~matexport17() 
{

}

int matexport17::ExtCount()
{
	return 1;
}

const TCHAR *matexport17::Ext(int /*i*/)
{		
	return _T("mat");
}

const TCHAR *matexport17::LongDesc()
{
	return _T("Freelancer MAT File Format");
}
	
const TCHAR *matexport17::ShortDesc() 
{			
	return _T("MAT");
}

const TCHAR *matexport17::AuthorName()
{			
	return _T("");
}

const TCHAR *matexport17::CopyrightMessage() 
{	
	return _T("");
}

const TCHAR *matexport17::OtherMessage1() 
{		
	return _T("");
}

const TCHAR *matexport17::OtherMessage2() 
{		
	return _T("");
}

unsigned int matexport17::Version()
{				
	return 100;
}

void matexport17::ShowAbout(HWND /*hWnd*/)
{			
	// Optional
}

BOOL matexport17::SupportsOptions(int /*ext*/, DWORD /*options*/)
{
	return TRUE;
}

unsigned int fl_crc32(char * string)
{
	unsigned int crc;

	crc = 0xFFFFFFFFL;
	for (uint i = 0; i < strlen(string); i++)
		crc = ((crc >> 8) & 0x00FFFFFFL) ^ flcrc32tbl[(crc ^ (tolower(string[i]))) & 0xFF];
	crc = crc ^ 0xFFFFFFFFL;

	return crc;
}


void matexport17::Test(Interface *ip)
{
	BOOL two;
	float utile, vtile;
	TSTR buf;
	// Get the material and texture properties from the node.
	if (ip->GetSelNodeCount() < 1) return;
	INode *node = ip->GetSelNode(0);
	// Get the material from the node
	Mtl *m = node->GetMtl();
	if (!m) return; // No material assigned
					// See if it's a Standard material
	if (m->ClassID() == Class_ID(DMTL_CLASS_ID, 0))
	{
		// It is -- Access the two sided property of the material
		StdMat* std = (StdMat *)m;
		two = std->GetTwoSided();
		// Access the Diffuse map and see if it's a Bitmap texture
		Texmap *tmap = m->GetSubTexmap(ID_DI);
		if (tmap->ClassID() == Class_ID(BMTEX_CLASS_ID, 0))
		{
			// It is -- Access the UV tiling settings at time 0.
			BitmapTex *bmt = (BitmapTex*)tmap;
			StdUVGen *uv = bmt->GetUVGen();
			utile = uv->GetUScl(0);
			vtile = uv->GetVScl(0);
			buf.printf(_T("Two sided=%d, U Tile = %.1f, V Tile = %.1f"),
				two, utile, vtile);
			MessageBox(ip->GetMAXHWnd(), buf, _T("Info..."), MB_ICONINFORMATION);
		}
	}
}
bool DataSortPredicate(const MMESH* lhs, const MMESH* rhs)
{
	return lhs->material < rhs->material;
}
BOOL matexport17::ExportGroup(IGameNode * pMesh, const TCHAR* name)
{

	IGameScene *nMeshes;
	nMeshes = GetIGameInterface();
	nMeshes->SetStaticFrame(0);

	ExportOptions OptionsDlgExport(NULL);

	OptionsDlgExport.DoModal();
	if (!OptionsDlgExport.bDoExport)
		return 1;

	meshList = new list<MMESH *>;
	MMESH * mesh;

	BOOL two = false;
	bool IsSelfIllum = false;

	Meshes = nMeshes->GetIGameNodeByType(IGameObject::IGAME_MESH);
	for (int nMesh = 0; nMesh < Meshes.Count(); nMesh++)
	{

		mesh = new MMESH;	memset(mesh, 0, sizeof(MMESH));

		IGameObject *pModel;
		pModel = pMesh->GetIGameObject();
		IGameMesh *gMesh = (IGameMesh*)Meshes[nMesh]->GetIGameObject();

		if (gMesh->GetIGameType() == IGameObject::IGAME_MESH)
		{
			IGameNode *pMesh = (IGameNode*)gMesh;
			meshList->push_back(mesh);
			gMesh->InitializeData();

			IGameMaterial *pMaterial = NULL;
			int faces = gMesh->GetNumberOfFaces();
			for (int i = 0; i<faces; i++)
			{
				pMaterial = gMesh->GetMaterialFromFace(i);
				int SubMat = pMaterial->GetSubMaterialCount();
				for (int i = 0; i<SubMat; i++)
				{
					IGameMaterial * subMat;
					subMat = pMaterial->GetSubMaterial(i);
				}

				IGameMesh *gMesh = (IGameMesh*)pMesh;
				//mesh->pMesh = gMesh;
			}
			if (pMaterial == NULL)
			{
				MessageBox(0, TEXT("No material on one of the meshes"), TEXT("Error exporting Material"), MB_ICONERROR);
			}
			if (pMaterial != NULL)
			{
				mesh->material = wstos(pMaterial->GetMaterialName());
				MaterialNames.push_back(wstos(pMaterial->GetMaterialName()));

				float Opacity = 1.0f;
				Point3 Diffuse;
				Diffuse.x = Diffuse.y = Diffuse.z = 1.0f;
				pMaterial->GetOpacityData()->GetPropertyValue(Opacity);
				pMaterial->GetDiffuseData()->GetPropertyValue(Diffuse);

				int texCount = pMaterial->GetNumberOfTextureMaps();
				for (int i = 0; i<texCount; i++)
				{
					IsSelfIllum = false;
					IGameTextureMap * tex = pMaterial->GetIGameTextureMap(i);
					const TCHAR * name = tex->GetTextureName();
					if (tex->IsEntitySupported()) //its a bitmap texture    
					{
						Mtl *m = pMaterial->GetMaxMaterial();
						// See if it's a Standard material
						if (m->ClassID() == Class_ID(DMTL_CLASS_ID, 0))
						{
							// It is -- Access the two sided property of the material
							StdMat* std = (StdMat *)m;
							two = std->GetTwoSided();
						}
						if (tex->GetStdMapSlot() == ID_SI)
						{
							IsSelfIllum = true;
							mesh->SIname = wstos(tex->GetTextureName());
							mesh->pFilePath = wstos(pMaterial->GetIGameTextureMap(0)->GetBitmapFileName());
							mesh->pSIFilePath = wstos(tex->GetBitmapFileName());
						}


						IGameProperty * prop = tex->GetClipHData();
						prop = tex->GetClipUData();
						prop = tex->GetClipVData();
						prop = tex->GetClipWData();
					}
				}
				if (IsSelfIllum == true)
				{
					mesh->IsSelfIlluminate = true;
					mesh->MatType = "DcDtEt";
					mesh->OpacityVal = Opacity;
					mesh->DiffuseVal.x = Diffuse.x;
					mesh->DiffuseVal.y = Diffuse.y;
					mesh->DiffuseVal.z = Diffuse.z;
				}

				else if (Opacity < 1.0f)
				{
					mesh->IsOpac = true;
					mesh->MatType = "DcDtOcOt";
					mesh->OpacityVal = Opacity;
					mesh->DiffuseVal.x = Diffuse.x;
					mesh->DiffuseVal.y = Diffuse.y;
					mesh->DiffuseVal.z = Diffuse.z;
				}
				else if (Opacity == 1.0f)
				{
					int texCount = pMaterial->GetNumberOfTextureMaps();
					for (int i = 0; i<texCount; i++)
					{
						IGameTextureMap * tex = pMaterial->GetIGameTextureMap(i);
						const TCHAR * name = tex->GetTextureName();
						if (tex->IsEntitySupported()) //its a bitmap texture    
						{
							if (two == 1)
							{
								mesh->MatType = "DcDtTwo";
							}
							else
							{
								mesh->MatType = "DcDt";
							}

							mesh->pFilePath = wstos(pMaterial->GetIGameTextureMap(0)->GetBitmapFileName());
						}
					}
					if (texCount == 0)
					{
						mesh->IsOpac = true;
						mesh->MatType = "DcDtOcOt";
						mesh->OpacityVal = Opacity;
						mesh->DiffuseVal.x = Diffuse.x;
						mesh->DiffuseVal.y = Diffuse.y;
						mesh->DiffuseVal.z = Diffuse.z;
					}
				}
			}
		}
	}
	/*	for (std::list<MMESH*>::iterator i = meshList->begin();i != meshList->end(); ++i)
	{
	meshList->sort(DataSortPredicate);

	}

	list<MMESH *>::iterator i = meshList->begin();

	while (i != meshList->end())
	{
	if(mesh->IsOpac == false)
	{
	bool isActive = (*i)->pFilePath != NULL;
	if (!isActive)
	{
	meshList->erase(i++);  // alternatively, i = items.erase(i);
	}
	else
	{

	++i;
	}
	}
	}*/

	nMeshes->ReleaseIGame();

	mesh = new MMESH;	memset(mesh, 0, sizeof(MMESH));
	// -----------------------------------------------------------------------------------------
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	cDlgOptions dlgOptions(NULL);
	dlgOptions.SetMesh(meshList);
	dlgOptions.SetFileName(wstos(name).c_str());
	dlgOptions.DoModal();

	return 1;
}
BOOL matexport17::ExportRootMesh(IGameNode * pMesh, const TCHAR *name)
{
	ExportOptions OptionsDlgExport(NULL);

	IGameScene *nMeshes;
	nMeshes = GetIGameInterface();
	nMeshes->SetStaticFrame(0);

	meshList = new list<MMESH *>;
	MMESH * mesh;

	/*OptionsDlgExport.DoModal();
	if (!OptionsDlgExport.bDoExport)
		return 1;*/

	BOOL two = false;
	bool IsSelfIllum = false;

	for (int nMesh = 0; nMesh < nMeshes->GetTopLevelNodeCount(); nMesh++)
	{
		mesh = new MMESH;

		IGameNode *pMesh = nMeshes->GetTopLevelNode(nMesh);
		IGameObject *pModel;
		pModel = pMesh->GetIGameObject();
		if (pModel->GetIGameType() == IGameObject::IGAME_MESH)
		{
			meshList->push_back(mesh);

			pModel->InitializeData();
			IGameMaterial *pMaterial = NULL;
			pMaterial = pMesh->GetNodeMaterial();
			IGameTextureMap *pTexMap = NULL;
			if (pMaterial == NULL)
			{
				IGameMesh *pMesh = (IGameMesh*)pModel;
				int faces = pMesh->GetNumberOfFaces();
				for (int i = 0; i<faces; i++)
				{
					pMaterial = pMesh->GetMaterialFromFace(i);
					int SubMat = pMaterial->GetSubMaterialCount();
					for (int i = 0; i<SubMat; i++)
					{
						IGameMaterial * subMat;
						subMat = pMaterial->GetSubMaterial(i);
					}
				}
			}
			else
				if (pMaterial != NULL)
				{
					pTexMap = pMaterial->GetIGameTextureMap(0);
					mesh->material = wstos(pMaterial->GetMaterialName());
				}
			float Opacity = 1.0f;
			Point3 Diffuse;
			Diffuse.x = Diffuse.y = Diffuse.z = 1.0f;

			MaterialNames.push_back(wstos(pMaterial->GetMaterialName()));
			IGameMesh *pMesh = (IGameMesh*)pModel;
			pMaterial->GetOpacityData()->GetPropertyValue(Opacity);
			pMaterial->GetDiffuseData()->GetPropertyValue(Diffuse);

			int texCount = pMaterial->GetNumberOfTextureMaps();
			for (int i = 0; i<texCount; i++)
			{
				IsSelfIllum = false;
				IGameTextureMap * tex = pMaterial->GetIGameTextureMap(i);
				const TCHAR * name = tex->GetTextureName();
				if (tex->IsEntitySupported()) //its a bitmap texture    
				{
					Mtl *m = pMaterial->GetMaxMaterial();
					// See if it's a Standard material
					if (m->ClassID() == Class_ID(DMTL_CLASS_ID, 0))
					{
						// It is -- Access the two sided property of the material
						StdMat* std = (StdMat *)m;
						two = std->GetTwoSided();
					}
					if (tex->GetStdMapSlot() == ID_SI)
					{
						IsSelfIllum = true;
						mesh->SIname = wstos(tex->GetTextureName());
						mesh->pFilePath = wstos(pMaterial->GetIGameTextureMap(0)->GetBitmapFileName());
						mesh->pSIFilePath = wstos(tex->GetBitmapFileName());
					}

					IGameProperty * prop = tex->GetClipHData();
					prop = tex->GetClipUData();
					prop = tex->GetClipVData();
					prop = tex->GetClipWData();
				}
			}

			if (IsSelfIllum == true)
			{
				mesh->IsSelfIlluminate = true;
				mesh->MatType = "DcDtEt";
				mesh->OpacityVal = Opacity;
				mesh->DiffuseVal.x = Diffuse.x;
				mesh->DiffuseVal.y = Diffuse.y;
				mesh->DiffuseVal.z = Diffuse.z;
			}
			else if (Opacity < 1.0f)
			{
				mesh->IsOpac = true;
				mesh->MatType = "DcDtOcOt";
				mesh->OpacityVal = Opacity;
				mesh->DiffuseVal.x = Diffuse.x;
				mesh->DiffuseVal.y = Diffuse.y;
				mesh->DiffuseVal.z = Diffuse.z;
			}
			else if (Opacity == 1.0f)
			{
				int texCount = pMaterial->GetNumberOfTextureMaps();
				for (int i = 0; i<texCount; i++)
				{
					IGameTextureMap * tex = pMaterial->GetIGameTextureMap(i);
					const TCHAR * name = tex->GetTextureName();
					if (tex->IsEntitySupported()) //its a bitmap texture    
					{
						if (tex->IsEntitySupported()) //its a bitmap texture    
						{
							if (two == 1)
							{
								mesh->MatType = "DcDtTwo";
							}
							else
							{
								mesh->MatType = "DcDt";
							}

							mesh->pFilePath = wstos(pMaterial->GetIGameTextureMap(0)->GetBitmapFileName());
						}
					}
				}
				if (texCount == 0)
				{
					mesh->IsOpac = true;
					mesh->MatType = "DcDtOcOt";
					mesh->OpacityVal = Opacity;
					mesh->DiffuseVal.x = Diffuse.x;
					mesh->DiffuseVal.y = Diffuse.y;
					mesh->DiffuseVal.z = Diffuse.z;
				}
			}

			mesh->pMesh = pMesh;
		}
	}
	nMeshes->ReleaseIGame();
	// -----------------------------------------------------------------------------------------
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	cDlgOptions dlgOptions(NULL);
	dlgOptions.SetMesh(meshList);
	dlgOptions.SetFileName((char*)name);
	dlgOptions.DoModal();

	return 1;
}
void matexport17::ExportNodeInfo(IGameNode * pMesh, const TCHAR *name)
{
	if (pMesh->IsGroupOwner())
		ExportGroup(pMesh, name);
	else
		ExportRootMesh(pMesh, name);
}


int	matexport17::DoExport(const TCHAR* name, ExpInterface* /*ei*/, Interface* i, BOOL suppressPrompts, DWORD options)
{
	//TODO: Implement the actual file Export here and 
	//		return TRUE If the file is exported properly

	// Set a global prompt display switch
	exportSelected = (options & SCENE_EXPORT_SELECTED) ? TRUE : FALSE;

	// Grab the interface pointer.
	ip = i;

	IGameScene *nMeshes;
	nMeshes = GetIGameInterface();
	IGameConversionManager * cm = GetConversionManager();
	cm->SetCoordSystem(IGameConversionManager::IGAME_USER);

	UserCoord myCoordSystem = {
		1,	//Right Handed
		0,	//X axis goes Left
		2,	//Y Axis goes up
		4,	//Z Axis goes in.
		1,	//U Tex axis is right
		1,  //V Tex axis is Down
	};

	cm->SetUserCoordSystem(myCoordSystem);
	nMeshes->InitialiseIGame(false); // true- we want selected only - false we want all!
	nMeshes->SetStaticFrame(0);

	meshList = new list<MMESH *>;
	MMESH *mesh;

	for (int nMesh = 0; nMesh < nMeshes->GetTopLevelNodeCount(); nMesh++)
	{
		mesh = new MMESH;	memset(mesh, 0, sizeof(MMESH));

		IGameNode *pMesh = nMeshes->GetTopLevelNode(nMesh);

		mesh->nname = wstos(nMeshes->GetTopLevelNode(nMesh)->GetName());
		//gNode->gname = mesh->nname;


		if (pMesh->IsTarget())
			continue;
		ExportNodeInfo(pMesh, name);
	}
	// -----------------------------------------------------------------------------------------
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	list<MMESH *>::iterator j;

	// destroy list
	for (j = meshList->begin(); j != meshList->end(); j++)
	{
		MMESH * m = *j;
		delete m;
	}
	delete meshList;

	return 1;
}


