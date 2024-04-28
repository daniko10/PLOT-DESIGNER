#include "MyApp.h"
#include "MyFrame.h"

bool MyApp::OnInit() {
	SetProcessDPIAware();
	MyFrame* frame = new MyFrame("Wykresy");
	frame->Show(true);
	return true;
}

