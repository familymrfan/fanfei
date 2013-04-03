#include <iostream>

#include <memory>
#include <gtk/gtk.h>
#include "mainflow.h"
#include "dialogflow.h"
#include "screen_capture_controller.h"

#if defined(WIN32) || defined(_WIN32)

int main( int argc, char *argv[]);

#include <windows.h> 

int WINAPI WinMain(HINSTANCE hInstance, 
                   HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, 
                   int nCmdShow) 
{ 
    return main (__argc, __argv);
} 

#endif

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    auto flow = std::make_shared<Mainflow>();
    auto dialog = std::make_shared<Dialogflow>();
    auto screen_capture = std::make_shared<ScreenCaptureController>();
    
    flow->SetDownFlow(dialog);
    dialog->SetDownFlow(screen_capture,true,0);
    flow->Fall();
    gtk_main();
    
    return 0;
}
