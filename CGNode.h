#pragma once 
#include "CGObject.h" 
#include <vector> 

//预声明（本文件中只用到相关类指针，为避免交叉包含） 
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
	//序列化 
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写） 
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
	//支持共享子节点（如，实例节点共享几何模型） 
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
	//支持共享子节点 
	ParentList mParents;    //一个模型关联到多个图形节点（产生多个实例节点） 
	void AddParent(CGGroup* parent);
	void RemoveParent(CGGroup* parent);


public:
	//平移 
	virtual void Translate(double tx, double ty) {}
	//旋转（逆时针为正，度）
	virtual void Rotate(double angle, double cx, double cy) {}
	//缩放（关于坐标原点缩放）
	virtual void Scale(double sx, double sy) {}
	//关于X轴对称（二维） 
	virtual void MirrorXAxis() {}
	//关于Y轴对称（二维） 
	virtual void MirrorYAxis() {}
	//关于y=x对称（二维） 
	virtual void MirrorYeqPosX() {}
	//关于y=-x对称（二维） 
	virtual void MirrorYeNegPX() {}
	//关于原点对称（二维）
	virtual void MirrorOrigin() {}
	//关于线段se对称（二维） 
	virtual void Mirror(const glm::dvec3& vs, const glm::dvec3& ve) {}
	//沿X轴错切 
	virtual void ShearXAxis(double shx) {}
	//沿Y轴错切 
	virtual void ShearYAxis(double shy) {}
	//沿X、Y轴错切 
	virtual void ShearXYAxis(double shx, double shy) {}
	//几何变换（左乘给定矩阵） 
	virtual void Transform(const glm::dmat3& mat) {}
};