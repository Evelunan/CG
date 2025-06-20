// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CG2022112453游坤坤Doc.cpp: CCG2022112453游坤坤Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2022112453游坤坤.h"
#endif

#include "CG2022112453游坤坤Doc.h"

#include <propkey.h>
#include "CG2022112453游坤坤View.h" 
#include "CGScene.h" 
#include "CGCamera.h" 
#include "CGTransform.h" 
#include "CGGeode.h" 
#include "CGLineSegment.h" 
#include "CGRenderContext.h" 
#include "UIEventHandler.h" 
#include "CGDraw2DLineSeg.h" 
#include "CGDraw2DLineStrip.h"
#include "CCGSceneGraphView.h" 
#include "CGModel2DTransform.h"
#include "TessellationHints.h"
#include "CGCube.h"
#include "CGSphere.h"
#include "MyDialog.h"
#include "RobotBodyTransform.h"
#include "CGBasicCameraControl.h"
#include "CGArcballCameraControl.h"
#include "CGMaterial.h"
#include "CGLightModel.h"
#include "LightDialog.h"
#include "CGRenderStateCallback.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CCG2022112453游坤坤Doc

IMPLEMENT_DYNCREATE(CCG2022112453游坤坤Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2022112453游坤坤Doc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINESEG, &CCG2022112453游坤坤Doc::OnUpdateDraw2dLineseg)
	ON_COMMAND(ID_DRAW2D_LINESEG, &CCG2022112453游坤坤Doc::OnDraw2dLineseg)
	ON_COMMAND(ID_DRAW2D_LINE_STRIP, &CCG2022112453游坤坤Doc::OnDraw2dLineStrip)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_LINE_STRIP, &CCG2022112453游坤坤Doc::OnUpdateDraw2dLineStrip)
	ON_COMMAND(ID_TRANSLATE2D_LEFT, &CCG2022112453游坤坤Doc::OnTranslate2dLeft)
	ON_COMMAND(ID_TRANSLATE2D_RIGHT, &CCG2022112453游坤坤Doc::OnTranslate2dRight)
	ON_COMMAND(ID_TRANSLATE2D_UP, &CCG2022112453游坤坤Doc::OnTranslate2dUp)
	ON_COMMAND(ID_TRANSLATE2D_DOWN, &CCG2022112453游坤坤Doc::OnTranslate2dDown)
	ON_COMMAND(ID_ROTATE2D_COUNTERCLOCKWISE, &CCG2022112453游坤坤Doc::OnRotate2dCounterclockwise)
	ON_COMMAND(ID_ROTATE2D_CLOCKWISE, &CCG2022112453游坤坤Doc::OnRotate2dClockwise)
	ON_COMMAND(ID_SCALEX2D_UP, &CCG2022112453游坤坤Doc::OnScalex2dUp)
	ON_COMMAND(ID_SCALEX2D_DOWN, &CCG2022112453游坤坤Doc::OnScalex2dDown)
	ON_COMMAND(ID_SACLEY2D_UP, &CCG2022112453游坤坤Doc::OnSacley2dUp)
	ON_COMMAND(ID_SCALEY2D_DOWN, &CCG2022112453游坤坤Doc::OnScaley2dDown)
	ON_COMMAND(ID_SCALE2D_UP, &CCG2022112453游坤坤Doc::OnScale2dUp)
	ON_COMMAND(ID_SCALE2D_DOWN, &CCG2022112453游坤坤Doc::OnScale2dDown)
	ON_COMMAND(ID_SHEARX2D_POSITIVE, &CCG2022112453游坤坤Doc::OnShearx2dPositive)
	ON_COMMAND(ID_SHEARX2D_NEGATIVE, &CCG2022112453游坤坤Doc::OnShearx2dNegative)
	ON_COMMAND(ID_SHEARY2D_POSITIVE, &CCG2022112453游坤坤Doc::OnSheary2dPositive)
	ON_COMMAND(ID_SHEARY2D_NEGATIVE, &CCG2022112453游坤坤Doc::OnSheary2dNegative)
	ON_COMMAND(ID_MIRROR2D_ORIGIN, &CCG2022112453游坤坤Doc::OnMirror2dOrigin)
	ON_COMMAND(ID_MIRROR2D_YEQ_POS_X, &CCG2022112453游坤坤Doc::OnMirror2dYeqPosX)
	ON_COMMAND(ID_MIRROR2D_YEQ_NEG_X, &CCG2022112453游坤坤Doc::OnMirror2dYeqNegX)
	ON_COMMAND(ID_MIRRORX2D, &CCG2022112453游坤坤Doc::OnMirrorx2d)
	ON_COMMAND(ID_MIRRORY2D, &CCG2022112453游坤坤Doc::OnMirrory2d)
	ON_COMMAND(ID_BUTTON_TRANSFORM2D, &CCG2022112453游坤坤Doc::OnButtonTransform2d)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TRANSFORM2D, &CCG2022112453游坤坤Doc::OnUpdateButtonTransform2d)
	ON_COMMAND(ID_BUTTON_DRAW3D_SPHERE, &CCG2022112453游坤坤Doc::OnButtonDraw3dSphere)
	ON_COMMAND(ID_BUTTON_CUBE, &CCG2022112453游坤坤Doc::OnButtonCube)
	ON_COMMAND(ID_BUTTON_TIMER, &CCG2022112453游坤坤Doc::OnButtonTimer)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TIMER, &CCG2022112453游坤坤Doc::OnUpdateButtonTimer)
	ON_COMMAND(ID_BUTTON_ROBOT, &CCG2022112453游坤坤Doc::OnButtonRobot)
	ON_COMMAND(ID_BUTTON_CAMERA_CONTROL, &CCG2022112453游坤坤Doc::OnButtonCameraControl)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CAMERA_CONTROL, &CCG2022112453游坤坤Doc::OnUpdateButtonCameraControl)
	ON_COMMAND(ID_BUTTON_ARCBALL_CONTROL, &CCG2022112453游坤坤Doc::OnButtonArcballControl)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ARCBALL_CONTROL, &CCG2022112453游坤坤Doc::OnUpdateButtonArcballControl)
	ON_COMMAND(ID_BUTTON_LIGHT_CONTROL, &CCG2022112453游坤坤Doc::OnButtonLightControl)
	ON_COMMAND(ID_BUTTON_DIRECTIONAL_LIGHT, &CCG2022112453游坤坤Doc::OnButtonDirectionalLight)
	ON_COMMAND(ID_BUTTON_SPOT_LIGHT, &CCG2022112453游坤坤Doc::OnButtonSpotLight)
	ON_COMMAND(ID_BUTTON_TURN_OFF_LIGHT, &CCG2022112453游坤坤Doc::OnButtonTurnOffLight)
	ON_COMMAND(ID_BUTTON_POINT_LIGHT, &CCG2022112453游坤坤Doc::OnButtonPointLight)

