#include "pch.h"
#include "CGLineStrip.h"


IMPLEMENT_SERIAL(CGLineStrip, CGGeometry, 1)
CGLineStrip::CGLineStrip()
{
}

CGLineStrip::CGLineStrip(const std::vector<glm::dvec3>& points, void(*drawLine)(int, int, int, int, glm::vec3))
	:points(points), drawLine(drawLine)
{
}

CGLineStrip::~CGLineStrip()
{
}

void CGLineStrip::Serialize(CArchive& ar)
{
	CGRenderable::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
	if (ar.IsStoring())  //保存 
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明 
	}
	else //读取 
	{
		//ar >> ; 
	}
}

bool CGLineStrip::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;

	drwaLineStrip(points); //绘制线段

	return true;
}

void CGLineStrip::drwaLineStrip(const std::vector<glm::dvec3>& points)
{
	// 白色
	auto white = glm::vec3(1.0f, 1.0f, 1.0f);

	for (size_t i = 0; i < points.size() - 1; ++i)
	{
		drawLine(
			int(points[i].x), int(points[i].y),
			int(points[i + 1].x), int(points[i + 1].y),
			white);
	}
}

