#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>

void BLA_line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    if (dy < dx) { // If |m| < 1
        int d = 2 * (dy - dx);
        int x = x1, y = y1;
        glBegin(GL_POINTS);
        glVertex2i(x, y);

        for (int i = 0; i <= dx; ++i) {
            glVertex2i(x + i, y);
            if (d > 0) {
                y += 1;
                d += 2 * (dy - dx);
            } else {
                d += 2 * dy;
            }
        }
    } else { // If |m| >= 1
        int d = 2 * (dx - dy);
        int x = x1, y = y1;

        glBegin(GL_POINTS);
        glVertex2i(x, y);

        for (int i = 0; i <= dy; ++i) {
            glVertex2i(x, y + i);
            if (d > 0) {
                x += 1;
                d += 2 * (dx - dy);
            } else {
                d += 2 * dx;
            }
        }
    }

    glEnd();
}

void display(int x1, int y1, int x2, int y2) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    BLA_line(x1, y1, x2, y2);
}

void init(int width, int height) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // Set up orthographic projection to cover the entire window
    glOrtho(0.0, static_cast<double>(width), 0.0, static_cast<double>(height), -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    init(width, height);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }
    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(500, 500, "BLA Line Drawing Algorithm using GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);
    // Set up the viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Set the framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Initialize OpenGL settings
    init(width, height);
    int x1, y1, x2, y2;
    std::cout << "Enter x1, y1, x2, y2: ";
    std::cin >> x1 >> y1 >> x2 >> y2;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        display(x1, y1, x2, y2);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
