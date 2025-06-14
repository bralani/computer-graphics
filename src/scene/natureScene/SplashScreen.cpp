#include "scene/natureScene/SplashScreen.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

// --- Custom Image Loading Implementation ---

// A simple struct to hold image data and properties
struct ImageData
{
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char *data = nullptr;

    // Check if the data is valid
    bool isValid() const
    {
        return data != nullptr;
    }
};

// Deallocates the memory for the image data
void freeImageData(ImageData &imageData)
{
    if (imageData.data)
    {
        delete[] imageData.data;
        imageData.data = nullptr;
    }
}

ImageData loadBMP(const char *filePath)
{
    ImageData imageData;
    std::ifstream file(filePath, std::ios::binary);

    if (!file)
    {
        std::cerr << "ERROR::BMP_LOADER::FILE_NOT_FOUND: " << filePath << std::endl;
        return imageData;
    }

    // BMP File Header (14 bytes)
    char fileHeader[14];
    file.read(fileHeader, 14);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M')
    {
        std::cerr << "ERROR::BMP_LOADER::INVALID_SIGNATURE" << std::endl;
        return imageData;
    }

    // DIB (Device-Independent Bitmap) Header (we assume BITMAPINFOHEADER - 40 bytes)
    char dibHeader[40];
    file.read(dibHeader, 40);

    // Get image dimensions
    int width = *reinterpret_cast<int *>(&dibHeader[4]);
    // A negative height in BMP means the image is stored top-down. We'll handle the common positive case.
    int height = *reinterpret_cast<int *>(&dibHeader[8]);
    short bitsPerPixel = *reinterpret_cast<short *>(&dibHeader[14]);

    if (bitsPerPixel != 24 && bitsPerPixel != 32)
    {
        std::cerr << "ERROR::BMP_LOADER::UNSUPPORTED_BPP: " << bitsPerPixel << std::endl;
        return imageData;
    }

    int channels = bitsPerPixel / 8;
    int dataOffset = *reinterpret_cast<int *>(&fileHeader[10]);

    // Each row in a BMP must be a multiple of 4 bytes. Calculate padding.
    int rowPadded = (width * channels + 3) & (~3);
    int rawDataSize = rowPadded * height;
    std::vector<char> rawData(rawDataSize);

    // Seek to the beginning of the pixel data and read it all
    file.seekg(dataOffset, std::ios::beg);
    file.read(rawData.data(), rawDataSize);
    file.close();

    // Allocate final buffer for color-swizzled data
    unsigned char *finalData = new unsigned char[width * height * channels];

    // --- CORRECTED LOGIC ---
    // The BMP data is already bottom-up, which is what OpenGL expects.
    // We just need to copy it, handle row padding, and convert from BGR(A) to RGB(A).
    for (int y = 0; y < height; y++)
    {
        // Point to the source row (with padding)
        char *sourceRow = rawData.data() + y * rowPadded;
        // Point to the destination row (no padding)
        unsigned char *destRow = finalData + y * width * channels;

        for (int x = 0; x < width; x++)
        {
            int sourceIndex = x * channels;
            int destIndex = x * channels;

            // BGR -> RGB swizzling
            destRow[destIndex + 0] = sourceRow[sourceIndex + 2]; // Red
            destRow[destIndex + 1] = sourceRow[sourceIndex + 1]; // Green
            destRow[destIndex + 2] = sourceRow[sourceIndex + 0]; // Blue
            if (channels == 4)
            {
                destRow[destIndex + 3] = sourceRow[sourceIndex + 3]; // Alpha
            }
        }
    }

    imageData.width = width;
    imageData.height = height;
    imageData.channels = channels;
    imageData.data = finalData;

    return imageData;
}

const char *backgroundVertexShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    TexCoords = aTexCoords;
}
)glsl";

const char *backgroundFragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D backgroundTexture;

void main()
{
    FragColor = texture(backgroundTexture, TexCoords);
}
)glsl";

