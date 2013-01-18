
// FileHasherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileHasher.h"
#include "FileHasherDlg.h"
#include "afxdialogex.h"

#include "MD5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFileHasherDlg dialog




CFileHasherDlg::CFileHasherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileHasherDlg::IDD, pParent)
	, m_szPath(_T(""))
	, m_szMD5(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileHasherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szPath);
	DDX_Text(pDX, IDC_EDIT2, m_szMD5);
}

BEGIN_MESSAGE_MAP(CFileHasherDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CFileHasherDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFileHasherDlg::OnBnClickedCancel)
	ON_WM_DROPFILES()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_OPENFILEBTN, &CFileHasherDlg::OnClickedOpenFilebtn)
	ON_COMMAND(ID_HELP_ABOUT, &CFileHasherDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CFileHasherDlg message handlers

BOOL CFileHasherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileHasherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileHasherDlg::OnPaint()
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
HCURSOR CFileHasherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFileHasherDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CFileHasherDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}


void CFileHasherDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	WCHAR path[MAX_PATH];
	::DragQueryFile(hDropInfo, 0, path, MAX_PATH);

	m_szPath = path;
	m_szMD5 = GetMD5(path);

	::DragFinish(hDropInfo);

	UpdateData(FALSE);
	//CDialogEx::OnDropFiles(hDropInfo);
}


void CFileHasherDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	//CDialogEx::OnClose();
}


void CFileHasherDlg::OnDestroy()
{
	//CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	PostQuitMessage(0);
}


void CFileHasherDlg::OnClickedOpenFilebtn()
{
	// TODO: 在此添加控件通知处理程序代码
	static TCHAR BASED_CODE szFilter[] = TEXT("All Files(*.*)|*.*");
	CFileDialog   filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
				szFilter);
	if(IDOK == filedlg.DoModal())
	{
		m_szPath = filedlg.GetPathName();
		m_szMD5 = GetMD5(m_szPath.GetBuffer());

		UpdateData(FALSE);
	}
}


CString CFileHasherDlg::GetMD5(TCHAR * szPath)
{
	ifstream fin(szPath, std::ios::binary | std::ios::in);

	MD5 m1(fin);
	string str = m1.toString();
	CString MD5(str.c_str());
	MD5.MakeUpper();
	
	fin.close();

	return MD5;
}


void CFileHasherDlg::OnHelpAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg DlgAbout;
	DlgAbout.DoModal();
}
