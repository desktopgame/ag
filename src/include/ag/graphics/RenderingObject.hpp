#pragma once
#include <memory>

namespace ag {
enum class PrimitiveType {
    Polygon,
    Triangles,
    LineStrip,
};

class IShader;
class RenderingContext;
class RenderingObject {
public:
    using Instance = std::shared_ptr<RenderingObject>;
    explicit RenderingObject(
        PrimitiveType primitiveType,
        int primitiveCount,
        const std::shared_ptr<IShader>& shader,
        const std::shared_ptr<RenderingContext>& context);

    static std::shared_ptr<RenderingObject> createColorRectangle(bool isFill);
    static std::shared_ptr<RenderingObject> createColorCircle(bool isFill);

    PrimitiveType getPrimitiveType() const;
    int getPrimitiveCount() const;
    std::shared_ptr<IShader> getShader() const;
    std::shared_ptr<RenderingContext> getContext() const;

private:
    static std::shared_ptr<RenderingContext> createRenderingContext();
    PrimitiveType m_primitiveType;
    int m_primitiveCount;
    std::shared_ptr<IShader> m_shader;
    std::shared_ptr<RenderingContext> m_context;
};
}