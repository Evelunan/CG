#pragma once
#include "CGObject.h"
#include "CGRenderState.h"
#include "CGLightModel.h"
#include "CGMaterial.h"
#include "CGTransform.h"
#include <chrono>
class LightTransformParam : public CGObject{
public:
    glm::vec3 center{ 0.0f };      // 旋转中心
    float radius = 100.0f;       // 旋转半径
    float deltaAngle = 0.1f;    // 每次旋转的角度（弧度）
    glm::vec3 axis{ 0, 1, 0 };     // 旋转轴（必须是单位向量）
    LightTransformParam() {
        axis = glm::normalize(axis); // 确保是单位向量
    }
    glm::vec4 getNextPosition(const glm::vec4& currentPos) {
        // 确保旋转轴是单位向量
        glm::vec3 normAxis = glm::normalize(axis);

        // 从中心指向当前位置的向量
        glm::vec3 relative = glm::vec3(currentPos) - center;

        // 构造绕 axis 旋转 deltaAngle 的旋转矩阵
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), deltaAngle, normAxis);

        // 应用旋转
        glm::vec3 rotated = center + glm::vec3(rotation * glm::vec4(relative, 0.0f));

        return glm::vec4(rotated, currentPos.w); // 返回旋转后的位置
    }

};

class LightCallback : public CGCallback
{
public:
    virtual bool run(CGObject* object, void* data) override
    {
        if (!mEnabled || !object)
            return false;
        CGLight* state = dynamic_cast<CGLight*>(object);  //要求变换节点 
        if (!state)
            return false;
        LightTransformParam* d = nullptr;
        if (data) { //是否传入自定义参数 
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

    // 上次变化的时间
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();
    // 最小间隔（单位：毫秒）
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
        CGTransform* tran = dynamic_cast<CGTransform*>(object);  //要求变换节点 
        if (!tran)
            return false;
        MaterialTransformParam* d = nullptr;
        if (data) { //是否传入自定义参数 
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