#include "pch.h"
#include "CGBasicCameraControl.h"
#include "CG2022112453游坤坤Doc.h" //包含View之前要包含Doc 
#include "CG2022112453游坤坤View.h" 

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
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mCamera == nullptr)
		return -1;
	float detal = 5.0f; // 调整的步长
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {

		case GLFW_KEY_EQUAL:
			if (mods & GLFW_MOD_SHIFT) {
				mCamera->ScaleWindow(1.25); // 放大
			}
			view->ShowPrompt("放大窗口");
			break;
		case GLFW_KEY_MINUS:
			mCamera->ScaleWindow(0.8); // 缩小
			view->ShowPrompt("缩小窗口");
			break;
		case GLFW_KEY_L:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+L -> 左视图
				mCamera->SetLeftView();
			}
			else {
				// L -> 左边界左移, l->右移
				mCamera->AdjustLeft((mods & GLFW_MOD_SHIFT) ? detal : -detal);
			}
			break;

		case GLFW_KEY_R:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+R -> 右视图
				mCamera->SetRightView();
			}
			else {
				// R -> 右边界左移， r 右移
				mCamera->AdjustRight((mods & GLFW_MOD_SHIFT) ? -detal : detal);
			}
			break;

		case GLFW_KEY_F:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+F -> 前视图
				mCamera->SetFrontView();
			}
			break;

		case GLFW_KEY_B:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+B -> 后视图
				mCamera->SetBackView();
			}
			else {
				// B -> 下边界下移， b 上移
				mCamera->AdjustBottom((mods & GLFW_MOD_SHIFT) ? -detal : detal);
			}
			break;

		case GLFW_KEY_T:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+T -> 俯视图
				mCamera->SetTopView();
			}
			else {
				// T -> 上边界下移， t上移
				mCamera->AdjustTop((mods & GLFW_MOD_SHIFT) ? -detal : detal);
			}
			break;

		case GLFW_KEY_D:
			if ((mods & GLFW_MOD_CONTROL)) {
				// Ctrl+D -> 顶视图/仰视图
				mCamera->SetBottomView(); // 或 SetUpsideDownView()
			}
			break;

		case GLFW_KEY_P:
			mCamera->SetProjectionMode(1);
			mCamera->Projection(1);
			break;

		case GLFW_KEY_O:
		{
			 //o 正交投影（二维） 2 ， O 三维 0
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
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
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
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mCamera == nullptr)
		return -1;

	// 检查鼠标左键是否被按下
	if (mLeftPressed)
	{
		if (mFirstMove)
		{
			mLastX = xpos;
			mLastY = ypos;
			mFirstMove = false;
		}
		float xoffset = mLastX - xpos;
		float yoffset = mLastY - ypos; // 注意：y坐标是从上到下递增的
		mLastX = xpos;
		mLastY = ypos;

		const float sensitivity = 0.2f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		mCamera->RotateAroundTarget(xoffset, yoffset);
		std::string prompt = "Yaw: " + std::to_string(xoffset) + ", Pitch: " + std::to_string(yoffset);
		view->ShowPrompt(prompt);
		view->Invalidate(); // 更新视图
	}
	else
	{
		// 如果鼠标左键未按下，重置标志位以便下次按下时正确初始化
		mFirstMove = true;
	}

	return 0;
}

int CGBasicCameraControl::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	if (window == nullptr)
		return -1;
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
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

