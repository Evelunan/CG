#pragma once
#include "UIEventHandler.h"
#include "CGNode.h"
class CGModel2DTransform :public UIEventHandler
{
public:
	//���캯������Ҫʩ�ӱ任�Ķ������ѻ��Ƶ�ֱ�߶Ρ����ߵ� 
	CGModel2DTransform(CGNode* node, GLFWwindow* window = nullptr);
	~CGModel2DTransform();
	virtual EventType GetType() override;

	//�������� 
	//�ٶ�ʹ��������ʵ�ֶ������ţ���ס����ƶ�ʵ�ֶ���ƽ�ƣ���ס�Ҽ��ƶ�ʵ�ֶ�����ת
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;

	//ȡ������ִ�е�����簴ESC���� 
	virtual int Cancel(GLFWwindow* window) override;
protected:
	CGNode* mNode; //�����ݵ�ģ�� 
	glm::dvec3 mPivotPoint; //�任�ο��㣬�ٶ���סShift+���������ȡ
	glm::dvec3 lastPoint; //�ϴ����λ��
	enum class TransformType
	{
		Translate,	// ƽ��
		Rotate,		// ��ת
		Scale,		// ����
		Shear,		// ����
		Mirror,		// ����
		End			// ����
	};
	TransformType transformType; //�任����
};


