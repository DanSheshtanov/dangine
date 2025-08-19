#include <Windows.h>

#include "Debug.h"
#include "TimeSystem.h"
#include "Window.h"
#include "Renderer.h"
#include "materials/Material.h"
#include "materials/Material_Lit.h"
#include "materials/Material_Waves.h"
#include "materials/Material_Skybox.h"
#include "Mesh.h"
#include "ModelLoader.h"
#include "Texture.h"
#include "Camera.h"
#include "Entity.h"


// Program entry point
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    Window wnd{ 800, 600, hInstance, nCmdShow };
    if (!wnd.Exists())
    {
        LOG("Failed to create a window, quitting...");
        return -1;
    }

    Renderer rend;
    if (FAILED(rend.Init(&wnd)))
    {
        LOG("Failed to create a renderer, quitting...");
        return -1;
    }

    // Assets
    Texture* tex_colourmap = new Texture{ rend, "assets/textures/colormap.png" };
    Texture* tex_white = new Texture{ rend, "assets/textures/white.png" };
    Texture* tex_skybox = new Texture{ rend, "assets/textures/skybox/skybox02.dds", Texture::TextureType::Cubemap };
    Texture* tex_skyboxTest = new Texture{ rend, "assets/textures/skybox/TestCubemap.dds", Texture::TextureType::Cubemap };
    Material* mat_standard = new Material{ "m_standard", rend, "Compiled Shaders/VertexShader.cso", "Compiled Shaders/PixelShader.cso", tex_white };
    //Material_Lit* mat_lit = new Material_Lit{ "m_lit", rend, "Compiled Shaders/VShaderLit.cso", "Compiled Shaders/PixelShader.cso", tex_colourmap };
    Material_Lit* mat_lit_coloured = new Material_Lit{ "m_lit", rend, "Compiled Shaders/VShaderLit.cso", "Compiled Shaders/ReflectivePS.cso", tex_colourmap };
    Material_Lit* mat_lit_white = new Material_Lit{ "m_lit", rend, "Compiled Shaders/VShaderLit.cso", "Compiled Shaders/ReflectivePS.cso", tex_white };
    mat_lit_coloured->SetReflectionTexture(tex_skybox);
    mat_lit_white->SetReflectionTexture(tex_skybox);
    mat_lit_white->reflectiveness = 0.5f;
    Material_Waves* mat_waves = new Material_Waves{ "m_waves", rend,"Compiled Shaders/VShaderWaves.cso", "Compiled Shaders/PixelShader.cso", tex_colourmap };
    Material_Skybox* mat_skybox = new Material_Skybox{ "m_skybox", rend, "Compiled Shaders/SkyboxVS.cso", "Compiled Shaders/SkyboxPS.cso", tex_skybox };
    Mesh* mesh_cube = new Mesh{ rend, "assets/models/cube.obj"};
    Mesh* mesh_sphere = new Mesh{ rend, "assets/models/sphere.obj"};
    Mesh* mesh_sub = new Mesh{ rend, "assets/models/sub.obj"};
    Mesh* mesh_pizza = new Mesh{ rend, "assets/models/pizza.obj"};

    // Scene
    Camera cam;
    cam.transform.position = XMVectorSetZ(cam.transform.position, -8);

    Entity skybox{ "Skybox", &mesh_cube, (Material**)&mat_skybox };
    rend.SetSkybox(&skybox);

    Entity e1{ "Sub", &mesh_sub, (Material**)&mat_waves};
    e1.transform.scale = XMVectorSet(10, 10, 10, 1);
    rend.RegisterEntity(&e1);

    Entity e2{ "Sphere", &mesh_sphere,(Material**)&mat_skybox};
    //Entity e2{ "Cube", &mesh2, &mat_standard};
    rend.RegisterEntity(&e2);
    e2.transform.Translate({ 3, 0, 0.5f });

    Entity e3{ "Cube", &mesh_cube, (Material**)&mat_lit_white};
    rend.RegisterEntity(&e3);
    e3.transform.Translate({ -3, 0, 0.5f });

    Entity e4{ "Pizza", &mesh_pizza, (Material**)&mat_lit_coloured };
    rend.RegisterEntity(&e4);
    e4.transform.Translate({ 0, -2.5f, 0 });
    e4.transform.scale = XMVectorSet(10, 10, 10, 1);

    rend.GetPointLights()[0].enabled = true;
    rend.GetPointLights()[0].colour = { 0, 1, 1, 1 };
    rend.GetPointLights()[0].position = { 0, 0, 0, 1 };

    // Used to hold windows event messages
    MSG msg;

    // Enter the main loop:
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // Translate certain messages into correct format, namely key presses
            TranslateMessage(&msg);
            // Send the message to the WindowProc function
            DispatchMessage(&msg);
            // Break out of the loop if a quit message is detected
            if (msg.message == WM_QUIT)
                break;
        }
        else
        {
            // Game code here
            Time::Update();

            XMVECTOR rotation = XMVectorScale({ 0.1f, 0.4f, 0.05f }, Time::GetDeltaTime());
            e2.transform.Rotate(XMVectorScale(rotation, 2.5f));
            //e3.transform.Rotate(XMVectorScale(-rotation, 2.5f));
            
            rend.GetPointLights()[0].position = XMVectorSetX(rend.GetPointLights()[0].position, sin(Time::GetElapsedTime() * 5));

            auto kbState = Keyboard::Get().GetState();
            auto msState = Mouse::Get().GetState();
            if (kbState.W)
                cam.transform.Translate(cam.transform.GetForward() * 5 * Time::GetDeltaTime());
            if (kbState.S)
                cam.transform.Translate(-cam.transform.GetForward() * 5 * Time::GetDeltaTime());
            if(kbState.D)
                cam.transform.Translate(cam.transform.GetRight() * 5 * Time::GetDeltaTime());
            if (kbState.A)
                cam.transform.Translate(-cam.transform.GetRight() * 5 * Time::GetDeltaTime());
            if (kbState.E)
                cam.transform.Translate(cam.transform.GetUp() * 5 * Time::GetDeltaTime());
            if (kbState.Q)
                cam.transform.Translate(-cam.transform.GetUp() * 5 * Time::GetDeltaTime());
            if (msState.leftButton)
                cam.transform.position = XMVectorSet(0, 0, 0, 0);
            cam.transform.Rotate(XMVECTOR{ -(float)msState.y, (float)msState.x } *0.001f);

            rend.RenderFrame(cam);
        }
    }

    return 0;
}