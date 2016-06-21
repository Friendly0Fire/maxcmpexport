#include "stdafx.h"
#include "resource.h"
#include "DlgOptions.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <wchar.h>
#include <io.h>

#include "cmpexport17.h"
#include "UTF.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//======================================================================
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

void cDlgOptions::AddFileAsNode(HTREEITEM parent, const char* szFileName, const char* szNodeName)
{
	FILE * file = fopen(szFileName, "rb");
	fseek (file, 0, SEEK_END);
	uint file_size = ftell(file);
	if(file_size > 0)
	{
		HTREEITEM node = utf->AddNewNode(tree, parent, (char*)szNodeName);
		fseek (file, 0, SEEK_SET);
		char * file_data = (char *)malloc (file_size + 4);
		fread (file_data + 4, file_size, 1, file);
		*(int *)file_data = file_size;	// first 4 bytes is the size, data comes afterwards
		tree->SetItemData(node, (DWORD_PTR)file_data);
	}
	fclose(file);
	unlink(szFileName);
}

BOOL cDlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CDialog::CenterWindow();


	tree = (CTreeCtrl *) GetDlgItem(IDC_TREE);
	utf = new UTF();
	


	HTREEITEM root = utf->AddNewNode(tree, NULL, "\\");
		HTREEITEM VMeshLibrary = utf->AddNewNode(tree, root, "VMeshLibrary");

			for(list<VMESHDATA_FILE*>::iterator it = lstVMeshData->begin(); it != lstVMeshData->end(); it++)
			{
				HTREEITEM meshdata = utf->AddNewNode(tree, VMeshLibrary, (char*)(*it)->sFilename.c_str());
					AddFileAsNode(meshdata, (*it)->sFilename.c_str(), "VMeshData");
			}


		HTREEITEM Cmpnd = utf->AddNewNode(tree, root, "Cmpnd");

			HTREEITEM Cmpnd_cons = utf->AddNewNode(tree, Cmpnd, "Cons");
				AddFileAsNode(Cmpnd_cons, "fixnode.bin", "Fix");
				AddFileAsNode(Cmpnd_cons, "revnode.bin", "Rev");
				AddFileAsNode(Cmpnd_cons, "prisnode.bin", "Pris");

		for(list<CMPND_DATA*>::iterator itcmpnd = lstCMPData->begin(); itcmpnd != lstCMPData->end(); itcmpnd++)
		{
			HTREEITEM Cmpnd_item = utf->AddNewNode(tree, Cmpnd, (char*)(*itcmpnd)->sName.c_str());
				HTREEITEM CR_filename = utf->AddNewNode(tree, Cmpnd_item, "File name");
					// set data entry for "File name"
					char * CR_filename_data = (char *) malloc ( (*itcmpnd)->object_data->sFileName.size() + 1 + 4);
					strcpy (CR_filename_data + 4, (*itcmpnd)->object_data->sFileName.c_str());	// 4 = int position at beginning
					*(unsigned int *)CR_filename_data = (uint)(*itcmpnd)->object_data->sFileName.size() + 1;	
					tree->SetItemData(CR_filename, (DWORD_PTR)CR_filename_data);
				HTREEITEM CR_index = utf->AddNewNode(tree, Cmpnd_item, "Index");
					// set data entry for "Index"
					int * CR_index_data = (int *)malloc (sizeof(int) + 4);
					CR_index_data[0] = 4;	// size = 4 (1 integer )
					CR_index_data[1] = (*itcmpnd)->index;
					tree->SetItemData(CR_index, (DWORD_PTR)CR_index_data);
				HTREEITEM CR_objname = utf->AddNewNode(tree, Cmpnd_item, "Object name");
					// set data entry for "Object name"
					char * CR_objname_data = (char *) malloc ( (*itcmpnd)->sObjectName.size() + 1 + 4);
					strcpy (CR_objname_data + 4, (*itcmpnd)->sObjectName.c_str());
					*(unsigned int *)CR_objname_data = (uint)(*itcmpnd)->sObjectName.size() + 1;
					tree->SetItemData(CR_objname, (DWORD_PTR)CR_objname_data);


			HTREEITEM Cmpnd_threedb = utf->AddNewNode(tree, root, (char*)(*itcmpnd)->object_data->sFileName.c_str());

				if(OptionsDlgExport->bWireFrame)
				{
					HTREEITEM Cmpnd_vmeshwire = utf->AddNewNode(tree, Cmpnd_threedb, "VMeshWire");
						string sVWDFile = (*itcmpnd)->sObjectName + ".vwd";
						AddFileAsNode(Cmpnd_vmeshwire, sVWDFile.c_str(), "VWireData");
				}

				HTREEITEM Cmpnd_multilevel = utf->AddNewNode(tree, Cmpnd_threedb, "MultiLevel");


				if((*itcmpnd)->object_data->iLODs > 1)
				{
					// Switch2 float array
					HTREEITEM Cmpnd_multilevel_switch2 = utf->AddNewNode(tree, Cmpnd_multilevel, "Switch2");
					uint iSwitch2Size = 4*(*itcmpnd)->object_data->iLODs + 4 + 4;
					char* Cmpnd_multilevel_switch2_data = (char *) malloc (iSwitch2Size);
					*(uint*)Cmpnd_multilevel_switch2_data = iSwitch2Size - 4;
					*(float*)(Cmpnd_multilevel_switch2_data + 4) = 0;
					for(uint iLOD = 1; iLOD < (*itcmpnd)->object_data->iLODs; iLOD++)
						*(float*)(Cmpnd_multilevel_switch2_data + 4 + iLOD*4) = pow(10.0f,(float)iLOD+1);
					*(float*)(Cmpnd_multilevel_switch2_data + 4 + (*itcmpnd)->object_data->iLODs*4) = 1000000;		
					tree->SetItemData(Cmpnd_multilevel_switch2, (DWORD_PTR)Cmpnd_multilevel_switch2_data);		
				}

				for(uint iLOD = 0; iLOD < (*itcmpnd)->object_data->iLODs; iLOD++)
				{

					string sLevel = "Level";
					sLevel += (char)(48 + iLOD);
						HTREEITEM Cmpnd_lodlevel = utf->AddNewNode(tree, Cmpnd_multilevel, (char*)sLevel.c_str());
							HTREEITEM Cmpnd_VMeshPart = utf->AddNewNode(tree, Cmpnd_lodlevel, "VMeshPart");
								HTREEITEM Cmpnd_VMeshRef = utf->AddNewNode(tree, Cmpnd_VMeshPart, "VMeshRef");
									char* Cmpdn_vmeshref_data = (char *) malloc ( sizeof(VMeshRef) + 4);
									*(VMeshRef*)(Cmpdn_vmeshref_data+4) = (*itcmpnd)->object_data->data[iLOD].vmeshref;
									*(uint*)Cmpdn_vmeshref_data = sizeof(VMeshRef);
									tree->SetItemData(Cmpnd_VMeshRef, (DWORD_PTR)Cmpdn_vmeshref_data);
				}
			
		}
	
	
	utf->Save(tree, fileName);

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
	// clean up memory

	utf->DestroyTree(tree);

	delete utf;

	for(list<VMESHDATA_FILE*>::iterator it = lstVMeshData->begin(); it != lstVMeshData->end(); it++)
		delete (*it);
	delete lstVMeshData;

	for(list<CMPND_DATA*>::iterator itcmpnd = lstCMPData->begin(); itcmpnd != lstCMPData->end(); itcmpnd++)
	{
		delete (*itcmpnd)->object_data;
		delete (*itcmpnd);
	}
	delete lstCMPData;


	CDialog::OnCancel();
}

// CMP exporter methods here

void cDlgOptions::SetFileName(char * fileName)
{
	strcpy (this->fileName, fileName);
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
