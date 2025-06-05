#pragma once
#include "CGRenderState.h"

class CGMaterial : public CGRenderState {

public:
    CGMaterial();
    virtual ~CGMaterial() = default;

    virtual ERenderState type() const override { return RS_Material; }
    // ���ò��ʵ��Է�����ɫ����ʹû�й���Ҳ����ʾ����ɫ��
    void setEmission(const glm::vec4& emission);

    // ���ò��ʶԻ�����ķ�����ɫ��Ӱ��������ȫ�ֻ������µĻ������ȣ�
    void setAmbient(const glm::vec4& ambient);

    // ���ò��ʵ���������ɫ�����������ڹ����µ���Ҫ�Ӿ���ɫ��
    void setDiffuse(const glm::vec4& diffuse);

    // ���ò��ʵľ��淴����ɫ�����Ƹ߹��������ɫ��ǿ�ȣ�
    void setSpecular(const glm::vec4& specular);

    // ���ò��ʵĹ���ȣ�shininess����ֵԽ��߹�Խ���С�ԽСԽ��ɢ����Χ 0~128��
    void setShininess(float shininess);

    // �����Ƿ�������ɫ׷�ٲ���ģʽ������ĳЩ���Ը��� glColor �ı仯��
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
        Ceramic // �մ�
    };

    inline CGMaterial CreateMaterialWithColor(const glm::vec4& color, MaterialType type) {
        CGMaterial mat;

        mat.setDiffuse(color);              // ������ɫ������������ɫ��
        mat.setAmbient(color * 0.3f);       // ������������ɫ���ɵ���
        mat.setEmission(glm::vec4(0.0f));   // Ĭ�����Է���
        mat.setColorMaterial(CM_None);      // ��ʹ�� glColor �Զ�����

        switch (type) {
        case MaterialType::Plastic:
            mat.setSpecular(glm::vec4(0.3f));   // ��΢����߹�
            mat.setShininess(32.0f);
            break;
        case MaterialType::Metal:
            mat.setSpecular(glm::vec4(0.8f));   // ���Խ�������
            mat.setShininess(96.0f);
            break;
        case MaterialType::Wood:
            mat.setSpecular(glm::vec4(0.1f));   // ľ�Ľ��ٸ߹�
            mat.setShininess(8.0f);
            break;
        case MaterialType::Ceramic:
            mat.setSpecular(glm::vec4(0.5f));   // ��͸߹�
            mat.setShininess(48.0f);
            break;
        }
        return mat;
    }
}
