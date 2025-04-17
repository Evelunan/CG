#include "pch.h"
#include "CGRenderContext.h"

const glm::vec3 CCGRenderContext::DEFAULT_COLOR = glm::vec3(1.0f, 0.0f, 0.0f);
// 常量 PI
const double PI = 3.14159265358979323846;

CCGRenderContext::CCGRenderContext()
{
}
CCGRenderContext::~CCGRenderContext()
{
}

void CCGRenderContext::drawPentagram(POINT center, GLint len, glm::vec3 color1, glm::vec3 color2)
{
	double tan18 = tan(18 * PI / 180);
	double tan36 = tan(36 * PI / 180);
	GLdouble y1 = len / (tan36 / tan18 + 1);
	GLdouble x1 = y1 * tan36;
	// 保存当前矩阵状态
	glPushMatrix();
	// 将坐标系原点移动到中心点 center
	glTranslated(center.x, center.y, 0);

	for (int i = 0; i < 5; ++i) {
		// 绘制 tri1
		glBegin(GL_TRIANGLES);
		glColor3f(color1.r, color1.g, color1.b);
		glVertex2d(0, 0); // 中心点
		glVertex2d(x1, y1);
		glVertex2d(0, len);
		glEnd();
		// 绘制 tri2
		glBegin(GL_TRIANGLES);
		glColor3f(color2.r, color2.g, color2.b);
		glVertex2d(0, 0); // 中心点
		glVertex2d(-x1, y1);
		glVertex2d(0, len);
		glEnd();
		// 旋转 72 度
		glRotated(72, 0, 0, 1); // 绕 Z 轴旋转 72 度
	}
	// 恢复之前的矩阵状态
	glPopMatrix();
	glFlush();
}

void CCGRenderContext::drawTest1()
{
	POINT points[] = { {920, 50}, {980, 180}, {1050, 120}, {1100, 30}, {1150, 160}, {1000, 80}, {1180, 100}, {950, 10} };
	POINT points_line[] = { {50, 450}, {250, 550}, {100, 470}, {200, 580}, {150, 490}, {270, 520}, {70, 500}, {220, 570} };
	POINT points_line_strip[] = { {50, 250}, {250, 350}, {100, 300}, {200, 380}, {150, 280} };
	POINT points_line_loop[] = { {50, 50}, {250, 150}, {100, 100}, {200, 50}, {150, 150}, {200, 100} };
	POINT points_triangles[] = { {350, 450}, {400, 550}, {500, 450}, {450, 500}, {550, 550}, {600, 500} };
	POINT points_triangle_strip[] = { {350, 250}, {450, 350}, {550, 250}, {400, 300}, {500, 300}, {475, 375} };
	POINT points_triangle_fan[] = { {350, 50}, {400, 180}, {500, 150}, {550, 125}, {570, 30} };
	POINT points_quads[] = { {600, 420}, {640, 500}, {700, 550}, {725, 400}, {760, 400}, {820, 500}, {870, 550}, {850, 500} };
	POINT points_quad_strip[] = { {650, 220}, {620, 300}, {700, 230}, {720, 320}, {800, 250}, {750, 350}, {850, 270}, {875, 380} };
	POINT points_polygon[] = { {620, 100}, {700, 180}, {800, 120}, {880, 50}, {750, 30} };

	display(points, 8, GL_POINTS);
	display(points_line, 8, GL_LINES);
	display(points_line_strip, 5, GL_LINE_STRIP);
	display(points_line_loop, 6, GL_LINE_LOOP);
	display(points_triangles, 6, GL_TRIANGLES);
	display(points_triangle_strip, 6, GL_TRIANGLE_STRIP);
	display(points_triangle_fan, 5, GL_TRIANGLE_FAN);
	display(points_quads, 8, GL_QUADS);
	display(points_quad_strip, 8, GL_QUAD_STRIP);
	display(points_polygon, 5, GL_POLYGON);
}

