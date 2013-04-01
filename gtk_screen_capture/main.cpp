#include <iostream>

#include <memory>
#include <gtk/gtk.h>
#include "mainflow.h"
#include "dialogflow.h"
#include "screencapture.h"

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    auto flow = std::make_shared<Mainflow>();
    auto dialog = std::make_shared<Dialogflow>();
    auto screen_capture = std::make_shared<ScreenCapture>();
    
    flow->SetDownFlow(dialog);
    dialog->SetDownFlow(screen_capture);
    flow->Fall();
    gtk_main();
    
    return 0;
}
