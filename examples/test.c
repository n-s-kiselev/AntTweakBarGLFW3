// gcc test.c -lglfw -framework Cocoa -framework OpenGL -framework IOKit -o test
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}