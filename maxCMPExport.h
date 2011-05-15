/**********************************************************************
 *<
	FILE: maxCMPExport.h

	DESCRIPTION:	Includes for Plugins

	CREATED BY:

	HISTORY:

 *>	Copyright (c) 2003, All Rights Reserved.
 **********************************************************************/

#ifndef __maxCMPExport__H
#define __maxCMPExport__H


#include "stdafx.h"

#include <string>
#include <list>
using namespace std;


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
//SIMPLE TYPE


#define CFGFILENAME		_T("maxCMPExport.CFG")
#define CMPEXPORT_VERSION 0.9
#define MAX_LODS 7

typedef unsigned int uint;

struct FileName_
{
	const TCHAR * File_Name;
};

enum EXPORT_CMPNT_OPTION
{
	EXPORT_CMPNT_RELOCATE = 0,
	EXPORT_CMPNT_NORELOCATE = 1,
	EXPORT_CMPNT_FORCE_DWORD = 0x7FFFFFFF
};

enum FVF_TYPE
{
	FVF_NORMAL,
	FVF_VERTEXARGB,
	FVF_VERTEXARGB_NORMALS,
	FVF_EXTRAUV,
	FVF_TANGENTS,
	FVF_EXTRAUV_TANGENTS,
	FVF_TYPE_FORCE_DWORD = 0x7FFFFFFF
};

unsigned int fl_crc32(char *);

struct VECTOR
{
	Point3 vec;
};

struct sObjInfo
{
	TCHAR *gName;
	TCHAR *parentName;
	int				objID;
	int				parentID;	
	//sPRS			prs;
	// initialize (assign) values from a IGameNode class
	void fromNode(IGameNode *pNode);
};
//-------------------------------------------------------------------------------------------
// VMeshData structures

struct Line {
	unsigned short v1, v2;
};

struct VWireData
{
	uint StructSize; // 16 dec
	uint VMeshLibID;
	unsigned short VertBase;
	unsigned short VertQuant;
	unsigned short RefVertQuant;
	unsigned short VertRange;
};
struct VWireMesh {
	int start_vertex, end_vertex, num_triangles;
};

struct vmsVert
{
	Point3 vert;
	Point3 normal;
	uint diffuse;
	Point2 uv;
	Point2 uv2;
	Point3 tangent;
	Point3 binormal;
};
struct StartVertArray
{
	short StartVertNumber;
	short EndVertNumber;
	short RefVertNum;
};
struct SplineVert
{
	Point3 SVert;
};
struct mSplineKnot
{
	unsigned short SVertice[3];
};
struct VMeshRef
{
	uint Header_Size; // 0x0000003C
	uint VMesh_LibId; // crc of vmeshdata name
	unsigned short Start_Vert;
	unsigned short Num_Vert;
	unsigned short Start_Index;
	unsigned short Num_Index;
	unsigned short Start_Mesh;
	unsigned short Num_Meshes;
	float bmaxx;
	float bminx;
	float bmaxy;
	float bminy;
	float bmaxz;
	float bminz;
	float Center_X;
    float Center_Y;
	float Center_Z;
	float _Radius;

};


struct vmsTri
{
	unsigned short vertice[3];
};
struct gvmsTri
{
	unsigned short gvertice[3];
};
struct vmsHeader
{
	int unk1, unk2;
	unsigned short	nMeshes, nRefVertices, FVF, nVertices;
};

struct vmsMesh
{
	unsigned int material;	// material ID is a CRC32 (with mod table) of the material name
	unsigned short start_vert_number;
	unsigned short end_vert_number;
	unsigned short number_of_vert_references; // faces * 3;
	short padding;	// = 0xcc, for dword allignment, apparently
};

struct GLIST
{

	TCHAR * glname ;
	int NodeCount;
	IGameNode *GroupMesh;
};

struct GroupA
{
	int gChildren;
	Tab<IGameNode*> NodeInfo;
	TCHAR * gname;

	void fromNode(IGameNode *pNode);

};
struct ConsFix
{
	uint cfParent;
	uint cfChild;
	float OriginX;
	float OriginY;
	float OriginZ;
	Point3 RotationX;
	Point3 RotationY;
	Point3 RotationZ;
};

struct sNodeInfo
{
	TCHAR *NodeName;
	TCHAR *parentName;
	int				objID;
	int				parentID;	
	// initialize (assign) values from a IGameNode class
	void fromNode(IGameNode *pNode);
};
struct MSpline
{
	SplineVert * sv;	// vmsVert array
	// vmsTri array
	mSplineKnot * spk;
	TCHAR* sname;
	int nSVerts;
	int Num_Splines;
	// mesh name

	//IGameMesh *pMesh; // 3ds max mesh object
};


struct SMESH
{
	vmsVert * v;	// vmsVert array
	vmsTri * t;		// vmsTri array
	int nVerts;
	int nTris;
	
	string sMaterial;	// material name
	string sName;	// mesh name

	IGameMesh *pMesh; // 3ds max mesh object
};

struct VMESHDATA_FILE
{
	string sFilename;
	FILE* file;
	uint nRefVertices;
	uint nVertices;
	uint nMeshes;
};

struct LOD_DATA
{
	VMESHDATA_FILE* vmeshdata_file;
	VMeshRef vmeshref;
	list<SMESH*> meshes;
	bool bUseAsWireframe;
};

struct THREEDB_DATA
{
	string sFileName; 
	uint iLODs;
	uint iLODWireframe;
	LOD_DATA data[MAX_LODS];
};


struct PartFix
{
     char ParentName[0x40];
     char ChildName[0x40];
     float OriginX;
     float OriginY;
     float OriginZ;
     float RotMatXX;
     float RotMatXY;
     float RotMatXZ;
     float RotMatYX;
     float RotMatYY;
     float RotMatYZ;
     float RotMatZX;
     float RotMatZY;
     float RotMatZZ;
};

struct PartRev
{
     char ParentName[0x40];
     char ChildName[0x40];
     float OriginX;
     float OriginY;
     float OriginZ;
	 float OffsetX;
	 float OffsetY;
     float OffsetZ;
     float RotMatXX;
     float RotMatXY;
     float RotMatXZ;
     float RotMatYX;
     float RotMatYY;
     float RotMatYZ;
     float RotMatZX;
     float RotMatZY;
     float RotMatZZ;
	 float AxisRotX;
     float AxisRotY;
     float AxisRotZ;
     float Min;
     float Max;
};

struct CMPND_DATA
{
	string sName;
	string sObjectName;
	THREEDB_DATA* object_data;
	int index;
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
