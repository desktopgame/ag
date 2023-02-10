#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxUtil.hpp>
#include <iostream>

namespace ag {
void DxUtil::getString(ID3DBlob* blob, std::string& outString)
{
    outString.resize(blob->GetBufferSize());
    std::copy_n((char*)blob->GetBufferPointer(), blob->GetBufferSize(), outString.begin());
}
std::string DxUtil::getString(ID3DBlob* blob)
{
    std::string str;
    getString(blob, str);
    return str;
}
}

#endif