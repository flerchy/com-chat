
// COM-ChatDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "COM-Chat.h"
#include "COM-ChatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// диалоговое окно CMainDlg



CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
	, message(_T(""))
	, sourceFileAddress(_T(""))
	, messagesLogText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_MESSAGE, message);
	DDX_Text(pDX, IDC_EDIT2_FILESOURCE, sourceFileAddress);
	DDX_Text(pDX, IDC_EDIT3, messagesLogText);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CMainDlg::OnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_ADDFILE, &CMainDlg::OnClickedBtnAddfile)
	ON_BN_CLICKED(IDC_BTN_SENDFILE, &CMainDlg::OnClickedBtnSendFile)
END_MESSAGE_MAP()


// обработчики сообщений CMainDlg

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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


	messagesLogText = "Логи беседы";
	UpdateData(FALSE);
	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CMainDlg::OnClickedBtnSend()
{
	UpdateData(TRUE);
	CString msg = message; 
	//sendMessage(message);
	MessageBox(L"В разработке\nОтправляемая строка: " + msg, 
			   L"Внимание", 
			   MB_OK | MB_ICONEXCLAMATION);
}


void CMainDlg::OnClickedBtnAddfile()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		sourceFileAddress = dlg.m_ofn.lpstrFile;
		UpdateData(FALSE);
	}
}


void CMainDlg::OnClickedBtnSendFile()
{
	UpdateData(TRUE);

	if (sendFile(sourceFileAddress) != TRUE) {
		MessageBox(L"Невозможно преобразовать адрес файла в файл", 
				   L"Ошибка!",
				   MB_OK| MB_ICONERROR);
	} else {
		MessageBox(L"Отправлен файл " + sourceFileAddress, 
				   L"Успех", 
				   MB_OK | MB_ICONASTERISK);
	}
}


bool CMainDlg::sendFile(CString fileAddress)
{
	CFile sourceFile;
	if (sourceFile.Open(sourceFileAddress, CFile::modeRead) == FALSE) {
		MessageBox(L"Невозможно открыть файл " + sourceFileAddress,
				   L"Ошибка!",
				   MB_OK | MB_ICONERROR);
		return FALSE;
	}
	//ТУТ ЛОГИКА ОТПРАВЛЕНИЯ ФАЙЛА
	MessageBox(L"Вы видите это сообщение, потому что функционал отправки файла не допилен", 
			   L"Внимание",
			   MB_OK | MB_ICONEXCLAMATION);
	return TRUE;
}
