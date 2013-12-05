
// abcDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"



typedef struct st_Thread
{
	int	iInterval;
} ThreadStruct;


// CabcDlg �Ի���
class CabcDlg : public CDialog
{
// ����
public:
	CabcDlg(CWnd* pParent = NULL);	// ��׼���캯��
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

// �Ի�������
	enum { IDD = IDD_ABC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
