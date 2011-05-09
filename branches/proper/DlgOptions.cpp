#include "stdafx.h"
#include "resource.h"
#include "DlgOptions.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <wchar.h>
#include <io.h>

#include "maxCMPExport.h"
#include "UTF.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct vwMesh {
	int start_vertex, end_vertex, num_triangles;
};

struct Line {
	int v1, v2;
};

void check_if_line_exists_and_add_if_not(struct Line *lines, int *num_lines, struct Line new_line) {
	int i;
	for (i = 0; i < *num_lines; ++i) {
		if (((lines[i].v1 == new_line.v1) && (lines[i].v2 == new_line.v2)) || ((lines[i].v1 == new_line.v2) && (lines[i].v2 == new_line.v1)))
			return;
	}
	lines[*num_lines] = new_line;
	++(*num_lines);
}

int cDlgOptions::create_vwiredata(HTREEITEM item, const TCHAR* WireDat)
{
	

	//Pretty much the old make wire with some changes to suite my neads
	//I know cheap bastard, I had intended to create a wireframe using 
	//splines but still havn't found a way of doing this.

	FILE * VMeshData_file;
	HTREEITEM vwiredata = utf->AddNewNode(tree, item, "VWireData");

	// -------------------------------------

	char VMeshLibraryName[200];
	char VWireIn[200];

	int numb_meshes;
	int num_triangles;
	int num_vertices;

	std::list<string>::iterator i = lstNames.begin();
	string nameInList = *i;
		

	strcpy (VMeshLibraryName, nameInList.c_str());
	string sLod = ".lod";
	sLod += (char)(48 + OptionsDlgExport->iLOD);
	sLod += ".vms";
	strcat (VMeshLibraryName, sLod.c_str());
	strcpy (VWireIn,WireDat);
	string sWLod = ".lod";
	sWLod += (char)(48 + OptionsDlgExport->iLOD);
	sWLod += ".vwd";
	strcat (VWireIn, sWLod.c_str());

	int crc = fl_crc32(VMeshLibraryName);
		
	char buffer [1000];
	int *temp_int = (int *)buffer;
	float *temp_float = (float *)buffer;

   // Open file to read line from:
   fopen_s( &VMeshData_file,VWireIn,"rb");
   if( VMeshData_file == NULL )
      exit( 0 );

	struct vwMesh vwmesh;
	struct Line lines[100000];
	int num_lines = 0;
		
//	find number of meshes, number of triangles and number of vertices
	fread(buffer,1,8,VMeshData_file);
	*temp_int = 0;
	fread(buffer,1,2,VMeshData_file);
	numb_meshes = *temp_int;
	fread(buffer,1,2,VMeshData_file);
	num_triangles = *temp_int / 3;
	fread(buffer,1,2,VMeshData_file);
	fread(buffer,1,2,VMeshData_file);
	num_vertices = *temp_int;
	
	
	
	//read in first mesh
	fread(buffer,1,4,VMeshData_file);
	*temp_int = 0;
	fread(buffer,1,2,VMeshData_file);
	vwmesh.start_vertex = *temp_int;
	fread(buffer,1,2,VMeshData_file);
	vwmesh.end_vertex = *temp_int;
	fread(buffer,1,2,VMeshData_file);
	vwmesh.num_triangles = *temp_int / 3;
	fread(buffer,1,2,VMeshData_file);

		for (int j = 0; j < vwmesh.num_triangles; ++j) 
		{
			int v0, v1, v2;
			struct Line temp_line;
			*temp_int=0;
			fread(buffer,1,2,VMeshData_file);
			v0 = *temp_int;
			fread(buffer,1,2,VMeshData_file);
			v1 = *temp_int;
			fread(buffer,1,2,VMeshData_file);
			v2 = *temp_int;
			temp_line.v1 = v0;
			temp_line.v2 = v1;
			check_if_line_exists_and_add_if_not(lines, &num_lines, temp_line);
			temp_line.v1 = v1;
			temp_line.v2 = v2;
			check_if_line_exists_and_add_if_not(lines, &num_lines, temp_line);
			temp_line.v1 = v2;
			temp_line.v2 = v0;
			check_if_line_exists_and_add_if_not(lines, &num_lines, temp_line);
			}
	
		fclose(VMeshData_file);

		char sVWireOut[200];
		strcpy (sVWireOut,WireDat);
		string sVWLod = ".lod";
		sVWLod += (char)(48 + OptionsDlgExport->iLOD);
		sVWLod += ".vwd2";
		strcat (sVWireOut, sVWLod.c_str());
		
		FILE * file;
		file = _tfopen (sVWireOut, "wb");

		*temp_int = 16;
		fwrite(buffer,4, 1, file);
		*temp_int = crc;
		fwrite(buffer,4, 1, file);
		*temp_int = vwmesh.start_vertex;
		fwrite(buffer,2, 1, file);
		*temp_int = num_vertices;
		fwrite(buffer,2, 1, file);
		*temp_int = num_lines * 2;
		fwrite(buffer,2, 1, file);
		*temp_int = num_vertices;
		fwrite(buffer,2, 1, file);
		
		//write lines
		for (int i = 0; i < num_lines; ++i) 
		{
			*temp_int = lines[i].v1;
			fwrite(buffer,2, 1, file);
			*temp_int = lines[i].v2;
			fwrite(buffer,2, 1, file);
		}
		fclose(file);

		FILE * VWireData_file = fopen (sVWireOut,"rb");
		fseek (VWireData_file, 0, SEEK_END);
		int VWireData_file_size = ftell(VWireData_file);
		fseek (VWireData_file, 0, SEEK_SET);
		char * VWireData_file_data = (char *)malloc (VWireData_file_size + 4);
		fread (VWireData_file_data + 4, VWireData_file_size, 1, VWireData_file);
		*(int *)VWireData_file_data = VWireData_file_size;	// first 4 bytes is the size, data comes afterwards
		tree->SetItemData(vwiredata, (DWORD_PTR)VWireData_file_data);
		fclose(VWireData_file);
		unlink (sVWireOut);
		unlink (VWireIn);
	
 return 1;
}

