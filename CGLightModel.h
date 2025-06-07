#pragma once
#include "CGRenderState.h"
class CGLightModel : public CGRenderState
{
public:
	CGLightModel();
	virtual ~CGLightModel() = default;
	virtual ERenderState type() const { return RS_LightModel; }
	virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const;
	void setLocalViewer(bool localviewer) { mLocalViewer = localviewer; }
	void setTwoSide(bool twoside) { mTwoSide = twoside; }
	void setAmbientColor(const glm::vec4& ambientcolor) { mAmbientColor = ambientcolor; }
	bool localViewer() const { return mLocalViewer; }
	bool twoSide() const { return mTwoSide; }
	const glm::vec4& ambientColor() const { return mAmbientColor; }
protected:
	glm::vec4 mAmbientColor;//全局环境光 
	bool mLocalViewer;      //无限远或局部观察（镜面反射角度的计算） 
	bool mTwoSide;          //双面光照

};


// 表示一个光源状态，可用于 OpenGL 固定管线光照系统
class CGLight : public CGRenderState
{
public:
    // 光源类型定义
    enum class LightType {
        Directional, // 平行光（方向光，位置向量的w为0）
        Point,       // 点光源（从一点向四周发散，位置向量的w为1）
        Spot         // 聚光灯（有方向和角度限制的点光源）
    };

    // 构造函数与析构函数
    CGLight();
    ~CGLight();

    // 设置光源类型
    void setType(LightType type);

    // 设置环境光成分
    void setAmbient(const glm::vec4& color);
    // 设置漫反射光成分
    void setDiffuse(const glm::vec4& color);
    // 设置镜面反射光成分
    void setSpecular(const glm::vec4& color);

    // 设置光源位置（w=0 为方向光，w=1 为点光或聚光灯）
    void setPosition(const glm::vec4& position);
    // 获取光源位置
    glm::vec4 Position() { return mPosition; };

    // 设置聚光灯方向
    void setSpotDirection(const glm::vec3& direction);
    // 设置聚光灯截止角度（[0, 90]，超过90视为点光源）
    void setSpotCutoff(float degrees);
    // 设置聚光灯的衰减指数（决定聚光灯聚焦程度）
    void setSpotExponent(float exponent);

    // 设置光源的衰减因子（常数项、线性项、二次项）
    void setAttenuation(float constant, float linear, float quadratic);

    // 启用或禁用光源
    void enable(bool enable);

    // 将光源属性应用到 OpenGL
    void apply() const;

    // 获取渲染状态类型（返回 RS_Light）
    virtual ERenderState type() const override { return RS_Light; }

    // 应用光源到指定渲染上下文（带摄像机和上下文信息）
    virtual void apply(const CGCamera*, CGRenderContext*, int) const override;

    // 获取光源编号（GL_LIGHT0 + index）
    int Index() const;
    // 设置光源编号
    void setIndex(int idx);

    // 获取当前光源类型
    LightType lightType() const;

private:
    int index = 0;                        // 光源编号（用于映射到 GL_LIGHT0 ~ GL_LIGHT7）
    LightType mType = LightType::Point;   // 当前光源类型

    glm::vec4 mAmbient;                  // 环境光成分
    glm::vec4 mDiffuse;                  // 漫反射光成分
    glm::vec4 mSpecular;                 // 镜面反射光成分

    glm::vec4 mPosition;                 // 光源位置（w=0方向光，w=1点光）
    glm::vec3 mSpotDirection;            // 聚光灯方向
    float mSpotCutoff;                   // 聚光灯的截锥角度（0~90）
    float mSpotExponent;                 // 聚光灯指数，决定光线分布集中程度

    float mAttenuationConstant;          // 衰减因子常数项
    float mAttenuationLinear;            // 衰减因子线性项
    float mAttenuationQuadratic;         // 衰减因子二次项

    bool mEnabled;                       // 是否启用光源
};

namespace SceneLights {

    inline CGLight DirectionalLight = [] {
        CGLight light;
        light.setType(CGLight::LightType::Directional);
        light.setPosition(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)); // w = 0 表示方向
        light.setAmbient(glm::vec4(0.2f));
        light.setDiffuse(glm::vec4(0.8f));
        light.setSpecular(glm::vec4(1.0f));
        light.setIndex(0);
        return light;
        }();

    inline CGLight PointLight = [] {
        CGLight light;
        light.setType(CGLight::LightType::Point);
        light.setPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)); // w = 1 表示位置
        light.setAmbient(glm::vec4(0.1f));
        light.setDiffuse(glm::vec4(0.9f));
        light.setSpecular(glm::vec4(1.0f));
        light.setAttenuation(1.0f, 0.0f, 0.0f);
        light.setIndex(1);
        return light;
        }();

    inline CGLight SpotLight = [] {
        CGLight light;
        light.setType(CGLight::LightType::Spot);
        light.setPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        light.setSpotDirection(glm::vec3(0.0f, -1.0f, -1.0f));
        light.setSpotCutoff(60.0f);
        light.setSpotExponent(16.0f);
        light.setAmbient(glm::vec4(0.05f));
        light.setDiffuse(glm::vec4(0.9f));
        light.setSpecular(glm::vec4(1.0f));
        light.setAttenuation(1.0f, 0.0f, 0.0f);
        light.setIndex(2);
        return light;
        }();
    //CGLightModel mode;
}
