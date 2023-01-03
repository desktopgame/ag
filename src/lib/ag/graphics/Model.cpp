#include <ag/graphics/Model.hpp>
#include <ag/native/assimp.hpp>

namespace ag {
Model::Instance Model::loadFromFile(const std::string& file)
{
    Model::Instance ret = std::shared_ptr<Model>(new Model());
    Assimp::Importer importer;
    const aiScene* aScene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords | aiProcess_ConvertToLeftHanded);
    if (!aScene) {
        throw std::runtime_error("invalid format.");
    }
    ret->m_rootNode = Model::loadNode(nullptr, aScene, nullptr, aScene->mRootNode);
    return ret;
}

Node::Instance Model::getRootNode() const { return m_rootNode; }
// private
Model::Model()
    : m_rootNode(nullptr)
{
}

std::shared_ptr<Node> Model::loadNode(std::shared_ptr<Node> parent,
    const aiScene* aScene,
    aiNode* aParent,
    aiNode* aNode)
{
    // ローカル行列を設定
    aiMatrix4x4 t = aNode->mTransformation;
    auto node = std::make_shared<Node>(parent, std::string(aNode->mName.C_Str()));
    node->setTransform(glm::mat4 {
        { t.a1, t.a2, t.a3, t.a4 },
        { t.b1, t.b2, t.b3, t.b4 },
        { t.c1, t.c2, t.c3, t.c4 },
        { t.d1, t.d2, t.d3, t.d4 } });
    // ノードに紐づいた全てのメッシュ
    for (int i = 0; i < aNode->mNumMeshes; i++) {
        unsigned int meshIndex = aNode->mMeshes[i];
        aiMesh* aMesh = aScene->mMeshes[meshIndex];
        aiMaterial* aMaterial = aScene->mMaterials[aMesh->mMaterialIndex];
        auto mesh = std::make_shared<Mesh>(std::string(aMesh->mName.C_Str()));
        auto material = mesh->getMaterial();
        // マテリアルを設定
        loadMaterial(aMaterial, material);
        node->addMesh(mesh);
        // メッシュの全ての面
        std::vector<unsigned int> iV;
        for (int j = 0; j < aMesh->mNumFaces; j++) {
            aiFace* face = &aMesh->mFaces[j];
            for (int vI = 0; vI < face->mNumIndices; vI++) {
                unsigned int ui = face->mIndices[vI];
                iV.emplace_back(ui);
            }
        }
        // テクスチャがあるならUVも設定
        if (material->texture && material->texCoordIndex >= 0) {
            std::vector<VertexData3D> verts;
            aiVector3D* texCoords = aMesh->mTextureCoords[material->texCoordIndex];
            for (int i = 0; i < aMesh->mNumVertices; i++) {
                VertexData3D vert;
                vert.position = glm::vec3 { aMesh->mVertices[i].x, aMesh->mVertices[i].y, aMesh->mVertices[i].z };
                vert.texcoord = glm::vec2 { texCoords[i].x, texCoords[i].y };
                verts.push_back(vert);
            }
            mesh->updateVertex(verts.data(), verts.size());
        } else {
            mesh->updateVertex(reinterpret_cast<glm::vec3*>(aMesh->mVertices), aMesh->mNumVertices);
            //mesh->updateNormal(aMesh->mNormals, aMesh->mNumVertices);
        }
        mesh->updateIndex(iV.data(), iV.size());
    }
    // 子階層の読み込み
    for (int i = 0; i < aNode->mNumChildren; i++) {
        auto cc = loadNode(node, aScene, aNode, aNode->mChildren[i]);
        node->addNode(cc);
    }
    return node;
}

void Model::loadMaterial(const aiMaterial* aMaterial,
    const std::shared_ptr<Material> material)
{
    // テクスチャ情報の取得
    int aTexType = aiTextureType_NONE;
    while (aTexType != AI_TEXTURE_TYPE_MAX) {
        int textureCount = aMaterial->GetTextureCount(static_cast<aiTextureType>(aTexType));
        for (int j = 0; j < textureCount; j++) {
            aiString aPath;
            aiTextureMapping aTexMap;
            unsigned int aTexCoordIndex;
            ai_real aBlend;
            aiTextureOp aTexOp;
            aiTextureMapMode aTexMapMode;
            aiReturn aTexFound = aMaterial->GetTexture(
                static_cast<aiTextureType>(aTexType), j, &aPath, &aTexMap,
                &aTexCoordIndex, &aBlend, &aTexOp, &aTexMapMode);
            if (aTexFound == AI_SUCCESS && aTexType == aiTextureType_DIFFUSE) {
                //material->texture = std::make_shared<Texture>(aPath.data, aTexCoordIndex);
                material->texCoordIndex = aTexCoordIndex;
            }
        }
        aTexType++;
    }
    // 色情報の取得
    aiColor4D aAmbient, aDiffuse, aSpecular, aEmission;
    float shininess;
    if (AI_SUCCESS == aiGetMaterialColor(aMaterial, AI_MATKEY_COLOR_AMBIENT, &aAmbient)) {
        material->ambient = { aAmbient.r, aAmbient.g, aAmbient.b, aAmbient.a };
    }
    if (AI_SUCCESS == aiGetMaterialColor(aMaterial, AI_MATKEY_COLOR_DIFFUSE, &aDiffuse)) {
        material->diffuse = { aDiffuse.r, aDiffuse.g, aDiffuse.b, aDiffuse.a };
    }
    if (AI_SUCCESS == aiGetMaterialColor(aMaterial, AI_MATKEY_COLOR_SPECULAR, &aSpecular)) {
        material->specular = { aSpecular.r, aSpecular.g, aSpecular.b, aSpecular.a };
    }
    if (AI_SUCCESS == aiGetMaterialColor(aMaterial, AI_MATKEY_COLOR_EMISSIVE, &aEmission)) {
        material->emission = { aEmission.r, aEmission.g, aEmission.b, aEmission.a };
    }
    if (AI_SUCCESS == aiGetMaterialFloat(aMaterial, AI_MATKEY_SHININESS, &shininess)) {
        material->shininess = shininess;
    }
}
}