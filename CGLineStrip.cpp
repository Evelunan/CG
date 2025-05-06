#include "pch.h"
#include "CGLineStrip.h"
#include "constant.h"
#include <cmath>

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

void CGLineStrip::Transform(const glm::dmat4& mat)
{
	for (auto& point : points)
	{
		auto p4 = mat * glm::dvec4(point, 1);
		point = glm::dvec3(p4.x, p4.y, p4.z);
	}
}

void CGLineStrip::Translate(double tx, double ty)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat = translate(mat, dvec3(tx, ty, 0));
	Transform(mat);
}

void CGLineStrip::Rotate(double angle, double cx, double cy)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat = translate(mat, dvec3(cx, cy, 0));
	mat = rotate(mat, radians(angle), dvec3(0, 0, 1.0));
	mat = translate(mat, dvec3(-cx, -cy, 0));
	Transform(mat);
}

void CGLineStrip::Scale(double sx, double sy)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat = scale(mat, dvec3(sx, sy, 1.0));
	Transform(mat);
}

void CGLineStrip::Scale(double sx, double sy, double cx, double cy)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat = translate(mat, dvec3(cx, cy, 0));
	mat = scale(mat, dvec3(sx, sy, 1.0));
	mat = translate(mat, dvec3(-cx, -cy, 0));
	Transform(mat);
}

void CGLineStrip::MirrorXAxis()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[1][1] = -1.0;
	Transform(mat);
}

void CGLineStrip::MirrorYAxis()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][0] = -1.0;
	Transform(mat);
}

void CGLineStrip::MirrorYeqPosX()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][0] = 0;
	mat[1][1] = 0;
	mat[0][1] = 1;
	mat[1][0] = 1;
	Transform(mat);
}

void CGLineStrip::MirrorYeNegPX()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][0] = 0;
	mat[1][1] = 0;
	mat[0][1] = -1;
	mat[1][0] = -1;
	Transform(mat);
}

void CGLineStrip::MirrorOrigin()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][0] = -1.0;
	mat[1][1] = -1.0;
	Transform(mat);
}

void CGLineStrip::Mirror(const glm::dvec3& vs, const glm::dvec3& ve)
{
	using namespace glm;
	dmat4 mat = dmat4(1.0);
	// ƽ�Ƶ�ԭ��
	mat = translate(mat, -vs);

	dvec2 dir = dvec2(ve.x - vs.x, ve.y - vs.y);

	dir = normalize(dir);
	double angle = atan2(dir.y, dir.x);
	// ��ת��X��
	mat = rotate(mat, -angle, dvec3(0, 0, 1));

	dmat4 mirrorMat = dmat4(1.0);
	mirrorMat[1][1] = -1.0;
	// ����
	mat = mirrorMat * mat;
	// ��ת��ȥ
	mat = rotate(mat, angle, dvec3(0, 0, 1));
	// ƽ�ƻ�ȥ
	mat = translate(mat, vs);
	// �任
	Transform(mat);
}

void CGLineStrip::ShearXAxis(double shx)
{
	ShearXYAxis(shx, 0);
}

void CGLineStrip::ShearYAxis(double shy)
{
	ShearXYAxis(0, shy);
}

void CGLineStrip::ShearXYAxis(double shx, double shy)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][1] = tan(radians(shx));
	mat[1][0] = tan(radians(shy));
	Transform(mat);
}

void CGLineStrip::Transform(const glm::dmat3& mat)
{
	for (auto& point : points)
	{
		point = mat * point;
	}
}