END_MESSAGE_MAP()


// CCG2022112453游坤坤Doc 构造/析构

CCG2022112453游坤坤Doc::CCG2022112453游坤坤Doc() noexcept
{
	mScene = std::make_shared<CGScene>();

	auto lightModel = std::make_shared<CGLightModel>();
	lightModel->setAmbientColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)); 
	lightModel->setLocalViewer(true);  // 启用局部观察者，意味着视点位置会影响高光计算（更真实）
	lightModel->setTwoSide(true);      // 启用双面光照，使物体背面也能被正确照亮（否则背面可能看起来是黑的）。

	// 将光照模型设置到场景根节点（防止多次覆盖）
	mScene->GetSceneData()->asGroup()->gocRenderStateSet()->setRenderState(lightModel, -1);
	

	//mScene->SetMainCamera(std::make_shared<CGCamera>());
	//auto e = std::make_shared<CGGeode>();
	////auto line = std::make_shared<CGLineSegment>(glm::dvec3(100, 100, 0), glm::dvec3(400, 300, 0));
	////e->AddChild(line);
	//auto g = std::make_shared<CGTransform>();
	//g->AddChild(e);
	//mScene->SetSceneData(g);
}

CCG2022112453游坤坤Doc::~CCG2022112453游坤坤Doc()
{
}

CCGSceneGraphView* CCG2022112453游坤坤Doc::GetSceneGraphView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCGSceneGraphView))) {
			CCGSceneGraphView* view = dynamic_cast<CCGSceneGraphView*>(pView);
			return view;
		}
	}
	return nullptr;
}
void CCG2022112453游坤坤Doc::InstToSceneTree(CTreeCtrl* pTree)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hInst;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = NULL;// 
	CString str(_T("场景"));
	tvinsert.item.pszText = str.GetBuffer();
	str.ReleaseBuffer();
	hInst = pTree->InsertItem(&tvinsert);
	pTree->SetItemData(hInst, DWORD_PTR(mScene.get()));

	InstToSceneTree(pTree, hInst, mScene->GetSceneData());

	pTree->Expand(hInst, TVE_EXPAND);
}
void CCG2022112453游坤坤Doc::InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hParent, CGNode* node)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hTree;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = LPARAM(&node);// 
	if (node->asGeode()) {
		CString str(_T("Geode"));
		if (node->Name())
			str = node->Name();
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		//叶子实例节点不再显示模型节点 
	}
	else if (node->asTransform()) {
		CString str(_T("Trans"));
		if (node->Name())
			str = node->Name();
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asTransform()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asTransform()->GetChild(i));
		}
	}
	else if (node->asGroup()) {
		CString str(_T("Group"));
		if (node->Name())
			str = node->Name();
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asGroup()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asGroup()->GetChild(i));
		}

	}
}
void CCG2022112453游坤坤Doc::OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem)
{
	mSelectedItem = hItem;
	if (!mSelectedItem) {
		mSelectedGroup = nullptr;
		return;
	}
	HTREEITEM hRoot = pTree->GetRootItem();
	if (mSelectedItem == hRoot) {
		mSelectedGroup = nullptr;
	}
	else {
		CGGroup* node = (CGGroup*)(pTree->GetItemData(mSelectedItem));
		if (node && node->asGroup() && !(node->asGeode())) { //不允许叶子节点上再 
			mSelectedGroup = dynamic_cast<CGGroup*>(node);
		}
		else {
			mSelectedGroup = nullptr;
		}
	}
}



