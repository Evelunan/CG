#pragma once
#include "CGObject.h"
#include "CGTransform.h"
//�ڵ�任�Զ�����������Ը��ݸ�����Ҫ������� 
class RobotBodyTransformParam : public CGObject
{
public:
	void setRotateDegree(float degree) { mRotateDegree = degree; }
	float rotateDegree() const { return mRotateDegree; }
protected:
	float mRotateDegree = 1.0f;
};

//��ת���»ص�ʾ�� 
class RobotBodyRotate : public CGCallback
{
public:
	virtual bool run(CGObject* object, void* data) override
	{
		if (!mEnabled || !object)
			return false;
		CGTransform* body = dynamic_cast<CGTransform*>(object);  //Ҫ��任�ڵ� 
		if (body) {
			RobotBodyTransformParam* d = nullptr;
			if (data) { //�Ƿ����Զ������ 
				d = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
			}
			if (d) {
				body->rotate(d->rotateDegree(), 0.0f, 1.0f, 0.0f);
			}
			else { //���û�����Զ���������Ĭ�ϲ������� 
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
	float mArmAngle = -45.0f; // ��ʼ�Ƕ�
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

		// ֱ��ת�� data �� ArmSwingParam*
		ArmSwingParam* param = nullptr;
		if (data) {
			param = static_cast<ArmSwingParam*>(data); // ���� data ָ����� ArmSwingParam
		}

		float angle = param ? param->armAngle() : -45.0f; // Ĭ�ϽǶ�

		// ���½Ƕ�
		if (param) { // ȷ�� param ��Ϊ nullptr
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
		// ��� param Ϊ nullptr��ʹ��Ĭ�ϽǶ� -45.0f
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
//		float stepHeight = param ? param->stepHeight() : -15.0f; // Ĭ�ϲ���
//
//		if (stepHeight >= 15.0f) {
//			stepHeight = -15.0f; // ����
//		}
//		else {
//			stepHeight += 1.0f; // ���Ӳ���
//		}
//
//		if (param) {
//			param->setStepHeight(stepHeight);
//		}
//
//		if (rightLeg && leftLeg) {
//			// ����̧�����ȷ���
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