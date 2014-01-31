#include <FL/Fl.H>
#include <FL/Fl_Input.H>

#include "MyWindow.h"

#ifndef MYINPUT_H
#define MYINPUT_H

class MyInput: public Fl_Input {

protected:
	MyWindow *parent;
	
public:
	MyInput(int x, int y, int w, int h, char* label, MyWindow* parent):Fl_Input(x, y, w, h, label){
		this->parent = parent;
	}
	
	int handle(int event) {
		int value = Fl_Input::handle(event);
		
		if (event == 8) {
		
			if ((Fl::event_button() == 37) || (Fl::event_button() == 165))
				parent->handleEnterCallback(this);
			else
				parent->handleCallback(this);
		}
		
		return event;
	}

};

#endif
