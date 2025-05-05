#pragma once
#include "UIEventHandler.h"
#include "CGNode.h"
class CGModel2DTransform :public UIEventHandler
{
public:
	//构造函数传入要施加变换的对象，如已绘制的直线段、折线等 
	CGModel2DTransform(CGNode* node, GLFWwindow* window = nullptr);
	~CGModel2DTransform();
	virtual EventType GetType() override;

	//命令类型 
	//假定使用鼠标滚动实现对象缩放，按住左键移动实现对象平移，按住右键移动实现对象旋转
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;

	//取消正在执行的命令（如按ESC键） 
	virtual int Cancel(GLFWwindow* window) override;
protected:
	CGNode* mNode; //被操纵的模型 
	glm::dvec3 mPivotPoint; //变换参考点，假定按住Shift+左键单击获取
	glm::dvec3 lastPoint; //上次鼠标位置
	enum class TransformType
	{
		Translate,	// 平移
		Rotate,		// 旋转
		Scale,		// 缩放
		Shear,		// 错切
		Mirror,		// 镜像
		End			// 结束
	};
	TransformType transformType; //变换类型
};