bool CCG2022112453游坤坤Doc::RenderScene(CGRenderContext* pRC)
{
	if (pRC == nullptr)
		return false;
	if (mScene == nullptr)
		return false;
	CGCamera* pCamera = mScene->GetMainCamera();
	if (pCamera == nullptr)
		return false;

	return mScene->Render(pRC, pCamera);
}

bool CCG2022112453游坤坤Doc::AddRenderable(std::shared_ptr<CGNode> r)
{
	if (mSelectedGroup) { //需要先选中一各组节点 
		//模型加入实例节点后加入场景 
		auto ge = std::make_shared<CGGeode>();
		ge->AddChild(r);
		mSelectedGroup->AddChild(ge);
		CTreeCtrl& tree = GetSceneGraphView()->GetTreeCtrl();
		InstToSceneTree(&tree, mSelectedItem, ge.get());
		return true;
	}
	else {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
	}
	return false;
}

bool CCG2022112453游坤坤Doc::AddNode(std::shared_ptr<CGNode>  node)
{
	if (node.get() == nullptr)
		return false;
	if (mSelectedGroup) {
		mSelectedGroup->AddChild(node);
	}
	else{
		mScene->GetSceneData()->asGroup()->AddChild(node);
	}
	return true;
}

BOOL CCG2022112453游坤坤Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCG2022112453游坤坤Doc 序列化

void CCG2022112453游坤坤Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2022112453游坤坤Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCG2022112453游坤坤Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCG2022112453游坤坤Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCG2022112453游坤坤Doc 诊断

#ifdef _DEBUG
void CCG2022112453游坤坤Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2022112453游坤坤Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

CCG2022112453游坤坤View* CCG2022112453游坤坤Doc::getView()
{
	CCG2022112453游坤坤View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453游坤坤View))) {
			view = dynamic_cast<CCG2022112453游坤坤View*>(pView);
			break;
		}
	}
	return view;
}

void CCG2022112453游坤坤Doc::updateHandle(CCmdUI* pCmdUI, EventType type)
{
	// TODO: 在此添加命令更新用户界面处理程序代码 
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		type);
}

void CCG2022112453游坤坤Doc::commandHandler()
{
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
}

