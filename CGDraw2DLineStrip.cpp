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
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
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
		view->ShowPrompt("请鼠标左键单击选择下一个点或右键选择终点");

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
			point = view->DCS2WCS(point); //转换到场景坐标
		}
		view->AddRenderable(std::make_shared<CGLineStrip>(points, drawLine)); //创建添加到场景 
		view->Invalidate();  //客户区需要重绘 
		view->UpdateWindow(); //客户区执行重绘 
		points.clear();
	}
    return 0;
}

int CGDraw2DLineStrip::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (window == nullptr)
		return -1;
	CCG2022112453游坤坤View* view = (CCG2022112453游坤坤View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mStep == 0)
	{
		view->ShowPrompt("请鼠标左键单击输入直线段的起点"); //状态栏显示
		return 0;
	}
	if (xpos == start.x && ypos == start.y)
		return 0; //两点重合，不做处理

	end = { xpos, ypos, 0.0 };
	mMoveCount++;

	clearCache(view, window);

	return 0;
}


int CGDraw2DLineStrip::Cancel(GLFWwindow* window)
{
    return 0;
}

void CGDraw2DLineStrip::clearCache(CCG2022112453游坤坤View* view, GLFWwindow* window)
{
	// 显示当前是第几次移动
	auto convertedStart = view->DCS2WCS(start);
	auto convertedEnd = view->DCS2WCS(end);
	auto convertedPrePos2 = view->DCS2WCS(mPrePos2);
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_XOR); //设置逻辑运算符为异或
	// rgb
	//glColor3f(1.0f, 0.0f, 0.0f); //设置颜色为蓝色
	if (mMoveCount > 1)
		drawLine(convertedStart.x, convertedStart.y, convertedPrePos2.x, convertedPrePos2.y, GREEN); //绘制上一个终点到当前鼠标位置的线段
	
	drawLine(convertedStart.x, convertedStart.y, convertedEnd.x, convertedEnd.y, GREEN); //绘制当前鼠标位置到起点的线段
	glDisable(GL_COLOR_LOGIC_OP); //禁用逻辑运算符
	glfwSwapBuffers(window); //交换缓冲区以显示绘制的内容

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

