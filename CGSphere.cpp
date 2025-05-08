#include "pch.h"
#include "CGSphere.h"
#include "TessellationHints.h"

IMPLEMENT_SERIAL(CGSphere, CGRenderable, 1)
CGSphere::CGSphere(float radius):radius(radius)
{

}

CGSphere::~CGSphere()
{
}

void CGSphere::setRadius(float radius)
{
	this->radius = radius;
}

float CGSphere::getRadius() const
{
    return radius;
}

float CGSphere::getRadius()
{
    return radius;
}

void CGSphere::setTessellationHints(std::shared_ptr<TessellationHints> hints)
{
	if (mTessellationHints.get() != hints.get())
	{
		mTessellationHints = hints;
		mDisplayListDirty = true;
	}
}

void CGSphere::buildDisplayList()
{
    auto hints = tessellationHints();
    bool createBody = (hints ? hints->createBody() : true);
    int slices = (hints ? hints->targetSlices() : 40); // 默认细分数
    int stacks = (hints ? hints->targetStacks() : 20);

    if (!createBody)
        return;

    float dTheta = glm::pi<float>() / stacks;
    float dPhi = 2.0f * glm::pi<float>() / slices;

    glBegin(GL_QUADS);
    for (int i = 0; i < stacks; ++i)
    {
        float theta1 = i * dTheta - glm::half_pi<float>(); // 从 -π/2 到 π/2
        float theta2 = (i + 1) * dTheta - glm::half_pi<float>();

        for (int j = 0; j < slices; ++j)
        {
            float phi1 = j * dPhi;
            float phi2 = (j + 1) * dPhi;

            // 四个顶点位置
            glm::vec3 v1(radius * cos(theta1) * cos(phi1),
                radius * sin(theta1),
                radius * cos(theta1) * sin(phi1));

            glm::vec3 v2(radius * cos(theta2) * cos(phi1),
                radius * sin(theta2),
                radius * cos(theta2) * sin(phi1));

            glm::vec3 v3(radius * cos(theta2) * cos(phi2),
                radius * sin(theta2),
                radius * cos(theta2) * sin(phi2));

            glm::vec3 v4(radius * cos(theta1) * cos(phi2),
                radius * sin(theta1),
                radius * cos(theta1) * sin(phi2));

            // 法向量与顶点一致（单位球面）
            glm::vec3 n1 = glm::normalize(v1);
            glm::vec3 n2 = glm::normalize(v2);
            glm::vec3 n3 = glm::normalize(v3);
            glm::vec3 n4 = glm::normalize(v4);

            // 纹理坐标
            float u1 = static_cast<float>(j) / slices;
            float u2 = static_cast<float>(j + 1) / slices;
            float v1_ = static_cast<float>(i) / stacks;
            float v2_ = static_cast<float>(i + 1) / stacks;

            // 第一个四边形
            glNormal3fv(&n1[0]);
            glTexCoord2f(u1, v1_);
            glVertex3fv(&v1[0]);

            glNormal3fv(&n2[0]);
            glTexCoord2f(u1, v2_);
            glVertex3fv(&v2[0]);

            glNormal3fv(&n3[0]);
            glTexCoord2f(u2, v2_);
            glVertex3fv(&v3[0]);

            glNormal3fv(&n4[0]);
            glTexCoord2f(u2, v1_);
            glVertex3fv(&v4[0]);
        }
    }
    glEnd();
}
