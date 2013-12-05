
// abcDlg.h : 头文件
//

#pragma once
#include "afxwin.h"



typedef struct st_Thread
{
	int	iInterval;
} ThreadStruct;


// CabcDlg 对话框
class CabcDlg : public CDialog
{
// 构造
public:
	CabcDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CabcDlg()
	{
		CloseTHand(hHand);
		nid.uFlags = NULL;
		bEndFlag = false;
		beFlag = false;
		::UnregisterHotKey(m_hWnd,4001);
		::UnregisterHotKey(m_hWnd,4002);
		Shell_NotifyIcon(NIM_DELETE,&nid);

	}

// 对话框数据
	enum { IDD = IDD_ABC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	afx_msg HRESULT OnMyMessage(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedOk();
	inline void	CloseTHand(HANDLE& hHand)
	{
		if (hHand)
		{
			bEndFlag = true;
						
			hHand = NULL;
		}
	}
public:
	HANDLE hHand;
	CEdit m_edit;
	NOTIFYICONDATA nid;
	bool bEndFlag;
	bool beFlag;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
};
