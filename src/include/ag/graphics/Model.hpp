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

    Node::Instance getRootNode() const;

private:
    Model();
    static std::shared_ptr<Node> loadNode(std::shared_ptr<Node> root,
        const struct aiScene* aScene,
        struct aiNode* aParent, struct aiNode* aNode);
    static void loadMaterial(const struct aiMaterial* aMaterial,
        const std::shared_ptr<Material> material);
    Node::Instance m_rootNode;
};
}