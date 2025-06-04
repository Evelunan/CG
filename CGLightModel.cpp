#include "pch.h"
#include "CGLightModel.h"
CGLightModel::CGLightModel()
	: mAmbientColor(0.2f, 0.2f, 0.2f, 1.0f), mLocalViewer(false), mTwoSide(false)
{
}
void CGLightModel::apply(const CGCamera*, CGRenderContext*, int) const
{
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, mLocalViewer ? 1.0f : 0.0f);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &mAmbientColor.r);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, mTwoSide ? 1.0f : 0.0f);
}


CGLight::CGLight() {}

CGLight::~CGLight() {}

void CGLight::setType(LightType type)
{
    mType = type;

    // 如果是方向光，则位置的 w 分量为 0
    if (type == LightType::Directional)
        mPosition.w = 0.0f;
    else
        mPosition.w = 1.0f;
}

void CGLight::setAmbient(const glm::vec4& color)
{
    mAmbient = color;
}

void CGLight::setDiffuse(const glm::vec4& color)
{
    mDiffuse = color;
}

void CGLight::setSpecular(const glm::vec4& color)
{
    mSpecular = color;
}

void CGLight::setPosition(const glm::vec3& position)
{
    mPosition = glm::vec4(position, mPosition.w);
}

void CGLight::setSpotDirection(const glm::vec3& direction)
{
    mSpotDirection = glm::normalize(direction);
}

void CGLight::setSpotCutoff(float degrees)
{
    mSpotCutoff = degrees;
}

void CGLight::setSpotExponent(float exponent)
{
    mSpotExponent = exponent;
}

void CGLight::setAttenuation(float constant, float linear, float quadratic)
{
    mAttenuationConstant = constant;
    mAttenuationLinear = linear;
    mAttenuationQuadratic = quadratic;
}

void CGLight::enable(int index)
{
    glEnable(GL_LIGHT0 + index);
    mEnabled = true;
}

void CGLight::disable(int index)
{
    glDisable(GL_LIGHT0 + index);
    mEnabled = false;
}

bool CGLight::isEnabled() const
{
    return mEnabled;
}

void CGLight::apply(int index)
{
    GLenum light = GL_LIGHT0 + index;

    glLightfv(light, GL_AMBIENT, &mAmbient[0]);
    glLightfv(light, GL_DIFFUSE, &mDiffuse[0]);
    glLightfv(light, GL_SPECULAR, &mSpecular[0]);
    glLightfv(light, GL_POSITION, &mPosition[0]);

    if (mType == LightType::Spot)
    {
        glLightfv(light, GL_SPOT_DIRECTION, &mSpotDirection[0]);
        glLightf(light, GL_SPOT_CUTOFF, mSpotCutoff);
        glLightf(light, GL_SPOT_EXPONENT, mSpotExponent);
    }
    else if (mType == LightType::Point)
    {
        glLightf(light, GL_CONSTANT_ATTENUATION, mAttenuationConstant);
        glLightf(light, GL_LINEAR_ATTENUATION, mAttenuationLinear);
        glLightf(light, GL_QUADRATIC_ATTENUATION, mAttenuationQuadratic);
    }
}