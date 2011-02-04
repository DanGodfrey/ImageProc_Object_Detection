
// ImageProcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageProc.h"
#include "ImageProcDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcDlg dialog




CImageProcDlg::CImageProcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageProcDlg::IDD, pParent)
	, strPath(_T("[Video Not Yet Loaded]"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageProcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_STATICPATH, strPath);
}

BEGIN_MESSAGE_MAP(CImageProcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CImageProcDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CImageProcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTONPROCESS, &CImageProcDlg::OnBnClickedButtonprocess)
	ON_BN_CLICKED(IDC_BUTTONSAVE, &CImageProcDlg::OnBnClickedButtonsave)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &CImageProcDlg::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONSHOW, &CImageProcDlg::OnBnClickedButtonshow)
	ON_BN_CLICKED(IDC_BUTTONTEST, &CImageProcDlg::OnBnClickedButtontest)
END_MESSAGE_MAP()


// CImageProcDlg message handlers

BOOL CImageProcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageProcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageProcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageProcDlg::OnBnClickedCancel()
{
}


void CImageProcDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void CImageProcDlg::OnBnClickedButtonprocess()
{
	ocv.processVideo();
}


void CImageProcDlg::OnBnClickedButtonsave()
{
	ocv.saveProcessedVideo();
}


void CImageProcDlg::OnBnClickedButtonload()
{
	if (ocv.loadVideo(&ocv.path)){
		strPath = ocv.getPath();
		UpdateData(false);
	}
}


void CImageProcDlg::OnBnClickedButtonshow()
{
	ocv.showVideo(ocv.vidOriginal, "Original Video");
}


void CImageProcDlg::OnBnClickedButtontest()
{
	ocv.processTest();
}
