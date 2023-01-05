#pragma once
#include <ag/graphics/Node.hpp>
#include <memory>
#include <string>

struct aiScene;
struct aiNode;
struct aiMaterial;

namespace ag {
class Model {
public:
    using Instance = std::shared_ptr<Model>;
    static Instance loadFromFile(const std::string& file);
    static Instance loadFromMemory(const void* buf, size_t len, const std::string& hint);

    Node::Instance getRootNode() const;

private:
    Model();
    static unsigned int getPostProcessFlags();
    static std::shared_ptr<Node> loadNode(const std::string& modelFile, std::shared_ptr<Node> root,
        const struct aiScene* aScene,
        struct aiNode* aParent, struct aiNode* aNode);
    static void loadMaterial(const std::string& modelFile, const struct aiMaterial* aMaterial,
        const std::shared_ptr<Material> material);
    Node::Instance m_rootNode;
};
}