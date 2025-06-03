#include "pch.h"
#include "CGShadeModel.h"
CGShadeModel::CGShadeModel(EShadeModel shademodel)
	: mShadeModel(shademodel)
{
}
void CGShadeModel::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const
{
	glShadeModel((GLenum)mShadeModel);
}