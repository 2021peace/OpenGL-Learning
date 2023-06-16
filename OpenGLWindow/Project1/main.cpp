#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//检查按键是否按下
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


int main() {
	int ret = glfwInit();//初始化glfw
	//设置主版本号和此版本号3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//设置profile类型---指定哪个更opengl来配置生成上下文
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800,800,"myOpengl",NULL,NULL);
	if (window == NULL) {
		printf("error");
		glfwTerminate();
		return -1;
	}
	//将这个窗口设置为主要的上下文
	glfwMakeContextCurrent(window);

	//初始化GLEW
	glewExperimental = true;  //无原因
	if (glewInit() != GLEW_OK) {
		printf("init glew error");
		glfwTerminate();
		return -1;
	}

	//渲染窗口尺寸
	//1,2设置左下角，右下角坐标，
	//3,4设置控制渲染窗口的宽度和高度（像素）
	glViewport(0, 0, 800, 600);
	//设置窗口变化时的大小。
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);




	//循环渲染,
	while (!glfwWindowShouldClose(window)) {//检查glfw是否被退出
		//检查按键是否按下
		processInput(window);
		
		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//检查调用事件，交换缓存
		//双缓冲：前面缓存一张画面用于显示，后台会额外缓存另一张，当第一张结束，直接交换，效果上便不会有重新逐行绘制带来的闪屏。
		glfwSwapBuffers(window);//交换颜色缓存
		glfwPollEvents();//检查鼠标，键盘，更新窗口状态，并调用对应的回调函数。
	}

	//退出glfw
	glfwTerminate();
	return 0;
}