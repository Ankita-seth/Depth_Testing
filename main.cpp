#include "framework.h"

int WINAPI WinMain(HINSTANCE hInstance,    //Main windows function
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nShowCmd)

{
    DepthTesting* depth = new DepthTesting();
    if (depth)
    {
        // create the window
        if (!depth->InitializeWindow(hInstance, nShowCmd, depth->FullScreen))
        {
            MessageBox(0, L"Window Initialization - Failed",
                L"Error", MB_OK);
            return 1;
        }

        // initialize direct3d
        if (!depth->InitD3D())
        {
            MessageBox(0, L"Failed to initialize direct3d 12",
                L"Error", MB_OK);
            depth->Cleanup();
            return 1;
        }

        // start the main loop
        depth->mainloop();

        // we want to wait for the gpu to finish executing the command list before we start releasing everything
        depth->WaitForPreviousFrame();

        // close the fence event
        CloseHandle(depth->fenceEvent);

        // clean up everything
        depth->Cleanup();
    }
    delete depth;
    depth = NULL;
    return 0;
}
