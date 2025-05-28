#include "pch.h"
#include "CGBasicCameraControl.h"
#include "CG2022112453������Doc.h" //����View֮ǰҪ����Doc 
#include "CG2022112453������View.h" 

CGBasicCameraControl::CGBasicCameraControl(GLFWwindow* window, CGCamera* camera)
	:UIEventHandler(window), mCamera(camera)
{
}

CGBasicCameraControl::~CGBasicCameraControl()
{
}

EventType CGBasicCameraControl::GetType()
{
	return EventType::CGBasicCameraControl;
}

int CGBasicCameraControl::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mCamera == nullptr)
		return -1;
	float detal = 5.0f; // �����Ĳ���
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {

		case GLFW_KEY_EQUAL:
			if (mods & GLFW_MOD_SHIFT) {
				mCamera->ScaleWindow(1.25); // �Ŵ�
			}
			view->ShowPrompt("�Ŵ󴰿�");
			break;
		case GLFW_KEY_MINUS:
			mCamera->ScaleWindow(0.8); // ��С
			view->ShowPrompt("��С����");
			break;
		case GLFW_KEY_L:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+L -> ����ͼ
				mCamera->SetLeftView();
			}
			else {
				// L -> ��߽�����, l->����
				mCamera->AdjustLeft((mods & GLFW_MOD_SHIFT) ? detal : -detal);
			}
			break;

		case GLFW_KEY_R:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+R -> ����ͼ
				mCamera->SetRightView();
			}
			else {
				// R -> �ұ߽����ƣ� r ����
				mCamera->AdjustRight((mods & GLFW_MOD_SHIFT) ? -detal : detal);
			}
			break;

		case GLFW_KEY_F:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+F -> ǰ��ͼ
				mCamera->SetFrontView();
			}
			break;

		case GLFW_KEY_B:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+B -> ����ͼ
				mCamera->SetBackView();
			}
			else {
				// B -> �±߽����ƣ� b ����
				mCamera->AdjustBottom((mods & GLFW_MOD_SHIFT) ? -detal : detal);
			}
			break;

		case GLFW_KEY_T:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+T -> ����ͼ
				mCamera->SetTopView();
			}
			else {
				// T -> �ϱ߽����ƣ� t����
				mCamera->AdjustTop((mods & GLFW_MOD_SHIFT) ? -detal : detal);
			}
			break;

		case GLFW_KEY_D:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+D -> ����ͼ/����ͼ
				mCamera->SetBottomView(); // �� SetUpsideDownView()
			}
			break;

		case GLFW_KEY_P:
			mCamera->SetProjectionMode(1);
			mCamera->Projection(1);
			break;

		case GLFW_KEY_O:
		{
			 //o ����ͶӰ����ά�� 2 �� O ��ά 0
			int mode = (mods & GLFW_MOD_SHIFT) ? 0 : 2;
			//int mode = 0;
			mCamera->SetProjectionMode(mode);
			mCamera->Projection(mode);
		}
			break;

		default:
			break;

		}
	}
	view->Invalidate();
	return 0;
}

int CGBasicCameraControl::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
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

int CGBasicCameraControl::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (window == nullptr)
		return -1;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mCamera == nullptr)
		return -1;

	// ����������Ƿ񱻰���
	if (mLeftPressed)
	{
		if (mFirstMove)
		{
			mLastX = xpos;
			mLastY = ypos;
			mFirstMove = false;
		}
		float xoffset = mLastX - xpos;
		float yoffset = mLastY - ypos; // ע�⣺y�����Ǵ��ϵ��µ�����
		mLastX = xpos;
		mLastY = ypos;

		const float sensitivity = 0.2f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		mCamera->RotateAroundTarget(xoffset, yoffset);
		std::string prompt = "Yaw: " + std::to_string(xoffset) + ", Pitch: " + std::to_string(yoffset);
		view->ShowPrompt(prompt);
		view->Invalidate(); // ������ͼ
	}
	else
	{
		// ���������δ���£����ñ�־λ�Ա��´ΰ���ʱ��ȷ��ʼ��
		mFirstMove = true;
	}

	return 0;
}

int CGBasicCameraControl::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
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
	mCamera->ScaleDistance(factor);
	std::string prompt = "Zoom Factor: " + std::to_string(factor);
	view->ShowPrompt(prompt);
	view->Invalidate();
	return 0;
}

