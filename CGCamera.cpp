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

void CGCamera::ScaleDistance(float factor)
{
    // 计算从观察目标点到相机位置的方向向量
    glm::vec3 direction = mEye - mTarget;

    // 当前距离
    float currentDistance = glm::length(direction);
    if (currentDistance < 1e-4f) return; // 防止方向长度为0

    // 缩放方向
    direction *= factor;

    // 更新相机位置
    mEye = mTarget + direction;

    this->Projection(mProjectionMode);
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
    // 将角度转换为弧度
    float yawRad = glm::radians(mYaw);
    float pitchRad = glm::radians(mPitch);

    // 球坐标转笛卡尔坐标，计算新相机位置
    glm::vec3 direction;
    direction.x = mDistance * cos(pitchRad) * sin(yawRad);
    direction.y = mDistance * sin(pitchRad);
    direction.z = mDistance * cos(pitchRad) * cos(yawRad);

    mEye = mTarget + direction;

    // 重新设置相机方向
    Projection(mProjectionMode);
}

void CGCamera::ArcballRotate(float yaw, float pitch)
{
    // 更新 yaw 和 pitch 角度
    mYaw += yaw;
    mPitch += pitch;

    // 根据新的 yaw 和 pitch 更新相机位置
    UpdatePosition();
}

void CGCamera::ArcballZoom(float factor)
{
     mDistance *= factor;
    // 限制距离范围
    mDistance = std::clamp(mDistance, 10.0f, 10000.0f);
    UpdatePosition();
}
