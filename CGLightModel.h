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


class CGLight
{
public:
    enum class LightType {
        Directional, // 方向光，平行光
        Point,       // 点光源
        Spot         // 聚光灯
    };

public:
    CGLight();
    ~CGLight();

    // 设置光源类型
    void setType(LightType type);

    // 控制的是环境光（全局照亮）
    void setAmbient(const glm::vec4& color);
    // 控制的是主光照颜色（决定物体本色）
    void setDiffuse(const glm::vec4& color);
    // 控制的是高光颜色（体现材质光滑度）
    void setSpecular(const glm::vec4& color);

    // 设置光源位置（方向光时 w=0）
    void setPosition(const glm::vec3& position);

    // 设置聚光参数
    void setSpotDirection(const glm::vec3& direction);
    void setSpotCutoff(float degrees);     // 发散角（0~90 或 180）
    void setSpotExponent(float exponent);  // 聚光指数（0~128）

    // 设置光源衰减系数
    void setAttenuation(float constant, float linear, float quadratic);

    // 启用/禁用该光源（index: 0~7）
    void enable(int index);
    void disable(int index);

    // 获取当前启用状态
    bool isEnabled() const;

    // 应用光源设置到 OpenGL（调用 glLightfv）
    void apply(int index);

private:
    LightType mType = LightType::Point;

    glm::vec4 mAmbient  = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 mDiffuse  = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 mSpecular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec4 mPosition = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); // 默认在 z 轴前方
    glm::vec3 mSpotDirection = glm::vec3(0.0f, 0.0f, -1.0f); // 默认指向负 z 方向
    float mSpotCutoff   = 180.0f; // 默认不是聚光灯
    float mSpotExponent = 0.0f;

    float mAttenuationConstant  = 1.0f;
    float mAttenuationLinear    = 0.0f;
    float mAttenuationQuadratic = 0.0f;

    bool mEnabled = false;
};

namespace LightPresets {

    inline static const CGLight GlobalAmbient = []() {
        CGLight light;
        light.setType(CGLight::LightType::Directional);
        light.setAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
        light.setDiffuse(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        light.setSpecular(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        light.setPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // 方向光位置无效
        return light;
        }();

    inline static const CGLight Directional = []() {
        CGLight light;
        light.setType(CGLight::LightType::Directional);
        light.setAmbient(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        light.setDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        light.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        light.setPosition(glm::vec3(0.0f, 0.0f, 1000.0f)); // 从上往下照射
        return light;
        }();

    inline static const CGLight PointLight = []() {
        CGLight light;
        light.setType(CGLight::LightType::Point);
        light.setAmbient(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        light.setDiffuse(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        light.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        light.setPosition(glm::vec3(0.0f, 0.0f, 1000.0f));
        light.setAttenuation(1.0f, 0.09f, 0.032f);
        return light;
        }();

    inline static const CGLight SpotLight = []() {
        CGLight light;
        light.setType(CGLight::LightType::Spot);
        light.setAmbient(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        light.setDiffuse(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        light.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        light.setPosition(glm::vec3(0.0f, 0.0f, 1000.0f));
        light.setSpotDirection(glm::vec3(0.0f, -1.0f, 0.0f));
        light.setSpotCutoff(30.0f);
        light.setSpotExponent(64.0f);
        light.setAttenuation(1.0f, 0.09f, 0.032f);
        return light;
        }();

} // namespace LightPresets