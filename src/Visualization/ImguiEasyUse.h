#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

/// @brief A easy-to-use wrapper for ImGui.
/// @note You should call init() before render loop, render() in render loop, cleanup() after render loop.
/// Write whatever you want to extra render in renderThings(). See `void MiniGL::mainLoop()` for example.
class ImguiEasyUse
{
public:
	// before render loop
	static void init(GLFWwindow* window)
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();
	}

	// in render loop(before glfwSwapBuffers and after draw other elements)
	static void render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		renderThings();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	static void renderThings()
	{
		ImGui::ShowDemoWindow();
		ImGui::Begin("Hello, world!");
		ImGui::Button("Look at this pretty button");
		ImGui::End();
	}

	// after render loop(before glfwDestroyWindow)
	static void cleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};