void CCG2022112453游坤坤Doc::performTransformation(std::function<void(CGRenderable*)> transformFunc)
{
	CCG2022112453游坤坤View* view = getView();
	if (view == nullptr)
		return;
	commandHandler();

	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CTreeCtrl* pTree = &(pSceneGraphView->GetTreeCtrl());
	CGGeode* node = (CGGeode*)pTree->GetItemData(mSelectedItem);

	if (!node || node->GetNumRenderables() <= 0)
	{
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	CGRenderable* child = node->GetRenderable(0);
	if (!child)
	{
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	transformFunc(child);
	view->Invalidate(); // 强制视图重绘
}

void CCG2022112453游坤坤Doc::translate2d(double x, double y)
{
	performTransformation([x, y](CGRenderable* child) {
		child->Translate(x, y);
		});
}

void CCG2022112453游坤坤Doc::rotate2d(double angle, double cx, double cy)
{
	performTransformation([angle, cx, cy](CGRenderable* child) {
		child->Rotate(angle, cx, cy);
		});
}

void CCG2022112453游坤坤Doc::scale2d(double sx, double sy)
{
	performTransformation([sx, sy](CGRenderable* child) {
		child->Scale(sx, sy);
		});
}

void CCG2022112453游坤坤Doc::shear2d(double shx, double shy)
{
	performTransformation([shx, shy](CGRenderable* child) {
		child->ShearXYAxis(shx, shy);
		});
}


//void CCG2022112453游坤坤Doc::draw3D(std::shared_ptr<CGRenderable> render, glm::vec3 center)
//{
//	auto material = std::make_shared<CGMaterial>();
//	material->setAmbient(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
//	material->setDiffuse(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
//	material->setSpecular(glm::vec4(0.7f, 0.7f, 0.7f, 1.0f));
//	material->setShininess(32.0f);
//
//	using namespace std;
//	auto tran1 = make_shared<CGTransform>();
//	auto geode = make_shared<CGGeode>();
//	auto color = make_shared<CGColor>();
//	color->setValue(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
//	geode->gocRenderStateSet()->setRenderState(color, -1);
//	geode->gocRenderStateSet()->setRenderState(material, -1);
//
//	tran1->translate(center.x, center.y, center.z);
//	tran1->rotate(45, 1, 1, 1);
//	tran1->scale(100, 100, 100);
//	geode->AddChild(render);
//	tran1->AddChild(geode);
//	mScene->GetSceneData()->asGroup()->AddChild(tran1);
//
//	color = make_shared<CGColor>();
//	tran1 = make_shared<CGTransform>();
//	geode = make_shared<CGGeode>();
//	color->setValue((glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))); //蓝色
//	geode->gocRenderStateSet()->setRenderState(color, -1);
//	auto mode = std::make_shared<CGPolygonMode>(PM_LINE, PM_LINE); //设置线框模式 
//	geode->gocRenderStateSet()->setRenderState(mode, -1);
//	geode->gocRenderStateSet()->setRenderState(material, -1);
//
//	tran1->translate(-center.x, center.y, center.z);
//	tran1->rotate(45, 1, 1, 1);
//	tran1->scale(100, 100, 100);
//	geode->AddChild(render);
//	tran1->AddChild(geode);
//	mScene->GetSceneData()->asGroup()->AddChild(tran1);
//
//
//	//std::shared_ptr<RobotBodyTransformParam> data = std::make_shared<RobotBodyTransformParam>();
//	//std::shared_ptr<RobotBodyRotate> rc = std::make_shared<RobotBodyRotate>();
//	//tran1->setUserData(data);
//	//tran1->SetUpdateCallback(rc);
//}
void CCG2022112453游坤坤Doc::draw3D(std::shared_ptr<CGRenderable> render, glm::vec3 center)
{
	//using namespace std;

	//vector<shared_ptr<CGRenderState>> states;
	//auto blue = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//auto metal = SceneMaterials::CreateMaterialWithColor(blue, SceneMaterials::MaterialType::Metal);
	//auto material = make_shared<CGMaterial>(metal);

	//states.push_back(material);
	//glColor4fv((glm::value_ptr(blue)));
	//auto tran = createGeometry(render, center, states);
	//tran->scale(100, 100, 100);
	//AddNode(tran);
}

std::shared_ptr<CGTransform> CCG2022112453游坤坤Doc::createGeometry(const std::shared_ptr<CGRenderable>& render, const glm::vec3& center, const std::vector<std::shared_ptr<CGRenderState>>& states, const CString& name)
{
	using namespace std;
	auto tran = make_shared<CGTransform>();
	tran->setName(name);
	tran->AddChild(render); // 添加可渲染对象
	
	for (auto state : states)
	{
		tran->gocRenderStateSet()->setRenderState(state, -1);
	}
	tran->translate(center);
	return tran;
}


std::shared_ptr<CGTransform> CCG2022112453游坤坤Doc::createTransfrom(CString name)
{
	auto tran = std::make_shared<CGTransform>();
	tran->setName(name);
	return tran;
}

std::shared_ptr<CGTransform> CCG2022112453游坤坤Doc::createBoxPart(float len, float width, float height, const glm::vec4& color,const  CString name, MaterialPreset preset)
{
	using namespace std;
	auto cube = make_shared<CGCube>(len, width, height);
	auto hints = make_shared<TessellationHints>();

	cube->setTessellationHints(hints);
	cube->setDisplayListEnabled(true);

	auto geode = make_shared<CGGeode>();
	geode->AddChild(cube);
	geode->setName(name);

	// 设置颜色
	auto colorState = make_shared<CGColor>();
	colorState->setValue(color);
	geode->gocRenderStateSet()->setRenderState(colorState, -1);

	auto material = make_shared<CGMaterial>(CreateMaterial(preset));
	geode->gocRenderStateSet()->setRenderState(material, -1);
	 //设置线框模式
	//auto mode = make_shared<CGPolygonMode>(PM_LINE, PM_LINE);
	//geode->gocRenderStateSet()->setRenderState(mode, -1);

	auto tran = make_shared<CGTransform>();
	tran->AddChild(geode);
	tran->setName(name);
	return tran;
}
void CCG2022112453游坤坤Doc::buildRobot() {
	using namespace std;
	using namespace glm;
	// 定义常用颜色常量
	auto red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // 红色
	auto white = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // 纯白
	auto black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // 纯黑
	auto blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); // 蓝色
	auto green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); // 绿色
	auto yellow = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f); // 黄色
	auto cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f); // 青色
	auto magenta = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f); // 品红
	auto orange = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f); // 橙色
	auto purple = glm::vec4(0.5f, 0.0f, 0.5f, 1.0f); // 紫色
	auto brown = glm::vec4(0.6f, 0.3f, 0.0f, 1.0f); // 棕色
	auto pink = glm::vec4(1.0f, 0.75f, 0.8f, 1.0f); // 粉色
	auto gray = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); // 灰色

	// 创建根节点
	auto root = createTransfrom("root");

	// create trunk 
	auto trunk = createTransfrom("trunk");

	auto middleTrunk = createBoxPart(80, 30, 50, cyan, "middleTrunk");
	auto upperTrunk = createBoxPart(100, 40, 60, cyan, "upperTrunk");
	auto lowerTrunk = createBoxPart(60, 20, 40, cyan, "lowerTrunk");

	upperTrunk->translate(0, 35, 0); 
	lowerTrunk->translate(0, -25, 0);

	trunk->AddChild(middleTrunk);
	trunk->AddChild(upperTrunk);
	trunk->AddChild(lowerTrunk);
	root->AddChild(trunk);


	//  head
	auto head = createBoxPart(40, 40, 40, gray, "head");
	head->translate(0, 75, 0);
	//head->rotate(45, 1, 1, 0); 
	root->AddChild(head);

	// create rightArm
	auto rightArm = createTransfrom("rightArm");

	auto rightUpperArm = createBoxPart(20, 50, 20, yellow, "rightUpperArm");
	auto rightLowerArm = createBoxPart(20, 50, 20, pink, "rightLowerArm");
	
	rightLowerArm->translate( 0, -40, 0);
	rightUpperArm->AddChild(rightLowerArm);

	rightArm->AddChild(rightUpperArm);
	rightArm->translate(60, 50, 0);
	rightArm->rotate(145, 0, 0, 1); // 将手臂旋转45度
	root->AddChild(rightArm);

	// 创建右手掌
	auto rightPalm = createBoxPart(25, 10, 20, white, "rightPalm");
	rightPalm->translate(0, -30, 0); // 根据手臂长度调整位置
	rightLowerArm->AddChild(rightPalm);

	// 定义手指的基本参数
	float fingerWidth = 4.0f; // 手指宽度
	float fingerHeight = 20.0f; // 手指长度
	float fingerSpacing = 6.0f; // 手指之间的间距

	// 创建右手的手指
	// 拇指
	auto thumb = createBoxPart(fingerWidth, fingerHeight, fingerWidth, cyan, "thumb");
	thumb->translate(-8.0f, -15.0f, 10.0f); // 调整到合适的位置
	rightPalm->AddChild(thumb);

	// 食指
	auto indexFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, cyan, "indexFinger");
	indexFinger->translate(-(fingerSpacing * 2), -15.0f, 0.0f);
	rightPalm->AddChild(indexFinger);

	// 中指
	auto middleFinger = createBoxPart(fingerWidth, fingerHeight + 5.0f, fingerWidth, cyan, "middleFinger"); // 中指稍长一些
	middleFinger->translate(-(fingerSpacing), -15.0f, 0.0f);
	rightPalm->AddChild(middleFinger);

	// 无名指
	auto ringFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, cyan, "ringFinger");
	ringFinger->translate(0.0f, -15.0f, 0.0f);
	rightPalm->AddChild(ringFinger);

	// 小指
	auto littleFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, cyan, "littleFinger");
	littleFinger->translate((fingerSpacing), -15.0f, 0.0f);
	rightPalm->AddChild(littleFinger);


	// create leftArm
	auto leftArm = createTransfrom("leftArm");

	auto leftUpperArm = createBoxPart(20, 50, 20, yellow, "leftUpperArm");
	auto leftLowerArm = createBoxPart(20, 50, 20, pink, "leftLowerArm");

	leftLowerArm->translate(0, -40, 0);
	leftUpperArm->AddChild(leftLowerArm);

	leftArm->AddChild(leftUpperArm);
	leftArm->translate(-60, 50, 0);
	leftArm->rotate(-145, 0, 0, 1); // 将手臂旋转45度
	root->AddChild(leftArm);

	// 创建左手掌
	auto leftPalm = createBoxPart(25, 10, 20, white, "leftPalm");
	leftPalm->translate(0, -30, 0); // 根据手臂长度调整位置
	leftLowerArm->AddChild(leftPalm);

	// 创建左手的手指
	// 拇指
	auto leftThumb = createBoxPart(fingerWidth, fingerHeight, fingerWidth, cyan, "leftThumb");
	leftThumb->translate(8.0f, -15.0f, 10.0f); // 调整到合适的位置
	leftPalm->AddChild(leftThumb);

	// 食指
	auto leftIndexFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, cyan, "leftIndexFinger");
	leftIndexFinger->translate((fingerSpacing * 2), -15.0f, 0.0f);
	leftPalm->AddChild(leftIndexFinger);

	// 中指
	auto leftMiddleFinger = createBoxPart(fingerWidth, fingerHeight + 5.0f, fingerWidth, cyan, "leftMiddleFinger");
	leftMiddleFinger->translate((fingerSpacing), -15.0f, 0.0f);
	leftPalm->AddChild(leftMiddleFinger);

	// 无名指
	auto leftRingFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, cyan, "leftRingFinger");
	leftRingFinger->translate(0.0f, -15.0f, 0.0f);
	leftPalm->AddChild(leftRingFinger);

	// 小指
	auto leftLittleFinger = createBoxPart(fingerWidth, fingerHeight, fingerWidth, cyan, "leftLittleFinger");
	leftLittleFinger->translate(-(fingerSpacing), -15.0f, 0.0f);
	leftPalm->AddChild(leftLittleFinger);

	// right leg
	auto rightLeg = createTransfrom("rightLeg");
	auto rightUpperLeg = createBoxPart(20, 60, 20, yellow, "rightUpperLeg");
	auto rightLowerLeg = createBoxPart(20, 60, 20, gray, "rightLowerLeg");

	rightLowerLeg->translate(-15, -55, 0);
	rightLowerLeg->rotate(-30, 0, 0, 1);

	rightUpperLeg->AddChild(rightLowerLeg);
	rightLeg->rotate(30, 0, 0, 1);

	rightLeg->translate(10, -70, 0);

	rightLeg->AddChild(rightUpperLeg);
	root->AddChild(rightLeg);


	// 创建右脚掌
	auto rightFoot = createBoxPart(25, 10, 40, white, "rightFoot"); // 尺寸适合脚掌
	rightFoot->translate(0, -35, 0); // 调整到合适的位置
	rightLowerLeg->AddChild(rightFoot);

	// left leg
	auto leftLeg = createTransfrom("leftLeg");
	auto leftUpperLeg = createBoxPart(20, 60, 20, yellow, "leftUpperLeg");
	auto leftLowerLeg = createBoxPart(20, 60, 20, gray, "leftLowerLeg");

	leftLowerLeg->translate(15, -55, 0);
	leftLowerLeg->rotate(30, 0, 0, 1);

	leftUpperLeg->AddChild(leftLowerLeg);
	leftLeg->rotate(-30, 0, 0, 1);

	leftLeg->translate(-10, -70, 0);

	leftLeg->AddChild(leftUpperLeg);

	root->AddChild(leftLeg);

	// 创建左脚掌
	auto leftFoot = createBoxPart(25, 10, 40, white, "leftFoot");
	leftFoot->translate(0, -35, 0);
	leftLowerLeg->AddChild(leftFoot);

	AddNode(root);

	// 设置机器人身体的变换参数和旋转回调
	std::shared_ptr<RobotBodyTransformParam> data = std::make_shared<RobotBodyTransformParam>();
	std::shared_ptr<RobotBodyRotate> rc = std::make_shared<RobotBodyRotate>();
	
	root->setUserData(data);
	root->SetUpdateCallback(rc);

	// 设置手臂和腿的旋转参数和回调
	shared_ptr<RotateParam> leftParam = make_shared<RotateParam>();
	shared_ptr<RotateParam> rightParam = make_shared< RotateParam>();
	shared_ptr<RotateCallback> callback = make_shared<RotateCallback>();

	rightParam->setMaxAngle(45);
	rightParam->setAngle(45);
	rightParam->setStep(-2);


	leftArm->setUserData(leftParam);
	leftArm->SetUpdateCallback(callback);

	rightArm->setUserData(rightParam);
	rightArm->SetUpdateCallback(callback);


	leftLeg->setUserData(leftParam);
	leftLeg->SetUpdateCallback(callback);

	rightLeg->setUserData(rightParam);
	rightLeg->SetUpdateCallback(callback);

	// 刷新视图
	UpdateAllViews(NULL);
}

