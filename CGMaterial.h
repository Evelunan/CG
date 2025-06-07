#pragma once
#include "CGRenderState.h"

// CGMaterial 表示材质状态，包含影响物体表面光照效果的各类属性
class CGMaterial : public CGRenderState {
public:
    CGMaterial();
    virtual ~CGMaterial() = default;

    // 返回渲染状态类型：材质
    virtual ERenderState type() const override { return RS_Material; }

    // 设置自发光颜色（即使没有光源也能看到的颜色，类似“发光体”）
    void setEmission(const glm::vec4& emission);

    // 设置环境光反射颜色（影响在全局光下的表现，通常较暗）
    void setAmbient(const glm::vec4& ambient);

    // 设置漫反射颜色（物体在受到光照后表现出的基本颜色）
    void setDiffuse(const glm::vec4& diffuse);

    // 设置镜面反射颜色（用于表现高光效果）
    void setSpecular(const glm::vec4& specular);

    // 设置材质的光泽度（越高越锐利集中的高光，范围 [0, 128]）
    void setShininess(float shininess);

    // 设置颜色材质追踪模式（开启时允许材质属性追踪 glColor）
    void setColorMaterial(EColorMaterial cm);

    // 获取自发光颜色
    const glm::vec4& emission() const;
    // 获取环境光反射颜色
    const glm::vec4& ambient() const;
    // 获取漫反射颜色
    const glm::vec4& diffuse() const;
    // 获取镜面反射颜色
    const glm::vec4& specular() const;
    // 获取光泽度
    float shininess() const;
    // 获取颜色材质追踪模式
    EColorMaterial colorMaterial() const;

    // 将材质应用到当前渲染上下文（绑定到 OpenGL 状态）
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const override;

protected:
    glm::vec4 mEmission;        // 自发光颜色
    glm::vec4 mAmbient;         // 环境光反射颜色
    glm::vec4 mDiffuse;         // 漫反射颜色
    glm::vec4 mSpecular;        // 镜面反射颜色
    float mShininess;           // 高光系数（0~128）
    EColorMaterial mColorMaterial; // 颜色追踪材质设置（如 GL_AMBIENT_AND_DIFFUSE）
};

// 常见材质类型的预设枚举
enum class MaterialPreset {
    Wood_Light,       // 浅色木材
    Wood_Dark,        // 深色木材
    Plastic_Red,      // 红色塑料
    Plastic_Black,    // 黑色塑料
    Metal_Gold,       // 金属 - 金
    Metal_Silver,     // 金属 - 银
    Metal_Copper,     // 金属 - 铜
    Ceramic_White,    // 陶瓷 - 白色
    Rubber_Black,     // 黑色橡胶
    Glass_Clear,      // 透明玻璃
        

    COUNT             // 计算枚举个数       
};
// 根据给定的材质预设类型，返回一个设置好属性的 CGMaterial 实例
inline CGMaterial CreateMaterial(MaterialPreset preset) {
    CGMaterial mat;

    // 默认关闭颜色材质跟踪
    mat.setColorMaterial(CM_None);

    // 默认不设置自发光
    mat.setEmission(glm::vec4(0.0f));

    switch (preset) {
    case MaterialPreset::Wood_Light:
        // 浅色木材 - 带有自然的暖色调，漫反射为主
        mat.setDiffuse(glm::vec4(0.8f, 0.6f, 0.4f, 1.0f));
        mat.setAmbient(glm::vec4(0.3f, 0.2f, 0.15f, 1.0f));
        mat.setSpecular(glm::vec4(0.1f)); // 木材不怎么反光
        mat.setShininess(8.0f);
        break;

    case MaterialPreset::Wood_Dark:
        // 深色木材 - 更沉稳的颜色，弱高光
        mat.setDiffuse(glm::vec4(0.4f, 0.25f, 0.1f, 1.0f));
        mat.setAmbient(glm::vec4(0.15f, 0.1f, 0.05f, 1.0f));
        mat.setSpecular(glm::vec4(0.05f));
        mat.setShininess(4.0f);
        break;

    case MaterialPreset::Plastic_Red:
        // 红色塑料 - 明亮、轻微高光
        mat.setDiffuse(glm::vec4(0.8f, 0.1f, 0.1f, 1.0f));
        mat.setAmbient(glm::vec4(0.2f, 0.05f, 0.05f, 1.0f));
        mat.setSpecular(glm::vec4(0.3f));
        mat.setShininess(32.0f);
        break;

    case MaterialPreset::Plastic_Black:
        // 黑色塑料 - 显得沉稳但仍有少量镜面反射
        mat.setDiffuse(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        mat.setAmbient(glm::vec4(0.05f));
        mat.setSpecular(glm::vec4(0.2f));
        mat.setShininess(16.0f);
        break;

    case MaterialPreset::Metal_Gold:
        // 金属 - 金色：高反射率，强高光
        mat.setDiffuse(glm::vec4(0.75f, 0.6f, 0.1f, 1.0f));
        mat.setAmbient(glm::vec4(0.25f, 0.2f, 0.05f, 1.0f));
        mat.setSpecular(glm::vec4(1.0f, 0.9f, 0.3f, 1.0f));
        mat.setShininess(96.0f);
        break;

    case MaterialPreset::Metal_Silver:
        // 金属 - 银色：均衡的中性灰亮度
        mat.setDiffuse(glm::vec4(0.7f));
        mat.setAmbient(glm::vec4(0.3f));
        mat.setSpecular(glm::vec4(0.9f));
        mat.setShininess(100.0f);
        break;

    case MaterialPreset::Metal_Copper:
        // 金属 - 铜色：偏暖色调的金属
        mat.setDiffuse(glm::vec4(0.7f, 0.4f, 0.2f, 1.0f));
        mat.setAmbient(glm::vec4(0.25f, 0.15f, 0.1f, 1.0f));
        mat.setSpecular(glm::vec4(0.8f, 0.5f, 0.3f, 1.0f));
        mat.setShininess(76.8f);
        break;

    case MaterialPreset::Ceramic_White:
        // 白色陶瓷 - 漫反射为主，中等高光
        mat.setDiffuse(glm::vec4(0.95f));
        mat.setAmbient(glm::vec4(0.3f));
        mat.setSpecular(glm::vec4(0.5f));
        mat.setShininess(40.0f);
        break;

    case MaterialPreset::Rubber_Black:
        // 黑色橡胶 - 几乎无镜面反射，非常哑光
        mat.setDiffuse(glm::vec4(0.01f));
        mat.setAmbient(glm::vec4(0.02f));
        mat.setSpecular(glm::vec4(0.02f));
        mat.setShininess(2.0f);
        break;

    case MaterialPreset::Glass_Clear:
        // 透明玻璃 - 高光强，alpha透明度小
        mat.setDiffuse(glm::vec4(0.2f, 0.2f, 0.25f, 0.3f)); // 半透明
        mat.setAmbient(glm::vec4(0.1f));
        mat.setSpecular(glm::vec4(0.9f));
        mat.setShininess(100.0f);
        break;
    }
    return mat;
}

