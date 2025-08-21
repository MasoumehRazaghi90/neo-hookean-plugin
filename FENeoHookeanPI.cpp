#include "FENeoHookeanPI.h"

// تعریف پارامترها
BEGIN_FECORE_CLASS(FENeoHookeanPI, FEElasticMaterial)
    ADD_PARAMETER(m_E, FE_RANGE_GREATER(0.0), "E");
    ADD_PARAMETER(m_v, FE_RANGE_RIGHT_OPEN(-1.0,0.5), "v");
END_FECORE_CLASS();

FENeoHookeanPI::FENeoHookeanPI(FEModel* pfem) : FEElasticMaterial(pfem) {}

bool FENeoHookeanPI::Init()
{
    if (FEElasticMaterial::Init() == false) return false;
    return true;
}

bool FENeoHookeanPI::Validate()
{
    if (FEElasticMaterial::Validate() == false) return false;

    // محاسبه ثابت‌های لامه از E و v
    m_lam = (m_v * m_E) / ((1.0 + m_v) * (1.0 - 2.0 * m_v));
    m_mu  = 0.5 * m_E / (1.0 + m_v);

    return true;
}

// --- معادله اصلی Neo-Hookean ---
mat3ds FENeoHookeanPI::Stress(FEMaterialPoint& mp)
{
    FEElasticMaterialPoint& pt = *mp.ExtractData<FEElasticMaterialPoint>();

    const double J = pt.m_J;
    const mat3ds b = pt.LeftCauchyGreen();
    const mat3dd I(1.0);

    // σ = μ/J (b - I) + λ ln(J)/J I
    return (b - I) * (m_mu / J) + I * (m_lam * log(J) / J);
}

tens4ds FENeoHookeanPI::Tangent(FEMaterialPoint& mp)
{
    FEElasticMaterialPoint& pt = *mp.ExtractData<FEElasticMaterialPoint>();
    const double J = pt.m_J;

    const double lam1 = m_lam / J;
    const double mu1  = (m_mu - m_lam * log(J)) / J;

    const mat3dd I(1.0);
    const tens4ds IxI = dyad1s(I);
    const tens4ds I4  = dyad4s(I);

    // c = 2μ1 * I4 + λ1 * (I ⊗ I)
    return I4 * (2.0 * mu1) + IxI * lam1;
}