/*void write_parts()
{
	// Build your parts list.
	for (std::list<string>::iterator i = lstNames.begin(); i != lstNames.end(); i++)
	{
		Part *part = new Part;
		memset(part, 0, sizeof(Part));
		strcpy(part->ParentName, "Root"); // replace i->c_str() with whatever the parent name should be
		strcpy(part->ChildName, i->c_str());
		part->OriginX = 0.0f; // and do the others.
		// OriginY, etc...
		lstParts.push_back(part);
	}	
		
	// This works because the structure above is in exactly the same format as the stuff
	// in the consfix node.
	FILE *file = fopen("consfix.bin", "wb");
	if (file)
	{
		for (std::list<Part*>::iterator partiter = lstParts.begin(); partiter != lstParts.end(); partiter++)
		{
			// derefering the iterator gives us a pointer to part
			Part *part = *partiter;
			fwrite(part, sizeof(Part), 1, file);
		}
		fclose(file);
	}
	
	// Delete the memory allocated to the parts and remove the pointers to prevent us accidentally
	// reusing them.
	for (std::list<Part*>::iterator partiter = lstParts.begin(); partiter != lstParts.end(); partiter++)
	{
		Part *part = *partiter;
		delete part;					
	}
	lstParts.clear();
}*/

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

IGameNode *pMesh;
sNodeInfo * snode;

