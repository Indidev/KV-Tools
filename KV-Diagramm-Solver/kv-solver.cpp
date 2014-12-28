
#include "InputWindow.cpp"
#include <FL/Fl.H>

#define GTKP "gtk+"
#define PLASTIC "plastic"
#define STANDART "none"

int main() {

Fl::scheme(GTKP);
Fl_Window *win = new InputWindow(50, 50, 400, 250, "Test");

win->show();

return Fl::run();
}
