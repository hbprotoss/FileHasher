
// FileHasherDlg.h : header file
//

#pragma once


// CFileHasherDlg dialog
class CFileHasherDlg : public CDialogEx
{
// Construction
public:
	CFileHasherDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FILEHASHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	CString m_szPath;
	CString m_szMD5;
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnClickedOpenFilebtn();
	CString GetMD5(TCHAR * szPath);
	afx_msg void OnHelpAbout();
};