void CCGRenderContext::draWTest2()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	drawPentagram({ 1050, 500 }, 50, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	drawPentagram({ 1050, 300 }, 100, { 0.8f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.9f });
}

void CCGRenderContext::testLine()
{

	testPlyogon(DDA_Line, 14, 150, 150, 75);

	testPlyogon(Midpoint_Line, 14, 350, 150, 75);

	testPlyogon(Bresenham_Line, 14, 550, 150, 75);
}

void CCGRenderContext::testCircle()
{
	for (int i = 20; i <= 100; i += 10)
	{
		MidpointCircle(1000, 450, i);
		MidpointCircle(700, 450, i);
		BresenhamCircle(1000, 200, i);
	}
	drawArcByMidPoint(50, 500, 50, 0, 90);

	drawArcByMidPoint(150, 500, 50, 0, 180);

	drawArcByMidPoint(250, 500, 50, 0, 270);

	drawArcByMidPoint(350, 500, 50, 0, 360);


}

void CCGRenderContext::testScanPloygon()
{
	using namespace std;
	using namespace glm;
	// 测试扫描线填充算法

	vector<vec2> points1 = { {100, 200}, {200, 250}, {300, 200}, {300, 380}, {100, 300} };
	vector<vec2> points2 = { {100, 400}, {200, 450}, {300, 400}, {200, 580} };

	vector<vec2> points3 = { {350, 300}, {400, 250}, {450, 320}, {430, 400}, {380, 380} };
	vector<vec2> points4 = { {500, 300}, {600, 250}, {650, 320}, {630, 400}, {580, 380} };

	vector<vec2> poinst5 = { {700, 300}, {900, 300}, {1000, 500},  {800, 500} };
	scanPloygon(points1);
	scanPloygon(points2);
	scanPloygon(points3);
	scanPloygon(points4);
	scanPloygon(poinst5);
}

void CCGRenderContext::testFill()
{
	BresenhamCircle(100, 100, 50);
	BresenhamCircle(300, 100, 50);

	glm::u8vec3 color1(255, 0, 0), color2(0, 255, 0);

	boundaryFill4(300, 100, color1, color2);

	// 测试边界填充算法
	boundaryFill4(100, 100, color1, color2);
	// 测试洪水填充算法
	floodFill4(100, 100, color2, color1);
}

void CCGRenderContext::testPlyogon(void(*drawLine)(int, int, int, int, glm::vec3), int n, int x, int y, int r, glm::vec3 color)
{
	auto points = getPolygonVertices(n, x, y, r);
	// 遍历相邻顶点并绘制边
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			// 绘制边
			drawLine(points[i].x, points[i].y, points[j].x, points[j].y, color);
		}
	}
}



void CCGRenderContext::DDA_Line(int x1, int y1, int x2, int y2, glm::vec3 color)
{
	if (kZeroOrNotExist(x1, y1, x2, y2, color))
		return;

	bool flag = checkArgs(x1, y1, x2, y2);
	int dx = x2 - x1, dy = y2 - y1;

	double k = double(y2 - y1) / double(x2 - x1);
	double y = y1 + 0.5;
	double x = x1 + 0.5;
	int len = dx + 1;
	auto points = std::make_unique<POINT[]>(len);
	for (int i = 0; i <= dx; i++)
	{
		// 没有交换x和y轴
		if (!flag)
		{
			//SetPixel(hdc, (int)(x + i), (int)(y), color);
			points[i].x = int(x + i);
			points[i].y = int(y);
		}
		else
		{
			//SetPixel(hdc, (int)(y), (int)(x + i), color);
			points[i].x = int(y);
			points[i].y = int(x + i);
		}
		y += k;
	}
	displayPoint(points.get(), len, color);
}

