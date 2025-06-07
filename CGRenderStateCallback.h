#pragma once
#include "CGObject.h"
#include "CGRenderState.h"
#include "CGLightModel.h"
#include "CGMaterial.h"
#include "CGTransform.h"
#include <chrono>
class LightTransformParam : public CGObject{
public:
    glm::vec3 center{ 0.0f };      // ��ת����
    float radius = 100.0f;       // ��ת�뾶
    float deltaAngle = 0.1f;    // ÿ����ת�ĽǶȣ����ȣ�
    glm::vec3 axis{ 0, 1, 0 };     // ��ת�ᣨ�����ǵ�λ������
    LightTransformParam() {
        axis = glm::normalize(axis); // ȷ���ǵ�λ����
    }
    glm::vec4 getNextPosition(const glm::vec4& currentPos) {
        // ȷ����ת���ǵ�λ����
        glm::vec3 normAxis = glm::normalize(axis);

        // ������ָ��ǰλ�õ�����
        glm::vec3 relative = glm::vec3(currentPos) - center;

        // ������ axis ��ת deltaAngle ����ת����
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), deltaAngle, normAxis);

        // Ӧ����ת
        glm::vec3 rotated = center + glm::vec3(rotation * glm::vec4(relative, 0.0f));

        return glm::vec4(rotated, currentPos.w); // ������ת���λ��
    }

};

class LightCallback : public CGCallback
{
public:
    virtual bool run(CGObject* object, void* data) override
    {
        if (!mEnabled || !object)
            return false;
        CGLight* state = dynamic_cast<CGLight*>(object);  //Ҫ��任�ڵ� 
        if (!state)
            return false;
        LightTransformParam* d = nullptr;
        if (data) { //�Ƿ����Զ������ 
            d = dynamic_cast<LightTransformParam*>((CGObject*)data);
        }
        if (!d)
            return false;
        
        auto nextPos = d->getNextPosition(state->Position());
        state->setPosition(nextPos);

        return true;
    }
};

class MaterialTransformParam :public CGObject
{
public :
    int count = static_cast<int>(MaterialPreset::COUNT);
    int current = 0;

    // �ϴα仯��ʱ��
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    // ��С�������λ�����룩
    int interval = 500;

    int Next() {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count();
        if (duration >= interval) {
            lastTime = now;
            current = (current + 1) % count;
        }
        return current;
    }
};
class MaterialTransfomCallback : public CGCallback
{
public:
    virtual bool run(CGObject* object, void* data) override
    {
        if (!mEnabled || !object)
            return false;
        CGTransform* tran = dynamic_cast<CGTransform*>(object);  //Ҫ��任�ڵ� 
        if (!tran)
            return false;
        MaterialTransformParam* d = nullptr;
        if (data) { //�Ƿ����Զ������ 
            d = dynamic_cast<MaterialTransformParam*>((MaterialTransformParam*)data);
        }


        std::shared_ptr<CGMaterial> material = std::make_shared<CGMaterial>();
        if (d) 
        {
            material = std::make_shared<CGMaterial>(
                CreateMaterial(static_cast<MaterialPreset>(d->Next())));
        }
        tran->gocRenderStateSet()->setRenderState(material, -1);
        
        return true;
    }

};