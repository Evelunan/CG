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

	bool mLeftPressed = false; // 鼠标左键是否按下
	bool mRightPressed = false; // 鼠标右键是否按下
	bool mFirstMove = true; // 是否第一次移动
	double mLastX = 0.0f; // 上一次鼠标位置的X坐标
	double mLastY = 0.0f; // 上一次鼠标位置的Y坐标
};

