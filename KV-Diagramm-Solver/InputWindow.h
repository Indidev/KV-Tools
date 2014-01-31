#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

class InputWindow: public MyWindow {

	private:
		Fl_Button *exitButton;
		Fl_Button *okButton;
		Fl_Int_Input *input;
	
	public: 
		InputWindow(int t, int l, int w, int h, char* title);
		void handleCallback(Fl_Widget* widgetptr);
		void handleEnterCallback(Fl_Widget* widgetptr);

};

#endif
