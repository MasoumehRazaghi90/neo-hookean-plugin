FENeoHookeanPI.h
#pragma once
#include <FECore/FEModel.h>
#include <FEBioMech/FEElasticMaterial.h>
class FENeoHookeanPI : public FEElasticMaterial
{
public:
    FENeoHookeanPI(FEModel* pfem);
    bool Init() override;
    bool Validate() override;
    // constitutive response
    mat3ds Stress(FEMaterialPoint& mp) override;
    tens4ds Tangent(FEMaterialPoint& mp) override;
public:
    // user parameters (Young’s modulus and Poisson’s ratio)
    double m_E = 1.0;
    double m_v = 0.499;
private:
    // internal Lamé parameters
    double m_lam = 0.0;
    double m_mu  = 0.0;
    DECLARE_FECORE_CLASS();
};