// CCG2022112453游坤坤Doc 命令

void CCG2022112453游坤坤Doc::OnViewResize(int cx, int cy)
{
	mScene->GetMainCamera()->viewport()->set(0, 0, cx, cy);
}

void CCG2022112453游坤坤Doc::setLight(CGLight& light)
{
	glEnable(GL_NORMALIZE); // 确保法线正确
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	// 关闭其他光源
	for (int i = 0; i < 8; ++i)
	{
		glDisable(GL_LIGHT0 + i);
	}
	//light.apply();
	using namespace std;
	auto lightState = make_shared<CGLight>(light);
	auto data = make_shared<LightTransformParam>();
	auto callbackk = make_shared<LightCallback>();

	lightState->setUserData(data);
	lightState->SetUpdateCallback(callbackk);
	mScene->GetSceneData()->asGroup()->gocRenderStateSet()->setRenderState(lightState, 0);

	UpdateAllViews(NULL);
}

std::shared_ptr<CGTransform> CCG2022112453游坤坤Doc::createSolidAndWireframeObject(
	std::shared_ptr<CGRenderable> shape,
	const glm::vec3& position,
	const glm::vec4& color,
	MaterialPreset preset,
	const CString& name)
{
	using namespace std;

	vector<shared_ptr<CGRenderState>> states;

	auto colorState = make_shared<CGColor>();
	colorState->setValue(color);
	states.push_back(colorState);

	auto material = make_shared<CGMaterial>(CreateMaterial(preset));
	states.push_back(material);

	auto tranSolid = createGeometry(shape, position, states, name);

	// 加入线框模式
	auto wireframeStates = states; // 复制已有状态
	auto mode = make_shared<CGPolygonMode>(PM_LINE, PM_LINE);
	wireframeStates.push_back(mode);
	auto tranWireframe = createGeometry(shape, { -position.x, position.y, position.z }, wireframeStates, name + "-线框");

	// 创建变换节点
	auto transform = createTransfrom(name);

	float scaleFactor = 50.0f;
	tranSolid->scale(scaleFactor, scaleFactor, scaleFactor);
	tranWireframe->scale(scaleFactor, scaleFactor, scaleFactor);
	transform->AddChild(tranSolid);
	transform->AddChild(tranWireframe);

	auto param1 = make_shared<MaterialTransformParam>();
	param1->current = static_cast<int>(preset);

	auto callback = make_shared<MaterialTransfomCallback>();

	tranSolid->setUserData(param1);
	tranSolid->SetUpdateCallback(callback);

	auto param2 = make_shared<MaterialTransformParam>();
	param2->current = static_cast<int>(preset);
	tranWireframe->setUserData(param2);
	tranWireframe->SetUpdateCallback(callback);

	return transform;
}

