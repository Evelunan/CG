#pragma once
#include "afxdialogex.h"
#include "glIncludes.h"

// SphereDialog �Ի���
enum class DrawType
{
	SPHERE,
	CUBE
};
class SphereDialog : public CDialogEx
{
	DECLARE_DYNAMIC(SphereDialog)

public:
	SphereDialog(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~SphereDialog();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Sphere };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void setDrawType(DrawType type) { this->type = type; }
	DrawType drawType() { return type; }

	void drawSphere();
	void drawCube();

public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	float radius;
	int slice;
	int mstack;
	float xpos;
	float ypos;
	float zpos;

	DrawType type = DrawType::CUBE;
	float height;
	float len;
	float width;
};
