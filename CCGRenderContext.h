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
	// 默认颜色
	static const glm::vec3 DEFAULT_COLOR;

public:
	CCGRenderContext();
	virtual ~CCGRenderContext();

	// 画五角星，center为五角星中心，len为中心到顶点距离，color1和color2分别为两个三角形颜色
	static void drawPentagram(POINT center, GLint len, glm::vec3 color1, glm::vec3 color2);
	// 实验1-（1）
	static void drawTest1();
	static void draWTest2();


	/**
	* @brief 测试三种画线算法
	*/
	static void testLine();

	/**
	* @brief 测试画圆算法。
	*/
	static void testCircle();

	static void testScanPloygon();

	static void testFill();

	/**
	* @brief 测试多边形的绘制。
	*
	* @param drawLine 绘制线段的函数指针。
	* @param n 多边形的边数。
	* @param x 多边形的中心x坐标。
	* @param y 多边形的中心y坐标。
	* @param r 多边形的半径。
	* @param color 多边形的颜色，默认值为DEFAULT_COLOR。
	*/
	static void testPlyogon(void (*drawLine)(int, int, int, int, glm::vec3), int n, int x, int y, int r, glm::vec3 color = DEFAULT_COLOR);



	/**
	 * @brief 使用DDA算法绘制直线。
	 *
	 * @param x1 起点的x坐标。
	 * @param y1 起点的y坐标。
	 * @param x2 终点的x坐标。
	 * @param y2 终点的y坐标。
	 * @param color 直线的颜色，默认值为DEFAULT_COLOR。
	*/
	static void DDA_Line(int x1, int y1, int x2, int y2, glm::vec3 color = DEFAULT_COLOR);


	/**
	* @brief 使用中点算法绘制直线。
	*
	* @param x1,y1 起点的坐标。
	* @param x2,y2 终点的坐标。
	* @param color 颜色，默认值为DEFAULT_COLOR。
	*/
	static void Midpoint_Line(int x1, int y1, int x2, int y2, glm::vec3 color = DEFAULT_COLOR);

	/**
	* @brief 使用Bresenham算法绘制直线。
	*
	* @param x1,y1 起点的坐标。
	* @param x2,y2 终点的坐标。
	* @param color 颜色，默认值为DEFAULT_COLOR。
	*/
	static void Bresenham_Line(int x1, int y1, int x2, int y2, glm::vec3 color = DEFAULT_COLOR);


	/**
	* @brief 中点画圆算法
	*
	* @param xc,yc 圆心坐标
	* @param r 半径
	* @param color 颜色，默认值为DEFAULT_COLOR。
	*/
	static void MidpointCircle(int xc, int yc, int r, glm::vec3 color = DEFAULT_COLOR);


	/**
	* @brief 通过中点画圆算法画弧线
	*
	* @param xc,yc 圆心坐标
	* @param r 半径
	* @param startAngle 起始角度
	* @param endAngle 结束角度
	* @param color 颜色，默认值为DEFAULT_COLOR。
	*/
	static void drawArcByMidPoint(int xc, int yc, int r, double startAngle, double endAngle, glm::vec3 color = DEFAULT_COLOR);


	/*
	* @brief Bresenham算法画圆
	*
	* @param xc,yc 圆心坐标
	* @param r 半径
	* @param color 颜色
	*/
	static void BresenhamCircle(int xc, int yc, int r, glm::vec3 color = DEFAULT_COLOR);

	/**
	* @breif 扫描线填充算法
	* 
	* @param points 多边形顶点坐标
	* @param color 颜色，默认值为DEFAULT_COLOR
	*/
	static void scanPloygon(const std::vector<glm::vec2> &points, glm::vec3 color = DEFAULT_COLOR);
	
	/**
	* @brief 边界填充算法
	* 
	* @param x,y 区域内部任意一点坐标
	* @param bColor 边界颜色
	* @param nColor 内部颜色
	*/
	static void boundaryFill4(int x, int y, glm::u8vec3 bColor, glm::u8vec3 nColor);

	/**
	* @brief 洪水填充算法
	* 
	* @param x,y 区域内部任意一点坐标
	* @param oldColor 旧颜色
	* @param newColor 新颜色
	*/
	static void floodFill4(int x, int y, glm::u8vec3 oldColor, glm::u8vec3 newColor);


	/**
	* @brief 种子填充算法
	* 
	* @param x,y 区域内部任意一点坐标
	* @param color1 边界表示时为边界颜色，内点表示时为旧颜色
	* @param color2 边界表示时为内点颜色，内点表示时为新颜色
	* @param shouldFill 判断是否填充的函数
	*/
	static void CCGRenderContext::fillHelper(int x, int y,
		glm::u8vec3 color1, glm::u8vec3 color2, 
		std::function<bool(glm::u8vec3, glm::u8vec3)> shouldFill);
private:

	/*
	* @brief 入点集合，长度，画图模式，颜色，是否使用自定义颜色
	* points 点集合
	* len 点集合长度
	* mode 画图模式
	* color 自定义颜色
	* customColor 是否使用自定义颜色
	*/
	static void display(POINT points[], GLint len, GLenum mode, glm::vec3 color = DEFAULT_COLOR, bool customColor = false);

	// 画线算法使用
	static void displayPoint(POINT points[], GLint len, glm::vec3 color = DEFAULT_COLOR);

	// 获取随机点集合
	static std::unique_ptr<POINT[]> getRandomPoints(GLint len);

	// 保证参数x1 <= x2以及dx < dy，返回是否交换了x和y轴
	static bool checkArgs(int& x1, int& y1, int& x2, int& y2);

	// 处理k=0和k=无穷大情况
	static bool kZeroOrNotExist(int x1, int y1, int x2, int y2, glm::vec3 color = DEFAULT_COLOR);

	// 由x，y获取对称的8个点，每获取一个坐标就画出对应8个点，避免半径太大一次画太多点
	static void drawCirclePoints(int xc, int yc, int x, int y, glm::vec3 color = DEFAULT_COLOR);

	// 以(0,0)为原点判断点是否在弧线范围内，坐标，弧线起始角度（单位为度），弧线结束角度
	static bool isInArcRange(int x, int y, double startAngle, double endAngle);


	/*
	* @brief  获取正n边形的顶点坐标
	*
	* @param n 多边形边数
	* @param cx，cy 圆心
	* @param r 半径
	*/
	static std::unique_ptr<POINT[]> getPolygonVertices(int n, int cx, int cy, int r);

	/**
	* @brief 获取扫描线范围
	* 
	* @param points 多边形顶点坐标
	*/
	static std::pair<int, int> getScanlineRange(const std::vector<glm::vec2>& points);
};

struct ETNode
{
	// 边上端点y坐标
	float yMax;

	// ET表中表示下端点x坐标
	// AET表示边与扫描线的交点x坐标
	float x;

	// 斜率倒数
	float k;

	// 下一条边
	ETNode* next;

	ETNode(float yMax, float x, float k) : yMax(yMax), x(x), k(k), next(nullptr) {}
};