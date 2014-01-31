#include <FL/Fl.H>
#include <FL/Fl_Int_Input.H>

#include "MyWindow.h"

#ifndef MYINTINPUT_H
#define MYINTINPUT_H

class MyIntInput: public Fl_Int_Input {

protected:
	MyWindow *parent;
	
public:
	MyIntInput(int x, int y, int w, int h, char* label, MyWindow* parent):Fl_Int_Input(x, y, w, h, label){
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
