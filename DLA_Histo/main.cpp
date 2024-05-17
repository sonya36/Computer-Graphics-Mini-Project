#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <algorithm>

void dda_line(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_increment = dx / (float)steps;
    float y_increment = dy / (float)steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += x_increment;
        y += y_increment;
    }
    glEnd();
    glFlush();
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
        //  Set color for the bar
        glColor3f(color, 1.0 - color, 0.5); // Use frequency ratio for varying color
        // Calculate bar position
        int startX = i * barWidth;
        int startY = 0;
        int endX = startX + barWidth;
        int endY = barHeight;
        // Draw filled rectangle for the bar using DDA line drawing algorithm
        dda_line(startX, startY, startX, endY); // Vertical line for the left side of the bar
        dda_line(startX, endY, endX, endY);     // Horizontal line for the top side of the bar
        dda_line(endX, endY, endX, startY);     // Vertical line for the right side of the bar
        dda_line(endX, startY, startX, startY); // Horizontal line for the bottom side of the bar
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
    if (!glfwInit()) {
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(500, 500, "Histogram Using DDA", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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
        // Render here
        drawHistogram(frequencies, width, height);

        // Swap front and back buffers
        glfwSwapBuffers(window);
    // Poll for and process events
        glfwPollEvents();
    }
    // Terminate GLFW
    glfwTerminate();
    return 0;
}






















// #include <GLFW/glfw3.h>
// #include <iostream>
// #include <cstdlib>

// const int WINDOW_WIDTH = 800;
// const int WINDOW_HEIGHT = 600;

// void drawLine(int x1, int y1, int x2, int y2) {
//     int dx = x2 - x1;
//     int dy = y2 - y1;
//     int d = 2 * (dy - dx);
//     int x = x1, y = y1;
    
//     glBegin(GL_POINTS);
//     glVertex2i(x, y);

//    for (int i = 0; i <= dx; ++i) {
//     glVertex2i(x + i, y);
//     if (d > 0) {
//         y += 1;
//         d += 2 * (dy - dx);
//     } else {
//         d += 2 * dy;
//     }
// }

//     glEnd();
// }

// void renderScene() {
//     glClear(GL_COLOR_BUFFER_BIT);

//     glColor3f(1.0f, 1.0f, 1.0f); // Set color to white

//     // Accept the coordinates of the start and end points of the line: (x1, y1) and (x2, y2)
//     int x1 = 100, y1 = 100; // Example start point
//     int x2 = 500, y2 = 400; // Example end point

//     // Draw the line segment passing through the given start and end points
//     drawLine(x1, y1, x2, y2);

//     glFlush();
// }

// int main() {
//     GLFWwindow* window;

//     // Initialize GLFW
//     if (!glfwInit()) {
//         return -1;
//     }

//     // Create a windowed mode window and its OpenGL context
//     window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bresenham's Line Algorithm", NULL, NULL);
//     if (!window) {
//         glfwTerminate();
//         return -1;
//     }

//     // Make the window's context current
//     glfwMakeContextCurrent(window);

//     // Loop until the user closes the window
//     while (!glfwWindowShouldClose(window)) {
//         // Render scene
//         renderScene();

//         // Swap front and back buffers
//         glfwSwapBuffers(window);

//         // Poll for and process events
//         glfwPollEvents();
//     }

//     // Terminate GLFW
//     glfwTerminate();

//     return 0;
// }
// 
// #include <iostream>
// #include <GLFW/glfw3.h>
// #include <cmath>

// void BLA_line(int x1, int y1, int x2, int y2) {
//     int dx = abs(x2 - x1);
//     int dy = abs(y2 - y1);

//     if (dy < dx) { // If |m| < 1
//         int d = 2 * (dy - dx);
//         int x = x1, y = y1;
//         glBegin(GL_POINTS);
//         glVertex2i(x, y);

//         for (int i = 0; i <= dx; ++i) {
//             glVertex2i(x + i, y);
//             if (d > 0) {
//                 y += 1;
//                 d += 2 * (dy - dx);
//             } else {
//                 d += 2 * dy;
//             }
//         }
//     } else { // If |m| >= 1
//         int d = 2 * (dx - dy);
//         int x = x1, y = y1;

//         glBegin(GL_POINTS);
//         glVertex2i(x, y);

//         for (int i = 0; i <= dy; ++i) {
//             glVertex2i(x, y + i);
//             if (d > 0) {
//                 x += 1;
//                 d += 2 * (dx - dy);
//             } else {
//                 d += 2 * dx;
//             }
//         }
//     }

//     glEnd();
// }

