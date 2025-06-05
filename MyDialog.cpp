// MyDialog.cpp: 实现文件
//

#include "pch.h"
#include "CG2022112453游坤坤.h"
#include "afxdialogex.h"
#include "MyDialog.h"


// MyDialog 对话框

IMPLEMENT_DYNAMIC(MyDialog, CDialogEx)

MyDialog::MyDialog(CWnd* pParent)
	: CDialogEx(IDD_DIALOG_Sphere, pParent),
	type(type)
	, radius(0.5)
	, slice(40)
	, mstack(20)
	, xpos(50)
	, ypos(0)
	, zpos(0)
	, len(0.5)
	, height(0.5)
	, width(0.5)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_RADIUS, radius);
	DDX_Text(pDX, IDC_EDIT_SLICE, slice);
	DDX_Text(pDX, IDC_EDIT_STACKE, mstack);
	DDX_Text(pDX, IDC_EDIT_X, xpos);
	DDX_Text(pDX, IDC_EDIT_Y, ypos);
	DDX_Text(pDX, IDC_EDIT_Z, zpos);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, height);
	DDX_Text(pDX, IDC_EDIT_LEN, len);
	DDX_Text(pDX, IDC_EDIT_WIDTH, width);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_COLOR, colorButton);
	DDX_Control(pDX, IDC_COMBO_MATERIALS, materialCombox);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &MyDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON_COLOR, &MyDialog::OnBnClickedMfccolorbuttonColor)
	ON_CBN_SELCHANGE(IDC_COMBO_MATERIALS, &MyDialog::OnCbnSelchangeComboMaterials)
END_MESSAGE_MAP()


// MyDialog 消息处理程序

void MyDialog::drawSphere()
{
	int ids[] = { IDC_EDIT_LEN ,IDC_EDIT_WIDTH ,IDC_EDIT_HEIGHT,
	IDC_STATIC_LEN ,IDC_STATIC_WIDTH ,IDC_STATIC_HEIGHT };

	hideItems(ids, 6);
	// 刷新对话框以确保控件立即隐藏
	Invalidate();
	UpdateWindow();
}

void MyDialog::drawCube()
{
	int ids[] = { IDC_EDIT_RADIUS ,IDC_EDIT_SLICE,IDC_EDIT_STACKE,
		IDC_STATIC_R , IDC_STATIC_SLICE, IDC_STATIC_STACK };

	hideItems(ids, 6);
	// 刷新窗口
	this->Invalidate();
	this->UpdateWindow();
}

void MyDialog::hideItem(int nId)
{
	CWnd* item = GetDlgItem(nId);
	if (item)
		item->ShowWindow(SW_HIDE);
}

void MyDialog::hideItems(int nIds[], int len)
{
	for (int i = 0; i < len; i++)
	{
		hideItem(nIds[i]);
	}
}

glm::vec4 MyDialog::getColor()
{
	COLORREF cref = colorButton.GetColor();
	float r = GetRValue(cref) / 255.0f;
	float g = GetGValue(cref) / 255.0f;
	float b = GetBValue(cref) / 255.0f;

	return glm::vec4(r, g, b, 1.0f);
}

SceneMaterials::MaterialType MyDialog::getMaterialType()
{
	int sel = materialCombox.GetCurSel();
	return static_cast<SceneMaterials::MaterialType>(sel);
}

int MyDialog::getSel()
{
	int sel = materialCombox.GetCurSel();
	return sel;
}

void MyDialog::OnBnClickedOk()
{
	materialType = getMaterialType();
	mSel = getSel();
	CDialogEx::OnOK();
}



BOOL MyDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (type == DrawType::SPHERE)
	{
		this->drawSphere();
	}
	else if (type == DrawType::CUBE)
	{
		drawCube();
	}
	materialCombox.AddString(_T("塑料"));
	materialCombox.AddString(_T("金属"));
	materialCombox.AddString(_T("木制"));
	materialCombox.AddString(_T("陶瓷"));
	materialCombox.SetCurSel(0);

	colorButton.SetColor(RGB(0, 0, 255));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void MyDialog::OnBnClickedMfccolorbuttonColor()
{
	// TODO: 在此添加控件通知处理程序代码
}

void MyDialog::OnCbnSelchangeComboMaterials()
{
	//int sel = materialCombox.GetCurSel();
	//CString str;
	//materialCombox.GetLBText(sel, str);
	//AfxMessageBox(_T("选择了: ") + str);
}
