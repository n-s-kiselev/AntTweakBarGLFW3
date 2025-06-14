// g++ -std=c++11 MiniExample.cpp glad/src/glad.c -Iglad/include -I/path/to/glm -lglfw -ldl -lGL -o cube
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

void framebuffer_size_callback(GLFWwindow*, int, int);
std::string loadShader(const char* path);
GLuint compileShader(GLenum type, const char* source);
GLuint createShaderProgram(const char* vertPath, const char* fragPath);
void multiplyMatrix4(float* result, const float* a, const float* b);
void setIdentity(float* mat);
void setPerspective(float* mat, float fov, float aspect, float near, float far);
void setRotationY(float* mat, float angle);
void setTranslation(float* mat, float x, float y, float z);

float vertices[] = {
   -0.5f,-0.5f,-0.5f,  1.0f,0.0f,0.0f,
    0.5f,-0.5f,-0.5f,  0.0f,1.0f,0.0f,
    0.5f, 0.5f,-0.5f,  0.0f,0.0f,1.0f,
   -0.5f, 0.5f,-0.5f,  1.0f,1.0f,0.0f,
   -0.5f,-0.5f, 0.5f,  1.0f,0.0f,1.0f,
    0.5f,-0.5f, 0.5f,  0.0f,1.0f,1.0f,
    0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,
   -0.5f, 0.5f, 0.5f,  0.0f,0.0f,0.0f
};

unsigned int indices[] = {
    0,1,2, 2,3,0,  4,5,6, 6,7,4,
    0,1,5, 5,4,0,  2,3,7, 7,6,2,
    0,3,7, 7,4,0,  1,2,6, 6,5,1
};

const char* vShaderSrc = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 mvp;
out vec3 ourColor;
void main() {
    gl_Position = mvp * vec4(aPos, 1.0);
    ourColor = aColor;
}
)";

const char* fShaderSrc = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0); // красный
    // FragColor = vec4(ourColor, 1.0);
}
)";

float testTriangle[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS

    GLFWwindow* window = glfwCreateWindow(800, 600, "Cube No GLM", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderSrc, nullptr);
    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderSrc, nullptr);
    glCompileShader(fragment);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // Geometry
    GLuint VAO, VBO, EBO;
    // 1. Create and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // 2. Create and bind VBO with your data
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex, GL_STATIC_DRAW);
    // 3. Set up vertex attributes (your code)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // color
    glEnableVertexAttribArray(1);

    // 4. shaders should use these attributes
    // Vertex shader should have:
    // layout (location = 0) in vec3 aPos;
    // layout (location = 1) in vec3 aColor;  

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        float time = glfwGetTime();

        float model[16], view[16], proj[16];
        float rot[16], trans[16], viewproj[16], mvp[16];

        setRotationY(rot, time);  // вращение по времени
        setTranslation(trans, 0.0f, 0.0f, -3.0f); // отодвигаем куб
        multiplyMatrix4(model, trans, rot);      // model = T * R

        setPerspective(proj, 45.0f * 3.14159f / 180.0f, 800.0f/600.0f, 0.1f, 100.0f);
        setIdentity(view);
        multiplyMatrix4(viewproj, proj, view);   // VP = P * V
        multiplyMatrix4(mvp, viewproj, model);   // MVP = VP * M

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        GLuint loc = glGetUniformLocation(shaderProgram, "mvp");
        if (loc == -1) std::cerr << "uniform 'mvp' not found!" << std::endl;
        glUniformMatrix4fv(loc, 1, GL_FALSE, mvp);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


// Matrix helpers

void setIdentity(float* mat) {
    for (int i = 0; i < 16; i++) mat[i] = (i%5==0)?1.0f:0.0f;
}

void multiplyMatrix4(float* r, const float* a, const float* b) {
    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j) {
        r[i*4 + j] = 0;
        for (int k = 0; k < 4; ++k)
          r[i*4 + j] += a[i*4 + k] * b[k*4 + j];
      }
}

void setRotationY(float* mat, float angle) {
    setIdentity(mat);
    mat[0] = cos(angle);
    mat[2] = sin(angle);
    mat[8] = -sin(angle);
    mat[10] = cos(angle);
}

void setTranslation(float* mat, float x, float y, float z) {
    setIdentity(mat);
    mat[12] = x; mat[13] = y; mat[14] = z;
}

void setPerspective(float* mat, float fov, float aspect, float near, float far) {
    float f = 1.0f / tan(fov / 2.0f);
    setIdentity(mat);
    mat[0] = f / aspect;
    mat[5] = f;
    mat[10] = (far + near) / (near - far);
    mat[11] = -1.0f;
    mat[14] = (2 * far * near) / (near - far);
    mat[15] = 0.0f;
}

// Others

void framebuffer_size_callback(GLFWwindow*, int w, int h) {
    glViewport(0, 0, w, h);
}

std::string loadShader(const char* path) {
    std::ifstream file(path);
    std::stringstream buf;
    buf << file.rdbuf();
    return buf.str();
}

GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Проверка компиляции
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cerr << "Shader compilation failed (" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "):\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram(const char* vertPath, const char* fragPath) {
    std::string vertCode = loadShader(vertPath);
    std::string fragCode = loadShader(fragPath);

    if (vertCode.empty()) {
        std::cerr << "Vertex shader source is empty or file not found: " << vertPath << std::endl;
    }
    if (fragCode.empty()) {
        std::cerr << "Fragment shader source is empty or file not found: " << fragPath << std::endl;
    }

    GLuint vertex = compileShader(GL_VERTEX_SHADER, vertCode.c_str());
    GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragCode.c_str());

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    // Проверка линковки
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, nullptr, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return program;
}

