#include "pch.h"
#include "CGModel2DTransform.h"
#include "CG2022112453������Doc.h" //����View֮ǰҪ����Doc 
#include "CG2022112453������View.h" 

CGModel2DTransform::CGModel2DTransform(CGRenderable* node, GLFWwindow* window)
	: UIEventHandler(window), mNode(node)
{
	mPivotPoint = glm::dvec3(0.0f, 0.0f, 0.0f); //��ʼ�ο���
	transformType = TransformType::End; //��ʼ�任����
	lastPoint = glm::dvec3(0.0f, 0.0f, 0.0f); //��ʼ���λ��
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
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;

	if (action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		lastPoint.x = xpos;
		lastPoint.y = ypos;
		lastPoint = view->DCS2WCS(lastPoint); //ת������������
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (mods & GLFW_MOD_SHIFT)
			{
				mPivotPoint.x = xpos;
				mPivotPoint.y = ypos;
				mPivotPoint = view->DCS2WCS(mPivotPoint); //ת������������

				std::string str = "Pivot Point: (" + std::to_string(mPivotPoint.x) + ", " + std::to_string(mPivotPoint.y) + ")";
				view->ShowPrompt(str); //״̬����ʾ
			}
			transformType = TransformType::Translate; //ƽ��
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			transformType = TransformType::Rotate; //��ת
		}
	}
	else if (action == GLFW_RELEASE)
	{
		transformType = TransformType::End; //�����任
	}
	return 0;
}

int CGModel2DTransform::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (transformType == TransformType::End)
		return 0; //û�б任���ͣ�ֱ�ӷ���
	using namespace glm;
	if (window == nullptr)
		return -1;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	dvec3 currentPos = view->DCS2WCS(glm::vec3(xpos, ypos, 0.0));
	if (transformType == TransformType::Translate)
	{
		double dx = currentPos.x - lastPoint.x;
		double dy = currentPos.y - lastPoint.y;

		std::string str = "Translate: (" + std::to_string(dx) + ", " + std::to_string(dy) + ")";
		view->ShowPrompt(str); //״̬����ʾ
		mNode->Translate(dx, dy); //ƽ��
		view->ShowCoord(xpos, ypos); //״̬����ʾ
	}
	else if (transformType == TransformType::Rotate)
	{
		dvec3 seg1 = lastPoint - mPivotPoint;
		dvec3 seg2 = currentPos - mPivotPoint;

		double angle = atan2(seg2.y, seg2.x) - atan2(seg1.y, seg1.x);
		angle = degrees(angle);
		mNode->Rotate(angle, mPivotPoint.x, mPivotPoint.y);

		std::string str = "Pivot Point: (" + std::to_string(mPivotPoint.x) + ", " + std::to_string(mPivotPoint.y) + ")";
		view->ShowPrompt(str); //״̬����ʾ
	}
	lastPoint.x = xpos;
	lastPoint.y = ypos;
	lastPoint = view->DCS2WCS(lastPoint); //ת������������
	view->Invalidate(); //ǿ����ͼ�ػ�
	return 0;
}

int CGModel2DTransform::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	using namespace glm;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	// ��� Ctrl ���Ƿ񱻰��£��� Ctrl ���� Ctrl��
	bool ctrlPressed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;

	if (!ctrlPressed)
		return 0;
	// �����������ӣ��������ϷŴ�������С��
	std::string str = "Pivot Point: (" + std::to_string(mPivotPoint.x) + ", " + std::to_string(mPivotPoint.y) + ")";
	view->ShowPrompt(str); //״̬����ʾ
	double factor = (yoffset > 0) ? 1.1 : 0.9; // 10% ����
	mNode->Scale(factor, factor, mPivotPoint.x, mPivotPoint.y);
	view->Invalidate();
	return 0;
}

int CGModel2DTransform::Cancel(GLFWwindow* window)
{
	return 0;
}
