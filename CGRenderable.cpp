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
	CGNode::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
	if (ar.IsStoring())  //保存 
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明 
	}
	else //读取 
	{
		//ar >> ; 
	}
}

//渲染 
bool CGRenderable::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	// 
	if (getRenderStateSet()) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		getRenderStateSet()->apply(pCamera, pRC);
	}
	if (isDisplayListEnabled()) { //使用显示列表 
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
	// 平移到原点
	mat = translate(mat, -vs);

	dvec2 dir = dvec2(ve.x - vs.x, ve.y - vs.y);

	dir = normalize(dir);
	double angle = atan2(dir.y, dir.x);
	// 旋转到X轴
	mat = rotate(mat, -angle, dvec3(0, 0, 1));

	dmat4 mirrorMat = dmat4(1.0);
	mirrorMat[1][1] = -1.0;
	// 镜像
	mat = mirrorMat * mat;
	// 旋转回去
	mat = rotate(mat, angle, dvec3(0, 0, 1));
	// 平移回去
	mat = translate(mat, vs);
	// 变换
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
