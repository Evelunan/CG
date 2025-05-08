#pragma once
#include "CGRenderable.h"

class TessellationHints;
class CGSphere :public CGRenderable
{
public:

	DECLARE_SERIAL(CGSphere);
	CGSphere(float radius = 0.5f);
	virtual ~CGSphere();

	void setRadius(float radius);
	float getRadius()const;
	float getRadius();
	void setTessellationHints(std::shared_ptr<TessellationHints> hints);
	TessellationHints* tessellationHints() { return mTessellationHints.get(); }
	const TessellationHints* tessellationHints() const { return mTessellationHints.get(); }
protected:
	virtual void buildDisplayList() override;
protected:
	float radius;
	std::shared_ptr<TessellationHints> mTessellationHints = nullptr;
};

