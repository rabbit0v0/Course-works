#include <iostream>
#include <glad.h>
#include <cmath>
#include <glfw3.h>
using namespace std;
unsigned int shaderProgram;
const int WIDTH = 800, HEIGHT = 600;
const char *vertexShaderSource = "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "uniform vec3 offset;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos + offset,1.0f);\n"
        "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec3 color;\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(color,1.0f);\n"
        "}\0";

struct Wheel{
private:
    unsigned int VAO, VBO, EBO;
    float *vertices = NULL;
    unsigned int *area = NULL;
    float R, G, B;
public:
    Wheel(float x = 0, float y = 0,float r = 0.2f, float red = 1.0f,float g = 1.0f, float b = 1.0f) : R(red), G(g), B(b) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        vertices = new float[183];
        vertices[0] = x; vertices[1] = y; vertices[2] = 0.0f;
        for (int i = 1; i <= 60; ++i) {
            vertices[3 * i + 0] = x + r * float(cos(i*0.105));
            vertices[3 * i + 1] = y + r * float(sin(i*0.105));
            vertices[3 * i + 2] = 0.0f;
        }
        area = new unsigned int[180];
        for (int i = 0; i < 60; ++i) {
            area[3 * i + 0] = 0;
            area[3 * i + 1] = i + 1;
            area[3 * i + 2] = (i + 1) % 60 + 1;
        }
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 183 * sizeof(float), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 180 * sizeof(unsigned int), area, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }
    ~Wheel() {
        delete[] vertices;
        delete[] area;
    }
    void draw() {
        glBindVertexArray(VAO);
        GLint vertexColorId = glGetUniformLocation(shaderProgram, "color");
        glUniform3f(vertexColorId, R, G, B);
        glDrawElements(GL_TRIANGLES, 180, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};


struct Car{
    unsigned int area[9];
    Wheel w1, w2;
    unsigned int VAO, VBO, EBO;
public:
    Car(float x, float y) :
            w1(x - 0.3f, y - 0.3f, 0.1f, 0.0f, 1.0f, 0.0f),
            w2(x + 0.3f, y - 0.3f, 0.1f, 1.0f, 1.0f, 0.0f) {

        float vertices[] = {

                x + 0.4f, y + 0.3f, 0.0f,
                x, y + 0.6f, 0.0f,
                x - 0.4f, y + 0.3f, 0.0f,

                x + 0.5f, y - 0.3f, 0.0f,
                x + 0.5f, y + 0.3f, 0.0f,
                x - 0.5f, y - 0.3f, 0.0f,
                x - 0.5f, y + 0.3f, 0.0f

        };

        area[0] = 3; area[1] = 4; area[2] = 5;
        area[3] = 4; area[4] = 5; area[5] = 6;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 21 * sizeof(float), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), area, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }
    ~Car() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    void draw() {
        glBindVertexArray(VAO);
        GLint vertexColorId = glGetUniformLocation(shaderProgram, "color");
        glUniform3f(vertexColorId, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUniform3f(vertexColorId, 1.0f, 0.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        w1.draw();
        w2.draw();
    }
    void move(){
        double tim = glfwGetTime();
        GLfloat x = GLfloat(tim) / 10;
        GLint vertexOffsetId = glGetUniformLocation(shaderProgram, "offset");
        glUniform3f(vertexOffsetId, x, 0.0f, 0.0f);

    }
};

void check(unsigned int vertexShader, unsigned int fragmentShader, unsigned int shaderProgram) {
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
        getchar();
        exit(-1);
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
        getchar();
        exit(-1);
    }
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
        getchar();
        exit(-1);
    }
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "car", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        cout << "Failed to create GLFW window" << endl;
        getchar();
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        getchar();
        exit(-1);
    }

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    check(vertexShader, fragmentShader, shaderProgram);
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
//
//    float vertices[] = {
//            -0.5f,-0.5f,0.0f,
//            0.5f,-0.5f,0.0f,
//            0.0f, 0.5f,0.0f,
//    };
//
//    unsigned int VAO, VBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
//    glEnableVertexAttribArray(0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

    Car car(0.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        car.draw();
        car.move();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}
