#include "pch.h"
#include "CGArcballCameraControl.h"
#include "CG2022112453������Doc.h" //����View֮ǰҪ����Doc 
#include "CG2022112453������View.h" 
CGArcballCameraControl::CGArcballCameraControl(GLFWwindow* window, CGCamera* camera)
    :UIEventHandler(window), mCamera(camera)
{
}

EventType CGArcballCameraControl::GetType()
{
    return EventType::CGArcballCameraControl;
}

int CGArcballCameraControl::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mCamera == nullptr)
		return -1;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		mLeftPressed = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		mLeftPressed = false;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		mRightPressed = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		mRightPressed = false;
	}
	return 0;
}

int CGArcballCameraControl::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (window == nullptr)
		return -1;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mCamera == nullptr)
		return -1;

	if (mFirstMove)
	{
		mLastX = xpos;
		mLastY = ypos;
		mFirstMove = false;
	}
	// ����������Ƿ񱻰���
	if (mLeftPressed)
	{
		float xoffset = mLastX - xpos;
		float yoffset = mLastY - ypos; // ע�⣺y�����Ǵ��ϵ��µ�����

		const float sensitivity = 0.2f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		mCamera->ArcballRotate(xoffset, yoffset);
		std::string prompt = "Yaw: " + std::to_string(xoffset) + ", Pitch: " + std::to_string(yoffset);
		view->ShowPrompt(prompt);
		view->Invalidate(); // ������ͼ
	}
	mLastX = xpos;
	mLastY = ypos;

	return 0;
}

int CGArcballCameraControl::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	if (window == nullptr)
		return -1;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mCamera == nullptr)
		return -1;
	bool ctrlPressed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;

	if (!ctrlPressed)
		return 0;
	float factor = yoffset > 0 ? 1.25 : 0.8;
	mCamera->ArcballZoom(factor);
	std::string prompt = "ArcballZoom Factor: " + std::to_string(factor);
	view->ShowPrompt(prompt);
	view->Invalidate();
	return 0;
}