void CCG2022112453游坤坤Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	updateHandle(pCmdUI, EventType::Draw2DLineSeg);
}

void CCG2022112453游坤坤Doc::OnDraw2dLineseg()
{
	CCG2022112453游坤坤View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453游坤坤View))) {
			view = dynamic_cast<CCG2022112453游坤坤View*>(pView);
			break;
		}
	}

	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineSeg(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}

void CCG2022112453游坤坤Doc::OnDraw2dLineStrip()
{
	CCG2022112453游坤坤View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453游坤坤View))) {
			view = dynamic_cast<CCG2022112453游坤坤View*>(pView);
			break;
		}
	}

	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view == nullptr)
		return;
	UIEventHandler::SetCommand(new CGDraw2DLineStrip(view->glfwWindow(), view->DDA_Line)); //创建绘制直线段的命令对象
	//UIEventHandler::SetCommand(new CGDraw2DLineStrip(view->glfwWindow(), view->Bresenham_Line)); //创建绘制直线段的命令对象
	//UIEventHandler::SetCommand(new CGDraw2DLineStrip(view->glfwWindow(), view->Midpoint_Line)); //创建绘制直线段的命令对象
}

void CCG2022112453游坤坤Doc::OnUpdateDraw2dLineStrip(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码 
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==
		EventType::Draw2DLineStrip);
}



