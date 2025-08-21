#include <FECore/FECoreKernel.h>
#include "FENeoHookeanPI.h"

// نسخه SDK
FECORE_PLUGIN int GetSDKVersion() { return FE_SDK_VERSION; }

// وقتی پلاگین لود شد
FECORE_PLUGIN void PluginInitialize(FECoreKernel& kernel)
{
    // متریال ما رو رجیستر می‌کنه با اسم neo_hookean_pi
    REGISTER_MATERIAL(FENeoHookeanPI, FE_MAT_ELASTIC, "neo_hookean_pi");
}

// وقتی پلاگین unload شد
FECORE_PLUGIN void PluginCleanup() {}
