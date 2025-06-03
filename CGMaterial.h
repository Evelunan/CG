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
        // 设置启用颜色作为材质参数
        if (mColorMaterial != CM_AMBIENT_AND_DIFFUSE) {
            glEnable(GL_COLOR_MATERIAL);
            glColorMaterial(GL_FRONT_AND_BACK, static_cast<GLenum>(mColorMaterial));
        }
        else {
            glDisable(GL_COLOR_MATERIAL);
        }

        // 设置材质参数
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, &mEmission[0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &mAmbient[0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &mDiffuse[0]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &mSpecular[0]);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
    }

protected:
    glm::vec4 mEmission;   // 材质自发光强度
    glm::vec4 mAmbient;    // 材质环境光反射系数
    glm::vec4 mDiffuse;    // 材质漫反射系数
    glm::vec4 mSpecular;   // 材质镜面反射系数
    float mShininess;      // 材质光泽度
    EColorMaterial mColorMaterial; // 颜色作为哪种反射系数
};
