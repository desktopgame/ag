#pragma once
#ifdef AG_DIRECT_X
#include <ag/native/dx.hpp>
#include <string>

namespace ag {
class DxUtil {
public:
    static void getString(ID3DBlob* blob, std::string& outString);
    static std::string getString(ID3DBlob* blob);

private:
    DxUtil() = delete;
};
}
#endif