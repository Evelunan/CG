#pragma once
#include "glIncludes.h"
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime> 
#include <cmath>
#include <algorithm>
#include <stack>
#include <functional>
class CCGRenderContext
{
private:
	static const LONG X_MAX = 500;
	static const LONG X_MIN = 0;
	static const LONG Y_MAX = 500;
	static const LONG Y_MIN = 0;
	// Ĭ����ɫ
	static const glm::vec3 DEFAULT_COLOR;

public:
	CCGRenderContext();
	virtual ~CCGRenderContext();

	// ������ǣ�centerΪ��������ģ�lenΪ���ĵ�������룬color1��color2�ֱ�Ϊ������������ɫ
	static void drawPentagram(POINT center, GLint len, glm::vec3 color1, glm::vec3 color2);
	// ʵ��1-��1��
	static void drawTest1();
	static void draWTest2();


	/**
	* @brief �������ֻ����㷨
	*/
	static void testLine();

	/**
	* @brief ���Ի�Բ�㷨��
	*/
	static void testCircle();

	static void testScanPloygon();

	static void testFill();

	/**
	* @brief ���Զ���εĻ��ơ�
	*
	* @param drawLine �����߶εĺ���ָ�롣
	* @param n ����εı�����
	* @param x ����ε�����x���ꡣ
	* @param y ����ε�����y���ꡣ
	* @param r ����εİ뾶��
	* @param color ����ε���ɫ��Ĭ��ֵΪDEFAULT_COLOR��
	*/
	static void testPlyogon(void (*drawLine)(int, int, int, int, glm::vec3), int n, int x, int y, int r, glm::vec3 color = DEFAULT_COLOR);



	/**
	 * @brief ʹ��DDA�㷨����ֱ�ߡ�
	 *
	 * @param x1 ����x���ꡣ
	 * @param y1 ����y���ꡣ
	 * @param x2 �յ��x���ꡣ
	 * @param y2 �յ��y���ꡣ
	 * @param color ֱ�ߵ���ɫ��Ĭ��ֵΪDEFAULT_COLOR��
	*/
	static void DDA_Line(int x1, int y1, int x2, int y2, glm::vec3 color = DEFAULT_COLOR);


	/**
	* @brief ʹ���е��㷨����ֱ�ߡ�
	*
	* @param x1,y1 �������ꡣ
	* @param x2,y2 �յ�����ꡣ
	* @param color ��ɫ��Ĭ��ֵΪDEFAULT_COLOR��
	*/
	static void Midpoint_Line(int x1, int y1, int x2, int y2, glm::vec3 color = DEFAULT_COLOR);

	/**
	* @brief ʹ��Bresenham�㷨����ֱ�ߡ�
	*
	* @param x1,y1 �������ꡣ
	* @param x2,y2 �յ�����ꡣ
	* @param color ��ɫ��Ĭ��ֵΪDEFAULT_COLOR��
	*/
	static void Bresenham_Line(int x1, int y1, int x2, int y2, glm::vec3 color = DEFAULT_COLOR);


	/**
	* @brief �е㻭Բ�㷨
	*
	* @param xc,yc Բ������
	* @param r �뾶
	* @param color ��ɫ��Ĭ��ֵΪDEFAULT_COLOR��
	*/
	static void MidpointCircle(int xc, int yc, int r, glm::vec3 color = DEFAULT_COLOR);


	/**
	* @brief ͨ���е㻭Բ�㷨������
	*
	* @param xc,yc Բ������
	* @param r �뾶
	* @param startAngle ��ʼ�Ƕ�
	* @param endAngle �����Ƕ�
	* @param color ��ɫ��Ĭ��ֵΪDEFAULT_COLOR��
	*/
	static void drawArcByMidPoint(int xc, int yc, int r, double startAngle, double endAngle, glm::vec3 color = DEFAULT_COLOR);


	/*
	* @brief Bresenham�㷨��Բ
	*
	* @param xc,yc Բ������
	* @param r �뾶
	* @param color ��ɫ
	*/
	static void BresenhamCircle(int xc, int yc, int r, glm::vec3 color = DEFAULT_COLOR);

