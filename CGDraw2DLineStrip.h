#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"
#include <vector>
#include "CG2022112453游坤坤Doc.h" //包含View之前要包含Doc 
#include "CG2022112453游坤坤View.h" //用户交互绘制，并将图形对象通过Doc添加到场景 
class CGDraw2DLineStrip : public UIEventHandler
{
public:
	CGDraw2DLineStrip(GLFWwindow* window = nullptr, 
		void(*drawLine)(int, int, int, int, glm::vec3) = CCG2022112453游坤坤View::DDA_Line);
	~CGDraw2DLineStrip();

	virtual EventType GetType() override;      //命令类型 
	//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线 
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	//取消正在执行的命令（如按ESC键） 
	virtual int Cancel(GLFWwindow* window) override;

private:
	//清除缓存，擦除上次绘制的橡皮线
	void clearCache(CCG2022112453游坤坤View* view, GLFWwindow* window);

private:
	const static  glm::vec3 RED;
	const static  glm::vec3 GREEN;
	const static  glm::vec3 BLUE;

	std::vector<glm::dvec3> points; //线段的顶点集合

	glm::dvec3 start;
	glm::dvec3 end;

	//临时存放当前位置的前一、二光标位置（因为双缓存的原因，橡皮线可能绘制到了前两帧） 
	glm::dvec3 mPrePos1, mPrePos2;
	int mMoveCount = 0;

	void(*drawLine)(int, int, int, int, glm::vec3) = nullptr; //绘制线段的函数指针
};


