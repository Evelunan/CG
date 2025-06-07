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


CGLight::CGLight()
    : mAmbient(0.0f, 0.0f, 0.0f, 1.0f),
    mDiffuse(1.0f, 1.0f, 1.0f, 1.0f),
    mSpecular(1.0f, 1.0f, 1.0f, 1.0f),
    mPosition(0.0f, 0.0f, 1.0f, 1.0f),
    mSpotDirection(0.0f, 0.0f, -1.0f),
    mSpotCutoff(180.0f),
    mSpotExponent(0.0f),
    mAttenuationConstant(1.0f),
    mAttenuationLinear(0.0f),
    mAttenuationQuadratic(0.0f),
    mEnabled(true),
    mType(LightType::Point),
    index(0)
{
}

CGLight::~CGLight() {}

void CGLight::setType(LightType type) {
    mType = type;
}

void CGLight::setAmbient(const glm::vec4& color) {
    mAmbient = color;
}

void CGLight::setDiffuse(const glm::vec4& color) {
    mDiffuse = color;
}

void CGLight::setSpecular(const glm::vec4& color) {
    mSpecular = color;
}

void CGLight::setPosition(const glm::vec4& position) {
    mPosition = position;
}

void CGLight::setSpotDirection(const glm::vec3& direction) {
    mSpotDirection = direction;
}

void CGLight::setSpotCutoff(float degrees) {
    mSpotCutoff = degrees;
}

void CGLight::setSpotExponent(float exponent) {
    mSpotExponent = exponent;
}

void CGLight::setAttenuation(float constant, float linear, float quadratic) {
    mAttenuationConstant = constant;
    mAttenuationLinear = linear;
    mAttenuationQuadratic = quadratic;
}

void CGLight::enable(bool enable) {
    mEnabled = enable;
}

void CGLight::apply(const CGCamera*, CGRenderContext*, int) const
{
    apply();
}

int CGLight::Index() const {
    return index;
}

void CGLight::setIndex(int idx) {
    index = idx;
}

CGLight::LightType CGLight::lightType() const {
    return mType;
}

void CGLight::apply() const
{
    if (index < 0 || index > 7) return;

    GLenum lightEnum = GL_LIGHT0 + index;

    if (mEnabled)
        glEnable(lightEnum);
    else {
        glDisable(lightEnum);
        return;
    }

    glLightfv(lightEnum, GL_AMBIENT, &mAmbient[0]);
    glLightfv(lightEnum, GL_DIFFUSE, &mDiffuse[0]);
    glLightfv(lightEnum, GL_SPECULAR, &mSpecular[0]);

    glm::vec4 pos = mPosition;
    pos.w = (mType == LightType::Directional) ? 0.0f : 1.0f;
    glLightfv(lightEnum, GL_POSITION, &pos[0]);

    if (mType == LightType::Spot) {
        glLightfv(lightEnum, GL_SPOT_DIRECTION, &mSpotDirection[0]);
        glLightf(lightEnum, GL_SPOT_CUTOFF, mSpotCutoff);
        glLightf(lightEnum, GL_SPOT_EXPONENT, mSpotExponent);
    }
    else {
        glLightf(lightEnum, GL_SPOT_CUTOFF, 180.0f); // 禁用聚光参数
    }

    glLightf(lightEnum, GL_CONSTANT_ATTENUATION, mAttenuationConstant);
    glLightf(lightEnum, GL_LINEAR_ATTENUATION, mAttenuationLinear);
    glLightf(lightEnum, GL_QUADRATIC_ATTENUATION, mAttenuationQuadratic);
}
