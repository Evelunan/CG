#include "pch.h"
#include "CGMaterial.h"

// Ĭ�Ϲ��캯��
CGMaterial::CGMaterial()
    : mEmission(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
    , mAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
    , mDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f))
    , mSpecular(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
    , mShininess(0.0f)
    , mColorMaterial(CM_AMBIENT_AND_DIFFUSE)
{
}

// ���÷���
void CGMaterial::setEmission(const glm::vec4& emission) { mEmission = emission; }
void CGMaterial::setAmbient(const glm::vec4& ambient) { mAmbient = ambient; }
void CGMaterial::setDiffuse(const glm::vec4& diffuse) { mDiffuse = diffuse; }
void CGMaterial::setSpecular(const glm::vec4& specular) { mSpecular = specular; }
void CGMaterial::setShininess(float shininess) { mShininess = shininess; }
void CGMaterial::setColorMaterial(EColorMaterial cm) { mColorMaterial = cm; }

// ��ȡ����
const glm::vec4& CGMaterial::emission() const { return mEmission; }
const glm::vec4& CGMaterial::ambient() const { return mAmbient; }
const glm::vec4& CGMaterial::diffuse() const { return mDiffuse; }
const glm::vec4& CGMaterial::specular() const { return mSpecular; }
float CGMaterial::shininess() const { return mShininess; }
EColorMaterial CGMaterial::colorMaterial() const { return mColorMaterial; }

// Ӧ�ò��ʵ� OpenGL
void CGMaterial::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const {
    // ���û������ɫ����׷��
    if (mColorMaterial != CM_None) {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, static_cast<GLenum>(mColorMaterial));
    }
    else {
        glDisable(GL_COLOR_MATERIAL);
    }

    // ���ù̶����߲�������
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(mEmission));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(mAmbient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(mDiffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(mSpecular));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
}
