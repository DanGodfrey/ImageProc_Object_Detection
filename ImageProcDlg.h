
// ImageProcDlg.h : header file
//

#pragma once

#include "CSI4133.h"

// CImageProcDlg dialog
class CImageProcDlg : public CDialogEx
{
	//CSI4133
	CSI4133 ocv;
// Construction
public:
	CImageProcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IMAGEPROC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonprocess();
	afx_msg void OnBnClickedButtonsave();
	CString strPath;
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedButtonshow();
	afx_msg void OnBnClickedButtontest();
};
