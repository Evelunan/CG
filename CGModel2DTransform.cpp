#include "pch.h"
#include "CGModel2DTransform.h"
#include "CG2022112453游坤坤Doc.h" //包含View之前要包含Doc 
#include "CG2022112453游坤坤View.h" 

CGModel2DTransform::CGModel2DTransform(CGRenderable* node, GLFWwindow* window)
	: UIEventHandler(window), mNode(node)
{
	mPivotPoint = glm::dvec3(0.0f, 0.0f, 0.0f); //初始参考点
	transformType = TransformType::End; //初始变换类型
	lastPoint = glm::dvec3(0.0f, 0.0f, 0.0f); //初始鼠标位置
}

CGModel2DTransform::~CGModel2DTransform()
{
}

EventType CGModel2DTransform::GetType()
{
	return EventType::Model2DTransform;
}

int CGModel2DTransform::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;

	if (action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		lastPoint.x = xpos;
		lastPoint.y = ypos;
		lastPoint = view->DCS2WCS(lastPoint); //转换到场景坐标
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (mods & GLFW_MOD_SHIFT)
			{
				mPivotPoint.x = xpos;
				mPivotPoint.y = ypos;
				mPivotPoint = view->DCS2WCS(mPivotPoint); //转换到场景坐标

				std::string str = "Pivot Point: (" + std::to_string(mPivotPoint.x) + ", " + std::to_string(mPivotPoint.y) + ")";
				view->ShowPrompt(str); //状态栏显示
			}
			transformType = TransformType::Translate; //平移
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			transformType = TransformType::Rotate; //旋转
		}
	}
	else if (action == GLFW_RELEASE)
	{
		transformType = TransformType::End; //结束变换
	}
	return 0;
}

int CGModel2DTransform::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (transformType == TransformType::End)
		return 0; //没有变换类型，直接返回
	using namespace glm;
	if (window == nullptr)
		return -1;
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	dvec3 currentPos = view->DCS2WCS(glm::vec3(xpos, ypos, 0.0));
	if (transformType == TransformType::Translate)
	{
		double dx = currentPos.x - lastPoint.x;
		double dy = currentPos.y - lastPoint.y;

		std::string str = "Translate: (" + std::to_string(dx) + ", " + std::to_string(dy) + ")";
		view->ShowPrompt(str); //状态栏显示
		mNode->Translate(dx, dy); //平移
		view->ShowCoord(xpos, ypos); //状态栏显示
	}
	else if (transformType == TransformType::Rotate)
	{
		dvec3 seg1 = lastPoint - mPivotPoint;
		dvec3 seg2 = currentPos - mPivotPoint;

		double angle = atan2(seg2.y, seg2.x) - atan2(seg1.y, seg1.x);
		angle = degrees(angle);
		mNode->Rotate(angle, mPivotPoint.x, mPivotPoint.y);

		std::string str = "Pivot Point: (" + std::to_string(mPivotPoint.x) + ", " + std::to_string(mPivotPoint.y) + ")";
		view->ShowPrompt(str); //状态栏显示
	}
	lastPoint.x = xpos;
	lastPoint.y = ypos;
	lastPoint = view->DCS2WCS(lastPoint); //转换到场景坐标
	view->Invalidate(); //强制视图重绘
	return 0;
}

int CGModel2DTransform::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	using namespace glm;
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	// 检查 Ctrl 键是否被按下（左 Ctrl 或右 Ctrl）
	bool ctrlPressed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;

	if (!ctrlPressed)
		return 0;
	// 计算缩放因子（滚轮向上放大，向下缩小）
	std::string str = "Pivot Point: (" + std::to_string(mPivotPoint.x) + ", " + std::to_string(mPivotPoint.y) + ")";
	view->ShowPrompt(str); //状态栏显示
	double factor = (yoffset > 0) ? 1.1 : 0.9; // 10% 缩放
	mNode->Scale(factor, factor, mPivotPoint.x, mPivotPoint.y);
	view->Invalidate();
	return 0;
}

int CGModel2DTransform::Cancel(GLFWwindow* window)
{
	return 0;
}
