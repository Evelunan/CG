#pragma once 
#include "CGNode.h" 

class CGRenderContext; //Ԥ���� 
class CGCamera;  //Ԥ���� 
class CGRenderable : public CGNode
{
    DECLARE_SERIAL(CGRenderable)
public:
    CGRenderable();
    virtual ~CGRenderable();
    //���л� 
    virtual void Serialize(CArchive& ar) override;
    //���ƶ���������������д�� 
    virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
    virtual CGRenderable* asRenderable() { return this; }
    virtual const CGRenderable* asRenderable() const { return this; }

public:

	//ƽ�� 
	virtual void Translate(double tx, double ty) {}
	//��ת����ʱ��Ϊ�����ȣ�
	virtual void Rotate(double angle, double cx, double cy) {}
	//���ţ���������ԭ�����ţ�
	virtual void Scale(double sx, double sy) {}
	//���ţ�����ָ�������ţ�
	virtual void Scale(double sx, double sy, double cx, double cy) {}
	//����X��Գƣ���ά�� 
	virtual void MirrorXAxis() {}
	//����Y��Գƣ���ά�� 
	virtual void MirrorYAxis() {}
	//����y=x�Գƣ���ά�� 
	virtual void MirrorYeqPosX() {}
	//����y=-x�Գƣ���ά�� 
	virtual void MirrorYeNegPX() {}
	//����ԭ��Գƣ���ά��
	virtual void MirrorOrigin() {}
	//�����߶�se�Գƣ���ά�� 
	virtual void Mirror(const glm::dvec3& vs, const glm::dvec3& ve) {}
	//��X����� 
	virtual void ShearXAxis(double shx) {}
	//��Y����� 
	virtual void ShearYAxis(double shy) {}
	//��X��Y����� 
	virtual void ShearXYAxis(double shx, double shy) {}
	//���α任����˸������� 
	virtual void Transform(const glm::dmat3& mat) {}
};