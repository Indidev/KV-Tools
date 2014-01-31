#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

/**
	Provides a window to enter the number of variables of the kv-diagramm
*/
class InputWindow: public MyWindow {

	private:
		Fl_Button *exitButton;
		Fl_Button *okButton;
		Fl_Int_Input *input;
	
	public: 
		InputWindow(int x, int y, int w, int h, char* title);
		
		/**
			Handles different callbacks
		*/
		void handleCallback(Fl_Widget* widgetptr);
		
		/**
			handles callbackes thrown by pushing the enter button
		*/		
		void handleEnterCallback(Fl_Widget* widgetptr);

};

#endif
