#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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




	//ѭ����Ⱦ,
	while (!glfwWindowShouldClose(window)) {//���glfw�Ƿ��˳�
		//��鰴���Ƿ���
		processInput(window);
		
		//��Ⱦָ��
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//�������¼�����������
		//˫���壺ǰ�滺��һ�Ż���������ʾ����̨����⻺����һ�ţ�����һ�Ž�����ֱ�ӽ�����Ч���ϱ㲻�����������л��ƴ�����������
		glfwSwapBuffers(window);//������ɫ����
		glfwPollEvents();//�����꣬���̣����´���״̬�������ö�Ӧ�Ļص�������
	}

	//�˳�glfw
	glfwTerminate();
	return 0;
}