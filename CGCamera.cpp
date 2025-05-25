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
	CGTransform::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ�� 
	if (ar.IsStoring())  //���� 
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵�� 
	}
	else //��ȡ 
	{
		//ar >> ; 
	}
}

void CGCamera::Projection(int mode)
{
    viewport()->activate();

    //����ͶӰ�任 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glRenderMode(GL_RENDER);  //������Ⱦ����ѡ�� 
    if (mode == 0) { //��ƽ��ͶӰ������ͶӰ�� 
        glOrtho(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);
    }
    else if (mode == 1) {//͸��ͶӰ 
        glFrustum(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);
        //gluPerspective(45, (wRight- wLeft)/(wTop- wBottom), wNearPlane, wFarPlane); 
    }
    else if(mode == 2){//����ͶӰ����άЧ���� 
        gluOrtho2D(mLeft, mRight, mBottom, mTop);
    }

    //ģ����ͼ�任
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); //�ӵ㣨������������������ϵ 
    gluLookAt(mEye.x, mEye.y, mEye.z, mTarget.x, mTarget.y, mTarget.z, mUp.x, mUp.y, mUp.z); //�����ӵ����
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

    Projection(mProjectionMode); // ����ͶӰ����
}


// �������߽�ķ���
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

// �����ض���ͼ����
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
    // ����ӹ۲�Ŀ��㵽���λ�õķ�������
    glm::vec3 direction = mEye - mTarget;

    // ��ǰ����
    float currentDistance = glm::length(direction);
    if (currentDistance < 1e-4f) return; // ��ֹ���򳤶�Ϊ0

    // ���ŷ���
    direction *= factor;

    // �������λ��
    mEye = mTarget + direction;

    this->Projection(mProjectionMode);
}

void CGCamera::RotateAroundTarget(float yaw, float pitch) 
{
    // �����Ŀ��㵽���λ�õ�����
    glm::vec3 direction = mEye - mTarget;

    // ����������ת��Ϊ�����꣨�뾶��������pitch��ƫ����yaw��
    float radius = glm::length(direction);
    if (radius < 1e-4f) return; // �������

    // ��һ������
    direction = glm::normalize(direction);

    // ��ȡ��ǰ�� pitch �� yaw���ӷ����������ƣ�
    float currentYaw = atan2(direction.x, direction.z);
    float currentPitch = asin(direction.y);

    // ���½Ƕ�
    currentYaw += glm::radians(yaw);
    currentPitch += glm::radians(pitch);

    // ���¼��㷽��
    glm::vec3 newDirection;
    newDirection.x = radius * cos(currentPitch) * sin(currentYaw);
    newDirection.y = radius * sin(currentPitch);
    newDirection.z = radius * cos(currentPitch) * cos(currentYaw);

    // �������λ��
    mEye = mTarget + newDirection;

    this->Projection(mProjectionMode);
}

void CGCamera::UpdatePosition()
{
    // ���Ƕ�ת��Ϊ����
    float yawRad = glm::radians(mYaw);
    float pitchRad = glm::radians(mPitch);

    // ������ת�ѿ������꣬���������λ��
    glm::vec3 direction;
    direction.x = mDistance * cos(pitchRad) * sin(yawRad);
    direction.y = mDistance * sin(pitchRad);
    direction.z = mDistance * cos(pitchRad) * cos(yawRad);

    mEye = mTarget + direction;

    // ���������������
    Projection(mProjectionMode);
}

void CGCamera::ArcballRotate(float yaw, float pitch)
{
    // ���� yaw �� pitch �Ƕ�
    mYaw += yaw;
    mPitch += pitch;

    // �����µ� yaw �� pitch �������λ��
    UpdatePosition();
}

void CGCamera::ArcballZoom(float factor)
{
     mDistance *= factor;
    // ���ƾ��뷶Χ
    mDistance = std::clamp(mDistance, 10.0f, 10000.0f);
    UpdatePosition();
}