// void display(int x1, int y1, int x2, int y2) {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glColor3f(1.0, 1.0, 1.0);

//     BLA_line(x1, y1, x2, y2);
// }

// void init() {
//     glClearColor(0.0, 0.0, 0.0, 0.0);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();

//     // Set up orthographic projection to cover the entire window
//     int width, height;
//     glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
//     glOrtho(0.0, static_cast<double>(width), 0.0, static_cast<double>(height), -1.0, 1.0);
//     //  glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
//     // glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
//         // glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);


//     glMatrixMode(GL_MODELVIEW);
// }



// int main() {
//     // Initialize GLFW
//     if (!glfwInit()) {
//         return -1;
//     }

//     // Create a windowed mode window and its OpenGL context
//     GLFWwindow* window = glfwCreateWindow(500, 500, "BLA Line Drawing Algorithm using GLFW", NULL, NULL);
//     if (!window) {
//         glfwTerminate();
//         return -1;
//     }

//     // Make the window's context current
//     glfwMakeContextCurrent(window);

//     // Set up the viewport
//     glViewport(0, 0, 500, 500);

//     // Set the display function
//     glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
//         glViewport(0, 0, width, height);
//     });

//     // Set up OpenGL settings
//     // init();

//     // Test pointsB
//   // Test points
//      int x1 = 100, y1 = 100;
//     int x2 = 400, y2 = 300;


//     // Loop until the user closes the window
//     while (!glfwWindowShouldClose(window)) {
//         // Render here
//         display(x1, y1, x2, y2);

//         // Swap front and back buffers
//         glfwSwapBuffers(window);

//         // Poll for and process events
//         glfwPollEvents();
//     }

//     // Terminate GLFW
//     glfwTerminate();
//     return 0;
// }



// #include <iostream>
// #include <GLFW/glfw3.h>
// #include <cmath>

// void BLA_line(int x1, int y1, int x2, int y2) {
//     int dx = abs(x2 - x1);
//     int dy = abs(y2 - y1);

//     if (dy < dx) { // If |m| < 1
//         int d = 2 * (dy - dx);
//         int x = x1, y = y1;
//         glBegin(GL_POINTS);
//         glVertex2i(x, y);

//         for (int i = 0; i <= dx; ++i) {
//             glVertex2i(x + i, y);
//             if (d > 0) {
//                 y += 1;
//                 d += 2 * (dy - dx);
//             } else {
//                 d += 2 * dy;
//             }
//         }
//     } else { // If |m| >= 1
//         int d = 2 * (dx - dy);
//         int x = x1, y = y1;

//         glBegin(GL_POINTS);
//         glVertex2i(x, y);

//         for (int i = 0; i <= dy; ++i) {
//             glVertex2i(x, y + i);
//             if (d > 0) {
//                 x += 1;
//                 d += 2 * (dx - dy);
//             } else {
//                 d += 2 * dx;
//             }
//         }
//     }

//     glEnd();
// }

// void display(int x1, int y1, int x2, int y2) {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glColor3f(1.0, 1.0, 1.0);

//     BLA_line(x1, y1, x2, y2);
// }

// void init(int width, int height) {
//     glClearColor(0.0, 0.0, 0.0, 0.0);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
    
//     // Set up orthographic projection to cover the entire window
//     glOrtho(0.0, static_cast<double>(width), 0.0, static_cast<double>(height), -1.0, 1.0);

//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
// }

// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
//     init(width, height);
// }

// int main() {
//     // Initialize GLFW
//     if (!glfwInit()) {
//         return -1;
//     }

//     // Create a windowed mode window and its OpenGL context
//     GLFWwindow* window = glfwCreateWindow(500, 500, "BLA Line Drawing Algorithm using GLFW", NULL, NULL);
//     if (!window) {
//         glfwTerminate();
//         return -1;
//     }

//     // Make the window's context current
//     glfwMakeContextCurrent(window);

//     // Set up the viewport
//     int width, height;
//     glfwGetFramebufferSize(window, &width, &height);
//     glViewport(0, 0, width, height);

//     // Set the framebuffer size callback
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // Initialize OpenGL settings
//     init(width, height);

//     // // Test points
//     // int x1 = 100, y1 = 100;
//     // int x2 = 400, y2 = 300;
//     int x1, y1, x2, y2;
//     std::cout << "Enter x1, y1, x2, y2: ";
//     std::cin >> x1 >> y1 >> x2 >> y2;

//     // Loop until the user closes the window
//     while (!glfwWindowShouldClose(window)) {
//         // Render here
//         display(x1, y1, x2, y2);