void CCGRenderContext::Midpoint_Line(int x1, int y1, int x2, int y2, glm::vec3 color)
{
	if (kZeroOrNotExist(x1, y1, x2, y2, color))
		return;
	bool flag = checkArgs(x1, y1, x2, y2);
	// b, -a
	int dx = x2 - x1, dy = y2 - y1;
	int d = 0, deta1 = 0, deta2 = 0;
	double k = double(y2 - y1) / double(x2 - x1);
	int incY = 1;
	if (k > 0)
	{
		d = dx - (dy << 1);
		deta1 = -(dy << 1);
		deta2 = (dx - dy) << 1;
		incY = 1;
	}
	else if (k < 0)
	{
		d = -(dy << 1) + dx;
		deta1 = (-dy - dx) << 1;
		deta2 = -(dy << 1);
		incY = -1;
	}
	int len = dx + 1;
	auto points = std::make_unique<POINT[]>(len);

	for (int i = 0; i <= dx; i++)
	{
		if (!flag)
		{
			//SetPixel(hdc, x1 + i, y1, color);
			points[i].x = x1 + i;
			points[i].y = y1;
		}
		else
		{
			//SetPixel(hdc, y1, x1 + i, color);
			points[i].x = y1;
			points[i].y = x1 + i;
		}
		if (d > 0)
		{
			d += deta1;
			if (k < 0)
				y1 += incY;
		}
		else
		{
			d += deta2;
			if (k > 0)
				y1 += incY;
		}
	}
	displayPoint(points.get(), len, color);
}

void CCGRenderContext::Bresenham_Line(int x1, int y1, int x2, int y2, glm::vec3 color)
{
	if (kZeroOrNotExist(x1, y1, x2, y2, color))
		return;
	bool flag = checkArgs(x1, y1, x2, y2);
	int dx = x2 - x1, dy = y2 - y1;
	int d0, deta1, deta2, incY;
	double k = double(y2 - y1) / double(x2 - x1);
	if (k > 0)
	{
		d0 = dy * 2 - dx;
		deta1 = (dy - dx) * 2;
		deta2 = dy * 2;
		incY = 1;
	}
	else
	{
		d0 = -(dy * 2) - dx;
		deta1 = -((dy + dx) * 2);
		deta2 = -(dy * 2);
		incY = -1;
	}

	int len = dx + 1;
	auto points = std::make_unique<POINT[]>(len);
	for (int i = 0; i <= dx; i++)
	{
		if (!flag)
		{
			//SetPixel(hdc, x1 + i, y1, color);
			points[i].x = x1 + i;
			points[i].y = y1;
		}
		else
		{
			//SetPixel(hdc, y1, x1 + i, color);
			points[i].x = y1;
			points[i].y = x1 + i;
		}
		if (d0 < 0)
			d0 += deta2;
		else
		{
			d0 += deta1;
			y1 += incY;
		}

	}
	displayPoint(points.get(), len, color);
}

void CCGRenderContext::MidpointCircle(int xc, int yc, int r, glm::vec3 color)
{
	int x = 0, y = r;
	int d = 1 - r;  // 初始判别式


	while (x <= y)
	{
		drawCirclePoints(xc, yc, x, y, color);
		x++;
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			y--;
			d += 2 * (x - y) + 5;
		}
	}
}

