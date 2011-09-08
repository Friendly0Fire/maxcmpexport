#pragma once
#include "afxwin.h"
#include "maxcmpexport.h"


// ExportOptions-Dialogfeld

class ExportOptions : public CDialog
{
	DECLARE_DYNAMIC(ExportOptions)

public:
	bool bDoExport;


public:
	ExportOptions(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~ExportOptions();

// Dialogfelddaten
	enum { IDD = IDD_EXPORTOPTIONS	};

	virtual BOOL OnInitDialog();
	virtual void OnCancel();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung

	DECLARE_MESSAGE_MAP()
public:
	EXPORT_CMPNT_OPTION eRadioCmpnts;
	FVF_TYPE eFVFtype;
	BOOL bWireFrame;
};
