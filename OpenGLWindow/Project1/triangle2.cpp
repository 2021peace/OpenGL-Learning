#include <iostream>

#define GLEW_STATIC 
#include<GL/glew.h>
#include<GLFW/glfw3.h>

    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

//GLSL������ɫ����Դ����
const char* vertexShaderSource =
"#version 330 core \n"
"layout(location = 0) in vec3 aPos;\n"
"void main(){\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}\n";

//Ƭ����ɫ����Դ����
const char* fragmentShaderSource =
"#version 330 core          \n"
"out vec4 FragColor; \n"
"void main(){\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); }\n";

int main() {
	//��ʼ��Glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����openglΪ����ģʽ

	GLFWwindow* window = glfwCreateWindow(800,800,"myWindow",NULL,NULL);
	if (window == NULL) {
		printf("glfw��ʼ������");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//��������
	

	//��ʼ��GLEW
	glewExperimental = true;  //���Լ���ȫ��opengl��չ
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		printf("init glew error");
		fprintf(stderr,"glew��ʼ��ʧ�ܣ�%s\n", glewGetErrorString(err));
		glfwTerminate();
		return -1;
	}

	//����VAO
	unsigned int VAOs[2];
	glGenVertexArrays(2, VAOs);

	//����VBO
	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);

	//��VAO
	//����VAO[0];
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//����VAO[1];
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//Ƭ����ɫ��
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

	//������ɫ��
	unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

	//ѭ����Ⱦ
	while (!glfwWindowShouldClose(window)) {

		//��Ⱦָ��
		//״̬���ú���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//״̬Ӧ�ú���
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
        // ��һ��������
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
		//�ڶ���������
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//˫����
		glfwSwapBuffers(window);//������ɫ����
		glfwPollEvents();//����¼�
	}
	//ɾ���ڴ�
	glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}