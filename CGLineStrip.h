#pragma once
#include "CGGeometry.h" 
class CGLineStrip : public CGGeometry
{
	DECLARE_SERIAL(CGLineStrip);
public:
	CGLineStrip();
	CGLineStrip(const std::vector<glm::dvec3>& points, void(*drawLine)(int, int, int, int, glm::vec3));
	virtual ~CGLineStrip();

	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);

public:
	 void drwaLineStrip(const std::vector<glm::dvec3>& points);

	  void Transform(const glm::dmat4& mat);
public:

	//平移 
	virtual void Translate(double tx, double ty);	
	//旋转（逆时针为正，度）
	virtual void Rotate(double angle, double cx, double cy); 
	//缩放（关于坐标原点缩放）
	virtual void Scale(double sx, double sy);
	//关于X轴对称（二维） ）
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
	//沿X、Y轴错切，shx，shy分别表示X、Y轴错切角度
	virtual void ShearXYAxis(double shx, double shy); 
	//几何变换（左乘给定矩阵） 
	virtual void Transform(const glm::dmat3& mat);  

protected:
	std::vector<glm::dvec3> points; //线段的顶点集合
	void(*drawLine)(int, int, int, int, glm::vec3) = nullptr; //绘制线段的函数指针
};

