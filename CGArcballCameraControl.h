#pragma once
#include "UIEventHandler.h"
#include "CGCamera.h"

class CGArcballCameraControl :public UIEventHandler
{
public:
	CGArcballCameraControl(GLFWwindow* window = nullptr, CGCamera* camera = nullptr);
	
	virtual EventType GetType() override;

	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;
private:
	CGCamera* mCamera;

	bool mLeftPressed = false; // �������Ƿ���
	bool mRightPressed = false; // ����Ҽ��Ƿ���
	bool mFirstMove = true; // �Ƿ��һ���ƶ�
	double mLastX = 0.0f; // ��һ�����λ�õ�X����
	double mLastY = 0.0f; // ��һ�����λ�õ�Y����
};

