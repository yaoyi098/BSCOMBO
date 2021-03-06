
// abcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "abc.h"
#include "abcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void btime(LPVOID p)
{
	Sleep(5000);
	CabcDlg*  pdlg = (CabcDlg*)p;
	_tcscpy_s(pdlg->nid.szInfo,_T(""));
	pdlg->nid.uFlags = NIF_INFO;
	Shell_NotifyIcon(NIM_MODIFY,&pdlg->nid);
	return;

}

void LBD(LPVOID p)
{
	CabcDlg *pDlg = (CabcDlg*)p;
	if( pDlg == NULL)
	{
		::MessageBox(pDlg->m_hWnd,_T("未知错误！"),_T("错误！"),MB_OK|MB_ICONERROR);
		pDlg->CloseTHand(pDlg->hHand);
		return;
	}

	HWND hHwnd = ::FindWindow(NULL,_T("剑灵"));
	if (hHwnd == NULL)
	{
		::MessageBox(pDlg->m_hWnd,_T("未找到剑灵窗口！\r\n请先打开剑灵窗口后再试!"),_T("错误！"),MB_OK|MB_ICONERROR);
		pDlg->CloseTHand(pDlg->hHand);
		return;
	}
	ASSERT(hHwnd);
	int i = ((CButton*)pDlg->GetDlgItem(IDC_RADIO_F))->GetCheck();
	CString strTemp;
	pDlg->m_edit.GetWindowText(strTemp);
 	DWORD d = _tcstol(strTemp,NULL,10);
	pDlg->nid.uFlags = NIF_TIP | NIF_INFO | NIF_ICON;
	_tcscpy_s(pDlg->nid.szInfo,_T("连发已开始！"));
	_tcscpy_s(pDlg->nid.szTip,_T("BS：正在连发"));
	pDlg->nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2));
	Shell_NotifyIcon(NIM_MODIFY,&pDlg->nid);
	_beginthread(btime,NULL,p);
	if (i == 1)
	{
		while(1)
		{
			if (pDlg->bEndFlag == true)
				break;
			::SendMessage(hHwnd,WM_KEYDOWN,0x46,0x001f0001);
			Sleep(d);
		}

	}
	else if (i == 0)
	{
		POINT p;
		::GetCursorPos(&p);
		::ScreenToClient(hHwnd,&p);
		LONG x,y;
		x = p.x;
		y = p.y;
		LPARAM lp = MAKELPARAM(x,y);
		{
			while(1)
			{
				if (pDlg->bEndFlag == true)
					break;
// 				::PostMessage(hHwnd,WM_RBUTTONDOWN,0,lp);
// 				Sleep(50);
// 				::PostMessage(hHwnd,WM_RBUTTONUP,0,lp);
// 				Sleep(200);
// 				::PostMessage(hHwnd,WM_LBUTTONDOWN,0,lp);
// 				Sleep(50);
// 				::PostMessage(hHwnd,WM_LBUTTONUP,0,lp);
// 				Sleep(d);
				::SendMessage(hHwnd,WM_RBUTTONDOWN,0,lp);
				Sleep(50);
				::SendMessage(hHwnd,WM_RBUTTONUP,0,lp);
				Sleep(200);
				::SendMessage(hHwnd,WM_LBUTTONDOWN,0,lp);
				Sleep(50);
				::SendMessage(hHwnd,WM_LBUTTONUP,0,lp);
				Sleep(d);

			}
		}
	}

}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CabcDlg 对话框




CabcDlg::CabcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CabcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	bEndFlag = false;
	beFlag = false;
}

void CabcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CabcDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	ON_MESSAGE(WM_MYMESSAGE,OnMyMessage)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CabcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CabcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CabcDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CabcDlg 消息处理程序

BOOL CabcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。
	// IDM_ABOUTBOX 必须在系统命令范围内。
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
	
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	// TODO: 在此添加额外的初始化代码


	m_edit.SetWindowText(_T("0"));
	((CButton *)GetDlgItem(IDC_RADIO_LB))->SetCheck(TRUE);
	hHand = NULL;
 	BOOL b = ::RegisterHotKey(m_hWnd,4001,MOD_WIN,0x53);
// 	b = ::RegisterHotKey(m_hWnd,4002,NULL,69);
//	BOOL b = ::RegisterHotKey(m_hWnd,4001,NULL,VK_CAPITAL);

	if(b == FALSE)
	{
		::MessageBox(this->GetSafeHwnd(),_T("设置热键失败"),_T("ERROR"),MB_ICONERROR);
		PostQuitMessage(0);
	}
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDI_ICON1;
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_INFO|NIF_TIP;
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
	nid.uCallbackMessage = WM_MYMESSAGE;
	_tcscpy_s(nid.szTip,_T("BS连发程序"));
	_tcscpy_s(nid.szInfo,_T("BS连发程序启动！\r\nWin + S 键开启连发"));
	_tcscpy_s(nid.szInfoTitle,_T("BS连发"));
	nid.uTimeout = 1000;
	nid.uVersion = NOTIFYICON_VERSION;
	nid.dwInfoFlags = NIIF_INFO; 
	Shell_NotifyIcon(NIM_ADD,&nid);
	HANDLE hTemp = NULL;
	hTemp = (HANDLE)_beginthread(btime,NULL,this);

