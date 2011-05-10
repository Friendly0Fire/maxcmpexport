#include "stdafx.h"
#include "resource.h"
#include "DlgOptions.h"

#include "maxCMPExport.h"
#include "UTF.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int cDlgOptions::num_meshes()
{
	// iterate mesh list, calculate number of meshes
	int nMesh = 0;

	list<MMESH *>::iterator i;
	for (i = meshList->begin(); i != meshList->end(); i ++)
	{
		MMESH * m = *i;

		if ( _strnicmp(m->nname, "Hp", 2) )
			nMesh ++;
	}

	return nMesh;
}

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
BOOL cDlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CDialog::CenterWindow();

/*    m_nFlags = eMeshes | eMaterials;
    m_sPathName.Empty();

    CheckDlgButton (IDC_BTMESHES, TRUE);
    CheckDlgButton (IDC_BTMATERIALS, TRUE);
*/	

	tree = (CTreeCtrl *) GetDlgItem(IDC_TREE);
	utf = new UTF();

	// first mesh
	list<MMESH *>::iterator i = meshList->begin();
	MMESH * mesh = *i;

	// -------------------------------------
	char VMeshLibraryName[200];
	strcpy (VMeshLibraryName, mesh->nname);
	string sLod = ".lod";
	sLod += (char)(48 + iLODs);
	sLod += ".vms";
	strcat (VMeshLibraryName, sLod.c_str());

	HTREEITEM root = utf->AddNewNode(tree, NULL, "\\");
		HTREEITEM VMeshLibrary = utf->AddNewNode(tree, root, "VMeshLibrary");
			HTREEITEM meshdata = utf->AddNewNode(tree, VMeshLibrary, VMeshLibraryName);
				HTREEITEM VMeshData = utf->AddNewNode(tree, meshdata, "VMeshData");
					// attach temporary vms file to this node
					FILE * VMeshData_file = fopen ("___temp.vms","rb");
					fseek (VMeshData_file, 0, SEEK_END);
					int VMeshData_file_size = ftell(VMeshData_file);
					fseek (VMeshData_file, 0, SEEK_SET);
					char * VMeshData_file_data = (char *)malloc (VMeshData_file_size + 4);
					fread (VMeshData_file_data + 4, VMeshData_file_size, 1, VMeshData_file);
					*(int *)VMeshData_file_data = VMeshData_file_size;	// first 4 bytes is the size, data comes afterwards
					tree->SetItemData(VMeshData, (DWORD)VMeshData_file_data);
					fclose(VMeshData_file);

					unlink ("___temp.vms");

		HTREEITEM Cmpnd = utf->AddNewNode(tree, root, "Cmpnd");
			HTREEITEM Cmpnd_root = utf->AddNewNode(tree, Cmpnd, "Root");
				HTREEITEM CR_filename = utf->AddNewNode(tree, Cmpnd_root, "File name");
					// set data entry for "File name"
					char * CR_filename_data = (char *) malloc ( strlen(mesh->nname) + strlen (".3db") + 1 + 4);
					strcpy (CR_filename_data + 4, mesh->nname);	// 4 = int position at beginning
					strcat (CR_filename_data + 4, ".3db");
					*(int *)CR_filename_data = strlen(mesh->nname) + 4 + 1;	// 4 = strlen(".3db") 1 = '\0'
					tree->SetItemData(CR_filename, (DWORD)CR_filename_data);
				HTREEITEM CR_index = utf->AddNewNode(tree, Cmpnd_root, "Index");
					// set data entry for "Index"
					int * CR_index_data = (int *)malloc (2*sizeof(int) + 4);
					CR_index_data[0] = 8;	// size = 8 (2 integers)
					CR_index_data[1] = 0;
					CR_index_data[2] = 0;
					tree->SetItemData(CR_index, (DWORD)CR_index_data);
				HTREEITEM CR_objname = utf->AddNewNode(tree, Cmpnd_root, "Object name");
					// set data entry for "Object name"
					char * CR_objname_data = (char *) malloc ( strlen("Root") + 1 + 4 );
					strcpy (CR_objname_data + 4, "Root");
					*(int *)CR_objname_data = strlen("Root") + 1;
					tree->SetItemData(CR_objname, (DWORD)CR_objname_data);

		char objName[200];
		strcpy (objName, mesh->nname);
		strcat (objName, ".3db");
		HTREEITEM obj1 = utf->AddNewNode(tree, root, objName);
			HTREEITEM multilevel = utf->AddNewNode(tree, obj1, "MultiLevel");
				string sLevel = "Level";
				sLevel += (char)(48 + iLODs);
				HTREEITEM level0 = utf->AddNewNode(tree, multilevel, (char*)sLevel.c_str());
					HTREEITEM VMeshPart = utf->AddNewNode(tree, level0, "VMeshPart");
						HTREEITEM VMeshRef = utf->AddNewNode(tree, VMeshPart, "VMeshRef");
							// basic VMeshRef (single component with multiple meshes)
							int * VMeshRef_data = (int *) malloc (60 + 4);
							VMeshRef_data[0] = 60;
							tree->SetItemData(VMeshRef, (DWORD)VMeshRef_data);
							memset (VMeshRef_data + 1, 0, 60);
							VMeshRef_data[1] = 60;
							VMeshRef_data[2] = fl_crc32(VMeshLibraryName);
							VMeshRef_data[3] = 0;
							VMeshRef_data[4] = 0;
							VMeshRef_data[5] = num_meshes() << 16;


	
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

// CMP exporter methods here

void cDlgOptions::SetMesh(list<MMESH *> * meshList)
{
	this->meshList = meshList;
}

void cDlgOptions::SetFileName(char * fileName)
{
	strcpy (this->fileName, fileName);
}

void cDlgOptions::SetComponentMode(EXPORT_CMPNT_OPTION mode)
{
	cmpnt_mode = mode;
}

void cDlgOptions::SetLODs(int lod_setting)
{
	iLODs = lod_setting;
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
