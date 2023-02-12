#ifdef AG_DIRECT_X
#include <ag/graphics/dx/DxBuffer.hpp>
#include <ag/native/dx.hpp>
#include <stdexcept>

namespace ag {
DxBuffer::DxBuffer(ID3D12Device* device)
    : m_device(device)
    , m_resource(nullptr)
    , m_size(0)
{
}

DxBuffer::~DxBuffer()
{
    release();
}

void DxBuffer::allocate(size_t size)
{
    if (!m_resource) {
        D3D12_HEAP_PROPERTIES heapProps = {};
        heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
        heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
        heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
        D3D12_RESOURCE_DESC resDesc = {};
        resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
        resDesc.Width = size;
        resDesc.Height = 1;
        resDesc.DepthOrArraySize = 1;
        resDesc.MipLevels = 1;
        resDesc.Format = DXGI_FORMAT_UNKNOWN;
        resDesc.SampleDesc.Count = 1;
        resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
        resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
        if (FAILED(m_device->CreateCommittedResource(
                &heapProps,
                D3D12_HEAP_FLAG_NONE,
                &resDesc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&m_resource)))) {
            throw std::runtime_error("failed CreateCommittedResource()");
        }
        m_size = size;
    } else {
        throw std::runtime_error("already allocated.");
    }
}

void DxBuffer::update(const void* data)
{
    void* outData;
    if (FAILED(m_resource->Map(0, nullptr, (void**)&outData))) {
        throw std::runtime_error("failed Map()");
    }
    ::memcpy(outData, data, m_size);
    m_resource->Unmap(0, nullptr);
}

void DxBuffer::release()
{
    if (m_resource) {
        m_resource->Release();
        m_resource = nullptr;
    }
}

D3D12_VERTEX_BUFFER_VIEW DxBuffer::vertexView(unsigned int stride)
{
    D3D12_VERTEX_BUFFER_VIEW ret = {};
    ret.BufferLocation = m_resource->GetGPUVirtualAddress();
    ret.SizeInBytes = m_size;
    ret.StrideInBytes = stride;
    return ret;
}
D3D12_INDEX_BUFFER_VIEW DxBuffer::indexView()
{
    D3D12_INDEX_BUFFER_VIEW ret = {};
    ret.BufferLocation = m_resource->GetGPUVirtualAddress();
    ret.Format = DXGI_FORMAT_R32_UINT;
    ret.SizeInBytes = m_size;
    return ret;
}
}
#endif