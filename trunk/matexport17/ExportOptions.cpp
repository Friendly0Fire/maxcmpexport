// ExportOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "matexport17.h"
#include "ExportOptions.h"


// ExportOptions-Dialogfeld

IMPLEMENT_DYNAMIC(ExportOptions, CDialog)

ExportOptions::ExportOptions(CWnd* pParent /*=NULL*/)
	: CDialog(ExportOptions::IDD, pParent)
{
	bDoExport = true;
}

ExportOptions::~ExportOptions()
{
}

void ExportOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ExportOptions, CDialog)
END_MESSAGE_MAP()

// ExportOptions-Meldungshandler

BOOL ExportOptions::OnInitDialog()
{
	if(!CDialog::OnInitDialog())
		return false;

	return true;
}

void ExportOptions::OnCancel()
{
	CDialog::OnCancel();

	bDoExport = false;
}

