#pragma once 
#include "CGGeometry.h" 
class CGLineSegment : public CGGeometry
{
	DECLARE_SERIAL(CGLineSegment)
public:
	CGLineSegment();
	CGLineSegment(const glm::dvec3& start, const glm::dvec3& end);
	virtual ~CGLineSegment();
	//���л� 
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д�� 
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);


public:
	virtual void Transform(const glm::dmat4& mat) override;

protected:
	glm::dvec3 mStart;
	glm::dvec3 mEnd;

};