void CCG2022112453游坤坤Doc::OnTranslate2dLeft()
{
	translate2d(-STEP, 0);
}

void CCG2022112453游坤坤Doc::OnTranslate2dRight()
{
	translate2d(STEP, 0);
}

void CCG2022112453游坤坤Doc::OnTranslate2dUp()
{
	translate2d(0, STEP);
}

void CCG2022112453游坤坤Doc::OnTranslate2dDown()
{
	translate2d(0, -STEP);
}

void CCG2022112453游坤坤Doc::OnRotate2dCounterclockwise()
{
	rotate2d(ANGLE, 0, 0);
}

void CCG2022112453游坤坤Doc::OnRotate2dClockwise()
{
	rotate2d(-ANGLE, 0, 0);
}

void CCG2022112453游坤坤Doc::OnScalex2dUp()
{
	scale2d(SCALE_UP, 1);
}

void CCG2022112453游坤坤Doc::OnScalex2dDown()
{
	scale2d(SCALE_DOWN, 1);
}

void CCG2022112453游坤坤Doc::OnSacley2dUp()
{
	scale2d(1, SCALE_UP);
}

void CCG2022112453游坤坤Doc::OnScaley2dDown()
{
	scale2d(1, SCALE_DOWN);
}

void CCG2022112453游坤坤Doc::OnScale2dUp()
{
	scale2d(SCALE_UP, SCALE_UP);
}

void CCG2022112453游坤坤Doc::OnScale2dDown()
{
	scale2d(SCALE_DOWN, SCALE_DOWN);
}

void CCG2022112453游坤坤Doc::OnShearx2dPositive()
{
	shear2d(ANGLE, 0);
}

void CCG2022112453游坤坤Doc::OnShearx2dNegative()
{
	shear2d(-ANGLE, 0);
}

void CCG2022112453游坤坤Doc::OnSheary2dPositive()
{
	shear2d(0, ANGLE);
}

void CCG2022112453游坤坤Doc::OnSheary2dNegative()
{
	shear2d(0, -ANGLE);
}

void CCG2022112453游坤坤Doc::OnMirror2dOrigin()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorOrigin();
		});
}

void CCG2022112453游坤坤Doc::OnMirror2dYeqPosX()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorYeqPosX();
		});
}

void CCG2022112453游坤坤Doc::OnMirror2dYeqNegX()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorYeNegPX();
		});
}

void CCG2022112453游坤坤Doc::OnMirrorx2d()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorXAxis();
		});
}

void CCG2022112453游坤坤Doc::OnMirrory2d()
{
	performTransformation([](CGRenderable* child) {
		child->MirrorYAxis();
		});
}

void CCG2022112453游坤坤Doc::OnButtonTransform2d()
{
	CCG2022112453游坤坤View* view = getView();
	if (view == nullptr)
		return;
	commandHandler();

	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CTreeCtrl* pTree = &(pSceneGraphView->GetTreeCtrl());
	CGGeode* node = (CGGeode*)pTree->GetItemData(mSelectedItem);

	if (!node)
	{
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	if (node->GetNumRenderables() <= 0)
		return;
	CGRenderable* child = node->GetRenderable(0);
	if (!child)
	{
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow()));
}

void CCG2022112453游坤坤Doc::OnUpdateButtonTransform2d(CCmdUI* pCmdUI)
{
	updateHandle(pCmdUI, EventType::Model2DTransform);
}

