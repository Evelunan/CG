#include "pch.h"
#include "CGDraw2DLineStrip.h"
#include "CGLineStrip.h"

const glm::vec3 CGDraw2DLineStrip::RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 CGDraw2DLineStrip::GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 CGDraw2DLineStrip::BLUE = glm::vec3(0.0f, 0.0f, 1.0f);

CGDraw2DLineStrip::CGDraw2DLineStrip(GLFWwindow* window,
	void(*drawLine)(int, int, int, int, glm::vec3))
	:UIEventHandler(window), start(0.0, 0.0, 0.0), end(0.0, 0.0, 0.0)
{
	mPrePos1 = end;
	mPrePos2 = end;
	this->drawLine = drawLine;
}

CGDraw2DLineStrip::~CGDraw2DLineStrip()
{
}

EventType CGDraw2DLineStrip::GetType()
{
    return EventType::Draw2DLineStrip;
}

int CGDraw2DLineStrip::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	double xpos, ypos;
	if (action != GLFW_PRESS)
		return 0;

	glfwGetCursorPos(window, &xpos, &ypos);
	points.push_back({ xpos, ypos, 0.0 });

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		mStep++;
		if (mStep == 1)
		{
			start.x = xpos;
			start.y = ypos;
			end = start;
			mPrePos1 = end;
			mPrePos2 = end;
		}
		else 
		{
			start = end;
			end.x = xpos;
			end.y = ypos;
			glfwSwapBuffers(window);
		}
		view->ShowPrompt("������������ѡ����һ������Ҽ�ѡ���յ�");

	} 
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		mStep = 0;

		start = end;
		end.x = xpos;
		end.y = ypos;
		glfwSwapBuffers(window);

		for ( auto& point : points)
		{
			point = view->DCS2WCS(point); //ת������������
		}
		view->AddRenderable(std::make_shared<CGLineStrip>(points, drawLine)); //������ӵ����� 
		view->Invalidate();  //�ͻ�����Ҫ�ػ� 
		view->UpdateWindow(); //�ͻ���ִ���ػ� 
		points.clear();
	}
    return 0;
}

int CGDraw2DLineStrip::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (window == nullptr)
		return -1;
	CCG2022112453������View* view = (CCG2022112453������View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mStep == 0)
	{
		view->ShowPrompt("����������������ֱ�߶ε����"); //״̬����ʾ
		return 0;
	}
	if (xpos == start.x && ypos == start.y)
		return 0; //�����غϣ���������

	end = { xpos, ypos, 0.0 };
	mMoveCount++;

	clearCache(view, window);

	return 0;
}


int CGDraw2DLineStrip::Cancel(GLFWwindow* window)
{
    return 0;
}

void CGDraw2DLineStrip::clearCache(CCG2022112453������View* view, GLFWwindow* window)
{
	// ��ʾ��ǰ�ǵڼ����ƶ�
	auto convertedStart = view->DCS2WCS(start);
	auto convertedEnd = view->DCS2WCS(end);
	auto convertedPrePos2 = view->DCS2WCS(mPrePos2);
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_XOR); //�����߼������Ϊ���
	// rgb
	//glColor3f(1.0f, 0.0f, 0.0f); //������ɫΪ��ɫ
	if (mMoveCount > 1)
		drawLine(convertedStart.x, convertedStart.y, convertedPrePos2.x, convertedPrePos2.y, GREEN); //������һ���յ㵽��ǰ���λ�õ��߶�
	
	drawLine(convertedStart.x, convertedStart.y, convertedEnd.x, convertedEnd.y, GREEN); //���Ƶ�ǰ���λ�õ������߶�
	glDisable(GL_COLOR_LOGIC_OP); //�����߼������
	glfwSwapBuffers(window); //��������������ʾ���Ƶ�����

	if (mMoveCount == 1)
	{
		mPrePos1 = end;
		mPrePos2 = end;
	}
	else
	{
		mPrePos2 = mPrePos1;
		mPrePos1 = end;
	}
}