void CCGRenderContext::drawArcByMidPoint(int xc, int yc, int r, double startAngle, double endAngle, glm::vec3 color)
{
	int x = 0, y = r;
	int d = 1 - r;  // 初始判别式
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	while (x <= y)
	{
		POINT points[8] = {
		{ x, y }, { -x, y }, { x, -y }, { -x, -y },
		{ y, x }, { -y, x }, { y, -x }, { -y, -x }
		};
		for (int i = 0; i < 8; ++i)
		{
			if (isInArcRange(points[i].x, points[i].y, startAngle, endAngle))
			{
				glVertex2i(xc + points[i].x, yc + points[i].y);
			}
		}
		x++;
		if (d < 0)
		{
			d += 2 * x + 3;
		}
		else
		{
			y--;
			d += 2 * (x - y) + 5;
		}
	}
	glEnd();
}
void CCGRenderContext::BresenhamCircle(int xc, int yc, int r, glm::vec3 color)
{
	int x = 0, y = r;
	int d = 1 - r;  // 初始判别式
	int d1, d2;
	int choose;
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	while (y >= 0)
	{
		glVertex2i(xc + x, yc + y);
		glVertex2i(xc - x, yc + y);
		glVertex2i(xc + x, yc - y);
		glVertex2i(xc - x, yc - y);

		if (d < 0)
		{
			d1 = 2 * (d + y) - 1;
			if (d1 <= 0)
				choose = 1;
			else
				choose = 2;
		}
		else
		{
			d2 = 2 * (d - x) - 1;
			if (d2 <= 0)
				choose = 2;
			else
				choose = 3;
		}
		switch (choose)
		{
		case 1: x++; d += 2 * x + 1; break;
		case 2: x++; y--; d += 2 * (x - y + 1); break;
		case 3: y--; d += -2 * y + 1; break;
		}
	}
	glEnd();
}

void CCGRenderContext::scanPloygon(const std::vector<glm::vec2>& points, glm::vec3 color)
{
	size_t len = points.size();
	if (len < 3) return; // 多边形至少需要三个顶点
	using namespace std;
	// 获取扫描线范围
	auto [yMin, yMax] = getScanlineRange(points);
	// 创建边表
	vector<vector<ETNode>> edgeTable(yMax - yMin + 1);

	// 遍历所有边，填充边表
	for (int i = 0; i < len; i++)
	{
		auto p1 = points[i];
		auto p2 = points[(i + 1) % len]; // 下一个点，形成边

		if (p1.y > p2.y) swap(p1, p2);

		if (p1.y == p2.y) continue; // 水平边不处理)
		// 计算斜率倒数
		float k = (p2.x - p1.x) / (p2.y - p1.y);
		ETNode node(p2.y, p1.x, k);
		edgeTable[int(p1.y - yMin)].push_back(node);
	}

	// 创建活动边表 (Active Edge Table, AET)
	std::vector<ETNode> activeEdgeTable;

	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	// 开始扫描线填充
	for (int y = yMin; y <= yMax; ++y)
	{
		// 将当前扫描线的边加入 AET
		for (auto& node : edgeTable[y - yMin])
		{
			activeEdgeTable.push_back(node);
		}

		// 移除 yMax <= y 的边（超出范围的边）
		activeEdgeTable.erase(
			std::remove_if(activeEdgeTable.begin(), activeEdgeTable.end(),
				[y](const ETNode& node) { return node.yMax <= y; }),
			activeEdgeTable.end());


		// 按 x 坐标排序
		std::sort(activeEdgeTable.begin(), activeEdgeTable.end(),
			[](const ETNode& a, const ETNode& b) { return a.x < b.x; });

		for (size_t i = 0; i < activeEdgeTable.size(); i += 2) {
			int xStart = static_cast<int>(std::ceil(activeEdgeTable[i].x));
			int xEnd = static_cast<int>(std::floor(activeEdgeTable[i + 1].x));

			for (int x = xStart; x <= xEnd; ++x) {
				glVertex2i(x, y);
			}
		}

		// 更新 AET 中每条边的 x 值
		for (auto& node : activeEdgeTable) {
			node.x += node.k;
		}
	}
	glEnd();

}


void CCGRenderContext::boundaryFill4(int x, int y, glm::u8vec3 bColor, glm::u8vec3 nColor)
{
	// 定义填充条件：当前颜色不是边界颜色且不是新颜色
	auto shouldFill = [&](glm::u8vec3 currentColor, glm::u8vec3 boundaryColor) -> bool {
		return currentColor != boundaryColor && currentColor != nColor;
		};

	// 调用通用填充函数
	fillHelper(x, y, bColor, nColor, shouldFill);
}

