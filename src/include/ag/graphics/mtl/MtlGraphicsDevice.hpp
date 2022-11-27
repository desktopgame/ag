#pragma once
#ifdef AG_METAL
#include <ag/graphics/IGraphicsDevice.hpp>
#include <ag/native/metal.hpp>

namespace ag {
class MtlGraphicsDevice : public IGraphicsDevice {
public:
    explicit MtlGraphicsDevice();
    ~MtlGraphicsDevice();
    std::shared_ptr<ITexture> newTexture(int width, int height, const uint8_t* data) const override;
    std::shared_ptr<IBuffer> newVertexBuffer() const override;
    std::shared_ptr<IBuffer> newIndexBuffer() const override;
    MTL::RenderPipelineState* newRenderPipelineState(const MTL::RenderPipelineDescriptor* desc, NS::Error** err) const;

private:
    MTL::Device* m_device;
    MTL::CommandQueue* m_commandQueue;
};
}
#endif