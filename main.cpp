#include "raylib.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "include/scene/scene.h"
#include "include/head/head.h"
#include "include/constDefinitions.h"
#include "include/libraryManager/libraryManager.h"
#include "include/body/body.h"
#include "include/albumMenu/albumMenu.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::filesystem::directory_iterator;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

vector<std::filesystem::path> getInPWDmain()
{
    string path = "./";
    vector<std::filesystem::path> files;

    for (const auto &file : directory_iterator(path))
    {
        files.push_back(file.path()); // Store paths in a vector
    }

    return files;
}

EventBus bus = EventBus();
Scene scene = Scene(bus);
LibraryManager manager = LibraryManager(&scene);

int main(void)
{
    manager.indexLibrary("./Library", 0);

    vector<std::filesystem::path> files = getInPWDmain(); // Store files in a vector
    for (const auto &file : files)
        cout << file << endl;

    // Initialization
    //--------------------------------------------------------------------------------------
    const int widthInBoxes = 6;
    const int screenWidth = (int)((20*(widthInBoxes+1) + (100)*(widthInBoxes))/2.0 * 3);
    const int screenHeight = 500;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE|FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(screenWidth, screenHeight, "myTunes");
    InitAudioDevice();

    int bodyWidth = (20*(widthInBoxes+1) + (100)*(widthInBoxes));
    Body body = Body(&scene, 0, 100, bodyWidth, screenHeight, &manager);//Reihenfolge von body und head ist wichtig, sonst "sizeSet" nicht richtig gefeuert
    Header head = Header(&scene, 0, 0, (int)(GetScreenWidth()), 100);
    scene.addObject(&body); 
    scene.addObject(&head);

    AlbumMenu menuRight = AlbumMenu(&scene,bodyWidth,100,screenWidth-bodyWidth,screenHeight, &manager);
    scene.addObject(&menuRight);

    SetMasterVolume(10.0);
    SetTargetFPS(60); // Set game to run at 60 FPS
    

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (size_t i = 0; i < files.size(); i++) // Iterate using index
        {
            Color color = BLUE;
            if (std::filesystem::is_directory(files[i]))
            {
                color = RED;
            }

            DrawText(files[i].string().c_str(), 20, 20 * (i + 10), 10, color);
        }
        float wheelMove = GetMouseWheelMove();
        if (wheelMove != 0) // Only trigger event when the wheel moves
        {
            scene.getEventBus().event("mouseWheelMoved", to_string(wheelMove));
        }

        scene.render();
        scene.process();
        scene.getMusicPlayer().update();

        EndDrawing();
    }

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context
    CloseAudioDevice();//--------------------------------------------------------------------------------------

    return 0;
}
