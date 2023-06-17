#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//��������
float vertices[] = {
	-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
	0.5f,-0.5f,0.0f,
	0.0f,0.5f,0.0f,
	0.8f,0.8f,0.0f
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//��鰴���Ƿ���
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main() {
	int ret = glfwInit();//��ʼ��glfw
	//�������汾�źʹ˰汾��3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//����profile����---ָ���ĸ���opengl����������������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��������
	GLFWwindow* window = glfwCreateWindow(800,800,"myOpengl",NULL,NULL);
	if (window == NULL) {
		printf("error");
		glfwTerminate();
		return -1;
	}
	//�������������Ϊ��Ҫ��������
	glfwMakeContextCurrent(window);

	//��ʼ��GLEW
	glewExperimental = true;  //��ԭ��
	if (glewInit() != GLEW_OK) {
		printf("init glew error");
		glfwTerminate();
		return -1;
	}

	//��Ⱦ���ڳߴ�
	//1,2�������½ǣ����½����꣬
	//3,4���ÿ�����Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�
	glViewport(0, 0, 800, 600);
	//���ô��ڱ仯ʱ�Ĵ�С��
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	/////////////////////////////////////////////////////��������//////////////////////////////////////////////
	//VAO�����������
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	//VBO���㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO);//����һ�����壬���Ǵ�ʱopengl����֪������������ʲô��������Ҫ���а�
	//�󶨻�������--���㻺��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//����������д�뵽���㻺����
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices), vertices,GL_STATIC_DRAW);

	//������ɫ��
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//shader program---��vertexShader��fragmentShader���ӳ�һ��program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//���ý������㻺�����ķ�ʽ
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	//ѭ����Ⱦ,
	while (!glfwWindowShouldClose(window)) {//���glfw�Ƿ��˳�
		//��鰴���Ƿ���
		processInput(window);
		
		//��Ⱦָ��
		//glClearColor���������Ļ���õ���ɫ----״̬���ú���
		//glClear���������ɫ����֮����Ļ�����ΪglClearColor�е���ɫ��---״̬ʹ�ú���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//��������
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES,0,6);//��6����

		//�������¼�����������
		//˫���壺ǰ�滺��һ�Ż���������ʾ����̨����⻺����һ�ţ�����һ�Ž�����ֱ�ӽ�����Ч���ϱ㲻�����������л��ƴ�����������
		glfwSwapBuffers(window);//������ɫ����
		glfwPollEvents();//�����꣬���̣����´���״̬�������ö�Ӧ�Ļص�������
	}

	//�˳�glfw
	glfwTerminate();
	return 0;
}