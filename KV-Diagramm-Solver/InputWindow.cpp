#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL/fl_ask.H>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#include "MyWindow.h"
#include "MyButton.h"
#include "MyInput.h"
#include "MyIntInput.h"
#include "Functions.h"
#include "InputDataWin.cpp"


#include "InputWindow.h"

InputWindow::InputWindow(int x, int y, int w, int h, char* title):MyWindow(x, y, w, h, title) {

	this->color(FL_LIGHT3);

	this->begin();

		//add exit button
		exitButton = new MyButton(10, h - 40, 100, 30, "Exit", this);
		exitButton->color(FL_LIGHT3);
		
		//add ok button
		okButton = new MyButton(w - 110, h - 40, 100, 30, "Next", this);
		okButton->color(FL_LIGHT3);
		okButton->deactivate();
		
		//add input formular
		input = new MyIntInput(175, 50, 50, 25, "Number of Variables:", this);

		input->take_focus();

	this->end();
	
}

void InputWindow::handleCallback(Fl_Widget* widgetptr) {
	
	if (widgetptr == exitButton) {
	
		if (fl_ask("really exit?") == 1)
			this->close();
		
	} else if (widgetptr == okButton) {
		
		Fl_Window *datawin = new InputDataWin(10, 10, 600, 400, "Input Data", Functions::StringToInt(input->value()));
		datawin->show();
		
		this->close();
		
	} else if (widgetptr == input) {
	
		if (!Functions::isNumber(input->value())) {
			if (strlen(input->value()) > 0) {
				char* newValue = new char[strlen(input->value()) + 1];
				strcpy(newValue, input->value());
				newValue[strlen(newValue) - 1] = '\0';
				input->value(newValue);
			}
		}
		
		//activate or deactivate next button according to the input
		if (Functions::isNumber(input->value()))
			okButton->activate();
		else
			okButton->deactivate();
			
	}
}

void InputWindow::handleEnterCallback(Fl_Widget* widgetptr) {
	if (widgetptr == input) {
		if (okButton->active()) {
			handleCallback(okButton);
		}
	}
}
