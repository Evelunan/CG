#pragma once
#include "CGRenderState.h"
class CGShadeModel : public CGRenderState
{
public:
    CGShadeModel(EShadeModel shademodel = SM_SMOOTH);
    virtual ~CGShadeModel() = default;
    virtual ERenderState type() const { return RS_ShadeModel; }
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const;
    void set(EShadeModel shademodel) { mShadeModel = shademodel; }
    EShadeModel shadeModel() const { return mShadeModel; }
protected:
    EShadeModel mShadeModel;
};

