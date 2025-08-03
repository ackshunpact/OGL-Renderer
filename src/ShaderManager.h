//
// Created by bigbeev on 8/2/2025.
//

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <string>
#include <unordered_map>
#include <vector>
// #include <GL/gl.h>
#include <glm/glm.hpp>
#include <glad/glad.h>

class ShaderManager {

private:
    static ShaderManager *instance;
    static std::unordered_map<std::string, GLuint> shaderPrograms;
    static std::unordered_map<std::string, std::string> shaderModules;
    static std::unordered_map<std::string, std::unordered_map<std::string, GLint>> uniformLocations;
    static std::string currentShader;
    static GLuint currentProgramID;
    ShaderManager() {}

public:
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;
    static ShaderManager* getInstance() {
        if (!instance) {
            instance = new ShaderManager();
        }
        return instance;
    }

    static void loadModule(const std::string &name, const std::string &path);
    static void createShader(
        const std::string &name,
        const std::vector<std::string>& vertShaderModules,
        const std::vector<std::string>& fragShaderModules
        );

    static void checkCompileErrors(unsigned int shader, const std::string &type);

    static void useShader(const std::string& name);
    static void setUniform(const std::string& name, float value);
    static void setUniform(const std::string& name, int value);
    static void setUniform(const std::string& name, bool value);
    static void setUniform(const std::string& name, glm::vec3 value);
    static void setUniform(const std::string& name, glm::mat4 value);


};



#endif //SHADERMANAGER_H
