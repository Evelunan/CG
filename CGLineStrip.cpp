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
	CGRenderable::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	if (ar.IsStoring())  //���� 
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵�� 
	}
	else //��ȡ 
	{
		//ar >> ; 
	}
}

bool CGLineStrip::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;

	drwaLineStrip(points); //�����߶�

	return true;
}

void CGLineStrip::drwaLineStrip(const std::vector<glm::dvec3>& points)
{
	// ��ɫ
	auto white = glm::vec3(1.0f, 1.0f, 1.0f);

	for (size_t i = 0; i < points.size() - 1; ++i)
	{
		drawLine(
			int(points[i].x), int(points[i].y),
			int(points[i + 1].x), int(points[i + 1].y),
			white);
	}
}