// 	nid.uFlags = NIF_INFO;
// 	Shell_NotifyIcon(NIM_MODIFY,&nid);
	
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE); 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CabcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CabcDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType,cx,cy);
	// TODO: Add your message handler code here
	if(nType==SIZE_MINIMIZED)
	{
		ShowWindow(SW_HIDE); // 当最小化市，隐藏主窗口 
	}
}

void CabcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CabcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CabcDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
		//OnOK();
// 	CloseTHand(hHand);
// 	CString strTemp;
// 	m_edit.GetWindowText(strTemp);
// 	LONG i = wcstol(strTemp,NULL,10);
// 	hHand = (HANDLE)_beginthread(LBD,0,(void *)i);
	ShowWindow(SW_HIDE);

}

HRESULT CabcDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
// 	if (wParam == 4002)	// E
// 	{
// 		HWND hHwnd = ::FindWindow(NULL,_T("剑灵"));
// 		if (hHwnd == NULL)
// 				return 1;
// 		::PostMessage(hHwnd,WM_KEYDOWN,82,0x001f0001);
// 		Sleep(50);
// 		::PostMessage(hHwnd,WM_KEYUP,82,0x001f0001);
// 		Sleep(200);
// 		::PostMessage(hHwnd,WM_KEYDOWN,84,0x001f0001);
// 		Sleep(50);
// 		::PostMessage(hHwnd,WM_KEYUP,84,0x001f0001);
// 		return 1;
// 	}

	if (wParam == 4002)
	{
		if (hHand)	
		{
			CloseTHand(hHand);
			nid.uFlags = NIF_INFO | NIF_TIP | NIF_ICON;
			_tcscpy_s(nid.szInfo,_T("连发已结束！"));
			_tcscpy_s(nid.szTip,_T("BS连发程序"));
			nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
			Shell_NotifyIcon(NIM_MODIFY,&nid);
			_beginthread(btime,NULL,(void*)this);
			return 1;
		}
		else
		{	
			CString strTemp;
			m_edit.GetWindowText(strTemp);
			LONG i = wcstol(strTemp,NULL,10);
			bEndFlag = false;
			hHand = (HANDLE)_beginthread(LBD,0,(void*)this);
			return 1;
		}

	}

	int i = ((CButton*)GetDlgItem(IDC_RADIO_F))->GetCheck();
	if (wParam == 4001)		// win + s
	{
		if (i == 1)
		{
			if (hHand)	
			{
				CloseTHand(hHand);
				nid.uFlags = NIF_INFO | NIF_TIP;
				_tcscpy_s(nid.szInfo,_T("连发已结束！"));
				_tcscpy_s(nid.szTip,_T("BS连发程序"));
		
				Shell_NotifyIcon(NIM_MODIFY,&nid);
				_beginthread(btime,NULL,(void*)this);
				return 1;
			}
			else
			{	
				CString strTemp;
				m_edit.GetWindowText(strTemp);
				LONG i = wcstol(strTemp,NULL,10);
				bEndFlag = false;
				hHand = (HANDLE)_beginthread(LBD,0,(void*)this);
				return 1;
			}
		}	//连发
		else if (i == 0)
		{
			if (beFlag == false)
			{
				::RegisterHotKey(m_hWnd,4002,NULL,69);
				nid.uFlags = NIF_ICON;
				nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON2));
				Shell_NotifyIcon(NIM_MODIFY,&nid);
				beFlag = true;
			}else
			{
				::UnregisterHotKey(m_hWnd,4002);
				nid.uFlags = NIF_ICON;
				nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ICON1));
				Shell_NotifyIcon(NIM_MODIFY,&nid);
				beFlag = false;
			}
		}	//卡刀。
	}
	return 1;
}

HRESULT CabcDlg::OnMyMessage(WPARAM wParam,LPARAM lParam)
{
	UINT uMouse = LOWORD(lParam);
	switch(uMouse)
	{
	case WM_LBUTTONDBLCLK:
		{
			if (IsWindowVisible() == FALSE)
			{
				ShowWindow(SW_SHOW);
				PostMessage(WM_SYSCOMMAND,SC_RESTORE);
			}
			else
				ShowWindow(SW_HIDE);
			break;
		}
	case WM_RBUTTONUP:
		{
			CMenu menu;
			LPPOINT p = new tagPOINT;
			::GetCursorPos(p);
			menu.CreatePopupMenu();
			menu.AppendMenu(MF_STRING,WM_DESTROY,_T("退出"));
			menu.TrackPopupMenu(TPM_LEFTALIGN,p->x,p->y,this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete p;
			break;
		}
	default:
		break;
	}
	return 1;
}
void CabcDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	nid.uFlags = NIF_INFO;
	Shell_NotifyIcon(NIM_MODIFY,&nid);
}

void CabcDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