void CCG2022112453游坤坤Doc::OnButtonDraw3dSphere()
{
	using namespace std;
	MyDialog dialog;
	dialog.setDrawType(DrawType::SPHERE);
	if (dialog.DoModal() == IDOK)
	{
		glm::vec3 point(dialog.xpos, dialog.ypos, dialog.zpos);

        auto sphere = make_shared<CGSphere>();
        auto hints = make_shared<TessellationHints>();
        hints->setTargetSlices(dialog.slice);
        hints->setTargetStacks(dialog.mstack);
        sphere->setRadius(dialog.radius);
        sphere->setTessellationHints(hints);
        sphere->setDisplayListEnabled(true);

        auto tran = createSolidAndWireframeObject(
            sphere,
            point,
            dialog.getColor(),
            static_cast<MaterialPreset>(dialog.mSel),
            "球体"
        );

        AddNode(tran);
        UpdateAllViews(NULL);

	}
}

void CCG2022112453游坤坤Doc::OnButtonCube()
{
	using namespace std;
	MyDialog dialog;
	dialog.setDrawType(DrawType::CUBE);
	if (dialog.DoModal() == IDOK)
	{
		glm::vec3 point(dialog.xpos, dialog.ypos, dialog.zpos);

		auto cube = make_shared<CGCube>(dialog.len, dialog.width, dialog.height);
		auto hints = make_shared<TessellationHints>();
		cube->setTessellationHints(hints);
		cube->setDisplayListEnabled(true);

		auto tran = createSolidAndWireframeObject(
			cube,
			point,
			dialog.getColor(),
			static_cast<MaterialPreset>(dialog.mSel),
			"立方体"
		);
		AddNode(tran);
		UpdateAllViews(NULL);
	}
}

void CCG2022112453游坤坤Doc::OnButtonTimer()
{
	// TODO: 在此添加命令处理程序代码 
	CCG2022112453游坤坤View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453游坤坤View))) {
			view = dynamic_cast<CCG2022112453游坤坤View*>(pView);
			break;
		}
	}
	if (view != nullptr) {
		mTimer = view->toggleFrameTimer();// 启动定时器 
	}
}

void CCG2022112453游坤坤Doc::OnUpdateButtonTimer(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mTimer != 0);
}

void CCG2022112453游坤坤Doc::OnButtonRobot()
{
	buildRobot();
	//auto tran1 = createBoxPart(100, 100, 100, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//mScene->GetSceneData()->asGroup()->AddChild(tran1);
	UpdateAllViews(NULL);
}

void CCG2022112453游坤坤Doc::OnButtonCameraControl()
{
	CCG2022112453游坤坤View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453游坤坤View))) {
			view = dynamic_cast<CCG2022112453游坤坤View*>(pView);
			break;
		}
	}

	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view == nullptr)
		return;
	auto window = view->glfwWindow();
	auto camera = mScene->GetMainCamera();
	UIEventHandler::SetCommand(new CGBasicCameraControl(window, camera)); //创建绘制直线段的命令对象
}

void CCG2022112453游坤坤Doc::OnUpdateButtonCameraControl(CCmdUI* pCmdUI)
{
	updateHandle(pCmdUI, EventType::CGBasicCameraControl);
}

void CCG2022112453游坤坤Doc::OnButtonArcballControl()
{
	CCG2022112453游坤坤View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022112453游坤坤View))) {
			view = dynamic_cast<CCG2022112453游坤坤View*>(pView);
			break;
		}
	}

	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view == nullptr)
		return;
	auto window = view->glfwWindow();
	auto camera = mScene->GetMainCamera();
	UIEventHandler::SetCommand(new CGArcballCameraControl(window, camera)); //创建绘制直线段的命令对象
}

void CCG2022112453游坤坤Doc::OnUpdateButtonArcballControl(CCmdUI* pCmdUI)
{
	updateHandle(pCmdUI, EventType::CGArcballCameraControl);
}



void CCG2022112453游坤坤Doc::OnButtonLightControl()
{
	
}
void CCG2022112453游坤坤Doc::OnButtonPointLight()
{
	using namespace std;
	auto& light = SceneLights::PointLight;
	light.setPosition(glm::vec4(0, 0, 100, 1));
	light.enable(true);
	setLight(light);

}
void CCG2022112453游坤坤Doc::OnButtonDirectionalLight()
{
	auto& light = SceneLights::DirectionalLight;
	light.setPosition(glm::vec4(0, 0, 100, 0));
	setLight(light);

}

void CCG2022112453游坤坤Doc::OnButtonSpotLight()
{
	auto& light = SceneLights::SpotLight;

	glm::vec3 pos = glm::vec3(0, 0, 100);
	glm::vec3 target = glm::vec3(0, 0, 0);
	light.setPosition(glm::vec4(pos, 1.0f));
	light.setSpotDirection(glm::normalize(target - pos));

	setLight(light);
}

void CCG2022112453游坤坤Doc::OnButtonTurnOffLight()
{
	for (int i = 0; i < 8; ++i)
	{
		glDisable(GL_LIGHT0 + i);
	}
	UpdateAllViews(NULL);
}
