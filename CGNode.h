#pragma once 
#include "CGObject.h" 
#include <vector> 

//Ԥ���������ļ���ֻ�õ������ָ�룬Ϊ���⽻������� 
class CGNode;
class CGCamera;
class CGRenderContext;
class CGGroup;
class CGTransform;
class CGGeode;
class CGRenderable;
class CGGeometry;

class CGNode : public CGObject
{
	DECLARE_SERIAL(CGNode)
public:
	CGNode();
	//���л� 
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д�� 
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);

	virtual CGNode* asNode() { return this; }
	virtual const CGNode* asNode() const { return this; }
	virtual CGGroup* asGroup() { return 0; }
	virtual const CGGroup* asGroup() const { return 0; }
	virtual CGTransform* asTransform() { return 0; }
	virtual const CGTransform* asTransform() const { return 0; }
	virtual CGRenderable* asRenderable() { return 0; }
	virtual const CGRenderable* asRenderable() const { return 0; }
	virtual CGGeode* asGeode() { return 0; }
	virtual const CGGeode* asGeode() const { return 0; }
	virtual CGGeometry* asGeometry() { return 0; }
	virtual const CGGeometry* asGeometry() const { return 0; }

	void SetUpdateCallback(std::shared_ptr<CGCallback> uc) { mUpdateCallback = uc; }
	inline CGCallback* GetUpdateCallback() { return mUpdateCallback.get(); }

public:
	//֧�ֹ����ӽڵ㣨�磬ʵ���ڵ㹲����ģ�ͣ� 
	typedef std::vector<CGGroup*> ParentList;
	CGGroup* GetParent(unsigned int i);
	const CGGroup* GetParent(unsigned int i) const;
	inline const ParentList& GetParents() const { return mParents; }
	inline ParentList GetParents() { return mParents; }
	inline unsigned int GetNumParents() const { return static_cast<unsigned int>(mParents.size()); }

protected:
	virtual ~CGNode();
	std::shared_ptr<CGCallback> mUpdateCallback = nullptr;
	friend class CGGroup;
	friend class CGRenderable;
protected:
	//֧�ֹ����ӽڵ� 
	ParentList mParents;    //һ��ģ�͹��������ͼ�νڵ㣨�������ʵ���ڵ㣩 
	void AddParent(CGGroup* parent);
	void RemoveParent(CGGroup* parent);


public:
	//ƽ�� 
	virtual void Translate(double tx, double ty) {}
	//��ת����ʱ��Ϊ�����ȣ�
	virtual void Rotate(double angle, double cx, double cy) {}
	//���ţ���������ԭ�����ţ�
	virtual void Scale(double sx, double sy) {}
	//����X��Գƣ���ά�� 
	virtual void MirrorXAxis() {}
	//����Y��Գƣ���ά�� 
	virtual void MirrorYAxis() {}
	//����y=x�Գƣ���ά�� 
	virtual void MirrorYeqPosX() {}
	//����y=-x�Գƣ���ά�� 
	virtual void MirrorYeNegPX() {}
	//����ԭ��Գƣ���ά��
	virtual void MirrorOrigin() {}
	//�����߶�se�Գƣ���ά�� 
	virtual void Mirror(const glm::dvec3& vs, const glm::dvec3& ve) {}
	//��X����� 
	virtual void ShearXAxis(double shx) {}
	//��Y����� 
	virtual void ShearYAxis(double shy) {}
	//��X��Y����� 
	virtual void ShearXYAxis(double shx, double shy) {}
	//���α任����˸������� 
	virtual void Transform(const glm::dmat3& mat) {}
};