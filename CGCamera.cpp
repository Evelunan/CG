#include "pch.h" 
#include "CGCamera.h" 
#include <GL/glu.h> 
#include <algorithm>


IMPLEMENT_SERIAL(CGCamera, CGTransform, 1)

IMPLEMENT_SERIAL(Viewport, CGObject, 1)
Viewport::Viewport()
{
    mX = 0;
    mY = 0;
    mWidth = 0;
    mHeight = 0;
    mClearColor = glm::vec4(0, 0, 0, 1);
    mClearDepth = 1.0f;
    mClearStencil = 0;
    mClearFlags = CF_CLEAR_COLOR_DEPTH;
    mScissorEnabled = true;
}
Viewport::Viewport(int x, int y, int w, int h)
{
    mX = x;
    mY = y;
    mWidth = w;
    mHeight = h;
    mClearColor = glm::vec4(0, 0, 0, 1);
    mClearDepth = 1.0f;
    mClearStencil = 0;
    mClearFlags = CF_CLEAR_COLOR_DEPTH;
    mScissorEnabled = true;
}
void Viewport::activate() const
{
    int x = mX;
    int y = mY;
    int w = mWidth;
    int h = mHeight;

    if (w < 1) w = 1;
    if (h < 1) h = 1;

    glViewport(x, y, w, h);

    if (mClearFlags) {
        GLboolean color_write_mask[4] = { 0,0,0,0 };
        glGetBooleanv(GL_COLOR_WRITEMASK, color_write_mask);

        GLboolean depth_write_mask = 0;
        glGetBooleanv(GL_DEPTH_WRITEMASK, &depth_write_mask);

        GLboolean stencil_write_mask = 0;
        glGetBooleanv(GL_STENCIL_WRITEMASK, &stencil_write_mask);

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_TRUE);
        glStencilMask(GL_TRUE);

        if (mScissorEnabled) {
            glEnable(GL_SCISSOR_TEST);
            glScissor(x, y, w, h);
        }
        else {
            glDisable(GL_SCISSOR_TEST);
        }

        glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
        glClearDepth(mClearDepth);
        glClearStencil(mClearStencil);
        glClear(mClearFlags);

        glColorMask(color_write_mask[0], color_write_mask[1], color_write_mask[2],
            color_write_mask[3]);
        glDepthMask(depth_write_mask);
        glStencilMask(stencil_write_mask);
    }
}
CGCamera::CGCamera()
{
    mViewport = std::make_shared<Viewport>();
}
CGCamera::~CGCamera()
{
}
void CGCamera::Serialize(CArchive& ar)
{
	CGTransform::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
	if (ar.IsStoring())  //保存 
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明 
	}
	else //读取 
	{
		//ar >> ; 
	}
}

void CGCamera::Projection(int mode)
{
    viewport()->activate();

    //设置投影变换 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glRenderMode(GL_RENDER);  //用于渲染（非选择） 
    if (mode == 0) { //正平行投影（正交投影） 
        glOrtho(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);
    }
    else if (mode == 1) {//透视投影 
        glFrustum(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);
        //gluPerspective(45, (wRight- wLeft)/(wTop- wBottom), wNearPlane, wFarPlane); 
    }
    else if(mode == 2){//正交投影（二维效果） 
        gluOrtho2D(mLeft, mRight, mBottom, mTop);
    }

    //模型视图变换
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //视点（相机）相对于世界坐标系 
    gluLookAt(mEye.x, mEye.y, mEye.z, mTarget.x, mTarget.y, mTarget.z, mUp.x, mUp.y, mUp.z); //设置视点参数
}
void CGCamera::ScaleWindow(float factor)
{
    float centerX = (mLeft + mRight) / 2.0f;
    float centerY = (mBottom + mTop) / 2.0f;

    float width = mRight - mLeft;
    float height = mTop - mBottom;

    width *= factor;
    height *= factor;

    mLeft = centerX - width / 2.0f;
    mRight = centerX + width / 2.0f;
    mBottom = centerY - height / 2.0f;
    mTop = centerY + height / 2.0f;

    Projection(mProjectionMode); // 更新投影矩阵
}

void CGCamera::ScaleDistance(float factor)
{
    // 计算从观察目标点到相机位置的方向向量
    glm::vec3 direction = mEye - mTarget;

    // 当前距离
    float currentDistance = glm::length(direction);
    if (currentDistance < 1e-4f) return; // 防止方向长度为0

    // 缩放方向
    direction *= factor;

    // 限制最小最大距离
    float newDistance = glm::length(direction);
    if (newDistance < 10.0f || newDistance > 10000.0f) return;

    // 更新相机位置
    mEye = mTarget + direction;

    this->Projection(mProjectionMode);
}

