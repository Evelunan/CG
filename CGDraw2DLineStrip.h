#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"
#include <vector>
#include "CG2022112453������Doc.h" //����View֮ǰҪ����Doc 
#include "CG2022112453������View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ����� 
class CGDraw2DLineStrip : public UIEventHandler
{
public:
	CGDraw2DLineStrip(GLFWwindow* window = nullptr, 
		void(*drawLine)(int, int, int, int, glm::vec3) = CCG2022112453������View::DDA_Line);
	~CGDraw2DLineStrip();

	virtual EventType GetType() override;      //�������� 
	//�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ���� 
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	//ȡ������ִ�е�����簴ESC���� 
	virtual int Cancel(GLFWwindow* window) override;

private:
	//������棬�����ϴλ��Ƶ���Ƥ��
	void clearCache(CCG2022112453������View* view, GLFWwindow* window);

private:
	const static  glm::vec3 RED;
	const static  glm::vec3 GREEN;
	const static  glm::vec3 BLUE;

	std::vector<glm::dvec3> points; //�߶εĶ��㼯��

	glm::dvec3 start;
	glm::dvec3 end;

	//��ʱ��ŵ�ǰλ�õ�ǰһ�������λ�ã���Ϊ˫�����ԭ����Ƥ�߿��ܻ��Ƶ���ǰ��֡�� 
	glm::dvec3 mPrePos1, mPrePos2;
	int mMoveCount = 0;

	void(*drawLine)(int, int, int, int, glm::vec3) = nullptr; //�����߶εĺ���ָ��
};


