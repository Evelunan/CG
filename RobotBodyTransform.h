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


class ArmSwingParam : public RobotBodyTransformParam {
public:
	void setArmAngle(float angle) { mArmAngle = angle; }
	float armAngle() const { return mArmAngle; }

	void setStep(float s) { mStep = s; }
	float getStep() const { return mStep; }

protected:
	float mArmAngle = -45.0f; // 初始角度
	float mStep = 2.0f;
};

class ArmSwingCallback : public RobotBodyRotate {
public:
	virtual bool run(CGObject* object, void* data) override {

		RobotBodyRotate::run(object, data);

		auto leftUpperArm = dynamic_cast<CGTransform*>(object);
		if (!leftUpperArm) {

			return false;
		}

		// 直接转换 data 到 ArmSwingParam*
		ArmSwingParam* param = nullptr;
		if (data) {
			param = static_cast<ArmSwingParam*>(data); // 假设 data 指向的是 ArmSwingParam
		}

		float angle = param ? param->armAngle() : -45.0f; // 默认角度

		// 更新角度
		if (param) { // 确保 param 不为 nullptr
			float currentStep = param->getStep();
			float newAngle = angle + currentStep;

			if (newAngle >= 45.0f) {
				newAngle = 45.0f;
				currentStep = -2.0f;
			}
			else if (newAngle <= -45.0f) {
				newAngle = -45.0f;
				currentStep = 2.0f;
			}
			param->setStep(currentStep);
			param->setArmAngle(newAngle);
		}
		// 如果 param 为 nullptr，使用默认角度 -45.0f
		leftUpperArm->rotate(glm::radians(param ? param->armAngle() : 2.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//leftUpperArm->rotate(glm::radians( param->armAngle()), glm::vec3(0.0f, 0.0f, 1.0f));


		return true;
	}
};

//class WalkingCallback : public CGCallback {
//public:
//	virtual bool run(CGObject* object, void* data) override {
//		if (!mEnabled || !object)
//			return false;
//
//		auto rightLeg = dynamic_cast<CGTransform*>(object->getChildByName("rightLeg"));
//		auto leftLeg = dynamic_cast<CGTransform*>(object->getChildByName("leftLeg"));
//
//		WalkingParam* param = nullptr;
//		if (data) {
//			param = dynamic_cast<WalkingParam*>((RobotBodyTransformParam*)data);
//		}
//
//		float stepHeight = param ? param->stepHeight() : -15.0f; // 默认步高
//
//		if (stepHeight >= 15.0f) {
//			stepHeight = -15.0f; // 反向
//		}
//		else {
//			stepHeight += 1.0f; // 增加步高
//		}
//
//		if (param) {
//			param->setStepHeight(stepHeight);
//		}
//
//		if (rightLeg && leftLeg) {
//			// 左腿抬起，右腿放下
//			leftLeg->translate(0.0f, stepHeight, 0.0f);
//			leftLeg->rotate(glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//			rightLeg->translate(0.0f, -stepHeight, 0.0f);
//			rightLeg->rotate(glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//
//			return true;
//		}
//		return false;
//	}
//};