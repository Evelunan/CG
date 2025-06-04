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
	glm::vec4 mAmbientColor;//ȫ�ֻ����� 
	bool mLocalViewer;      //����Զ��ֲ��۲죨���淴��Ƕȵļ��㣩 
	bool mTwoSide;          //˫�����

};


class CGLight
{
public:
    enum class LightType {
        Directional, // ����⣬ƽ�й�
        Point,       // ���Դ
        Spot         // �۹��
    };

public:
    CGLight();
    ~CGLight();

    // ���ù�Դ����
    void setType(LightType type);

    // ���Ƶ��ǻ����⣨ȫ��������
    void setAmbient(const glm::vec4& color);
    // ���Ƶ�����������ɫ���������屾ɫ��
    void setDiffuse(const glm::vec4& color);
    // ���Ƶ��Ǹ߹���ɫ�����ֲ��ʹ⻬�ȣ�
    void setSpecular(const glm::vec4& color);

    // ���ù�Դλ�ã������ʱ w=0��
    void setPosition(const glm::vec3& position);

    // ���þ۹����
    void setSpotDirection(const glm::vec3& direction);
    void setSpotCutoff(float degrees);     // ��ɢ�ǣ�0~90 �� 180��
    void setSpotExponent(float exponent);  // �۹�ָ����0~128��

    // ���ù�Դ˥��ϵ��
    void setAttenuation(float constant, float linear, float quadratic);

    // ����/���øù�Դ��index: 0~7��
    void enable(int index);
    void disable(int index);

    // ��ȡ��ǰ����״̬
    bool isEnabled() const;

    // Ӧ�ù�Դ���õ� OpenGL������ glLightfv��
    void apply(int index);

private:
    LightType mType = LightType::Point;

    glm::vec4 mAmbient  = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 mDiffuse  = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 mSpecular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec4 mPosition = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); // Ĭ���� z ��ǰ��
    glm::vec3 mSpotDirection = glm::vec3(0.0f, 0.0f, -1.0f); // Ĭ��ָ�� z ����
    float mSpotCutoff   = 180.0f; // Ĭ�ϲ��Ǿ۹��
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
        light.setPosition(glm::vec3(0.0f, 0.0f, 0.0f)); // �����λ����Ч
        return light;
        }();

    inline static const CGLight Directional = []() {
        CGLight light;
        light.setType(CGLight::LightType::Directional);
        light.setAmbient(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        light.setDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
        light.setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        light.setPosition(glm::vec3(0.0f, 0.0f, 1000.0f)); // ������������
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