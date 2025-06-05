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
        Directional, // 平行光
        Point,       // 点光源
        Spot         // 聚光灯
    };

    CGLight();
    ~CGLight();

    void setType(LightType type);

    void setAmbient(const glm::vec4& color);
    void setDiffuse(const glm::vec4& color);
    void setSpecular(const glm::vec4& color);

    void setPosition(const glm::vec4& position);

    void setSpotDirection(const glm::vec3& direction);
    void setSpotCutoff(float degrees);
    void setSpotExponent(float exponent);

    void setAttenuation(float constant, float linear, float quadratic);

    void enable(bool enable);
    void apply();

    int Index() const;
    void setIndex(int idx);

    LightType type() const;

private:
    int index = 0;
    LightType mType = LightType::Point;

    glm::vec4 mAmbient;
    glm::vec4 mDiffuse;
    glm::vec4 mSpecular;

    glm::vec4 mPosition;
    glm::vec3 mSpotDirection;
    float mSpotCutoff;
    float mSpotExponent;

    float mAttenuationConstant;
    float mAttenuationLinear;
    float mAttenuationQuadratic;

    bool mEnabled;
};

namespace SceneLights {

    inline CGLight DirectionalLight = [] {
        CGLight light;
        light.setType(CGLight::LightType::Directional);
        //light.setPosition(glm::vec4(-1.0f, -1.0f, -1.0f, 0.0f)); // w = 0 表示方向
        light.setAmbient(glm::vec4(0.2f));
        light.setDiffuse(glm::vec4(0.8f));
        light.setSpecular(glm::vec4(1.0f));
        light.setIndex(0);
        return light;
        }();

    inline CGLight PointLight = [] {
        CGLight light;
        light.setType(CGLight::LightType::Point);
        //light.setPosition(glm::vec4(0.0f, 3.0f, 0.0f, 1.0f)); // w = 1 表示位置
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
        //light.setPosition(glm::vec4(0.0f, 5.0f, 5.0f, 1.0f));
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

}
