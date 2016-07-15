#include "stdafx.h"
#include "resource.h"
#include "DlgOptions.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <wchar.h>
#include <io.h>
#include <set>
#include <string>

#include "matexport17.h"
#include "UTF.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//=================================================================
// constructor
//======================================================================
cDlgOptions::cDlgOptions(CWnd* pParent /*=NULL*/)
: CDialog(IDD_OPTIONS, pParent)
{
	//{{AFX_DATA_INIT(cDlgOptions)
	//}}AFX_DATA_INIT
}
//======================================================================
// DoDataExchange
//======================================================================
void cDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cDlgOptions)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cDlgOptions, CDialog)
	//{{AFX_MSG_MAP(cDlgOptions)
	//ON_BN_CLICKED(IDC_BTBROWSE,     OnBrowse)
	//ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//======================================================================
// OnInitDialog
//======================================================================
std::set<MMESH*> found;



bool MyDataSortPredicate(const MMESH* lhs, const MMESH* rhs)
{
  return lhs->material < rhs->material;
}
bool MyUniquePredicate(const MMESH* lhs, const MMESH* rhs)
{
  return lhs->material < rhs->material;
}

BOOL cDlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CDialog::CenterWindow();

	tree = (CTreeCtrl *) GetDlgItem(IDC_TREE);
	utf = new UTF();


	char MatName[200];
	char SIMatName[200];
	char TypeName[200];
	char MatFilePath[262];
	char SIMatFilePath[262];
	
	HTREEITEM root = utf->AddNewNode(tree, NULL, "\\");
	HTREEITEM MaterialLib = utf->AddNewNode(tree, root, "material library");
	HTREEITEM TextureLib = utf->AddNewNode(tree, root, "texture library");

	for (std::list<MMESH*>::iterator i = meshList->begin();i != meshList->end(); ++i)
	{
		meshList->sort(MyDataSortPredicate);
		
	}

	char MatID[200];
	char MaterialID[200];
	string nameInList = "first";
	list<MMESH *>::iterator j = meshList->begin();
	while (j != meshList->end())
	{    
		MMESH * mesh = *j;
		string nameList = mesh->material;
		strcpy (MatID, nameInList.c_str());
		strcpy (MaterialID, nameList.c_str());

		string str1 (MaterialID);
		string str2 (MatID);

		//bool isActive;
		if (str1.compare(str2) != 0)
		{        
			j++;
		}    
		else    
		{        
			meshList->erase(j++);   
		}
		nameInList = mesh->material;
	}

	for (std::list<MMESH*>::iterator i = meshList->begin();i != meshList->end(); ++i)
	{
		MMESH * mesh = *i;
		string nameInList = mesh->material;
		strcpy (MatName, nameInList.c_str());
		string mType = mesh->MatType;
		strcpy (TypeName, mType.c_str());

		HTREEITEM MatData = utf->AddNewNode(tree, MaterialLib, MatName);
		HTREEITEM Type01 = utf->AddNewNode(tree, MatData, "Type");
		char * CR_Type_data = (char *) malloc ( strlen(TypeName) + 1 + 4 );
		strcpy (CR_Type_data + 4, TypeName);
		*(uint *)CR_Type_data = (uint)strlen(TypeName) + 1;
		tree->SetItemData(Type01, (DWORD_PTR)CR_Type_data);
		bool bIsOpac = mesh->IsOpac;
		bool bIsSelfIlluminate = mesh->IsSelfIlluminate;

		if(bIsOpac)
		{
			HTREEITEM OpacityChan = utf->AddNewNode(tree, MatData, "Oc");
			float * Opacity_data = (float *) malloc (4 + 4);
			*(int *) Opacity_data = 4;
			Opacity_data[1] = mesh->OpacityVal;
			tree->SetItemData(OpacityChan, (DWORD_PTR)Opacity_data);

			HTREEITEM DiffuseChan = utf->AddNewNode(tree, MatData, "Dc");
			float * Diffuse_data = (float *) malloc (12 + 4);
			*(int *) Diffuse_data = 12;
			Diffuse_data[1] = mesh->DiffuseVal.x;
			Diffuse_data[2] = mesh->DiffuseVal.y;
			Diffuse_data[3] = mesh->DiffuseVal.z;
			tree->SetItemData(DiffuseChan, (DWORD_PTR)Diffuse_data);

		}
		else if(bIsSelfIlluminate)
		{
			string sMat_Name = ".tga";
			string sSiMat_Name = ".tga";
			//strcat (MatName, nameInList.c_str());
			strcpy (SIMatName, mesh->SIname.c_str());
			strcat (MatName, sMat_Name.c_str());
			strcpy (MatFilePath, mesh->pFilePath.c_str());
			strcat (SIMatName, sSiMat_Name.c_str());
			strcpy (SIMatFilePath, mesh->pSIFilePath.c_str());

			HTREEITEM DtFlags = utf->AddNewNode(tree, MatData, "Dt_flags");
			int * DtFlags_data = (int *)malloc (2*sizeof(int) + 4);
			DtFlags_data[0] = 8;	// size = 8 (2 integers)
			DtFlags_data[1] = 64;
			DtFlags_data[2] = 0;
			tree->SetItemData(DtFlags, (DWORD_PTR)DtFlags_data);

			HTREEITEM DtName = utf->AddNewNode(tree, MatData, "Dt_name");
			char * DtName_data = (char *) malloc ( strlen(MatName) + 1 + 4 );
			strcpy (DtName_data + 4, MatName);
			*(uint *)DtName_data = (uint)strlen(MatName) + 1;
			tree->SetItemData(DtName, (DWORD_PTR)DtName_data);

			HTREEITEM EtFlags = utf->AddNewNode(tree, MatData, "Et_flags");
			int * EtFlags_data = (int *)malloc (2*sizeof(int) + 4);
			EtFlags_data[0] = 8;	// size = 8 (2 integers)
			EtFlags_data[1] = 64;
			EtFlags_data[2] = 0;
			tree->SetItemData(EtFlags, (DWORD_PTR)EtFlags_data);

			HTREEITEM EtName = utf->AddNewNode(tree, MatData, "Et_name");
			char * EtName_data = (char *) malloc ( strlen(SIMatName) + 1 + 4 );
			strcpy (EtName_data + 4, SIMatName);
			*(uint *)EtName_data = (uint)strlen(SIMatName) + 1;
			tree->SetItemData(EtName, (DWORD_PTR)EtName_data);

			HTREEITEM Texture = utf->AddNewNode(tree, TextureLib, MatName);
			HTREEITEM Texture2 = utf->AddNewNode(tree, TextureLib, SIMatName);

			{

				FILE * MatFilePath_file = fopen(MatFilePath, "rb");

				if (MatFilePath_file)
				{
					HTREEITEM MIPType;

					std::string fn = MatFilePath;
					if (icompare(fn.substr(fn.find_last_of(".") + 1), "DDS"))
						MIPType = utf->AddNewNode(tree, Texture, "MIPS");
					else
						MIPType = utf->AddNewNode(tree, Texture, "MIP0");

					fseek(MatFilePath_file, 0, SEEK_END);
					int MatFilePath_file_size = ftell(MatFilePath_file);
					fseek(MatFilePath_file, 0, SEEK_SET);
					char * MatFilePath_file_data = (char *)malloc(MatFilePath_file_size + 4);
					fread(MatFilePath_file_data + 4, MatFilePath_file_size, 1, MatFilePath_file);
					*(int *)MatFilePath_file_data = MatFilePath_file_size;	// first 4 bytes is the size, data comes afterwards
					tree->SetItemData(MIPType, (DWORD_PTR)MatFilePath_file_data);
					fclose(MatFilePath_file);
				}
				else
					utf->AddNewNode(tree, Texture, "__MISSING");
			}

			{
				FILE * SIMatFilePath_file = fopen(SIMatFilePath, "rb");

				if (SIMatFilePath_file)
				{
					HTREEITEM MIPType;

					std::string fn2 = SIMatFilePath;
					if (icompare(fn2.substr(fn2.find_last_of(".") + 1), "DDS"))
						MIPType = utf->AddNewNode(tree, Texture2, "MIPS");
					else
						MIPType = utf->AddNewNode(tree, Texture2, "MIP0");

					fseek(SIMatFilePath_file, 0, SEEK_END);
					int SIMatFilePath_file_size = ftell(SIMatFilePath_file);
					fseek(SIMatFilePath_file, 0, SEEK_SET);
					char * SIMatFilePath_file_data = (char *)malloc(SIMatFilePath_file_size + 4);
					fread(SIMatFilePath_file_data + 4, SIMatFilePath_file_size, 1, SIMatFilePath_file);
					*(int *)SIMatFilePath_file_data = SIMatFilePath_file_size;	// first 4 bytes is the size, data comes afterwards
					tree->SetItemData(MIPType, (DWORD_PTR)SIMatFilePath_file_data);
					fclose(SIMatFilePath_file);
				}
				else
					utf->AddNewNode(tree, Texture2, "__MISSING");
			}

		}
		else
		{

			string sMat_Name = ".tga";
			//strcat (MatName, nameInList.c_str());
			strcat (MatName, sMat_Name.c_str());
			strcpy (MatFilePath, mesh->pFilePath.c_str());

			HTREEITEM DtFlags = utf->AddNewNode(tree, MatData, "Dt_flags");
			int * DtFlags_data = (int *)malloc (2*sizeof(int) + 4);
			DtFlags_data[0] = 8;	// size = 8 (2 integers)
			DtFlags_data[1] = 64;
			DtFlags_data[2] = 0;
			tree->SetItemData(DtFlags, (DWORD_PTR)DtFlags_data);

			HTREEITEM DtName = utf->AddNewNode(tree, MatData, "Dt_name");
			char * DtName_data = (char *) malloc ( strlen(MatName) + 1 + 4 );
			strcpy (DtName_data + 4, MatName);
			*(uint *)DtName_data = (uint)strlen(MatName) + 1;
			tree->SetItemData(DtName, (DWORD_PTR)DtName_data);

			HTREEITEM Texture = utf->AddNewNode(tree, TextureLib, MatName);

			FILE * MatFilePath_file = fopen(MatFilePath, "rb");
			if (MatFilePath_file)
			{
				HTREEITEM MIPType;

				std::string fn = MatFilePath;
				if (icompare(fn.substr(fn.find_last_of(".") + 1), "DDS"))
					MIPType = utf->AddNewNode(tree, Texture, "MIPS");
				else
					MIPType = utf->AddNewNode(tree, Texture, "MIP0");

				fseek(MatFilePath_file, 0, SEEK_END);
				int MatFilePath_file_size = ftell(MatFilePath_file);
				fseek(MatFilePath_file, 0, SEEK_SET);
				char * MatFilePath_file_data = (char *)malloc(MatFilePath_file_size + 4);
				fread(MatFilePath_file_data + 4, MatFilePath_file_size, 1, MatFilePath_file);
				*(int *)MatFilePath_file_data = MatFilePath_file_size;	// first 4 bytes is the size, data comes afterwards
				tree->SetItemData(MIPType, (DWORD_PTR)MatFilePath_file_data);
				fclose(MatFilePath_file);
			}
			else
				utf->AddNewNode(tree, Texture, "__MISSING");
		}
	}			
	
	utf->Save(tree, fileName);
	// -------------------------------------
	return TRUE;
}

//======================================================================
// OnClose
//======================================================================
void cDlgOptions::OnClose() 
{
	OnCancel ();
}

//======================================================================
// OnCancel
//======================================================================

void cDlgOptions::OnCancel()
{
//	utf->DestroyTree(tree);
//	delete utf;
	CDialog::OnCancel();
}

// MAT exporter methods here

void cDlgOptions::SetFileName(const char * fileName)
{
	strcpy (this->fileName, fileName);
}
void cDlgOptions::SetMesh(list<MMESH *> * meshList)
{
	this->meshList = meshList;
}
//======================================================================
// OnOK
//======================================================================
void cDlgOptions::OnOK() 
{
	CDialog::OnOK();
}

//======================================================================
// GetPathName
//======================================================================
CString cDlgOptions::GetPathName() 
{
	return m_sPathName;
}

//======================================================================
// GetPathName
//======================================================================
int cDlgOptions::GetOptionFlags() 
{
	return m_nFlags;
}