namespace SplashScreen
{
    // Funzione helper per compilare gli shader
    GLuint compileShader(GLenum type, const char *source)
    {
        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cerr << "ERRORE::SHADER::COMPILAZIONE_FALLITA\n"
                      << infoLog << std::endl;
        }
        return shader;
    }

    // Funzione helper per creare lo shader program
    GLuint createShaderProgram(const char *vertexSource, const char *fragmentSource)
    {
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        int success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            std::cerr << "ERRORE::PROGRAM::LINKING_FALLITO\n"
                      << infoLog << std::endl;
        }
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return program;
    }

    AppState run()
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW for splash screen" << std::endl;
            return AppState::EXIT;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        const int screenWidth = 800;
        const int screenHeight = 600;
        GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "Medieval village", nullptr, nullptr);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window for splash screen" << std::endl;
            glfwTerminate();
            return AppState::EXIT;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return AppState::EXIT;
        }

        // --- 1. Preparazione per lo sfondo ---

        // Compila e linka lo shader program per lo sfondo
        GLuint backgroundShader = createShaderProgram(backgroundVertexShaderSource, backgroundFragmentShaderSource);

        // Vertici per un quad a schermo intero
        float quadVertices[] = {
            // positions   // texture Coords
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f};

        GLuint quadVAO, quadVBO;
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

        // Caricamento della texture di sfondo
        GLuint backgroundTexture;
        glGenTextures(1, &backgroundTexture);
        glBindTexture(GL_TEXTURE_2D, backgroundTexture);
        // Imposta opzioni di wrapping e filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // === MODIFIED SECTION: Use the custom BMP loader ===
        ImageData backgroundImage = loadBMP("background.bmp");

        if (backgroundImage.isValid())
        {
            GLenum format = (backgroundImage.channels == 4) ? GL_RGBA : GL_RGB;
            glTexImage2D(GL_TEXTURE_2D, 0, format, backgroundImage.width, backgroundImage.height, 0, format, GL_UNSIGNED_BYTE, backgroundImage.data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cerr << "Failed to load background texture using custom BMP loader." << std::endl;
        }
        // Free the memory used by our custom loader
        freeImageData(backgroundImage);
        // === END OF MODIFIED SECTION ===

        // --- 2. Inizializzazione di Dear ImGui ---
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        ImGui::StyleColorsDark();

        // --- START: MODIFICATION FOR LARGER FONT ---
        // We load the default font, but at a larger size. You can adjust the pixel size.
        ImFont *largeFont = nullptr;
        ImFontConfig font_config;
        font_config.SizePixels = 32.0f; // Set desired font size
        largeFont = io.Fonts->AddFontDefault(&font_config);
        // --- END: MODIFICATION FOR LARGER FONT ---

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330"); // This will also build the new font atlas

        AppState nextState = AppState::SPLASH_SCREEN;

        // --- 3. Loop dello Splash Screen ---
        while (nextState != AppState::EXIT && !glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // --- Rendering dello sfondo ---
            glDisable(GL_DEPTH_TEST);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Disegna il quad di sfondo
            glUseProgram(backgroundShader);
            glBindTexture(GL_TEXTURE_2D, backgroundTexture);
            glBindVertexArray(quadVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            switch (nextState)
            {
            /* ---------- Initialize Page ---------- */
            case AppState::INITIALIZE_VULKAN:
                glfwSetWindowShouldClose(window, true);
                break;


            /* ---------- SPLASH SCREEN ---------- */
            case AppState::SPLASH_SCREEN:
            {
                ImGui::SetNextWindowPos({screenWidth / 2.f, screenHeight / 2.f},
                                        ImGuiCond_Always, {0.5f, 0.5f});
                ImGui::SetNextWindowSize({300, 300});
                ImGui::Begin("Splash", nullptr,
                             ImGuiWindowFlags_NoDecoration |
                                 ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoBackground);

                ImGui::PushFont(largeFont);

                /* --- Play --- */
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.f - 100);
                if (ImGui::Button("Play", {200, 80}))
                    nextState = AppState::INITIALIZE_VULKAN;

                ImGui::Dummy({0, 10});

                /* --- Controls --- */
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.f - 100);
                if (ImGui::Button("Controls", {200, 80}))
                    nextState = AppState::CONTROLS_SCREEN;

                ImGui::Dummy({0, 10});

                /* --- Exit --- */
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.f - 100);
                if (ImGui::Button("Exit", {200, 80}))
                    nextState = AppState::EXIT;

                ImGui::PopFont();
                ImGui::End();
                break;
            }

            /* ---------- CONTROLS PAGE ---------- */
            case AppState::CONTROLS_SCREEN:
            {
                ImGui::SetNextWindowPos({screenWidth / 2.f, screenHeight / 2.f},
                                        ImGuiCond_Always, {0.5f, 0.5f});
                ImGui::SetNextWindowSize({600, 500});
                ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0.6f));
                ImGui::Begin("Controls", nullptr,
                             ImGuiWindowFlags_NoDecoration |
                                 ImGuiWindowFlags_NoMove);

                ImGui::PushFont(largeFont);
                ImGui::TextUnformatted("Controls");
                ImGui::PopFont();
                ImGui::Separator();

                ImGui::Text("W A S D  -  Move");
                ImGui::Text("Mouse    -  Look around");
                ImGui::Text("G        -  Grab / release object");
                ImGui::Text("H        -  Day / Night");
                ImGui::Text("V        -  Enter / Exit the boat");
                ImGui::Text("1        -  Switch to ISO view");
                ImGui::Text("2        -  Switch to DIME view");
                ImGui::Text("3        -  Switch to TRIME view");
                ImGui::Text("0        -  Switch to NORMAL view");

                ImGui::Dummy({0, 15});
                ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.f - 80);
                if (ImGui::Button("Back", {160, 60}))
                    nextState = AppState::SPLASH_SCREEN;

                ImGui::End();
                ImGui::PopStyleColor();
                break;
            }

            default: /* INITIALIZE_VULKAN o altro */
                break;
            }
            // --- END: MODIFICATION FOR LARGER UI ---

            // Rendering di ImGui
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }

        // --- 4. Cleanup ---
        // Cleanup delle risorse di sfondo
        glDeleteVertexArrays(1, &quadVAO);
        glDeleteBuffers(1, &quadVBO);
        glDeleteProgram(backgroundShader);
        glDeleteTextures(1, &backgroundTexture);

        // Cleanup di ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // Cleanup di GLFW
        glfwDestroyWindow(window);
        glfwTerminate();

        return nextState;
    }
}
