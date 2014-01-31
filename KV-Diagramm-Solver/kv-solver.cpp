
#include "InputWindow.cpp"
#include <FL/Fl.H>

#define GTKP "gtk+"
#define PLASTIC "plastic"
#define STANDART "none"

//just the main function
int main() {

//set gtk theme
Fl::scheme(GTKP);

//create input window
Fl_Window *win = new InputWindow(50, 50, 400, 250, "Test");

//show window
win->show();

//run fltk
return Fl::run();
}
