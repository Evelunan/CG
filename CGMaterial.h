#pragma once
#include "CGRenderState.h"

class CGMaterial : public CGRenderState {

public:
    CGMaterial();
    virtual ~CGMaterial() = default;

    virtual ERenderState type() const override { return RS_Material; }
    // 设置材质的自发光颜色（即使没有光照也会显示该颜色）
    void setEmission(const glm::vec4& emission);

    // 设置材质对环境光的反射颜色（影响物体在全局环境光下的基础亮度）
    void setAmbient(const glm::vec4& ambient);

    // 设置材质的漫反射颜色（决定物体在光照下的主要视觉颜色）
    void setDiffuse(const glm::vec4& diffuse);

    // 设置材质的镜面反射颜色（控制高光区域的颜色和强度）
    void setSpecular(const glm::vec4& specular);

    // 设置材质的光泽度（shininess），值越大高光越集中、越小越分散（范围 0~128）
    void setShininess(float shininess);

    // 设置是否启用颜色追踪材质模式（材质某些属性跟随 glColor 的变化）
    void setColorMaterial(EColorMaterial cm);

    const glm::vec4& emission() const;
    const glm::vec4& ambient() const;
    const glm::vec4& diffuse() const;
    const glm::vec4& specular() const;
    float shininess() const;
    EColorMaterial colorMaterial() const;

    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const override;

protected:
    glm::vec4 mEmission;
    glm::vec4 mAmbient;
    glm::vec4 mDiffuse;
    glm::vec4 mSpecular;
    float mShininess;
    EColorMaterial mColorMaterial;
};

namespace SceneMaterials {
    enum class MaterialType {
        Plastic,
        Metal,
        Wood,
        Ceramic // 陶瓷
    };

    inline CGMaterial CreateMaterialWithColor(const glm::vec4& color, MaterialType type) {
        CGMaterial mat;

        mat.setDiffuse(color);              // 设置主色（物体自身颜色）
        mat.setAmbient(color * 0.3f);       // 环境光弱反射色，可调节
        mat.setEmission(glm::vec4(0.0f));   // 默认无自发光
        mat.setColorMaterial(CM_None);      // 不使用 glColor 自动干扰

        switch (type) {
        case MaterialType::Plastic:
            mat.setSpecular(glm::vec4(0.3f));   // 轻微镜面高光
            mat.setShininess(32.0f);
            break;
        case MaterialType::Metal:
            mat.setSpecular(glm::vec4(0.8f));   // 明显金属反光
            mat.setShininess(96.0f);
            break;
        case MaterialType::Wood:
            mat.setSpecular(glm::vec4(0.1f));   // 木材较少高光
            mat.setShininess(8.0f);
            break;
        case MaterialType::Ceramic:
            mat.setSpecular(glm::vec4(0.5f));   // 柔和高光
            mat.setShininess(48.0f);
            break;
        }
        return mat;
    }
}
