#include "QWindowFactory.h"

#include <glad/glad.h>
#include "glfw/glfw3.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "implot.h"

#include <iostream>

bool _glfwInitialized = false;

void *QWindowFactory::CreateWindowGLFW(int width, int height, const char *title)
{
    // Check if GLFW is already initialized
    if (!_glfwInitialized)
    {
        if (!glfwInit())
        {
            // Initialization failed
            return nullptr;
        }
        _glfwInitialized = true;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    auto window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        // Window creation failed
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    // Setup Platform/Renderer bindings
    ImGui_ImplOpenGL3_Init("#version 450");

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    ImGui::SetCurrentContext(ImGui::GetCurrentContext());

    return window;
}

void DrawDockspace(bool *pOpen)
{
    static bool opt_fullscreen_persistant = true;
    bool opt_fullscreen = opt_fullscreen_persistant;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
    // and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

   
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("###DockSpace", pOpen, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // DockSpace
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }
    else
    {
        // ShowDockingDisabledMessage();
    }

    ImGui::End();
}

void QWindowFactory::RunWindowGLFW(void *window)
{
    GLFWwindow *pWindow = static_cast<GLFWwindow *>(window);
    if (!pWindow)
    {
        // Invalid window
        return;
    }

    glfwSwapInterval(1); // Enable V-Sync

    bool show_demo_window = true;
    while (!glfwWindowShouldClose(pWindow))
    {
        // Render here
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        const int size = 1000;
        float x_data[size];
        float y_data[size];

        // Generate a linear line: y = mx + b
        float m = 2.0f;  // Slope
        float b = 1.0f;  // Intercept

        for (int i = 0; i < size; i++) {
            x_data[i] = static_cast<float>(i);  // x values from 0 to 999
            y_data[i] = m * x_data[i] + b;      // Linear equation
        }
        // if (show_demo_window)
        // ImGui::ShowDemoWindow(&show_demo_window);

        // // Create ImGui windows
        ImGui::Begin("Hello, world!");
        if(ImPlot::BeginPlot("My Plot")){
            ImPlot::PlotLine("My Line", x_data, y_data, size);
            ImPlot::EndPlot();
        } 
        ImGui::End();
        bool open = true;
        DrawDockspace(&open);

        // Rendering
        int display_w, display_h;

        glfwGetFramebufferSize(pWindow, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
        glfwSwapBuffers(pWindow);
    }
}

void QWindowFactory::DestroyWindowGLFW(void *pWindow)
{

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();

    // cant really safely delete this guy... hmmm
    glfwDestroyWindow(static_cast<GLFWwindow *>(pWindow));
}