void CCGRenderContext::floodFill4(int x, int y, glm::u8vec3 oldColor, glm::u8vec3 newColor)
{
	// 定义填充条件：当前颜色等于目标颜色
	auto shouldFill = [&](glm::u8vec3 currentColor, glm::u8vec3 targetColor) -> bool {
		return currentColor == targetColor;
		};

	// 调用通用填充函数
	fillHelper(x, y, oldColor, newColor, shouldFill);
}

void CCGRenderContext::fillHelper(int x, int y, glm::u8vec3 color1, glm::u8vec3 color2,
	std::function<bool(glm::u8vec3, glm::u8vec3)> shouldFill)
{
	// 获取窗口大小
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int width = viewport[2] + 1;
	int height = viewport[3] + 1;

	// 读取整个帧缓冲区的颜色数据
	std::vector<GLubyte> pixels(width * height * 3);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

	// 定义一个栈用于迭代填充
	std::stack<std::pair<int, int>> stack;
	stack.push({ x, y });

	// 辅助函数：检查是否在边界内
	auto isValidPixel = [&](int x, int y) -> bool {
		return x >= 0 && x < width && y >= 0 && y < height;
		};

	// 设置绘制颜色
	glColor3ub(color2.r, color2.g, color2.b);

	// 开始绘制
	glBegin(GL_POINTS);
	while (!stack.empty())
	{
		auto [cx, cy] = stack.top();
		stack.pop();

		// 计算当前像素的索引
		int index = (cy * width + cx) * 3;

		// 提取当前像素的颜色
		glm::u8vec3 currentColor(pixels[index], pixels[index + 1], pixels[index + 2]);

		// 检查当前颜色是否满足填充条件
		if (!shouldFill(currentColor, color1))
			continue;

		// 更新像素颜色
		pixels[index] = color2.r;
		pixels[index + 1] = color2.g;
		pixels[index + 2] = color2.b;

		// 绘制当前像素
		glVertex2i(cx, cy);

		// 将四个方向的像素压入栈中（确保有效）
		if (isValidPixel(cx + 1, cy)) stack.push({ cx + 1, cy }); // 右
		if (isValidPixel(cx - 1, cy)) stack.push({ cx - 1, cy }); // 左
		if (isValidPixel(cx, cy + 1)) stack.push({ cx, cy + 1 }); // 上
		if (isValidPixel(cx, cy - 1)) stack.push({ cx, cy - 1 }); // 下
	}
	glEnd();
}

void CCGRenderContext::display(POINT points[], GLint len, GLenum mode, glm::vec3 color, bool customColor)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_FLAT);	// 单色模式
	if (customColor)
	{
		glColor3f(color.r, color.g, color.b);
	}
	// 设置点的大小
	if (mode == GL_POINTS)
	{
		//glPointSize(5.0f);  // 设置点的大小为 5 像素
	}

	glBegin(mode);

	for (int i = 0; i < len; i++)
	{
		if (!customColor)
		{
			// 为每个顶点设置不同的颜色
			glColor3f(static_cast<float>(i) / len,  // 红色分量
				static_cast<float>(len - i) / len,  // 绿色分量
				0.5f);  // 蓝色分量固定
		}
		glVertex2i(points[i].x, points[i].y);
	}
	glEnd();
	glFlush();
}

void CCGRenderContext::displayPoint(POINT points[], GLint len, glm::vec3 color)
{
	display(points, len, GL_POINTS, color, true);
}

std::unique_ptr<POINT[]> CCGRenderContext::getRandomPoints(GLint len)
{
	if (len <= 0) {
		return nullptr; // 如果输入无效，返回空指针
	}

	// 使用 std::make_unique 分配数组
	auto points = std::make_unique<POINT[]>(len);

	// 初始化随机数种子
	srand(static_cast<unsigned int>(time(nullptr)));

	// 填充随机点
	for (GLint i = 0; i < len; ++i) {
		points[i].x = X_MIN + rand() % (X_MAX - X_MIN + 1); // 随机生成 x 坐标
		points[i].y = Y_MIN + rand() % (Y_MAX - Y_MIN + 1); // 随机生成 y 坐标
	}

	return points; // 返回智能指针
}

