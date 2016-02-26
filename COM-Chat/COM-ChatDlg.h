
// COM-ChatDlg.h : файл заголовка
//

#pragma once


// диалоговое окно CMainDlg
class CMainDlg : public CDialogEx
{
// Создание
public:
	CMainDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_COMCHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnClickedBtnSend();
	CString message;
	afx_msg void OnClickedBtnAddfile();
	afx_msg void OnClickedBtnSendFile();
	CString sourceFileAddress;
	bool sendFile(CString fileAddress);
	CString messagesLogText;
};
