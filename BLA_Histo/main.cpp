#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <algorithm>

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
void drawHistogram(const std::vector<int>& frequencies, int width, int height) {
    glClear(GL_COLOR_BUFFER_BIT);
int numBars = frequencies.size();
    int barWidth = width / numBars;
    int maxFrequency = *std::max_element(frequencies.begin(), frequencies.end());
    for (int i = 0; i < numBars; ++i) {
        // Calculate bar height and color
        int barHeight = static_cast<int>((static_cast<double>(frequencies[i]) / maxFrequency) * height);
        float color = static_cast<float>(frequencies[i]) / maxFrequency; // Use frequency ratio for color
        // Set color for the bar
        glColor3f(color, 1.0 - color, 0.5); // Use frequency ratio for varying color
        // Calculate bar position
        int startX = i * barWidth;
        int startY = 0;
        int endX = startX + barWidth;
        int endY = barHeight;
        // Draw filled rectangle for the bar
        glBegin(GL_QUADS);
      // Draw filled rectangle for the bar using DDA line drawing algorithm
        BLA_line(startX, startY, startX, endY); // Vertical line for the left side of the bar
        BLA_line(startX, endY, endX, endY);     // Horizontal line for the top side of the bar
        BLA_line(endX, endY, endX, startY);     // Vertical line for the right side of the bar
        BLA_line(endX, startY, startX, startY); // Horizontal line for the bottom side of the bar
        glEnd();
    }
}
void init(int width, int height) {
    // glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearColor(1.0, 1.0, 1.0, 1.0);
     
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Adjust the orthographic projection to fit the histogram within the viewport
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
    GLFWwindow* window = glfwCreateWindow(500, 500, "Histogram Using BLA", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize OpenGL settings
    init(width, height);

    int numBars;
    std::cout << "Enter the number of bars: ";
    std::cin >> numBars;

    std::vector<int> frequencies(numBars);
    std::cout << "Enter the frequencies: ";
    for (int i = 0; i < numBars; ++i) {
        std::cin >> frequencies[i];
    }
     // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
       
        drawHistogram(frequencies, width, height);
        glfwSwapBuffers(window);  // Swap front and back buffer
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}