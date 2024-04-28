#include "MyApp.h"

int main(int argc, char* argv[]) {
    MyApp app;
    wxApp::SetInstance(&app);
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
    return 0;
}