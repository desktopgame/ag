#ifdef AG_DIRECT_X
#include <ag/ImageIO.hpp>
#include <ag/graphics/dx/DxTexture.hpp>
#include <stdexcept>

namespace ag {
DxTexture::DxTexture(ID3D12Device* device)
    : m_width(0)
    , m_height(0)
    , m_device(device)
    , m_resource(nullptr)
{
}
void DxTexture::update(int width, int height, const uint8_t* pixels)
{
    D3D12_HEAP_PROPERTIES texHeapProps = {};
    texHeapProps.Type = D3D12_HEAP_TYPE_CUSTOM;
    texHeapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
    texHeapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
    texHeapProps.CreationNodeMask = 0;
    texHeapProps.VisibleNodeMask = 0;
    D3D12_RESOURCE_DESC texResDesc = {};
    texResDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texResDesc.Width = m_width = width;
    texResDesc.Height = m_height = height;
    texResDesc.DepthOrArraySize = 1;
    texResDesc.SampleDesc.Count = 1;
    texResDesc.SampleDesc.Quality = 0;
    texResDesc.MipLevels = 1;
    texResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    texResDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    texResDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    // ID3D12Resource* texBuff = nullptr;
    if (FAILED(m_device->CreateCommittedResource(&texHeapProps, D3D12_HEAP_FLAG_NONE, &texResDesc, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, nullptr, IID_PPV_ARGS(&m_resource)))) {
        throw std::runtime_error("failed CreateCommittedResource()");
    }
    if (FAILED(m_resource->WriteToSubresource(0, nullptr, pixels, sizeof(Pixel) * width, sizeof(Pixel) * (width * height)))) {
        throw std::runtime_error("failed WriteToSubresource()");
    }
}
size_t DxTexture::getWidth() const { return m_width; }
size_t DxTexture::getHeight() const { return m_height; }
ID3D12Resource* DxTexture::getResource() const { return m_resource; }
}
#endif