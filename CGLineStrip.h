#pragma once
#include "CGGeometry.h" 
class CGLineStrip : public CGGeometry
{
	DECLARE_SERIAL(CGLineStrip);
public:
	CGLineStrip();
	CGLineStrip(const std::vector<glm::dvec3>& points, void(*drawLine)(int, int, int, int, glm::vec3));
	virtual ~CGLineStrip();

	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);

public:
	 void drwaLineStrip(const std::vector<glm::dvec3>& points);

	  void Transform(const glm::dmat4& mat);
public:

	//ƽ�� 
	virtual void Translate(double tx, double ty);	
	//��ת����ʱ��Ϊ�����ȣ�
	virtual void Rotate(double angle, double cx, double cy); 
	//���ţ���������ԭ�����ţ�
	virtual void Scale(double sx, double sy);
	//����X��Գƣ���ά�� ��
	virtual void MirrorXAxis();
	//����Y��Գƣ���ά�� 
	virtual void MirrorYAxis();  
	//����y=x�Գƣ���ά�� 
	virtual void MirrorYeqPosX(); 
	//����y=-x�Գƣ���ά�� 
	virtual void MirrorYeNegPX(); 
	//����ԭ��Գƣ���ά��
	virtual void MirrorOrigin();  
	//�����߶�se�Գƣ���ά�� 
	virtual void Mirror(const glm::dvec3& vs, const glm::dvec3& ve); 
	//��X����� 
	virtual void ShearXAxis(double shx);    
	//��Y����� 
	virtual void ShearYAxis(double shy);  
	//��X��Y����У�shx��shy�ֱ��ʾX��Y����нǶ�
	virtual void ShearXYAxis(double shx, double shy); 
	//���α任����˸������� 
	virtual void Transform(const glm::dmat3& mat);  

protected:
	std::vector<glm::dvec3> points; //�߶εĶ��㼯��
	void(*drawLine)(int, int, int, int, glm::vec3) = nullptr; //�����߶εĺ���ָ��
};

