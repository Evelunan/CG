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

	 
public:
	virtual void Transform(const glm::dmat4& mat) override;

protected:
	std::vector<glm::dvec3> points; //线段的顶点集合
	void(*drawLine)(int, int, int, int, glm::vec3) = nullptr; //绘制线段的函数指针
};

