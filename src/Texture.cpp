// //
// // Created by bigbeev on 7/30/2025.
// //
//
// #include "Texture.h"
//
// struct Image;
//
// void Texture::Bind() const {
//     glBindTexture(target, id);
// }
//
// void Texture::Unbind() const {
//     glBindTexture(target, 0);
// }
//
// void Texture::BindtoSlot(GLuint slot) const {
//     glActiveTexture(GL_TEXTURE0 + slot);
//     Bind();
// }
//
// GLuint Texture::getID() const {
//     return id;
// }
//
// std::shared_ptr<const Texture> Texture::loadTex2D(const std::string &filename) {
//     std::shared_ptr<const Image> tex = loadTex2D(filename);
// }
//
// std::shared_ptr<const Texture> Texture::loadTex2DArray(const std::string &filename) {
// }
//
// std::shared_ptr<const Texture> Texture::loadTextCubeMap(const std::string &filename) {
// }
