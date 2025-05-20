#pragma once
#include "CGObject.h"
#include "CGTransform.h"
//节点变换自定义参数，可以根据更新需要定义参数 
class RobotBodyTransformParam : public CGObject
{
public:
	void setRotateDegree(float degree) { mRotateDegree = degree; }
	float rotateDegree() const { return mRotateDegree; }
protected:
	float mRotateDegree = 1.0f;
};

//旋转更新回调示例 
class RobotBodyRotate : public CGCallback
{
public:
	virtual bool run(CGObject* object, void* data) override
	{
		if (!mEnabled || !object)
			return false;
		CGTransform* body = dynamic_cast<CGTransform*>(object);  //要求变换节点 
		if (body) {
			RobotBodyTransformParam* d = nullptr;
			if (data) { //是否传入自定义参数 
				d = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
			}
			if (d) {
				body->rotate(d->rotateDegree(), 0.0f, 1.0f, 0.0f);
			}
			else { //如果没传入自定参数，按默认参数进行 
				body->rotate(1.0f, 0.0f, 1.0f, 0.0f);
			}
			return true;
		}
		return false;
	}
};

class RotateParam : public CGObject
{
public:
	void setAngle(float angle) { mAngle = angle; }
	float armAngle() const { return mAngle; }

	void setStep(float s) { mStep = s; }
	float step() const { return mStep; }

	void setMaxAngle(float angel) { mMaxAngle = angel; }
	float maxAngle()const { return mMaxAngle; }

	void setAxis(glm::vec3 axis) { mAxis = axis; }
	glm::vec3 Axis() { return mAxis; }
protected:
	float mAngle = -45.0f; // 初始角度
	float mStep = 2.0f;
	float mMaxAngle = 45.0f;
	// 默认z轴
	glm::vec3 mAxis = glm::vec3(0.0f, 0.0f, 1.0f);
};

class RotateCallback : public CGCallback {
public:
	virtual bool run(CGObject* object, void* data) override {



		auto node = dynamic_cast<CGTransform*>(object);
		if (!node) {

			return false;
		}
		// 直接转换 data 到 ArmSwingParam*
		RotateParam* param = nullptr;
		if (data) {
			param = static_cast<RotateParam*>(data); // 假设 data 指向的是 ArmSwingParam
		}

		float angle = param ? param->armAngle() : -45.0f; // 默认角度

		// 更新角度
		if (param) { // 确保 param 不为 nullptr
			float currentStep = param->step();
			float newAngle = angle + currentStep;

			if (newAngle >= param->maxAngle()) {
				newAngle = param->maxAngle();
				param->setStep(-param->step());
			}
			else if (newAngle <= -param->maxAngle()) {
				newAngle = -param->maxAngle();
				param->setStep(-param->step());
			}
			//param->setStep(currentStep);
			param->setAngle(newAngle);
		}
		// 如果 param 为 nullptr，使用默认角度 -45.0f
		node->rotate(glm::radians(param ? param->armAngle() : 2.0f), param->Axis());
		//node->rotate(glm::radians( param->armAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
		return true;
	}
};
