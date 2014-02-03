#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>

#include <vector>
#include <string>
#include <iostream>

#include "MyLabel.h"
#include "InputDataWin.h"
#include "Functions.h"
#include "KVEntry.h"
#include "MyRadioButton.h"


#include "KVWindow.cpp"

using namespace std;

InputDataWin::InputDataWin(int t, int l, int w, int h, char* title, int quantity):MyWindow(t, l, w, h, title) {
	this->quantity = quantity;
	
	this->color(FL_LIGHT3);
	
	fulldef = true;
	isMint = true;
	selectedOption = 0;
	
	drawBasicComponents();
	drawSpecialComponents();
}

void InputDataWin::handleCallback(Fl_Widget* widgetptr) {
	if (widgetptr == exitButton) {
	
		if (fl_ask("really exit?") == 1) {
			this->hide();
			this->~MyWindow();
		}
		
	} else if (widgetptr == okButton) {
		
		initKVWin();
		
		this->close();
		
	} else if ((widgetptr == fulldefButton) || (widgetptr == nfulldefButton)) {
		fulldef = fulldefButton->value();
		
		this->redraw();
	} else if((widgetptr == mint) || (widgetptr == maxt)) {
		isMint = mint->value();
		
		this->redraw();
	} else if((widgetptr == option[0]) || (widgetptr == option[1]) || (widgetptr == option[2])) {
		if (widgetptr == option[0]) {
			selectedOption = 0;
		} else if (widgetptr == option[1]) {
			selectedOption = 1;
		} else {
			selectedOption = 2;
		}	
			
		this->redraw();
	} else if(widgetptr == input1) {
		value1 = input1->value();
		
	} else if(widgetptr == input2) {
		value2 = input2->value();
	}
}

void InputDataWin::handleEnterCallback(Fl_Widget* widgetptr) {
	if ((widgetptr == input1) || (widgetptr == input2))
		handleCallback(okButton);
}

void InputDataWin::redraw() {
	this->clear();

	if (typeGroup != NULL)
		typeGroup->clear();
		
	drawBasicComponents();
	drawSpecialComponents();
	MyWindow::redraw();
}

void InputDataWin::drawBasicComponents() {
	
	string text = "Your function: f(";
	
	
	for (int i = quantity - 1; i >= 0; i--) {
		text += (97 + i);
		if (i > 0)
			text += ", ";
	}
	
	text += ")";
	
	this->begin();
	
		functionText = new MyLabel(10, 40, w(), 30, Functions::StringToCString(text));
	
		//add exit button
		exitButton = new MyButton(10, h() - 40, 100, 30, "Exit", this);
		exitButton->color(FL_LIGHT3);
		
		//add ok button
		okButton = new MyButton(w() - 110, h() - 40, 100, 30, "Next", this);
		okButton->color(FL_LIGHT3);
	
		defGroup = new Fl_Group(0, 0, w(), h(), "");	
	
		defGroup->begin();
	
			fulldefButton = new MyRadioButton(100, 100, 150, 30, "Full defined function ", this);
	
			nfulldefButton = new MyRadioButton(100, 130, 150, 30, "No full defined function ", this);
			if (fulldef)
				fulldefButton->set();
			else
				nfulldefButton->set();
	
		defGroup->end();
	
	this->end();
}

void InputDataWin::drawSpecialComponents() {
	this->begin();
		typeGroup = new Fl_Group(0, 0, w(), h(), "");
	
	typeGroup->begin();
	
		if(fulldef) {
			char* input_label = Functions::StringToCString((isMint)?"MINt: ":"MAXt: ");
			input1 = new MyInput(300, 200, 150, 30, input_label, this);
		
			mint = new MyRadioButton(50, 200, 150, 30, "MINt", this);
			maxt = new MyRadioButton(50, 230, 150, 30, "MAXt", this);
		
			if(isMint)
				mint->set();
			else
				maxt->set();
		
		} else {
			
			option[0] = new MyRadioButton(50, 200, 150, 30, "MINt + D", this);
			option[1] = new MyRadioButton(50, 230, 150, 30, "MAXt + D", this);
			option[2] = new MyRadioButton(50, 260, 150, 30, "MINt + MAXt", this);
			
			char* label1 = Functions::StringToCString((selectedOption == 1)?"MAXt: ":"MINt: ");
			char* label2 = Functions::StringToCString((selectedOption == 2)?"MAXt: ":"D: ");
			
			input1 = new MyInput(300, 200, 150, 30, label1, this);
			input2 = new MyInput(300, 230, 150, 30, label2, this);
			
			input2->value(Functions::StringToCString(value2));
			
			option[selectedOption]->set();
		}
		
		input1->value(Functions::StringToCString(value1));
		input1->take_focus();
		
	typeGroup->end();
	this->end();
}

void InputDataWin::initKVWin() {
	vector<KVEntry*> entrys;
	
	int defEntry = 0;
		
	if ((fulldef && !isMint) || (!fulldef && (selectedOption == 1)))
		defEntry = 1;	
	else if (!fulldef && (selectedOption == 2))
		defEntry = 2;
  
	for (int i = 0; i < pow(2, quantity); i++) {
		KVEntry *e = new KVEntry(i, defEntry);
		entrys.push_back(e);
	}
		
	vector<int> *values1 = Functions::splitStringToInt(input1->value(), ',');
	vector<int> *values2;
	
	for (int i = 0; i < values1->size(); i++) {
		if (values1->at(i) < entrys.size()) {
			entrys.at(values1->at(i))->setValue(1 - (defEntry % 2));
			entrys.at(values1->at(i))->lock(true);
		}
	}
	
	if (!fulldef) {
		vector<int> *values2 = Functions::splitStringToInt(input2->value(), ',');
		
		cout << selectedOption << endl;
		defEntry = (selectedOption == 2)?0:2;
		
		for (int i = 0; i < values2->size(); i++) {
			if(!entrys.at(values2->at(i))->lock() && (values2->at(i) < entrys.size()))
				entrys.at(values2->at(i))->setValue(defEntry);
		}
	}
		
	Fl_Window *kvwin = new KVWindow(10, 10, 600, 400, "KV-Diagramm", &entrys);
	kvwin->show();
}
