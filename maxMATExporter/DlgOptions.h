#ifndef __DLG_OPTIONS_H__
#define __DLG_OPTIONS_H__



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "maxMATExporter.h"
#include "ExportOptions.h"

#include <list>
using namespace std;

extern std::list<string> MaterialNames;
//extern std::list<MMESH *> *meshList;

//
// option flags
//
enum {
    eMaterials      = 2
};

#include "UTF.h"

class cDlgOptions : public CDialog
{
private:
    int     m_nFlags;
    CString m_sPathName;

	list<MMESH *> * meshList;
	
	char fileName[1000];

public:
	
	cDlgOptions(CWnd* pParent = NULL);

public:

	
	CTreeCtrl * tree;
	UTF * utf;
	CTreeCtrl * tree2;
	UTF * utf2;
    CString GetPathName ();
    int GetOptionFlags ();
	void SetFileName(char * fileName);
	void SetMesh(list<MMESH *> *);
	
	//{{AFX_VIRTUAL(cDlgOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(cDlgOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // __DLG_OPTIONS_H__
