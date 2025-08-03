//
// Created by bigbeev on 8/2/2025.
//
#include "ShaderManager.h"
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

ShaderManager *ShaderManager::instance = nullptr;
std::unordered_map<std::string, GLuint> ShaderManager::shaderPrograms;
std::unordered_map<std::string, std::string> ShaderManager::shaderModules;
std::unordered_map<std::string, std::unordered_map<std::string, GLint>> ShaderManager::uniformLocations;
std::string ShaderManager::currentShader = "";
GLuint ShaderManager::currentProgramID = -1;
/*
 * General flow:
 *  1. initialization: load up shader code modules.
 *      these are modular pieces that can somehow be combined/concatenated to create composite shader code to load compile
 *      e.g.
 */


// loads up the .vs or .fs file code and stores it in a map for later use.
// stored as key: std::string name, value: std::string code
void ShaderManager::loadModule(const std::string &name, const std::string &path) {
    // parse the file extension
    std::string ext = path.substr(path.rfind('.') + 1);

    std::string shaderCode;
    std::ifstream shaderFile;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure e) {
        printf("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: %s\n", e.what());
    }
    shaderModules.insert(std::make_pair(name, shaderCode));

}

// 1. fetches shader code specified by name in arguements from shadermodules map
// 2. load up, compile, link a new shader program
// 3. store the program by key: name val: shaderID in the shaderProgram map
void ShaderManager::createShader(
     const std::string &name,
     const std::vector<std::string>& vertShaderModules,
     const std::vector<std::string>& fragShaderModules
     ) {
    // for now assume single fcomplete vs and fs shader in each vector
    const char* vs = shaderModules.at(vertShaderModules[0]).c_str();
    const char* fs = shaderModules.at(fragShaderModules[0]).c_str();

    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vs, NULL);
    glCompileShader(vert);
    checkCompileErrors(vert, "VERTEX");

    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fs, NULL);
    glCompileShader(frag);
    checkCompileErrors(frag, "FRAGMENT");

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    checkCompileErrors(program, "PROGRAM");
    glDeleteShader(vert);
    glDeleteShader(frag);
    shaderPrograms.insert(std::make_pair(name, program));
}

void ShaderManager::useShader(const std::string& name) {
    if (shaderPrograms.contains(name)) {
        glUseProgram(shaderPrograms.at(name));
        currentProgramID = shaderPrograms.at(name);
        currentShader = name;
    } else {
        printf("SHADER NOT FOUND: %s\n", name.c_str());
    }
}

void ShaderManager::setUniform(const std::string &name, float value) {
    GLuint loc = glGetUniformLocation(currentProgramID, name.c_str());
    glUniform1f(loc, value);
}

void ShaderManager::setUniform(const std::string &name, int value) {
    GLuint loc = glGetUniformLocation(currentProgramID, name.c_str());
    glUniform1i(loc, value);
}

void ShaderManager::setUniform(const std::string &name, bool value) {
    GLuint loc = glGetUniformLocation(currentProgramID, name.c_str());
    glUniform1i(loc, value);
}

void ShaderManager::setUniform(const std::string &name, glm::vec3 value) {
    GLuint loc = glGetUniformLocation(currentProgramID, name.c_str());
    glUniform3fv(loc, 1, glm::value_ptr(value));
}

void ShaderManager::setUniform(const std::string &name, glm::mat4 value) {
    GLuint loc = glGetUniformLocation(currentProgramID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderManager::checkCompileErrors(const unsigned int shader, const std::string &type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n\n -- --------------------------------------------------- -- \n", type.c_str(),  infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s \n %s \n -- --------------------------------------------------- -- ", type.c_str(), infoLog);
        }
    }
}
