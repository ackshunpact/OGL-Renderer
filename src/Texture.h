// //
// // Created by bigbeev on 7/30/2025.
// //
//
// #ifndef TEXTURE_H
// #define TEXTURE_H
// #include <ios>
// #include <memory>
// #include <GL/gl.h>
// #include <glad/glad.h>
//
//
// class Texture {
//     GLuint id;
//     GLuint target;
//     GLint internalFormat;
//     GLint format;
//     GLint type;
//     bool genMipMap;
// public:
//
//     Texture(GLuint target, GLint internalFormat, GLint type, bool genMipMap, GLint maxLod) : id(0), target(target),
//         internalFormat(internalFormat), format(0), type(type), genMipMap(genMipMap) {
//         glGenTextures(1, &id);
//         Bind();
//
//         glTexParameteri(target, GL_TEXTURE_MIN_FILTER, genMipMap ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST);
//         glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//         if (genMipMap) {
//             glTexParameteri(target, GL_TEXTURE_MAX_LOD, maxLod);
//         }
//
//         Unbind();
//     }
//
//     ~Texture() {
//         glDeleteTextures(1, &id);
//     }
//
//     void Bind() const;
//     void Unbind() const;
//     void BindtoSlot(GLuint slot) const;
//     GLuint getID() const;
//
//     static std::shared_ptr<const Texture> loadTex2D(const std::string& filename);
//     static std::shared_ptr<const Texture> loadTex2DArray(const std::string& filename);
//     static std::shared_ptr<const Texture> loadTextCubeMap(const std::string& filename);
//
// };
//
//
//
// #endif //TEXTURE_H
