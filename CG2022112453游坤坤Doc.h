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

// CG2022112453游坤坤Doc.h: CCG2022112453游坤坤Doc 类的接口
//


#pragma once

#include <memory> 
#include <functional>
#include "glIncludes.h"
class CGScene;
class CGRenderContext;
class CGNode;
class CGGroup;
class CCGSceneGraphView;
class CCG2022112453游坤坤View;
enum class EventType;
class CGRenderable;
class CGTransform;
class CGGeode;
class CGRenderState;
class CCG2022112453游坤坤Doc : public CDocument
{
protected: // 仅从序列化创建
	CCG2022112453游坤坤Doc() noexcept;
	DECLARE_DYNCREATE(CCG2022112453游坤坤Doc)
// 特性
public:
	std::shared_ptr<CGScene> mScene = nullptr;


protected:
	CGGroup* mSelectedGroup = nullptr;
	HTREEITEM mSelectedItem = nullptr;
public:
	CCGSceneGraphView* GetSceneGraphView();
	void InstToSceneTree(CTreeCtrl* pTree);//实列节点加入场景树 
	void InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hInst, CGNode* node);
	void OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem); //场景树中选中节点
	HTREEITEM GetSelectedItem() { return mSelectedItem; } //获取选中节点

// 操作
public:
	bool RenderScene(CGRenderContext* pRC);
	bool AddRenderable(std::shared_ptr<CGNode> r);
	bool AddNode(std::shared_ptr<CGNode>  node);
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CCG2022112453游坤坤Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	const double STEP = 10;
	const double ANGLE = 10;
	const double SCALE_UP = 1.25;
	const double SCALE_DOWN = 0.8;

	CCG2022112453游坤坤View* getView();
	void updateHandle(CCmdUI* pCmdUI, EventType type);
	void commandHandler();
	void performTransformation(std::function<void(CGRenderable*)> transformFunc);
	void translate2d(double x, double y);
	void rotate2d(double angle, double cx, double cy);
	void scale2d(double sx, double sy);
	void shear2d(double shx, double shy);

	void draw3D(std::shared_ptr<CGRenderable> render, glm::vec3 center);

	std::shared_ptr< CGTransform> createGeometry(
		const std::shared_ptr<CGRenderable> &render,	// 几何体
		const glm::vec3 &center,						// 中心
		const std::vector<std::shared_ptr<CGRenderState>> &states, 		// 状态集合
		const CString &name = "几何体"							// 节点名称
	);

	// 实验5
protected:
	UINT mTimer = 0; //定时器 
	std::shared_ptr<CGTransform> createTransfrom(CString name);
	std::shared_ptr<CGTransform> createBoxPart(float len, float width, float height, const glm::vec4& color, const CString name = "" );
	void CCG2022112453游坤坤Doc::buildRobot();

	// 实验6
public:
	void OnViewResize(int cx, int cy);

public:
	afx_msg void OnUpdateDraw2dLineseg(CCmdUI* pCmdUI);
	afx_msg void OnDraw2dLineseg();

	afx_msg void OnDraw2dLineStrip();
	afx_msg void OnUpdateDraw2dLineStrip(CCmdUI* pCmdUI);
	afx_msg void OnTranslate2dLeft();
	afx_msg void OnTranslate2dRight();
	afx_msg void OnTranslate2dUp();
	afx_msg void OnTranslate2dDown();
	afx_msg void OnRotate2dCounterclockwise();
	afx_msg void OnRotate2dClockwise();
	afx_msg void OnScalex2dUp();
	afx_msg void OnScalex2dDown();
	afx_msg void OnSacley2dUp();
	afx_msg void OnScaley2dDown();
	afx_msg void OnScale2dUp();
	afx_msg void OnScale2dDown();
	afx_msg void OnShearx2dPositive();
	afx_msg void OnShearx2dNegative();
	afx_msg void OnSheary2dPositive();
	afx_msg void OnSheary2dNegative();
	afx_msg void OnMirror2dOrigin();
	afx_msg void OnMirror2dYeqPosX();
	afx_msg void OnMirror2dYeqNegX();
	afx_msg void OnMirrorx2d();
	afx_msg void OnMirrory2d();
	afx_msg void OnButtonTransform2d();
	afx_msg void OnUpdateButtonTransform2d(CCmdUI* pCmdUI);
	afx_msg void OnButtonDraw3dSphere();
	afx_msg void OnButtonCube();
	afx_msg void OnButtonTimer();
	afx_msg void OnUpdateButtonTimer(CCmdUI* pCmdUI);
	afx_msg void OnButtonRobot();
	afx_msg void OnButtonCameraControl();
	afx_msg void OnUpdateButtonCameraControl(CCmdUI* pCmdUI);
	afx_msg void OnButtonArcballControl();
	afx_msg void OnUpdateButtonArcballControl(CCmdUI* pCmdUI);
	afx_msg void OnButtonLightControl();
	afx_msg void OnButtonPointLight();
	afx_msg void OnButtonDirectionalLight();
	afx_msg void OnButtonSpotLight();
	afx_msg void OnButtonTurnOffLight();
};
