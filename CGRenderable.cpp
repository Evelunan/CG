#include "pch.h" 
#include "CGRenderable.h" 
#include "CGCamera.h" 
#include "CGRenderContext.h" 

IMPLEMENT_SERIAL(CGRenderable, CGNode, 1)

CGRenderable::CGRenderable()
{
}

CGRenderable::~CGRenderable()
{
}
void CGRenderable::Serialize(CArchive& ar)
{
	CGNode::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	if (ar.IsStoring())  //���� 
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵�� 
	}
	else //��ȡ 
	{
		//ar >> ; 
	}
}

//��Ⱦ 
bool CGRenderable::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	// 
	if (getRenderStateSet()) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		getRenderStateSet()->apply(pCamera, pRC);
	}
	if (isDisplayListEnabled()) { //ʹ����ʾ�б� 
		if (displayListDirty()) {
			if (!displayList()) {
				setDisplayList(glGenLists(1));
			}
			assert(displayList());
			glNewList(displayList(), GL_COMPILE_AND_EXECUTE);
			buildDisplayList();
			glEndList();
			setDisplayListDirty(false);
		}
		else {
			assert(displayList());
			glCallList(displayList());
		}
	}
	else {
	}
	if (getRenderStateSet()) {
		glPopAttrib();
	}
	return true;
}

void CGRenderable::Translate(double tx, double ty)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat = translate(mat, dvec3(tx, ty, 0));
	Transform(mat);
}

void CGRenderable::Rotate(double angle, double cx, double cy)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat = translate(mat, dvec3(cx, cy, 0));
	mat = rotate(mat, radians(angle), dvec3(0, 0, 1.0));
	mat = translate(mat, dvec3(-cx, -cy, 0));
	Transform(mat);
}

void CGRenderable::Scale(double sx, double sy)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat = scale(mat, dvec3(sx, sy, 1.0));
	Transform(mat);
}

void CGRenderable::Scale(double sx, double sy, double cx, double cy)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat = translate(mat, dvec3(cx, cy, 0));
	mat = scale(mat, dvec3(sx, sy, 1.0));
	mat = translate(mat, dvec3(-cx, -cy, 0));
	Transform(mat);

}

void CGRenderable::MirrorXAxis()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[1][1] = -1.0;
	Transform(mat);
}

void CGRenderable::MirrorYAxis()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][0] = -1.0;
	Transform(mat);
}

void CGRenderable::MirrorYeqPosX()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][0] = 0;
	mat[1][1] = 0;
	mat[0][1] = 1;
	mat[1][0] = 1;
	Transform(mat);
}

void CGRenderable::MirrorYeNegPX()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][0] = 0;
	mat[1][1] = 0;
	mat[0][1] = -1;
	mat[1][0] = -1;
	Transform(mat);
}

void CGRenderable::MirrorOrigin()
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][0] = -1.0;
	mat[1][1] = -1.0;
	Transform(mat);
}

void CGRenderable::Mirror(const glm::dvec3& vs, const glm::dvec3& ve)
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

void CGRenderable::ShearXAxis(double shx)
{
	ShearXYAxis(shx, 0);
}

void CGRenderable::ShearYAxis(double shy)
{
	ShearXYAxis(0, shy);
}

void CGRenderable::ShearXYAxis(double shx, double shy)
{
	using namespace glm;
	auto mat = dmat4(1.0);
	mat[0][1] = tan(radians(shx));
	mat[1][0] = tan(radians(shy));
	Transform(mat);
}