BOOL cDlgOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CDialog::CenterWindow();


	tree = (CTreeCtrl *) GetDlgItem(IDC_TREE);
	utf = new UTF();
	
	list<GLIST *>::iterator GL;

	
	// -------------------------------------
	/*
	char sVWireOut[200];
	strcpy (sVWireOut,mesh->nname);
	string sVWLod = ".lod";
	sVWLod += (char)(48 + iLODs);
	sVWLod += ".vwd";
	strcat (sVWireOut, sVWLod.c_str());
	string sLod2 = ".lod";
	sLod2 += (char)(48 + iLODs);
	char VMeshLibraryName[200];
	strcpy (VMeshLibraryName, mesh->nname);
	string sLod = ".lod";
	sLod += (char)(48 + iLODs);
	sLod += ".vms";
	strcat (VMeshLibraryName, sLod.c_str());
	*/


	HTREEITEM root = utf->AddNewNode(tree, NULL, "\\");
		HTREEITEM VMeshLibrary = utf->AddNewNode(tree, root, "VMeshLibrary");

			for(list<VMESHDATA_FILE*>::iterator it = lstVMeshData->begin(); it != lstVMeshData->end(); it++)
			{
				HTREEITEM meshdata = utf->AddNewNode(tree, VMeshLibrary, (char*)(*it)->sFilename.c_str());
					HTREEITEM VMeshData = utf->AddNewNode(tree, meshdata, "VMeshData");
					// attach temporary vms file to this node
					FILE * VMeshData_file = fopen((*it)->sFilename.c_str(), "rb");
					fseek (VMeshData_file, 0, SEEK_END);
					int VMeshData_file_size = ftell(VMeshData_file);
					fseek (VMeshData_file, 0, SEEK_SET);
					char * VMeshData_file_data = (char *)malloc (VMeshData_file_size + 4);
					fread (VMeshData_file_data + 4, VMeshData_file_size, 1, VMeshData_file);
					*(int *)VMeshData_file_data = VMeshData_file_size;	// first 4 bytes is the size, data comes afterwards
					tree->SetItemData(VMeshData, (DWORD_PTR)VMeshData_file_data);
					fclose(VMeshData_file);
					// delete temporary file
					unlink((char*)(*it)->sFilename.c_str());
			}


		HTREEITEM Cmpnd = utf->AddNewNode(tree, root, "Cmpnd");

			HTREEITEM Cmpnd_cons = utf->AddNewNode(tree, Cmpnd, "Cons");

				HTREEITEM Cmpnd_fixnode = utf->AddNewNode(tree, Cmpnd_cons, "Fix");
					FILE * fixdata_file = fopen("fixnode.bin", "rb");
					fseek (fixdata_file, 0, SEEK_END);
					int fixdata_file_size = ftell(fixdata_file);
					fseek (fixdata_file, 0, SEEK_SET);
					char * fixdata_file_data = (char *)malloc (fixdata_file_size + 4);
					fread (fixdata_file_data + 4, fixdata_file_size, 1, fixdata_file);
					*(int *)fixdata_file_data = fixdata_file_size;	// first 4 bytes is the size, data comes afterwards
					tree->SetItemData(Cmpnd_fixnode, (DWORD_PTR)fixdata_file_data);
					fclose(fixdata_file);
					// delete temporary file
					unlink("fixnode.bin");

		for(list<CMPND_DATA*>::iterator itcmpnd = lstCMPData->begin(); itcmpnd != lstCMPData->end(); itcmpnd++)
		{
			HTREEITEM Cmpnd_item = utf->AddNewNode(tree, Cmpnd, (char*)(*itcmpnd)->sName.c_str());
				HTREEITEM CR_filename = utf->AddNewNode(tree, Cmpnd_item, "File name");
					// set data entry for "File name"
					char * CR_filename_data = (char *) malloc ( (*itcmpnd)->object_data->sFileName.size() + 4);
					strcpy (CR_filename_data + 4, (*itcmpnd)->object_data->sFileName.c_str());	// 4 = int position at beginning
					*(size_t *)CR_filename_data = (*itcmpnd)->object_data->sFileName.size() + 4;	
					tree->SetItemData(CR_filename, (DWORD_PTR)CR_filename_data);
				HTREEITEM CR_index = utf->AddNewNode(tree, Cmpnd_item, "Index");
					// set data entry for "Index"
					int * CR_index_data = (int *)malloc (sizeof(int) + 4);
					CR_index_data[0] = 4;	// size = 8 (1 integer + size data)
					CR_index_data[1] = (*itcmpnd)->index;
					tree->SetItemData(CR_index, (DWORD_PTR)CR_index_data);
				HTREEITEM CR_objname = utf->AddNewNode(tree, Cmpnd_item, "Object name");
					// set data entry for "Object name"
					char * CR_objname_data = (char *) malloc ( (*itcmpnd)->sObjectName.size() + 4);
					strcpy (CR_objname_data + 4, (*itcmpnd)->sObjectName.c_str());
					*(size_t *)CR_objname_data = (*itcmpnd)->sObjectName.size() + 4;
					tree->SetItemData(CR_objname, (DWORD_PTR)CR_objname_data);


				HTREEITEM Cmpnd_threedb = utf->AddNewNode(tree, root, (char*)(*itcmpnd)->object_data->sFileName.c_str());
					HTREEITEM Cmpnd_multilevel = utf->AddNewNode(tree, Cmpnd_threedb, "MultiLevel");
					string sLevel = "Level";
					sLevel += (char)(48 + OptionsDlgExport->iLOD);
						HTREEITEM Cmpnd_lodlevel = utf->AddNewNode(tree, Cmpnd_multilevel, (char*)sLevel.c_str());
							HTREEITEM Cmpnd_VMeshPart = utf->AddNewNode(tree, Cmpnd_lodlevel, "VMeshPart");
								HTREEITEM Cmpnd_VMeshRef = utf->AddNewNode(tree, Cmpnd_VMeshPart, "VMeshRef");
									char* Cmpdn_vmeshref_data = (char *) malloc ( sizeof(VMeshRef) + 4);
									*(VMeshRef*)(Cmpdn_vmeshref_data+4) = (*itcmpnd)->object_data->vmeshref;
									*(int*)Cmpdn_vmeshref_data = sizeof(VMeshRef);
									tree->SetItemData(Cmpnd_VMeshRef, (DWORD_PTR)Cmpdn_vmeshref_data);
			
		}



		/*

		char objName[200];
		char PartName[200];
		char Part_Name[200];
		char VMeshRefFile[200];
		char WireDat[200];

		//Use the lstNames to create any sub objects in the model
		for (std::list<string>::iterator i = lstNames.begin();i != lstNames.end(); ++i)
			{

			string nameInList = *i;
			strcpy (objName, nameInList.c_str());
			strcpy (VMeshRefFile, nameInList.c_str());
			string sVMeshRef = ".lod";
			sVMeshRef += (char)(48+iLODs);
			sVMeshRef += ".vmr";
			strcat (VMeshRefFile, sVMeshRef.c_str());
			strcpy (WireDat, nameInList.c_str());

			//strcpy (objName, glist->glname);
			strcat (objName, ".3db");
			HTREEITEM obj1 = utf->AddNewNode(tree, root, objName);

			// If we want a wireframe it's added here
			if(sWire==1)
			{
			HTREEITEM vmeshwire = utf->AddNewNode(tree, obj1, "VMeshWire");
			create_vwiredata(vmeshwire,(char*) WireDat);
			}
				HTREEITEM hardpoints = utf->AddNewNode(tree, obj1, "Hardpoints");
				create_hardpoints (hardpoints);
				HTREEITEM multilevel = utf->AddNewNode(tree, obj1, "MultiLevel");
				string sLevel = "Level";
					sLevel += (char)(48 + iLODs);
					HTREEITEM level0 = utf->AddNewNode(tree, multilevel, (char*)sLevel.c_str());
						HTREEITEM VMeshPart = utf->AddNewNode(tree, level0, "VMeshPart");
							HTREEITEM VMeshRef = utf->AddNewNode(tree, VMeshPart, "VMeshRef");


							FILE * VMeshRef_file = fopen (VMeshRefFile,"rb");
							fseek (VMeshRef_file, 0, SEEK_END);
							int VMeshRef_file_size = ftell(VMeshRef_file);
							fseek (VMeshRef_file, 0, SEEK_SET);
							char * VMeshRef_file_data = (char *)malloc (VMeshRef_file_size + 4);
							fread (VMeshRef_file_data + 4, VMeshRef_file_size, 1, VMeshRef_file);
							*(int *)VMeshRef_file_data = VMeshRef_file_size;	// first 4 bytes is the size, data comes afterwards
							tree->SetItemData(VMeshRef, (DWORD_PTR)VMeshRef_file_data);
							fclose(VMeshRef_file);
						
							unlink (VMeshRefFile);

		}
		//Do other object parts here
		lstNames.pop_front(); //delete first node

		int ConsFix = 0;
		int nParts = 0;
		for (std::list<string>::iterator i = lstNames.begin();i != lstNames.end(); ++i)
		{
			ConsFix = 1;
			
			string nameInList = *i;
			strcpy (PartName, nameInList.c_str());
			string sPart_Name = "Part_";
			strcpy (Part_Name, sPart_Name.c_str());
			strcat (Part_Name, nameInList.c_str());

			nParts ++;
			//HTREEITEM Cmpnd = utf->AddNewNode(tree, root, "Cmpnd");
			HTREEITEM Cmpnd_root = utf->AddNewNode(tree, Cmpnd, Part_Name);
				HTREEITEM CR_filename = utf->AddNewNode(tree, Cmpnd_root, "File name");
					// set data entry for "File name"
					char * CR_filename_data = (char *) malloc ( strlen(PartName) + strlen (".3db") + 1 + 4);
					strcpy (CR_filename_data + 4, PartName);	// 4 = int position at beginning
					strcat (CR_filename_data + 4, ".3db");
					*(size_t *)CR_filename_data = strlen(PartName) + 4 + 1;	// 4 = strlen(".3db") 1 = '\0'
					tree->SetItemData(CR_filename, (DWORD_PTR)CR_filename_data);
				HTREEITEM CR_index = utf->AddNewNode(tree, Cmpnd_root, "Index");
					// set data entry for "Index"
					int * CR_index_data = (int *)malloc (2*sizeof(int) + 4);
					CR_index_data[0] = 8;	// size = 8 (2 integers)
					CR_index_data[1] = nParts;
					CR_index_data[2] = 0;
					tree->SetItemData(CR_index, (DWORD_PTR)CR_index_data);
				HTREEITEM CR_objname = utf->AddNewNode(tree, Cmpnd_root, "Object name");
					// set data entry for "Object name"
					char * CR_objname_data = (char *) malloc ( strlen(PartName) + 1 + 4 );
					strcpy (CR_objname_data + 4, PartName);
					*(size_t *)CR_objname_data = strlen(PartName) + 1;
					tree->SetItemData(CR_objname, (DWORD_PTR)CR_objname_data);

					

		}

		//Thanks to Cannon we have a dummy Cons/Fix so the plugin will work 
		//till I can figure out these Parent/Child offsets
		if(ConsFix==1)
		{
			for (std::list<string>::iterator i = lstNames.begin(); i != lstNames.end(); i++)
			{
				Part *part = new Part;
				memset(part, 0, sizeof(Part));
				strcpy(part->ParentName, "Root"); // replace i->c_str() with whatever the parent name should be
				strcpy(part->ChildName, i->c_str());
				part->OriginX = 0.0f; // and do the others.
				part->OriginY = 0.0f;
				part->OriginZ = 0.0f;
				part->RotMatXX = 1.0f;
				part->RotMatXY = 0.0f;
				part->RotMatXZ = 0.0f;
				part->RotMatYX = 0.0f;
				part->RotMatYY = 1.0f;
				part->RotMatYZ = 0.0f;
				part->RotMatZX = 0.0f;
				part->RotMatZY = 0.0f;
				part->RotMatZZ = 1.0f;
				// OriginY, etc...
				lstParts.push_back(part);
			}	
				
			// This works because the structure above is in exactly the same format as the stuff
			// in the consfix node.
			FILE *file = fopen("consfix.bin", "wb");
			if (file)
			{
				for (std::list<Part*>::iterator partiter = lstParts.begin(); partiter != lstParts.end(); partiter++)
				{
					// derefering the iterator gives us a pointer to part
					Part *part = *partiter;
					fwrite(part, sizeof(Part), 1, file);
				}
				fclose(file);
			}
			
			// Delete the memory allocated to the parts and remove the pointers to prevent us accidentally
			// reusing them.
			for (std::list<Part*>::iterator partiter = lstParts.begin(); partiter != lstParts.end(); partiter++)
			{
				Part *part = *partiter;
				delete part;					
			}
			

			HTREEITEM CR_Cons = utf->AddNewNode(tree, Cmpnd, "Cons");
				HTREEITEM CR_Fix = utf->AddNewNode(tree, CR_Cons, "Fix");

				FILE * ConsFix_File = fopen ("consfix.bin","rb");
				fseek (ConsFix_File, 0, SEEK_END);
				int ConsFix_File_size = ftell(ConsFix_File);
				fseek (ConsFix_File, 0, SEEK_SET);
				char * ConsFix_File_data = (char *)malloc (ConsFix_File_size + 4);
				fread (ConsFix_File_data + 4, ConsFix_File_size, 1, ConsFix_File);
				*(int *)ConsFix_File_data = ConsFix_File_size;	
				tree->SetItemData(CR_Fix, (DWORD_PTR)ConsFix_File_data);
				fclose(ConsFix_File);
				
				unlink ("consfix.bin");

			lstParts.clear();
		}

							unlink ("___temp.verts");
							//unlink (sVWireOut);
							unlink ("___temp.vms");
							unlink ("___temp.vmref");
							// basic VMeshRef (single component with multiple meshes)
							//int * VMeshRef_data = (int *) malloc (60 + 4);
							//VMeshRef_data[0] = 60;
							//tree->SetItemData(VMeshRef, (DWORD_PTR)VMeshRef_data);
							//memset (VMeshRef_data + 1, 0, 60);
							//VMeshRef_data[1] = 60;
							//VMeshRef_data[2] = fl_crc32(VMeshLibraryName);
							//VMeshRef_data[3] = 0;
							//VMeshRef_data[4] = 0;
							//VMeshRef_data[5] = num_meshes() << 16;

	*/
							
	
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
//	utf->DestroyTree(tree);
//	delete utf;

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
