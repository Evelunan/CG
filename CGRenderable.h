#pragma once 
#include "CGNode.h" 

class CGRenderContext; //预声明 
class CGCamera;  //预声明 
class CGRenderable : public CGNode
{
	DECLARE_SERIAL(CGRenderable)
public:
	CGRenderable();
	virtual ~CGRenderable();
	//序列化 
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写） 
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGRenderable* asRenderable() { return this; }
	virtual const CGRenderable* asRenderable() const { return this; }

public:
	virtual void Transform(const glm::dmat4& mat){}
	//平移 
	virtual void Translate(double tx, double ty);
	//旋转（逆时针为正，度）
	virtual void Rotate(double angle, double cx, double cy);
	//缩放（关于坐标原点缩放）
	virtual void Scale(double sx, double sy);
	//缩放（关于指定点缩放）
	virtual void Scale(double sx, double sy, double cx, double cy);
	//关于X轴对称（二维） 
	virtual void MirrorXAxis();
	//关于Y轴对称（二维） 
	virtual void MirrorYAxis();
	//关于y=x对称（二维） 
	virtual void MirrorYeqPosX();
	//关于y=-x对称（二维） 
	virtual void MirrorYeNegPX();
	//关于原点对称（二维）
	virtual void MirrorOrigin();
	//关于线段se对称（二维） 
	virtual void Mirror(const glm::dvec3& vs, const glm::dvec3& ve);
	//沿X轴错切 
	virtual void ShearXAxis(double shx);
	//沿Y轴错切 
	virtual void ShearYAxis(double shy);
	//沿X、Y轴错切 
	virtual void ShearXYAxis(double shx, double shy);
	//几何变换（左乘给定矩阵） 
	virtual void Transform(const glm::dmat3& mat) {}


protected:
	CGRenderable(const CGRenderable& other) : CGNode(other)
	{
	}
	CGRenderable& operator=(const CGRenderable&) = default;
	virtual void buildDisplayList() {} //派生类中重写 

public:
	bool isDisplayListEnabled() const { return mDisplayListEnabled; }
	void setDisplayListEnabled(bool enabled) { mDisplayListEnabled = enabled; }
	bool displayListDirty() const { return mDisplayListDirty; }
	void setDisplayListDirty(bool dirty) { mDisplayListDirty = dirty; }
	GLuint displayList() const { return mDisplayList; }
	void setDisplayList(unsigned int disp_list) { mDisplayList = disp_list; }
	void deleteDisplayList()
	{
		if (displayList())
			glDeleteLists(displayList(), 1);
		mDisplayList = 0;
	}


protected:
	bool mDisplayListEnabled = false;
	bool mDisplayListDirty = true;
	GLuint mDisplayList = 0;
};