#pragma once
#include "CGRenderState.h"

// CGMaterial ��ʾ����״̬������Ӱ������������Ч���ĸ�������
class CGMaterial : public CGRenderState {
public:
    CGMaterial();
    virtual ~CGMaterial() = default;

    // ������Ⱦ״̬���ͣ�����
    virtual ERenderState type() const override { return RS_Material; }

    // �����Է�����ɫ����ʹû�й�ԴҲ�ܿ�������ɫ�����ơ������塱��
    void setEmission(const glm::vec4& emission);

    // ���û����ⷴ����ɫ��Ӱ����ȫ�ֹ��µı��֣�ͨ���ϰ���
    void setAmbient(const glm::vec4& ambient);

    // ������������ɫ���������ܵ����պ���ֳ��Ļ�����ɫ��
    void setDiffuse(const glm::vec4& diffuse);

    // ���þ��淴����ɫ�����ڱ��ָ߹�Ч����
    void setSpecular(const glm::vec4& specular);

    // ���ò��ʵĹ���ȣ�Խ��Խ�������еĸ߹⣬��Χ [0, 128]��
    void setShininess(float shininess);

    // ������ɫ����׷��ģʽ������ʱ�����������׷�� glColor��
    void setColorMaterial(EColorMaterial cm);

    // ��ȡ�Է�����ɫ
    const glm::vec4& emission() const;
    // ��ȡ�����ⷴ����ɫ
    const glm::vec4& ambient() const;
    // ��ȡ��������ɫ
    const glm::vec4& diffuse() const;
    // ��ȡ���淴����ɫ
    const glm::vec4& specular() const;
    // ��ȡ�����
    float shininess() const;
    // ��ȡ��ɫ����׷��ģʽ
    EColorMaterial colorMaterial() const;

    // ������Ӧ�õ���ǰ��Ⱦ�����ģ��󶨵� OpenGL ״̬��
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const override;

protected:
    glm::vec4 mEmission;        // �Է�����ɫ
    glm::vec4 mAmbient;         // �����ⷴ����ɫ
    glm::vec4 mDiffuse;         // ��������ɫ
    glm::vec4 mSpecular;        // ���淴����ɫ
    float mShininess;           // �߹�ϵ����0~128��
    EColorMaterial mColorMaterial; // ��ɫ׷�ٲ������ã��� GL_AMBIENT_AND_DIFFUSE��
};

// �����������͵�Ԥ��ö��
enum class MaterialPreset {
    Wood_Light,       // ǳɫľ��
    Wood_Dark,        // ��ɫľ��
    Plastic_Red,      // ��ɫ����
    Plastic_Black,    // ��ɫ����
    Metal_Gold,       // ���� - ��
    Metal_Silver,     // ���� - ��
    Metal_Copper,     // ���� - ͭ
    Ceramic_White,    // �մ� - ��ɫ
    Rubber_Black,     // ��ɫ��
    Glass_Clear,      // ͸������
        

    COUNT             // ����ö�ٸ���       
};
// ���ݸ����Ĳ���Ԥ�����ͣ�����һ�����ú����Ե� CGMaterial ʵ��
inline CGMaterial CreateMaterial(MaterialPreset preset) {
    CGMaterial mat;

    // Ĭ�Ϲر���ɫ���ʸ���
    mat.setColorMaterial(CM_None);

    // Ĭ�ϲ������Է���
    mat.setEmission(glm::vec4(0.0f));

    switch (preset) {
    case MaterialPreset::Wood_Light:
        // ǳɫľ�� - ������Ȼ��ůɫ����������Ϊ��
        mat.setDiffuse(glm::vec4(0.8f, 0.6f, 0.4f, 1.0f));
        mat.setAmbient(glm::vec4(0.3f, 0.2f, 0.15f, 1.0f));
        mat.setSpecular(glm::vec4(0.1f)); // ľ�Ĳ���ô����
        mat.setShininess(8.0f);
        break;

    case MaterialPreset::Wood_Dark:
        // ��ɫľ�� - �����ȵ���ɫ�����߹�
        mat.setDiffuse(glm::vec4(0.4f, 0.25f, 0.1f, 1.0f));
        mat.setAmbient(glm::vec4(0.15f, 0.1f, 0.05f, 1.0f));
        mat.setSpecular(glm::vec4(0.05f));
        mat.setShininess(4.0f);
        break;

    case MaterialPreset::Plastic_Red:
        // ��ɫ���� - ��������΢�߹�
        mat.setDiffuse(glm::vec4(0.8f, 0.1f, 0.1f, 1.0f));
        mat.setAmbient(glm::vec4(0.2f, 0.05f, 0.05f, 1.0f));
        mat.setSpecular(glm::vec4(0.3f));
        mat.setShininess(32.0f);
        break;

    case MaterialPreset::Plastic_Black:
        // ��ɫ���� - �Եó��ȵ������������淴��
        mat.setDiffuse(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
        mat.setAmbient(glm::vec4(0.05f));
        mat.setSpecular(glm::vec4(0.2f));
        mat.setShininess(16.0f);
        break;

    case MaterialPreset::Metal_Gold:
        // ���� - ��ɫ���߷����ʣ�ǿ�߹�
        mat.setDiffuse(glm::vec4(0.75f, 0.6f, 0.1f, 1.0f));
        mat.setAmbient(glm::vec4(0.25f, 0.2f, 0.05f, 1.0f));
        mat.setSpecular(glm::vec4(1.0f, 0.9f, 0.3f, 1.0f));
        mat.setShininess(96.0f);
        break;

    case MaterialPreset::Metal_Silver:
        // ���� - ��ɫ����������Ի�����
        mat.setDiffuse(glm::vec4(0.7f));
        mat.setAmbient(glm::vec4(0.3f));
        mat.setSpecular(glm::vec4(0.9f));
        mat.setShininess(100.0f);
        break;

    case MaterialPreset::Metal_Copper:
        // ���� - ͭɫ��ƫůɫ���Ľ���
        mat.setDiffuse(glm::vec4(0.7f, 0.4f, 0.2f, 1.0f));
        mat.setAmbient(glm::vec4(0.25f, 0.15f, 0.1f, 1.0f));
        mat.setSpecular(glm::vec4(0.8f, 0.5f, 0.3f, 1.0f));
        mat.setShininess(76.8f);
        break;

    case MaterialPreset::Ceramic_White:
        // ��ɫ�մ� - ������Ϊ�����еȸ߹�
        mat.setDiffuse(glm::vec4(0.95f));
        mat.setAmbient(glm::vec4(0.3f));
        mat.setSpecular(glm::vec4(0.5f));
        mat.setShininess(40.0f);
        break;

    case MaterialPreset::Rubber_Black:
        // ��ɫ�� - �����޾��淴�䣬�ǳ��ƹ�
        mat.setDiffuse(glm::vec4(0.01f));
        mat.setAmbient(glm::vec4(0.02f));
        mat.setSpecular(glm::vec4(0.02f));
        mat.setShininess(2.0f);
        break;

    case MaterialPreset::Glass_Clear:
        // ͸������ - �߹�ǿ��alpha͸����С
        mat.setDiffuse(glm::vec4(0.2f, 0.2f, 0.25f, 0.3f)); // ��͸��
        mat.setAmbient(glm::vec4(0.1f));
        mat.setSpecular(glm::vec4(0.9f));
        mat.setShininess(100.0f);
        break;
    }
    return mat;
}