bool CCGRenderContext::checkArgs(int& x1, int& y1, int& x2, int& y2)
{
	using namespace std;
	bool flag = false;
	// 先判断石否需要交换 x 和 y
	double dx = abs(x2 - x1), dy = abs(y2 - y1);
	if (dy > dx)
	{
		swap(x1, y1);
		swap(x2, y2);
		flag = true;
	}
	// 保证 x1 <= x2
	if (x1 > x2)
	{
		swap(x1, x2);
		swap(y1, y2);
	}
	return flag;
}

bool CCGRenderContext::kZeroOrNotExist(int x1, int y1, int x2, int y2, glm::vec3 color)
{
	using namespace std;
	// k not exist
	if (x1 == x2)
	{
		if (y1 > y2)
			swap(y1, y2);
		int len = y2 - y1 + 1;
		auto points = std::make_unique<POINT[]>(len);
		for (int i = y1; i <= y2; i++)
		{
			//SetPixel(hdc, x1, i, color);
			points[i - y1].x = x1;
			points[i - y1].y = i;
		}
		displayPoint(points.get(), len, color);
		return true;
	}
	else if (y1 == y2)
	{
		if (x1 > x2)
			swap(x1, x2);
		int len = x2 - x1 + 1;
		auto points = std::make_unique<POINT[]>(len);
		for (int i = x1; i <= x2; i++)
		{
			//SetPixel(hdc, i, y1, color);
			points[i - x1].x = i;
			points[i - x1].y = y1;
		}
		displayPoint(points.get(), len, color);
		return true;
	}
	return false;
}

void CCGRenderContext::drawCirclePoints(int xc, int yc, int x, int y, glm::vec3 color)
{
	int len = 8;
	auto points = std::make_unique<POINT[]>(len);
	points[0] = { xc + x, yc + y };
	points[1] = { xc - x, yc + y };
	points[2] = { xc + x, yc - y };
	points[3] = { xc - x, yc - y };
	points[4] = { xc + y, yc + x };
	points[5] = { xc - y, yc + x };
	points[6] = { xc + y, yc - x };
	points[7] = { xc - y, yc - x };
	displayPoint(points.get(), len, color);
}


bool CCGRenderContext::isInArcRange(int x, int y, double startAngle, double endAngle)
{
	double angle = atan2(y, x) * 180 / PI; // 计算角度
	if (angle < 0) angle += 360; // 保持角度为 0~360 范围

	// 处理跨越 360° 的情况
	if (startAngle < endAngle)
	{
		return angle >= startAngle && angle <= endAngle;
	}
	else
	{
		return angle >= startAngle || angle <= endAngle; // 跨越 0° 处理
	}
}

std::unique_ptr<POINT[]> CCGRenderContext::getPolygonVertices(int n, int cx, int cy, int r)
{
	auto points = std::make_unique<POINT[]>(n);
	// 顶点之间角度步长（弧度制）
	double angleStep = 2 * PI / n;
	for (int i = 0; i < n; i++)
	{
		double angle = i * angleStep;
		int x = static_cast<int>(cx + r * cos(angle));
		int y = static_cast<int>(cy + r * sin(angle));
		points[i] = { x, y };
	}
	return points;
}

std::pair<int, int> CCGRenderContext::getScanlineRange(const std::vector<glm::vec2>& points)
{
	// 初始化 yMin 和 yMax
	float yMin = points[0].y;
	float yMax = points[0].y;

	// 遍历所有顶点，找到 y 的最小值和最大值
	for (const auto& point : points) {
		if (point.y < yMin) yMin = point.y;
		if (point.y > yMax) yMax = point.y;
	}

	// 返回扫描线范围
	return { static_cast<int>(std::floor(yMin)), static_cast<int>(std::ceil(yMax)) };
}
