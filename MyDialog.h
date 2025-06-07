#pragma once
#include "afxdialogex.h"
#include "glIncludes.h"
#include "CGMaterial.h"
// MyDialog �Ի���
enum class DrawType
{
	SPHERE,
	CUBE
};
class MyDialog : public CDialogEx
{
	DECLARE_DYNAMIC(MyDialog)

public:
	MyDialog(CWnd* pParent = nullptr);   // ��׼���캯��
	virtual ~MyDialog();

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
	void hideItem(int nId);
	void hideItems(int nIds[], int len);
	glm::vec4 getColor();
	int getSel();
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

	DrawType type = DrawType::CUBE;

	float xpos;
	float ypos;
	float zpos;

	float radius;
	int slice;
	int mstack;

	float height;
	float len;
	float width;
	CMFCColorButton colorButton;
	CComboBox materialCombox;
	int mSel = 0;
	afx_msg void OnBnClickedMfccolorbuttonColor();
	afx_msg void OnCbnSelchangeComboMaterials();
};