	/**
	* @breif ɨ��������㷨
	* 
	* @param points ����ζ�������
	* @param color ��ɫ��Ĭ��ֵΪDEFAULT_COLOR
	*/
	static void scanPloygon(const std::vector<glm::vec2> &points, glm::vec3 color = DEFAULT_COLOR);
	
	/**
	* @brief �߽�����㷨
	* 
	* @param x,y �����ڲ�����һ������
	* @param bColor �߽���ɫ
	* @param nColor �ڲ���ɫ
	*/
	static void boundaryFill4(int x, int y, glm::u8vec3 bColor, glm::u8vec3 nColor);

	/**
	* @brief ��ˮ����㷨
	* 
	* @param x,y �����ڲ�����һ������
	* @param oldColor ����ɫ
	* @param newColor ����ɫ
	*/
	static void floodFill4(int x, int y, glm::u8vec3 oldColor, glm::u8vec3 newColor);


	/**
	* @brief ��������㷨
	* 
	* @param x,y �����ڲ�����һ������
	* @param color1 �߽��ʾʱΪ�߽���ɫ���ڵ��ʾʱΪ����ɫ
	* @param color2 �߽��ʾʱΪ�ڵ���ɫ���ڵ��ʾʱΪ����ɫ
	* @param shouldFill �ж��Ƿ����ĺ���
	*/
	static void CCGRenderContext::fillHelper(int x, int y,
		glm::u8vec3 color1, glm::u8vec3 color2, 
		std::function<bool(glm::u8vec3, glm::u8vec3)> shouldFill);
private:

	/*
	* @brief ��㼯�ϣ����ȣ���ͼģʽ����ɫ���Ƿ�ʹ���Զ�����ɫ
	* points �㼯��
	* len �㼯�ϳ���
	* mode ��ͼģʽ
	* color �Զ�����ɫ
	* customColor �Ƿ�ʹ���Զ�����ɫ
	*/
	static void display(POINT points[], GLint len, GLenum mode, glm::vec3 color = DEFAULT_COLOR, bool customColor = false);

	// �����㷨ʹ��
	static void displayPoint(POINT points[], GLint len, glm::vec3 color = DEFAULT_COLOR);

	// ��ȡ����㼯��
	static std::unique_ptr<POINT[]> getRandomPoints(GLint len);

	// ��֤����x1 <= x2�Լ�dx < dy�������Ƿ񽻻���x��y��
	static bool checkArgs(int& x1, int& y1, int& x2, int& y2);

	// ����k=0��k=��������
	static bool kZeroOrNotExist(int x1, int y1, int x2, int y2, glm::vec3 color = DEFAULT_COLOR);

	// ��x��y��ȡ�ԳƵ�8���㣬ÿ��ȡһ������ͻ�����Ӧ8���㣬����뾶̫��һ�λ�̫���
	static void drawCirclePoints(int xc, int yc, int x, int y, glm::vec3 color = DEFAULT_COLOR);

	// ��(0,0)Ϊԭ���жϵ��Ƿ��ڻ��߷�Χ�ڣ����꣬������ʼ�Ƕȣ���λΪ�ȣ������߽����Ƕ�
	static bool isInArcRange(int x, int y, double startAngle, double endAngle);


	/*
	* @brief  ��ȡ��n���εĶ�������
	*
	* @param n ����α���
	* @param cx��cy Բ��
	* @param r �뾶
	*/
	static std::unique_ptr<POINT[]> getPolygonVertices(int n, int cx, int cy, int r);

	/**
	* @brief ��ȡɨ���߷�Χ
	* 
	* @param points ����ζ�������
	*/
	static std::pair<int, int> getScanlineRange(const std::vector<glm::vec2>& points);
};

struct ETNode
{
	// ���϶˵�y����
	float yMax;

	// ET���б�ʾ�¶˵�x����
	// AET��ʾ����ɨ���ߵĽ���x����
	float x;

	// б�ʵ���
	float k;

	// ��һ����
	ETNode* next;

	ETNode(float yMax, float x, float k) : yMax(yMax), x(x), k(k), next(nullptr) {}
};