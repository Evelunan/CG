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

    // 静态常量材质
    static const CGMaterial Metallic;
    static const CGMaterial PlasticGreen;
    static const CGMaterial Wood;
    static const CGMaterial Glass;
    static const CGMaterial Default;

protected:
    glm::vec4 mEmission;
    glm::vec4 mAmbient;
    glm::vec4 mDiffuse;
    glm::vec4 mSpecular;
    float mShininess;
    EColorMaterial mColorMaterial;
};