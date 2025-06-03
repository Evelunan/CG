#pragma once
#include "CGRenderState.h"

class CGMaterial : public CGRenderState {
public:
    CGMaterial()
        : mEmission(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
        , mAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
        , mDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f))
        , mSpecular(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
        , mShininess(0.0f)
        , mColorMaterial(CM_AMBIENT_AND_DIFFUSE)
    {
    }

    virtual ~CGMaterial() = default;

    virtual ERenderState type() const override { return RS_Material; }

    void setEmission(const glm::vec4& emission) { mEmission = emission; }
    void setAmbient(const glm::vec4& ambient) { mAmbient = ambient; }
    void setDiffuse(const glm::vec4& diffuse) { mDiffuse = diffuse; }
    void setSpecular(const glm::vec4& specular) { mSpecular = specular; }
    void setShininess(float shininess) { mShininess = shininess; }
    void setColorMaterial(EColorMaterial cm) { mColorMaterial = cm; }

    const glm::vec4& emission() const { return mEmission; }
    const glm::vec4& ambient() const { return mAmbient; }
    const glm::vec4& diffuse() const { return mDiffuse; }
    const glm::vec4& specular() const { return mSpecular; }
    float shininess() const { return mShininess; }
    EColorMaterial colorMaterial() const { return mColorMaterial; }

    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const override {
        // ����������ɫ��Ϊ���ʲ���
        if (mColorMaterial != CM_AMBIENT_AND_DIFFUSE) {
            glEnable(GL_COLOR_MATERIAL);
            glColorMaterial(GL_FRONT_AND_BACK, static_cast<GLenum>(mColorMaterial));
        }
        else {
            glDisable(GL_COLOR_MATERIAL);
        }

        // ���ò��ʲ���
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &mEmission[0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &mAmbient[0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &mDiffuse[0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &mSpecular[0]);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    }

protected:
    glm::vec4 mEmission;   // �����Է���ǿ��
    glm::vec4 mAmbient;    // ���ʻ����ⷴ��ϵ��
    glm::vec4 mDiffuse;    // ����������ϵ��
    glm::vec4 mSpecular;   // ���ʾ��淴��ϵ��
    float mShininess;      // ���ʹ����
    EColorMaterial mColorMaterial; // ��ɫ��Ϊ���ַ���ϵ��
};
