#pragma once
#include "afxdialogex.h"


// LightDialog 对话框

class LightDialog : public CDialogEx
{
	DECLARE_DYNAMIC(LightDialog)

public:
	LightDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~LightDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
