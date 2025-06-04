#include "pch.h"
#include "CGMaterial.h"

// 默认构造函数
CGMaterial::CGMaterial()
    : mEmission(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
    , mAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
    , mDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f))
    , mSpecular(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
    , mShininess(0.0f)
    , mColorMaterial(CM_AMBIENT_AND_DIFFUSE)
{
}

// 设置方法
void CGMaterial::setEmission(const glm::vec4& emission) { mEmission = emission; }
void CGMaterial::setAmbient(const glm::vec4& ambient) { mAmbient = ambient; }
void CGMaterial::setDiffuse(const glm::vec4& diffuse) { mDiffuse = diffuse; }
void CGMaterial::setSpecular(const glm::vec4& specular) { mSpecular = specular; }
void CGMaterial::setShininess(float shininess) { mShininess = shininess; }
void CGMaterial::setColorMaterial(EColorMaterial cm) { mColorMaterial = cm; }

// 获取方法
const glm::vec4& CGMaterial::emission() const { return mEmission; }
const glm::vec4& CGMaterial::ambient() const { return mAmbient; }
const glm::vec4& CGMaterial::diffuse() const { return mDiffuse; }
const glm::vec4& CGMaterial::specular() const { return mSpecular; }
float CGMaterial::shininess() const { return mShininess; }
EColorMaterial CGMaterial::colorMaterial() const { return mColorMaterial; }

// 应用材质到 OpenGL
void CGMaterial::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const {
    if (mColorMaterial != CM_AMBIENT_AND_DIFFUSE) {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, static_cast<GLenum>(mColorMaterial));
    }
    else {
        glDisable(GL_COLOR_MATERIAL);
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &mEmission[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &mAmbient[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &mDiffuse[0]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &mSpecular[0]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
}

// 定义静态常量材质

const CGMaterial CGMaterial::Default = CGMaterial();
// 金属
const CGMaterial CGMaterial::Metallic = []() {
    CGMaterial mat;
    mat.setAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    mat.setDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    mat.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    mat.setShininess(64.0f);
    return mat;
    }();
// 塑料
const CGMaterial CGMaterial::PlasticGreen = []() {
    CGMaterial mat;
    mat.setAmbient(glm::vec4(0.0f, 0.1f, 0.06f, 1.0f));
    mat.setDiffuse(glm::vec4(0.0f, 0.50980392f, 0.50980392f, 1.0f));
    mat.setSpecular(glm::vec4(0.50196078f, 0.50196078f, 0.50196078f, 1.0f));
    mat.setShininess(32.0f);
    return mat;
    }();
// 木材
const CGMaterial CGMaterial::Wood = []() {
    CGMaterial mat;
    mat.setAmbient(glm::vec4(0.3f, 0.15f, 0.1f, 1.0f));
    mat.setDiffuse(glm::vec4(0.4f, 0.25f, 0.2f, 1.0f));
    mat.setSpecular(glm::vec4(0.3f, 0.2f, 0.15f, 1.0f));
    mat.setShininess(10.0f);
    return mat;
    }();
// 玻璃
const CGMaterial CGMaterial::Glass = []() {
    CGMaterial mat;
    mat.setAmbient(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mat.setDiffuse(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    mat.setSpecular(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    mat.setShininess(128.0f);
    return mat;
    }();