//         // Swap front and back buffers
//         glfwSwapBuffers(window);

//         // Poll for and process events
//         glfwPollEvents();
//     }

//     // Terminate GLFW
//     glfwTerminate();
//     return 0;
// }


//BlA HIsto 
// #include <iostream>
// #include <GLFW/glfw3.h>
// #include <cmath>
// #include <vector>
// #include <algorithm>

// void BLA_line(int x1, int y1, int x2, int y2) {
//     int dx = abs(x2 - x1);
//     int dy = abs(y2 - y1);

//     if (dy < dx) { // If |m| < 1
//         int d = 2 * (dy - dx);
//         int x = x1, y = y1;
//         glBegin(GL_POINTS);
//         glVertex2i(x, y);

//         for (int i = 0; i <= dx; ++i) {
//             glVertex2i(x + i, y);
//             if (d > 0) {
//                 y += 1;
//                 d += 2 * (dy - dx);
//             } else {
//                 d += 2 * dy;
//             }
//         }
//     } else { // If |m| >= 1
//         int d = 2 * (dx - dy);
//         int x = x1, y = y1;

//         glBegin(GL_POINTS);
//         glVertex2i(x, y);

//         for (int i = 0; i <= dy; ++i) {
//             glVertex2i(x, y + i);
//             if (d > 0) {
//                 x += 1;
//                 d += 2 * (dx - dy);
//             } else {
//                 d += 2 * dx;
//             }
//         }
//     }

//     glEnd();
// }




// void drawHistogram(const std::vector<int>& frequencies, int width, int height) {
//     glClear(GL_COLOR_BUFFER_BIT);

//     int numBars = frequencies.size();
//     int barWidth = width / numBars;
//     int maxFrequency = *std::max_element(frequencies.begin(), frequencies.end());

//     for (int i = 0; i < numBars; ++i) {
//         // Calculate bar height and color
//         int barHeight = static_cast<int>((static_cast<double>(frequencies[i]) / maxFrequency) * height);
//         float color = static_cast<float>(frequencies[i]) / maxFrequency; // Use frequency ratio for color
        
//         // Set color for the bar
//         glColor3f(color, 1.0 - color, 0.5); // Use frequency ratio for varying color
        
//         // Calculate bar position
//         int startX = i * barWidth;
//         int startY = 0;
//         int endX = startX + barWidth;
//         int endY = barHeight;

//         // Draw filled rectangle for the bar
//         glBegin(GL_QUADS);
//         glVertex2i(startX, startY);
//         glVertex2i(endX, startY);
//         glVertex2i(endX, endY);
//         glVertex2i(startX, endY);
//         glEnd();
//     }
// }



// void init(int width, int height) {
//     // glClearColor(0.0, 0.0, 0.0, 0.0);
//     glClearColor(1.0, 1.0, 1.0, 1.0);
     
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();

//     // Adjust the orthographic projection to fit the histogram within the viewport
//     glOrtho(0.0, static_cast<double>(width), 0.0, static_cast<double>(height), -1.0, 1.0);

//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
// }

// void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//     glViewport(0, 0, width, height);
//     init(width, height);
// }

// int main() {
//     // Initialize GLFW
//     if (!glfwInit()) {
//         return -1;
//     }

//     // Create a windowed mode window and its OpenGL context
//     GLFWwindow* window = glfwCreateWindow(500, 500, "Histogram Using BLA", NULL, NULL);
//     if (!window) {
//         glfwTerminate();
//         return -1;
//     }

//     // Make the window's context current
//     glfwMakeContextCurrent(window);

//     // Set up the viewport
//     int width, height;
//     glfwGetFramebufferSize(window, &width, &height);
//     glViewport(0, 0, width, height);

//     // Set the framebuffer size callback
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//     // Initialize OpenGL settings
//     init(width, height);

//     int numBars;
//     std::cout << "Enter the number of bars: ";
//     std::cin >> numBars;

//     std::vector<int> frequencies(numBars);
//     std::cout << "Enter the frequencies: ";
//     for (int i = 0; i < numBars; ++i) {
//         std::cin >> frequencies[i];
//     }
//     // int barThickness;
//     // std::cout << "Enter the bar thickness: ";
//     // std::cin >> barThickness;


//     // Loop until the user closes the window
//     while (!glfwWindowShouldClose(window)) {
//         // Render here
//         drawHistogram(frequencies, width, height);

//         // Swap front and back buffers
//         glfwSwapBuffers(window);

//         // Poll for and process events
//         glfwPollEvents();
//     }

//     // Terminate GLFW
//     glfwTerminate();
//     return 0;
// }