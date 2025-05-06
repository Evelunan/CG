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

	 
public:
	virtual void Transform(const glm::dmat4& mat) override;

protected:
	std::vector<glm::dvec3> points; //�߶εĶ��㼯��
	void(*drawLine)(int, int, int, int, glm::vec3) = nullptr; //�����߶εĺ���ָ��
};

