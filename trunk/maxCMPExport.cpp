/**********************************************************************
*<
	FILE: maxCMPExport.cpp

	DESCRIPTION:	Appwizard generated plugin

	CREATED BY: 

	HISTORY: 

*>	Copyright (c) 2003, All Rights Reserved.
**********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

#include "3dsmaxport.h"
#include "maxCMPExport.h"
#include "MeshDLib.h"
#include "inode.h"
#include "max.h"
#include "iparamb2.h"
#include "igame.h"
#include "igameobject.h"
//#include "forcelib.h"
#include "DlgOptions.h"
#include "ExportOptions.h"

static BOOL showPrompts;
static BOOL exportSelected;

#define maxCMPExport_CLASS_ID	Class_ID(0xaf82ab88, 0xadd6b246)
#define ID_GROUP				_T("*GROUP")

using namespace std;


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
//-------------------------------------------------------------------------------------------

class maxCMPExport : public SceneExport {
public:

	IGameScene * nMeshes;
	Control *control;

	static HWND hParams;

	//TSTR fileName;
	TSTR splitPath;

	IXMLDOMDocument * pXMLDoc;
	IXMLDOMNode * pRoot;		//this is our root node 	
	CComPtr<IXMLDOMNode> iGameNode;	//the IGame child - which is the main node
	CComPtr<IXMLDOMNode> rootNode;
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


	void check_line(Line *lines, uint *num_lines, Line new_line);
	void CreateVWData(CMPND_DATA* cmpnd);
	bool ExportGroup(IGameNode * pMesh, string);
	bool CreateCMPData(IGameNode * pRootGrp, list<CMPND_DATA*>* lstCMPData);
	bool NewNode(INode* node, IGameNode * mNode);
	int RegroupByMatID();
	int NodeProcess();
	BOOL nodeEnum(INode* node);
	void PreProcess(INode* node, int& nodeCount);
	BOOL SupportsOptions(int ext, DWORD options);
	int	DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);
	int staticFrame;
	int cS;
	int Bounds(float);
	int			nTotalNodeCount;
	int			nCurNode;
	Tab<IGameNode*>Meshes;
	Tab<IGameNode*>gMeshes;

	ExportOptions* OptionsDlgExport;

	maxCMPExport();
	~maxCMPExport();

	
	// Configuration methods
	TSTR	GetCfgFilename();
	BOOL	ReadConfig();
	void	WriteConfig();

	

private:
	Interface*	ip;
};

class maxCMPExportClassDesc : public ClassDesc2 
{
public:
	int 			IsPublic() { return TRUE; }
	void *			Create(BOOL loading = FALSE) { return new maxCMPExport(); }
	const TCHAR *	ClassName() { return GetString(IDS_CLASS_NAME); }
	SClass_ID		SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	Class_ID		ClassID() { return maxCMPExport_CLASS_ID; }
	const TCHAR* 	Category() { return GetString(IDS_CATEGORY); }

	const TCHAR*	InternalName() { return _T("maxCMPExport"); }	// returns fixed parsable name (scripter-visible name)
	HINSTANCE		HInstance() { return hInstance; }					// returns owning module handle
};

static maxCMPExportClassDesc maxCMPExportDesc;

ClassDesc2* GetmaxCMPExportDesc() 
{ 
	return &maxCMPExportDesc;
}
INT_PTR CALLBACK maxCMPExportOptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static maxCMPExport *imp = NULL;

	switch(message) {
	case WM_INITDIALOG:
		imp = (maxCMPExport *)lParam;
		CenterWindow(hWnd,GetParent(hWnd));
		return TRUE;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return 1;
	}
	return 0;
}
INT_PTR CALLBACK AboutBoxDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	switch (msg) {
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
INT_PTR CALLBACK OptionsBoxDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	switch (msg) {
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

void maxCMPExport::ShowAbout(HWND hWnd)
{	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutBoxDlgProc, 0);

}void maxCMPExport::ShowOptions(HWND hWnd)
{	
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_OPTIONS), hWnd, OptionsBoxDlgProc, 0);
}
CMaxPlugInApp::CMaxPlugInApp()
{
}

//--- maxCMPExport -------------------------------------------------------
#include <list>
using namespace std;


int CMaxPlugInApp::ExitInstance() 
{	return CWinApp::ExitInstance();
}
maxCMPExport::maxCMPExport()
{}

maxCMPExport::~maxCMPExport() 
{}

int maxCMPExport::ExtCount()
{	//TODO: Returns the number of file name extensions supported by the plug-in.
	return 1;
}
const TCHAR *maxCMPExport::Ext(int n)
{		
	//TODO: Return the 'i-th' file name extension (i.e. "3DS").
	return _T("cmp");
}
const TCHAR *maxCMPExport::LongDesc()
{	//TODO: Return long ASCII description (i.e. "Targa 2.0 Image File")
	return _T("Freelancer CMP File Format");
}
const TCHAR *maxCMPExport::ShortDesc() 
{			
	return _T("cmp");
}
const TCHAR *maxCMPExport::AuthorName()
{			
	//TODO: Return ASCII Author name
	return _T("w0dk4 & SilentAssassin82");
}
const TCHAR *maxCMPExport::CopyrightMessage() 
{	
	// Return ASCII Copyright message
	return _T("");
}
const TCHAR *maxCMPExport::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}
const TCHAR *maxCMPExport::OtherMessage2() 
{		
	//TODO: Return other message #2 in any
	return _T("");
}
unsigned int maxCMPExport::Version()
{				
	//TODO: Return Version number * 100 (i.e. v3.01 = 301)
	return (uint)(CMPEXPORT_VERSION * 100);
}
unsigned int fl_crc32 (char * string)
{	unsigned int crc;

	crc = 0xFFFFFFFFL;
	for (uint i = 0; i < strlen(string); i++)
	crc = ((crc>>8) & 0x00FFFFFFL) ^ flcrc32tbl[ (crc^ (tolower(string[i])) ) & 0xFF ];
	crc = crc^0xFFFFFFFFL;

	return crc;
}
void normalize (VECTOR * dest, VECTOR * src)
{	float len = sqrt(src->vec[0] * src->vec[0] +  src->vec[1] * src->vec[1] + src->vec[2] * src->vec[2]);
	dest->vec = src->vec / len;
}

FILE* fixnode;
FILE* revnode;
FILE* prisnode;

TriObject *GetTriObjectFromNode(INode *node, BOOL &deleteIt, Interface * ip)
{
	deleteIt = FALSE;

	//Get current time from UI
	TimeValue t = ip->GetTime();
	//Evaluate object at current time
	Object *obj = node->EvalWorldState(t).obj;
	//Can we convert it in a TriObject ?
	if (obj && obj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
	{
		//Let’s convert the object in a TriObject
		TriObject *tri = static_cast<TriObject *>
		( obj->ConvertToType(t,Class_ID(TRIOBJ_CLASS_ID, 0)));
		// Note that the TriObject should only be deleted
		// if the pointer to it is not equal to the object
		// pointer that called ConvertToType()
		if (obj != tri)
		deleteIt = TRUE;
		return tri;
	}
	else
	return NULL;
}
bool maxCMPExport::NewNode(INode* node, IGameNode * mNode)
{

	IGameNode * cur_lodnode = mNode->GetNodeParent();
	IGameNode * pRootGrp = cur_lodnode->GetNodeParent();

	IGameMaterial *pMaterial = mNode->GetNodeMaterial();

	if (!node)return TRUE;
	if( ip==NULL ) ip=GetCOREInterface(); //hack
	Mtl *material = node->GetMtl();
	if (material == NULL)return true;
	if (!material->IsMultiMtl())return true;
	int numSubs = material->NumSubMtls();
	if (numSubs <= 0) return true; // Shouldn't happen.

	if (numSubs == 1)
	{
		theHold.Begin ();
		node->SetMtl (material->GetSubMtl (0));

		theHold.Accept ("Mesh Split By MatID");
	}

	ObjectState os = node->EvalWorldState(ip->GetTime());
	if (!os.obj)return TRUE;
	if (!os.obj->CanConvertToType(triObjectClassID)) return TRUE;

	theHold.Begin ();

	BOOL deleteit;
	TriObject *tobj = GetTriObjectFromNode(node,deleteit, ip);
	Mesh & imesh = tobj->GetMesh();

	for (int i=0; i<material->NumSubMtls(); i++)
	{
		// Find faces with this material in the mesh.
		BitArray fsel;
		fsel.SetSize (imesh.numFaces);
		for (int f=0; f<imesh.numFaces; f++)
		{
			if (imesh.faces[f].getMatID()%numSubs == i) fsel.Set(f, true);
		}
		if (fsel.NumberSet() == 0) continue;

		TriObject *newObj;
		newObj = CreateNewTriObject();

		MeshDelta tmd;
		tmd.Detach (imesh, &(newObj->GetMesh()), fsel, true, false, false);

		// Set the material:
		INode *newNode = ip->CreateObjectNode (newObj);
		newNode->SetMtl (material->GetSubMtl (i));

		// Set the name:
		TSTR uname = node->GetName();
		newNode->SetName (uname);

		// Set the transform:
		newNode->SetNodeTM(ip->GetTime(),node->GetNodeTM(ip->GetTime()));

		// Set the other node properties:
		newNode->CopyProperties (node);
		newNode->FlagForeground(ip->GetTime(),FALSE);
		newNode->SetObjOffsetPos (node->GetObjOffsetPos());
		newNode->SetObjOffsetRot (node->GetObjOffsetRot());
		newNode->SetObjOffsetScale (node->GetObjOffsetScale());

		INode * RootGrp = pRootGrp->GetMaxNode();
		INode * parent = cur_lodnode->GetMaxNode();

		
		parent->AttachChild(newNode);
		parent->SetGroupMember(false);
		parent->Detach(0);
		RootGrp->AttachChild(parent);
		parent->SetGroupMember(true);
		newNode->SetGroupMember(true);
		node->SetGroupMember(false);
		node->Detach(0);

		if(pMaterial->GetSubMaterialCount())
		{
			NewNode(newNode, mNode);
		}
	}
	ip->DeleteNode (node);

	theHold.Accept ("Mesh Split By MatID");

	return 1;
}
int maxCMPExport::RegroupByMatID()
{
	IGameScene* nMeshes;

	nMeshes = GetIGameInterface();

	nMeshes->InitialiseIGame(false); // true- we want selected only - false we want all!

	nMeshes->SetStaticFrame(0);

	for(int nMesh = 0; nMesh < nMeshes->GetTopLevelNodeCount(); nMesh++)	
	{		
		IGameNode *pNode = nMeshes->GetTopLevelNode(nMesh);

		for(int nChilds = 0; nChilds < pNode->GetChildCount(); nChilds++)
		{
			IGameNode* lodNode = pNode->GetNodeChild(nChilds);
			int lodNodes = lodNode->GetChildCount();
			int RootMats = nMeshes->GetRootMaterialCount();

			for(int nRootMats = 0; nRootMats<RootMats; nRootMats++)
			{
				IGameMaterial * NodeMat = nMeshes->GetRootMaterial(nRootMats);

				for(int nLod = 0; nLod <lodNodes; nLod++)
				{
					IGameNode * mNode = lodNode->GetNodeChild(nLod);
					if (mNode->GetNodeMaterial() == NodeMat)
					{
						INode * node = mNode->GetMaxNode();

						IGameMesh * pMesh = (IGameMesh*)mNode->GetIGameObject();

						IGameMaterial * pMaterial = mNode->GetNodeMaterial();
						TSTR nMaterial = pMaterial->GetMaterialName();

						BOOL deleteit;
						TriObject *tobj = GetTriObjectFromNode(node,deleteit, ip);
						Mesh & imesh = tobj->GetMesh();

						MeshDelta tmd;

					}
				}
			}
		}
	}
	return 1;
}
int maxCMPExport::NodeProcess()
{
	IGameScene* nMeshes;

	nMeshes = GetIGameInterface();

	nMeshes->InitialiseIGame(false); // true- we want selected only - false we want all!

	nMeshes->SetStaticFrame(0);

	for(int nMesh = 0; nMesh < nMeshes->GetTopLevelNodeCount(); nMesh++)	
	{		
		IGameNode *pNode = nMeshes->GetTopLevelNode(nMesh);

		for(int nChilds = 0; nChilds < pNode->GetChildCount(); nChilds++)
		{
			IGameNode* lodNode = pNode->GetNodeChild(nChilds);
			int lodNodes = lodNode->GetChildCount();
			for(int nLod = 0; nLod <lodNodes; nLod++)
			{
				IGameNode * mNode = lodNode->GetNodeChild(nLod);
				INode * node = mNode->GetMaxNode();

				IGameMesh * pMesh = (IGameMesh*)mNode->GetIGameObject();

				pMesh->InitializeData();
				pMesh->InitializeBinormalData();
				

				IGameMaterial * pMaterial = mNode->GetNodeMaterial();

				if(pMaterial->GetSubMaterialCount())
					NewNode(node, mNode);
			}
		}
	}
	return 1;
}

bool maxCMPExport::CreateCMPData(IGameNode * pRootGrp, list<CMPND_DATA*>* lstCMPData)
{
	Point3 vOffset = Point3(0,0,0);


	CMPND_DATA* cmpnd = new CMPND_DATA;

	cmpnd->index = 0;
	cmpnd->sObjectName = string(pRootGrp->GetName());
	if(cmpnd->sObjectName == "Root")
		cmpnd->sName = "Root";
	else
	{
		cmpnd->sName = "Part_";
		cmpnd->sName += cmpnd->sObjectName;

		// offset only on component parts!
		if(OptionsDlgExport->eRadioCmpnts == EXPORT_CMPNT_RELOCATE)
		{
			Point3 objoffset = pRootGrp->GetMaxNode()->GetObjOffsetPos();
			// for whatever reason the objoffset seems to be in a wrong coordinate system
			float fSwap = objoffset.y;
			objoffset.y = -objoffset.z;
			objoffset.z = fSwap;

			Box3 BoundsRoot;
			pRootGrp->GetIGameObject()->GetBoundingBox(BoundsRoot);
			Point3 objcenter = BoundsRoot.Center();
			
			vOffset = objcenter + objoffset;
		}
	}

	cmpnd->object_data = new THREEDB_DATA;

	cmpnd->object_data->iLODWireframe = 0;

	int iLODS = 0;

	for(int nNodeLOD = 0; nNodeLOD < pRootGrp->GetChildCount(); nNodeLOD++)
	{
		IGameNode* cur_lodnode = pRootGrp->GetNodeChild(nNodeLOD);

		uint iLOD = 0;

		if(cur_lodnode->IsGroupOwner())
		{
			// get lod number
			iLOD = ((int)cur_lodnode->GetName()[(strlen(cur_lodnode->GetName())-1)]) - 48;
			if(iLOD > (MAX_LODS-1))
			{
				MessageBox(0,"You have specified a higher LOD number than supported (0 to 6)","Error exporting LOD",MB_ICONERROR);
				continue; // ignore
			}
			if(string(cur_lodnode->GetName()).substr(0,3) == "vwd")
				cmpnd->object_data->iLODWireframe = iLOD;

		} else
		{
			MessageBox(0,"The node under your component must specify the lod.","Error exporting LOD",MB_ICONERROR);
			continue; // ignore
		}

		iLODS++;
		
		// this is per vmeshpart (per lod)
		uint iNumVerts = 0;
		uint iNumFaces = 0;

		for(int nNode = 0; nNode < cur_lodnode->GetChildCount(); nNode++)
		{
			IGameNode* cur_node = cur_lodnode->GetNodeChild(nNode);
			
			IGameMaterial *pMaterial = cur_node->GetNodeMaterial();

			if(cur_node->GetIGameObject()->GetIGameType() == IGameObject::IGAME_MESH)
			{
				// found a mesh under group node
				SMESH* mesh = new SMESH;
				mesh->pMesh = (IGameMesh*)cur_node->GetIGameObject();

				mesh->pMesh->InitializeData();
				mesh->pMesh->InitializeBinormalData();

				int nTris = mesh->pMesh->GetNumberOfFaces();
				// failsave if there is no geometry
				if(!nTris)
				{
					delete mesh;
					continue;
				}

				// material
				IGameMaterial *pMaterial = cur_node->GetNodeMaterial();
				if(pMaterial==NULL)
                {
					MessageBox(0,"No material on one of the meshes, adding default name","Error exporting Material",MB_ICONERROR);
					mesh->sMaterial = "default";
                } else
				{
					mesh->sMaterial = string(pMaterial->GetMaterialName());
					if(pMaterial->GetSubMaterialCount())
						MessageBox(0,"Freelancer does not support sub-materials!","Error exporting Material",MB_ICONERROR);
				}

				// mesh name
				mesh->sName = string(cur_node->GetName());

				// vertices
				mesh->t = new vmsTri[nTris];
				int nVerts = nTris*3;
				mesh->v = new vmsVert[nVerts];
				
				uint iVertexDuplicates = 0;

				for (int nTri = 0; nTri < nTris; nTri++)
				{
					FaceEx * pTriangle = mesh->pMesh->GetFace(nTri);
					for(int i=0;i<3;i++)
					{
						int nVert = (nTri*3 + i) - iVertexDuplicates;
						
						Point3 vertice, normal, binormal, tangent, color;
						Point2 uv, uvfl;

						mesh->pMesh->GetVertex(pTriangle->vert[i], vertice);
						// offset vertice
						vertice -= vOffset;
						mesh->pMesh->GetTexVertex(pTriangle->texCoord[i], uv);
						mesh->pMesh->GetNormal(pTriangle->norm[i], normal);

						// before assigning the vert, check existing verts if there is a duplicate
						bool bDuplicate = false;
						for(int nVertB=0; nVertB < nVert; nVertB++)
						{
							if(mesh->v[nVertB].vert == vertice &&
									mesh->v[nVertB].normal == normal &&
									mesh->v[nVertB].uv == uv)
							{
								// match!
								// assign triangle corner to found vertex index
								mesh->t[pTriangle->meshFaceIndex].vertice[i] = nVertB;
								iVertexDuplicates++;
								bDuplicate = true;
								break;
							}
						}
						if(bDuplicate)
							continue;

						mesh->t[pTriangle->meshFaceIndex].vertice[i] = nVert;

						mesh->v[nVert].vert = vertice;
						mesh->v[nVert].normal = normal;
						mesh->v[nVert].uv = uv;
					
						int iTBindex = mesh->pMesh->GetFaceVertexTangentBinormal(pTriangle->meshFaceIndex, i);
						if(iTBindex != -1)
						{
							tangent = mesh->pMesh->GetTangent(iTBindex);
							binormal = mesh->pMesh->GetBinormal(iTBindex);
							mesh->v[nVert].tangent = tangent;
							mesh->v[nVert].binormal = binormal;
						}
						float alpha = 1.0f;
						int iVCindex = mesh->pMesh->GetFaceVertex(pTriangle->meshFaceIndex, i);		
						if(iVCindex != -1)
						{
							alpha = mesh->pMesh->GetAlphaVertex(pTriangle->alpha[i]);
							color = mesh->pMesh->GetColorVertex(pTriangle->color[i]);
							mesh->v[nVert].diffuse = (DWORD)(alpha * 255)<<24 | (DWORD)(color.x * 255)<<16 | (DWORD)(color.y *255)<<8 | (DWORD)(color.z * 255);
							mesh->v[nVert].uv = uv;
						}
						else
						{
							mesh->v[nVert].tangent = Point3(0,0,0);
							mesh->v[nVert].binormal = Point3(0,0,0);
						}
					}
				}

				mesh->nVerts = nVerts - iVertexDuplicates;
				iNumVerts += mesh->nVerts;
				mesh->nTris = nTris;
				iNumFaces += mesh->nTris;

				// insert into mesh list
				cmpnd->object_data->data[iLOD].meshes.push_back(mesh);
			}
		}

		// save vmeshref

		Box3 Bounds;
		cur_lodnode->GetIGameObject()->GetBoundingBox(Bounds);		

		cmpnd->object_data->data[iLOD].vmeshref.bmaxx = Bounds.pmax.x;
		cmpnd->object_data->data[iLOD].vmeshref.bmaxy = Bounds.pmax.y;
		cmpnd->object_data->data[iLOD].vmeshref.bmaxz = Bounds.pmax.z;
		cmpnd->object_data->data[iLOD].vmeshref.bminx = Bounds.pmin.x;
		cmpnd->object_data->data[iLOD].vmeshref.bminy = Bounds.pmin.y;
		cmpnd->object_data->data[iLOD].vmeshref.bminz = Bounds.pmin.z;
		Point3 vCenter = Bounds.Center() - vOffset; // center in local component space
		cmpnd->object_data->data[iLOD].vmeshref.Center_X = vCenter.x;
		cmpnd->object_data->data[iLOD].vmeshref.Center_Y = vCenter.y;
		cmpnd->object_data->data[iLOD].vmeshref.Center_Z = vCenter.z;
		// radius is the distance from center to one bounding box point
		Point3 radius_vec = Bounds.pmax - Bounds.Center();
 		// increase the radius by 25% as FLModelTool does the same
 		cmpnd->object_data->data[iLOD].vmeshref._Radius = radius_vec.FLength() * 1.25f; 


		cmpnd->object_data->data[iLOD].vmeshref.Header_Size = 60;
		cmpnd->object_data->data[iLOD].vmeshref.Num_Meshes = (unsigned short)cmpnd->object_data->data[iLOD].meshes.size();
		cmpnd->object_data->data[iLOD].vmeshref.Num_Vert = iNumVerts;

		// exit if referenced vertices is over unsigned short limit, because of vmeshdata header limitation
		if(iNumFaces*3 > 0xFFFF)
		{
			string sError = "The group \"";
			sError += cmpnd->sObjectName;
			sError += "\" references more vertices than Freelancer can handle. Split the group into smaller groups!";
			MessageBox(0,sError.c_str(),"Error exporting a group object",MB_ICONERROR);
			return false;
		}

		cmpnd->object_data->data[iLOD].vmeshref.Num_Index = iNumFaces*3;

	}
	
	cmpnd->object_data->iLODs = iLODS;

	cmpnd->index = (int)lstCMPData->size();

	lstCMPData->push_back(cmpnd);

		IGameScene* nMeshes;

	nMeshes = GetIGameInterface();

	//nMeshes->InitialiseIGame(false); // true- we want selected only - false we want all!

	nMeshes->SetStaticFrame(0);

	// write cons data
	if(cmpnd->sObjectName != "Root")
	{
		if(cmpnd->sObjectName.length() > 4 && cmpnd->sObjectName.substr(cmpnd->sObjectName.length()-4, cmpnd->sObjectName.length()) == ".rev")
		{
			PartRev revdata; memset(&revdata, 0, sizeof(PartRev));
			strcpy(revdata.ParentName, "Root");
			strcpy(revdata.ChildName, cmpnd->sObjectName.c_str());

			TimeValue endTime = nMeshes->GetSceneEndTime()/2;

			Interval interval;

			IGameControl *IGcontrol = pRootGrp->GetIGameControl();

			Control *rot = IGcontrol->GetMaxControl(IGAME_ROT);

			GMatrix OrObjTfm = pRootGrp->GetObjectTM(0);
			GMatrix ObjEndTfm = pRootGrp->GetObjectTM(endTime);
			Quat RotQ1st = OrObjTfm.Rotation();
			Quat RotQ = ObjEndTfm.Rotation();
			GMatrix RotMtx = OrObjTfm.Inverse();
			Matrix3 ObjTfm = RotMtx.ExtractMatrix3();

			rot->GetValue((endTime), &RotQ1st, interval, CTRL_ABSOLUTE);         
			AngAxis angAxis(RotQ1st.Invert()); 
			
						
			revdata.OriginX = vOffset.x;
			revdata.OriginY = vOffset.y;
			revdata.OriginZ = vOffset.z;

			// identity matrix (-> no rotation)
			revdata.RotMatXX = -ObjTfm.GetColumn(0).x;
			revdata.RotMatXY = -ObjTfm.GetColumn(1).x;
			revdata.RotMatXZ = -ObjTfm.GetColumn(2).x;
			revdata.RotMatYX = ObjTfm.GetColumn(0).y;
			revdata.RotMatYY = ObjTfm.GetColumn(1).y;
			revdata.RotMatYZ = ObjTfm.GetColumn(2).y;
			revdata.RotMatZX = ObjTfm.GetColumn(0).z;
			revdata.RotMatZY = ObjTfm.GetColumn(1).z;
			revdata.RotMatZZ = ObjTfm.GetColumn(2).z;

			// fill in some standard values for axis rotate and min/max angles so that the component shows up ingame (doesnt if its zero)
			revdata.AxisRotX = angAxis.axis.x;
			revdata.AxisRotY = angAxis.axis.y;
			revdata.AxisRotZ = angAxis.axis.z;

			int Revs = angAxis.GetNumRevs();

			revdata.Max = angAxis.angle*2;


			fwrite(&revdata, sizeof(revdata), 1, revnode);

		} else if(cmpnd->sObjectName.length() > 4 && cmpnd->sObjectName.substr(cmpnd->sObjectName.length()-5, cmpnd->sObjectName.length()) == ".pris")
		{
			PartRev prisdata; memset(&prisdata, 0, sizeof(PartRev));
			strcpy(prisdata.ParentName, "Root");
			strcpy(prisdata.ChildName, cmpnd->sObjectName.c_str());

			prisdata.OriginX = vOffset.x;
			prisdata.OriginY = vOffset.y;
			prisdata.OriginZ = vOffset.z;

			// identity matrix (-> no rotation)
			prisdata.RotMatXX = 1;
			prisdata.RotMatYY = 1;
			prisdata.RotMatZZ = 1;

			// fill in some standard values for axis rotate and min/max angles so that the component shows up ingame (doesnt if its zero)
			prisdata.AxisRotZ = 1;
			prisdata.Max = 360;

			fwrite(&prisdata, sizeof(prisdata), 1, prisnode);

		} else
		{
			PartFix fixdata;  memset(&fixdata, 0, sizeof(PartFix));
			strcpy(fixdata.ParentName, "Root");
			strcpy(fixdata.ChildName, cmpnd->sObjectName.c_str());

			fixdata.OriginX = vOffset.x;
			fixdata.OriginY = vOffset.y;
			fixdata.OriginZ = vOffset.z;

			// identity matrix
			fixdata.RotMatXX = 1;
			fixdata.RotMatYY = 1;
			fixdata.RotMatZZ = 1;

			fwrite(&fixdata, sizeof(fixdata), 1, fixnode);
		}
	}

	return true;
}

void maxCMPExport::check_line(Line *lines, uint *num_lines, Line new_line) {
	uint i;
	for (i = 0; i < *num_lines; ++i) {
		if (((lines[i].v1 == new_line.v1) && (lines[i].v2 == new_line.v2)) || ((lines[i].v1 == new_line.v2) && (lines[i].v2 == new_line.v1)))
			return;
	}
	lines[*num_lines] = new_line;
	++(*num_lines);
}

static uint iTotalVWireIndices = 0;

string convertInt(int number)
{
    if (number == 0)
        return "0";
    string temp="";
    string returnvalue="";
    while (number>0)
    {
        temp+=number%10+48;
        number/=10;
    }
    for (int i=0;i<(int)temp.length();i++)
        returnvalue+=temp[temp.length()-i-1];
    return returnvalue;
}

void maxCMPExport::CreateVWData(CMPND_DATA* cmpnd)
{
	uint iLOD = cmpnd->object_data->iLODWireframe;

	VWireData vwire;

	vwire.StructSize = 16;
	vwire.VMeshLibID = fl_crc32((char*)cmpnd->object_data->data[iLOD].vmeshdata_file->sFilename.c_str());
	vwire.VertBase = cmpnd->object_data->data[iLOD].vmeshref.Start_Vert;

	// array as big as number of faces*2
	uint num_lines = 0;
	Line* lines = (Line*)malloc(((cmpnd->object_data->data[iLOD].vmeshref.Num_Index)/3)*2 * sizeof(Line));

	uint iVertOffset = 0;

	for(list<SMESH*>::iterator meshiter = cmpnd->object_data->data[iLOD].meshes.begin(); meshiter != cmpnd->object_data->data[iLOD].meshes.end(); meshiter++)
	{
		SMESH* mesh = *meshiter;
		for(uint nFace = 0;nFace < (uint)mesh->nTris; nFace++)
		{
			Line templine;
			templine.v1 = iVertOffset + mesh->t[nFace].vertice[0];
			templine.v2 = iVertOffset + mesh->t[nFace].vertice[1];
			check_line(lines, &num_lines, templine);
			templine.v1 = iVertOffset + mesh->t[nFace].vertice[0];
			templine.v2 = iVertOffset + mesh->t[nFace].vertice[2];
			check_line(lines, &num_lines, templine);
		}
		iVertOffset += mesh->nVerts;
	}

	vwire.VertRange = iVertOffset;
	vwire.RefVertQuant = num_lines * 2;
	vwire.VertQuant = cmpnd->object_data->data[iLOD].vmeshref.Num_Vert;

	iTotalVWireIndices += vwire.RefVertQuant;

	if(iTotalVWireIndices > 16000)
	{

		string sError = "Warning: Your total indices count for the Wireframe exceeds Freelancer's limit of 16 000. Indices: ";
		sError += convertInt(iTotalVWireIndices);
		MessageBox(0,sError.c_str(),"Warning exporting VWireData",MB_ICONERROR);

	}

	// write file
	string sVWDFile = cmpnd->sObjectName + ".vwd";
	FILE* fVWire = fopen(sVWDFile.c_str(), "wb");
	fwrite(&vwire, sizeof(VWireData), 1, fVWire);
	fwrite(lines, sizeof(Line), num_lines, fVWire);
	fclose(fVWire);

	free(lines);
}


bool maxCMPExport::ExportGroup(IGameNode * pRootGrp, string sExportFilename)
{	
	
	IGameScene *nMeshes;
	nMeshes = GetIGameInterface();
	nMeshes->SetStaticFrame(0);

	list<CMPND_DATA*>* lstCMPData = new list<CMPND_DATA*>;

	fixnode = fopen("fixnode.bin", "wb");
	revnode = fopen("revnode.bin", "wb");
	prisnode = fopen("prisnode.bin", "wb");

	// create data for root grp
	if(!CreateCMPData(pRootGrp, lstCMPData))
		return false;

	// create data for all components
	for(int nNode = 0; nNode < nMeshes->GetTopLevelNodeCount(); nNode++)
	{	
		IGameNode* pNode = nMeshes->GetTopLevelNode(nNode);

		if(pNode != pRootGrp && pNode->IsGroupOwner())
			if(!CreateCMPData(pNode, lstCMPData))
				return false;
	}

	fclose(fixnode);
	fclose(revnode);
	fclose(prisnode);

	// create vmeshdata files
	list<VMESHDATA_FILE*>* lstVMeshData = new list<VMESHDATA_FILE*>;

	VMESHDATA_FILE* cur_meshdata_file = NULL;

	string sFilenameSubstr = sExportFilename.substr(sExportFilename.rfind("\\")+1, (sExportFilename.length()-3) - (sExportFilename.rfind("\\")+1));

	for(list<CMPND_DATA*>::iterator it = lstCMPData->begin(); it != lstCMPData->end(); it++)
	{
		for(uint iLOD = 0; iLOD < (*it)->object_data->iLODs; iLOD++)
		{
			if(!cur_meshdata_file || ((*it)->object_data->data[iLOD].vmeshref.Num_Index + cur_meshdata_file->nRefVertices) > 0xFFFF) // unsigned short limitation
			{
				cur_meshdata_file = new VMESHDATA_FILE;
				cur_meshdata_file->sFilename = sFilenameSubstr;
				cur_meshdata_file->sFilename += (char)(48+ (int)lstVMeshData->size());
				cur_meshdata_file->sFilename += ".vms";
				cur_meshdata_file->nVertices = 0;
				cur_meshdata_file->nRefVertices = 0;
				cur_meshdata_file->nMeshes = 0;
				cur_meshdata_file->file = fopen(cur_meshdata_file->sFilename.c_str(), "wb");
				lstVMeshData->push_back(cur_meshdata_file);
			}

			cur_meshdata_file->nRefVertices += (*it)->object_data->data[iLOD].vmeshref.Num_Index;
			cur_meshdata_file->nVertices += (*it)->object_data->data[iLOD].vmeshref.Num_Vert;
			cur_meshdata_file->nMeshes += (uint)(*it)->object_data->data[iLOD].vmeshref.Num_Meshes;

			(*it)->object_data->data[iLOD].vmeshref.VMesh_LibId = fl_crc32((char*)cur_meshdata_file->sFilename.c_str());
			(*it)->object_data->data[iLOD].vmeshdata_file = cur_meshdata_file;
		}

		// update cmp data
		(*it)->object_data->sFileName = sFilenameSubstr;
		(*it)->object_data->sFileName += (*it)->sObjectName;
		(*it)->object_data->sFileName += ".3db";
	}

	// now fill vmeshdata files
	for(list<VMESHDATA_FILE*>::iterator it = lstVMeshData->begin(); it != lstVMeshData->end(); it++)
	{
		// save header
		vmsHeader header;
		header.unk1 = 1;
		header.unk2 = 4;

		header.nMeshes = (*it)->nMeshes;

		switch(OptionsDlgExport->eFVFtype)
		{
			default:
			case FVF_NORMAL:
				header.FVF = 0x112;
				break;
			case FVF_VERTEXARGB:
				header.FVF = 0x142;
				break;
			case FVF_VERTEXARGB_NORMALS:
				header.FVF = 0x152;
				break;
			case FVF_EXTRAUV:
				header.FVF = 0x212;
				break;
			case FVF_TANGENTS:
				header.FVF = 0x412;
				break;
			case FVF_EXTRAUV_TANGENTS:
				header.FVF = 0x512;
				break;
		}

		header.nRefVertices = (*it)->nRefVertices;
		header.nVertices = (*it)->nVertices;

		fwrite (&header, sizeof(header), 1, (*it)->file);

		uint iMesh = 0;
		uint iGlobalStartVertex = 0;
		uint iGlobalStartIndex = 0;

		// save mesh header data
		for(list<CMPND_DATA*>::iterator itcmpnd = lstCMPData->begin(); itcmpnd != lstCMPData->end(); itcmpnd++)
		{
			for(uint iLOD = 0; iLOD < (*itcmpnd)->object_data->iLODs; iLOD++)
			{
				if( (*itcmpnd)->object_data->data[iLOD].vmeshdata_file == (*it))
				{
					(*itcmpnd)->object_data->data[iLOD].vmeshref.Start_Mesh = iMesh;
					(*itcmpnd)->object_data->data[iLOD].vmeshref.Start_Vert = iGlobalStartVertex;
					(*itcmpnd)->object_data->data[iLOD].vmeshref.Start_Index = iGlobalStartIndex;

					uint iStartVert = 0; // this is per vmeshpart

					for(list<SMESH*>::iterator itmesh = (*itcmpnd)->object_data->data[iLOD].meshes.begin(); itmesh != (*itcmpnd)->object_data->data[iLOD].meshes.end(); itmesh++)
					{
						vmsMesh vmesh;
						vmesh.material = fl_crc32((char*)(*itmesh)->sMaterial.c_str());
						vmesh.start_vert_number = iStartVert;
						vmesh.end_vert_number = (iStartVert + (*itmesh)->nVerts) - 1;
						vmesh.number_of_vert_references = (*itmesh)->nTris*3;
						vmesh.padding = 0xcc;
						
						fwrite(&vmesh, sizeof(vmesh), 1, (*it)->file);

						iStartVert += (*itmesh)->nVerts;
						iGlobalStartIndex += vmesh.number_of_vert_references;
						iGlobalStartVertex += (*itmesh)->nVerts;
						iMesh++;
					}
				}
			}
		}

		// save indices
		for(list<CMPND_DATA*>::iterator itcmpnd = lstCMPData->begin(); itcmpnd != lstCMPData->end(); itcmpnd++)
		{
			for(uint iLOD = 0; iLOD < (*itcmpnd)->object_data->iLODs; iLOD++)
			{
				if( (*itcmpnd)->object_data->data[iLOD].vmeshdata_file == (*it))
				{
					for(list<SMESH*>::iterator itmesh = (*itcmpnd)->object_data->data[iLOD].meshes.begin(); itmesh != (*itcmpnd)->object_data->data[iLOD].meshes.end(); itmesh++)
					{
						// write triangles
						fwrite((*itmesh)->t, sizeof(vmsTri) * (*itmesh)->nTris, 1, (*it)->file);				
					}
				}
			}
		}

		// save vertices
		for(list<CMPND_DATA*>::iterator itcmpnd = lstCMPData->begin(); itcmpnd != lstCMPData->end(); itcmpnd++)
		{
			for(uint iLOD = 0; iLOD < (*itcmpnd)->object_data->iLODs; iLOD++)
			{
				if( (*itcmpnd)->object_data->data[iLOD].vmeshdata_file == (*it))
				{
					for(list<SMESH*>::iterator itmesh = (*itcmpnd)->object_data->data[iLOD].meshes.begin(); itmesh != (*itcmpnd)->object_data->data[iLOD].meshes.end(); itmesh++)
					{
						// write vertices
						switch(OptionsDlgExport->eFVFtype)
						{
							default:
							case FVF_NORMAL:
								{
									for(int p=0;p<(*itmesh)->nVerts;p++)
									{
										// vertice
										fwrite((void*)(*itmesh)->v[p].vert, 3*4, 1, (*it)->file);	
										// normal
										fwrite((void*)(*itmesh)->v[p].normal, 3*4, 1, (*it)->file);	
										// uv
										fwrite((void*)(*itmesh)->v[p].uv, 2*4, 1, (*it)->file);	
									}
									break;
								}
							case FVF_VERTEXARGB:
								{
									for(int p=0;p<(*itmesh)->nVerts;p++)
									{
										// vertice
										fwrite((void*)(*itmesh)->v[p].vert, 3*4, 1, (*it)->file);	
										// diffuse
										fwrite(&(*itmesh)->v[p].diffuse, 1*4, 1, (*it)->file);	
										// uv
										fwrite((void*)(*itmesh)->v[p].uv, 2*4, 1, (*it)->file);	
									}
									break;
								}
							case FVF_VERTEXARGB_NORMALS:
								{
									for(int p=0;p<(*itmesh)->nVerts;p++)
									{
										// vertice
										fwrite((void*)(*itmesh)->v[p].vert, 3*4, 1, (*it)->file);	
										// normal
										fwrite((void*)(*itmesh)->v[p].normal, 3*4, 1, (*it)->file);
										// diffuse
										fwrite(&(*itmesh)->v[p].diffuse, 1*4, 1, (*it)->file);	
										// uv
										fwrite((void*)(*itmesh)->v[p].uv, 2*4, 1, (*it)->file);	
									}
									break;
								}
							case FVF_EXTRAUV:
								{
									for(int p=0;p<(*itmesh)->nVerts;p++)
									{
										// vertice
										fwrite((void*)(*itmesh)->v[p].vert, 3*4, 1, (*it)->file);	
										// normal
										fwrite((void*)(*itmesh)->v[p].normal, 3*4, 1, (*it)->file);	
										// uv
										fwrite((void*)(*itmesh)->v[p].uv, 2*4, 1, (*it)->file);	
										// uv2
										fwrite((void*)(*itmesh)->v[p].uv2, 2*4, 1, (*it)->file);
									}
									break;
								}
							case FVF_TANGENTS:
								{
									for(int p=0;p<(*itmesh)->nVerts;p++)
									{
										// vertice
										fwrite((void*)(*itmesh)->v[p].vert, 3*4, 1, (*it)->file);	
										// normal
										fwrite((void*)(*itmesh)->v[p].normal, 3*4, 1, (*it)->file);	
										// uv
										fwrite((void*)(*itmesh)->v[p].uv, 2*4, 1, (*it)->file);	
										// tangent
										fwrite((void*)(*itmesh)->v[p].tangent, 3*4, 1, (*it)->file);	
										// binormal
										fwrite((void*)(*itmesh)->v[p].binormal, 3*4, 1, (*it)->file);	
									}
									break;
								}
							case FVF_EXTRAUV_TANGENTS:
								{
									for(int p=0;p<(*itmesh)->nVerts;p++)
									{
										// vertice
										fwrite((void*)(*itmesh)->v[p].vert, 3*4, 1, (*it)->file);	
										// normal
										fwrite((void*)(*itmesh)->v[p].normal, 3*4, 1, (*it)->file);	
										// uv
										fwrite((void*)(*itmesh)->v[p].uv, 2*4, 1, (*it)->file);	
										// uv2
										fwrite((void*)(*itmesh)->v[p].uv2, 2*4, 1, (*it)->file);
										// tangent
										fwrite((void*)(*itmesh)->v[p].tangent, 3*4, 1, (*it)->file);	
										// binormal
										fwrite((void*)(*itmesh)->v[p].binormal, 3*4, 1, (*it)->file);	
									}
									break;
								}
						}

	
					}
				}
			}
		}

		
		// finished this vmeshdata file
		fclose((*it)->file);
	}

	// create vwiredata
	iTotalVWireIndices = 0;
	if(OptionsDlgExport->bWireFrame)
		for(list<CMPND_DATA*>::iterator it = lstCMPData->begin(); it != lstCMPData->end(); it++)
			CreateVWData((*it));


	cDlgOptions dlgOptions (NULL);
	dlgOptions.SetOptions(OptionsDlgExport);
	dlgOptions.SetCMPNDData(lstCMPData);
	dlgOptions.SetVMeshData(lstVMeshData);
	dlgOptions.SetFileName((char*)sExportFilename.c_str());
	dlgOptions.DoModal();
	
	return 0;

}


int	maxCMPExport::DoExport(const TCHAR *export_filename,ExpInterface *ei,Interface *i, BOOL suppressPrompts, DWORD options)
{	
	
	
	GroupA mGroup;

	// Set a global prompt display switch
	exportSelected = (options & SCENE_EXPORT_SELECTED) ? TRUE : FALSE;

	// Grab the interface pointer.
	ip = i;

	// Get the options the user selected the last time
	ReadConfig();
	
	OptionsDlgExport = new ExportOptions(NULL);
	
	OptionsDlgExport->DoModal();
	if(!OptionsDlgExport->bDoExport)
		return 1; // abort by user

	NodeProcess();

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
	cm->SetUserCoordSystem( myCoordSystem );

	nMeshes->InitialiseIGame(false); // true- we want selected only - false we want all!

	nMeshes->SetStaticFrame(0);

	// search for root group

	bool bFoundRoot = false;

	for(int nMesh = 0; nMesh < nMeshes->GetTopLevelNodeCount(); nMesh++)	
	{		
		IGameNode *pMesh = nMeshes->GetTopLevelNode(nMesh);	

		// ignore cameras, lights and hidden stuff
		if(pMesh->IsTarget() || pMesh->IsNodeHidden())
			continue;

		if(pMesh->IsGroupOwner() && !strcmp(pMesh->GetName(),"Root"))
		{
			if(bFoundRoot)
			{
				MessageBox(0,"You have more than one node with the name \"Root\"! One Root node has been picked as Root, however this might not be the intended one!","Warning exporting Root node.",MB_ICONERROR);
				return 1;
			}

			if(!ExportGroup(pMesh, string(export_filename)))
				return 1;
			bFoundRoot = true;
		}
	}
		
	if(!bFoundRoot)
	{
		MessageBox(0,"You need to have one group named \"Root\" to export!","Error finding Root node.",MB_ICONERROR);
		return 1;
	}


	// -----------------------------------------------------------------------------------------
	AFX_MANAGE_STATE(AfxGetStaticModuleState());



	// Write the current options to be used next time around.
	WriteConfig();

	return 1;
}

BOOL maxCMPExport::SupportsOptions(int ext, DWORD options) {
	assert(ext == 0);	// We only support one extension
	return(options == SCENE_EXPORT_SELECTED) ? TRUE : FALSE;
}
TSTR maxCMPExport::GetCfgFilename()
{	TSTR filename;
	filename += ip->GetDir(APP_PLUGCFG_DIR);
	filename += "\\";
	filename += CFGFILENAME;

	return filename;
}// NOTE: Update anytime the CFG file changes
#define CFG_VERSION 0x03

BOOL maxCMPExport::ReadConfig()
{	TSTR filename = GetCfgFilename();
	FILE* cfgStream;

	cfgStream = fopen(filename, "rb");
	if (!cfgStream)
	return FALSE;

	// First item is a file version
	int fileVersion = _getw(cfgStream);

	if (fileVersion > CFG_VERSION) {
		// Unknown version
		fclose(cfgStream);
		return FALSE;
	}

	fclose(cfgStream);

	return TRUE;
}
void maxCMPExport::WriteConfig()
{	TSTR filename = GetCfgFilename();
	FILE* cfgStream;

	cfgStream = fopen(filename, "wb");
	if (!cfgStream)
	return;

	// Write CFG version
	_putw(CFG_VERSION,				cfgStream);

	fclose(cfgStream);
}