// 调整各边界的方法
void CGCamera::AdjustLeft(float delta) {
    mLeft += delta * 5.0f;
    Projection(mProjectionMode);
}

void CGCamera::AdjustRight(float delta) {
    mRight += delta * 5.0f;
    Projection(mProjectionMode);
}

void CGCamera::AdjustBottom(float delta) {
    mBottom += delta * 5.0f;
    Projection(mProjectionMode);
}

void CGCamera::AdjustTop(float delta) {
    mTop += delta * 5.0f;
    Projection(mProjectionMode);
}

// 设置特定视图方向
void CGCamera::SetLeftView() {
    mEye = glm::vec3(-200, 0, 0);
    mTarget = glm::vec3(0, 0, 0);
    mUp = glm::vec3(0, 1, 0);
    Projection(mProjectionMode);
}

void CGCamera::SetRightView() {
    mEye = glm::vec3(200, 0, 0);
    mTarget = glm::vec3(0, 0, 0);
    mUp = glm::vec3(0, 1, 0);
    Projection(mProjectionMode);
}

void CGCamera::SetFrontView() {
    mEye = glm::vec3(0, 0, 200);
    mTarget = glm::vec3(0, 0, 0);
    mUp = glm::vec3(0, 1, 0);
    Projection(mProjectionMode);
}

void CGCamera::SetBackView() {
    mEye = glm::vec3(0, 0, -200);
    mTarget = glm::vec3(0, 0, 0);
    mUp = glm::vec3(0, 1, 0);
    Projection(mProjectionMode);
}

void CGCamera::SetTopView() {
    mEye = glm::vec3(0, 200, 0);
    mTarget = glm::vec3(0, 0, 0);
    mUp = glm::vec3(0, 0, -1);
    Projection(mProjectionMode);
}

void CGCamera::SetBottomView() {
    mEye = glm::vec3(0, -200, 0);
    mTarget = glm::vec3(0, 0, 0);
    mUp = glm::vec3(0, 0, 1);
    Projection(mProjectionMode);
}
void CGCamera::RotateAroundTarget(float yaw, float pitch) 
{
    // 计算从目标点到相机位置的向量
    glm::vec3 direction = mEye - mTarget;

    // 将方向向量转换为球坐标（半径、俯仰角pitch、偏航角yaw）
    float radius = glm::length(direction);
    if (radius < 1e-4f) return; // 避免除零

    // 归一化方向
    direction = glm::normalize(direction);

    // 获取当前的 pitch 和 yaw（从方向向量反推）
    float currentYaw = atan2(direction.x, direction.z);
    float currentPitch = asin(direction.y);

    // 更新角度
    currentYaw += glm::radians(yaw);
    currentPitch += glm::radians(pitch);

    // 限制 pitch（避免翻转）
    float pitchLimit = glm::radians(89.0f); // 避免万向锁
    currentPitch = glm::clamp(currentPitch, -pitchLimit, pitchLimit);

    // 重新计算方向
    glm::vec3 newDirection;
    newDirection.x = radius * cos(currentPitch) * sin(currentYaw);
    newDirection.y = radius * sin(currentPitch);
    newDirection.z = radius * cos(currentPitch) * cos(currentYaw);

    // 更新相机位置
    mEye = mTarget + newDirection;

    this->Projection(mProjectionMode);
}

void CGCamera::UpdatePosition()
{
    // pitch 是绕 X 轴的上下角，yaw 是绕 Y 轴的左右角
    float x = mDistance * cosf(mPitch) * sinf(mYaw);
    float y = mDistance * sinf(mPitch);
    float z = mDistance * cosf(mPitch) * cosf(mYaw);

    mEye = mTarget + glm::vec3(-x, -y, -z); // 相机在球面上观察目标

	this->Projection(mProjectionMode); // 更新投影矩阵
}

void CGCamera::ArcballRotate(float dx, float dy)
{
    const float sensitivity = 0.01f; // 控制旋转速度
    mYaw += dx * sensitivity;
    mPitch += dy * sensitivity;

    // 限制 pitch 避免翻转
    float limit = glm::radians(89.0f);
    mPitch = std::clamp(mPitch, -limit, limit);
    this->Projection(mProjectionMode); // 更新投影矩阵
}

void CGCamera::ArcballZoom(float dy)
{
    const float zoomFactor = 1.05f;
    if (dy > 0)
        mDistance *= zoomFactor;
    else
        mDistance /= zoomFactor;

    // 限制距离范围
    mDistance = std::clamp(mDistance, 10.0f, 10000.0f);
    this->Projection(mProjectionMode); // 更新投影矩阵
}
