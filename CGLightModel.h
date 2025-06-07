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


// ��ʾһ����Դ״̬�������� OpenGL �̶����߹���ϵͳ
class CGLight : public CGRenderState
{
public:
    // ��Դ���Ͷ���
    enum class LightType {
        Directional, // ƽ�й⣨����⣬λ��������wΪ0��
        Point,       // ���Դ����һ�������ܷ�ɢ��λ��������wΪ1��
        Spot         // �۹�ƣ��з���ͽǶ����Ƶĵ��Դ��
    };

    // ���캯������������
    CGLight();
    ~CGLight();

    // ���ù�Դ����
    void setType(LightType type);

    // ���û�����ɷ�
    void setAmbient(const glm::vec4& color);
    // �����������ɷ�
    void setDiffuse(const glm::vec4& color);
    // ���þ��淴���ɷ�
    void setSpecular(const glm::vec4& color);

    // ���ù�Դλ�ã�w=0 Ϊ����⣬w=1 Ϊ����۹�ƣ�
    void setPosition(const glm::vec4& position);
    // ��ȡ��Դλ��
    glm::vec4 Position() { return mPosition; };

    // ���þ۹�Ʒ���
    void setSpotDirection(const glm::vec3& direction);
    // ���þ۹�ƽ�ֹ�Ƕȣ�[0, 90]������90��Ϊ���Դ��
    void setSpotCutoff(float degrees);
    // ���þ۹�Ƶ�˥��ָ���������۹�ƾ۽��̶ȣ�
    void setSpotExponent(float exponent);

    // ���ù�Դ��˥�����ӣ����������������
    void setAttenuation(float constant, float linear, float quadratic);

    // ���û���ù�Դ
    void enable(bool enable);

    // ����Դ����Ӧ�õ� OpenGL
    void apply() const;

    // ��ȡ��Ⱦ״̬���ͣ����� RS_Light��
    virtual ERenderState type() const override { return RS_Light; }

    // Ӧ�ù�Դ��ָ����Ⱦ�����ģ������������������Ϣ��
    virtual void apply(const CGCamera*, CGRenderContext*, int) const override;

    // ��ȡ��Դ��ţ�GL_LIGHT0 + index��
    int Index() const;
    // ���ù�Դ���
    void setIndex(int idx);

    // ��ȡ��ǰ��Դ����
    LightType lightType() const;

private:
    int index = 0;                        // ��Դ��ţ�����ӳ�䵽 GL_LIGHT0 ~ GL_LIGHT7��
    LightType mType = LightType::Point;   // ��ǰ��Դ����

    glm::vec4 mAmbient;                  // ������ɷ�
    glm::vec4 mDiffuse;                  // �������ɷ�
    glm::vec4 mSpecular;                 // ���淴���ɷ�

    glm::vec4 mPosition;                 // ��Դλ�ã�w=0����⣬w=1��⣩
    glm::vec3 mSpotDirection;            // �۹�Ʒ���
    float mSpotCutoff;                   // �۹�ƵĽ�׶�Ƕȣ�0~90��
    float mSpotExponent;                 // �۹��ָ�����������߷ֲ����г̶�

    float mAttenuationConstant;          // ˥�����ӳ�����
    float mAttenuationLinear;            // ˥������������
    float mAttenuationQuadratic;         // ˥�����Ӷ�����

    bool mEnabled;                       // �Ƿ����ù�Դ
};

namespace SceneLights {

    inline CGLight DirectionalLight = [] {
        CGLight light;
        light.setType(CGLight::LightType::Directional);
        light.setPosition(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)); // w = 0 ��ʾ����
        light.setAmbient(glm::vec4(0.2f));
        light.setDiffuse(glm::vec4(0.8f));
        light.setSpecular(glm::vec4(1.0f));
        light.setIndex(0);
        return light;
        }();

    inline CGLight PointLight = [] {
        CGLight light;
        light.setType(CGLight::LightType::Point);
        light.setPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)); // w = 1 ��ʾλ��
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
