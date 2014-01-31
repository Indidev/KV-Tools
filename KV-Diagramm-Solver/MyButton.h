#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

#include "MyWindow.h"

#ifndef MYBUTTON_H
#define MYBUTTON_H

class MyButton: public Fl_Button {

protected:
	MyWindow *parent;

public:
	MyButton(int x, int y, int w, int h, char* label, MyWindow* parent):Fl_Button(x, y, w, h, label) {
		this->parent = parent;
	}


	int handle(int event) {
		int value = Fl_Button::handle(event);
		static bool clickedOnButton = false;
		//parent->hide();
	
		if ((Fl::event_x() >= this->x()) && 
			(Fl::event_x() <= (this->x() + this->w())) &&
			(Fl::event_y() >= this->y()) && 
			(Fl::event_y() <= (this->y() + this->h()))) {
		
				//leftbutton down
				if ((Fl::event_button() == 1) && (event == 1))
					clickedOnButton = true;
				
				//leftbutton up
				if (clickedOnButton && (Fl::event_button() == 1) && (event == 2))
					parent->handleCallback(this);
		
		} else {
			//leftbutton down
			if ((Fl::event_button() == 1) && (event == 1))
					clickedOnButton = false;
		}
		
					
		return value;
	}

};

#endif
