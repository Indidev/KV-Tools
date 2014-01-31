#ifndef INPUTDATAWIN_H
#define INPUTDATAWIN_H

class InputDataWin : public MyWindow {

	private:
		MyLabel *functionText;
		Fl_Button *exitButton;
		Fl_Button *okButton;
		Fl_Group *defGroup;
		Fl_Group *typeGroup;
		Fl_Round_Button *fulldefButton;
		Fl_Round_Button *nfulldefButton;
		Fl_Round_Button *mint;
		Fl_Round_Button *maxt;
		Fl_Round_Button *option[3];
		Fl_Input *input1;
		Fl_Input *input2;
		
		int quantity;
		bool fulldef;
		bool isMint;
		string value1;
		string value2;
		int selectedOption;
		
		void drawBasicComponents();
		void drawSpecialComponents();
		void initKVWin();
		
	
	public:
		InputDataWin(int t, int l, int w, int h, char* title, int quantity);
		void handleCallback(Fl_Widget* widgetptr);
		void handleEnterCallback(Fl_Widget* widgetptr);
		void redraw();
};

#endif
