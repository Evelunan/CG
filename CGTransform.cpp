#include "pch.h" 
#include "CGTransform.h" 

IMPLEMENT_SERIAL(CGTransform, CGGroup, 1)

CGTransform::CGTransform()
{
}

CGTransform::~CGTransform()
{
}
void CGTransform::Serialize(CArchive& ar)
{
    CGGroup::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要） 
    if (ar.IsStoring())  //保存 
    {
        //ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明 
    }
    else //读取 
    {
        //ar >> ;
    }
}

bool CGTransform::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
    if (pRC == nullptr || pCamera == nullptr)
        return false;

    glPushMatrix(); //保存 
    glMultMatrixf(glm::value_ptr(localMatrix())); //相对上一级变换 
    if (getRenderStateSet()) {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        getRenderStateSet()->apply(pCamera, pRC);
    }
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
    {
        (*itr)->Render(pRC, pCamera);
    }
    if (getRenderStateSet()) {
        glPopAttrib();
    }
    glPopMatrix();  //恢复 

    return true;
}

void CGTransform::dirtyWorldMatrix()
{
    mWorldMatrixDirty = true;
    for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
    {
        CGTransform* trans = (*itr != nullptr) ? (*itr)->asTransform() : 0;
        if (trans) {
            trans->dirtyWorldMatrix();
        }
    }
    dirtyBound();
}

void CGTransform::setLocalMatrix(const glm::mat4& m)
{
    mLocalMatrix = m;
    dirtyWorldMatrix(); //局部矩阵变化会导致到世界坐标系的矩阵改变。
}

void CGTransform::translate(float tx, float ty, float tz)
{
    // 创建一个表示平移操作的矩阵
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(tx, ty, tz));
    // 将该平移矩阵与当前局部矩阵相乘（右乘）
    postMultiply(translationMatrix);
}

void CGTransform::translate(const glm::vec3& t)
{
    // 重载函数，使用vec3作为参数
    translate(t.x, t.y, t.z);
}

void CGTransform::scale(float sx, float sy, float sz)
{
    // 创建一个表示缩放操作的矩阵
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz));
    // 将该缩放矩阵与当前局部矩阵相乘（右乘）
    postMultiply(scaleMatrix);
}

void CGTransform::rotate(float degrees, float x, float y, float z)
{
    // 创建一个表示旋转变换的矩阵
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::vec3(x, y, z));
    // 将该旋转矩阵与当前局部矩阵相乘（右乘）
    postMultiply(rotationMatrix);
}

void CGTransform::preMultiply(const glm::mat4& m)
{
    // 更新局部矩阵：将传入的矩阵左乘到局部矩阵上
    mLocalMatrix = m * mLocalMatrix;
    // 标记世界矩阵为需要更新
    dirtyWorldMatrix();
}

void CGTransform::postMultiply(const glm::mat4& m)
{
    // 更新局部矩阵：将传入的矩阵右乘到局部矩阵上
    mLocalMatrix = mLocalMatrix * m;
    // 标记世界矩阵为需要更新
    dirtyWorldMatrix();
}
