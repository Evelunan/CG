// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û�����
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο�����
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// CG2022112453������Doc.h: CCG2022112453������Doc ��Ľӿ�
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
class CCG2022112453������View;
enum class EventType;
class CGRenderable;
class CGTransform;
class CGGeode;
class CGRenderState;
class CCG2022112453������Doc : public CDocument
{
protected: // �������л�����
	CCG2022112453������Doc() noexcept;
	DECLARE_DYNCREATE(CCG2022112453������Doc)
// ����
public:
	std::shared_ptr<CGScene> mScene = nullptr;


protected:
	CGGroup* mSelectedGroup = nullptr;
	HTREEITEM mSelectedItem = nullptr;
public:
	CCGSceneGraphView* GetSceneGraphView();
	void InstToSceneTree(CTreeCtrl* pTree);//ʵ�нڵ���볡���� 
	void InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hInst, CGNode* node);
	void OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem); //��������ѡ�нڵ�
	HTREEITEM GetSelectedItem() { return mSelectedItem; } //��ȡѡ�нڵ�

// ����
public:
	bool RenderScene(CGRenderContext* pRC);
	bool AddRenderable(std::shared_ptr<CGNode> r);
	bool AddNode(std::shared_ptr<CGNode>  node);
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CCG2022112453������Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	const double STEP = 10;
	const double ANGLE = 10;
	const double SCALE_UP = 1.25;
	const double SCALE_DOWN = 0.8;

	CCG2022112453������View* getView();
	void updateHandle(CCmdUI* pCmdUI, EventType type);
	void commandHandler();
	void performTransformation(std::function<void(CGRenderable*)> transformFunc);
	void translate2d(double x, double y);
	void rotate2d(double angle, double cx, double cy);
	void scale2d(double sx, double sy);
	void shear2d(double shx, double shy);

	void draw3D(std::shared_ptr<CGRenderable> render, glm::vec3 center);

	std::shared_ptr< CGTransform> createGeometry(
		const std::shared_ptr<CGRenderable> &render,	// ������
		const glm::vec3 &center,						// ����
		const std::vector<std::shared_ptr<CGRenderState>> &states, 		// ״̬����
		const CString &name = "������"							// �ڵ�����
	);

	// ʵ��5
protected:
	UINT mTimer = 0; //��ʱ�� 
	std::shared_ptr<CGTransform> createTransfrom(CString name);
	std::shared_ptr<CGTransform> createBoxPart(float len, float width, float height, const glm::vec4& color, const CString name = "" );
	void CCG2022112453������Doc::buildRobot();

	// ʵ��6
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
