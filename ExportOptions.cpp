// ExportOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "maxCMPExport.h"
#include "ExportOptions.h"


// ExportOptions-Dialogfeld

IMPLEMENT_DYNAMIC(ExportOptions, CDialog)

ExportOptions::ExportOptions(CWnd* pParent /*=NULL*/)
	: CDialog(ExportOptions::IDD, pParent)
	, bWireFrame(FALSE)
	, eRadioCmpnts(EXPORT_CMPNT_RELOCATE)
	, eFVFtype(FVF_NORMAL)
{
	bDoExport = true;
}

ExportOptions::~ExportOptions()
{
}

void ExportOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_WIREFRAME, (int&)bWireFrame);
	DDX_Radio(pDX, IDC_CMPNT_RELOCATE, (int&)eRadioCmpnts);
	DDX_CBIndex(pDX, IDC_COMBO2, (int&)eFVFtype);
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

