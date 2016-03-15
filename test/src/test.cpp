#include "ImGUICommon/ImGUICommon.h"
#include "GLApp/GLApp.h"

struct Test : public GLApp::GLApp {
	typedef ::GLApp::GLApp Super;
	std::shared_ptr<ImGUICommon::ImGUICommon> gui;


    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);


	//post-sdl and gl init:
	virtual void init() {
		Super::init();
		gui = std::make_shared<ImGUICommon::ImGUICommon>(window);
	}

	virtual void shutdown() {
		Super::shutdown();
		gui = nullptr;	//dealloc and shutdown before sdl shuts down
	}

	virtual void update() {
		Super::update();

		gui->update([&](){

			// 1. Show a simple window
			// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
			{
				static float f = 0.0f;
				ImGui::Text("Hello, world!");
				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
				ImGui::ColorEdit3("clear color", (float*)&clear_color);
				if (ImGui::Button("Test Window")) show_test_window ^= 1;
				if (ImGui::Button("Another Window")) show_another_window ^= 1;
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			// 2. Show another simple window, this time using an explicit Begin/End pair
			if (show_another_window)
			{
				ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
				ImGui::Begin("Another Window", &show_another_window);
				ImGui::Text("Hello");
				ImGui::End();
			}

			// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
			if (show_test_window)
			{
				ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
				ImGui::ShowTestWindow(&show_test_window);
			}

		});
	}
};

GLAPP_MAIN(Test)
