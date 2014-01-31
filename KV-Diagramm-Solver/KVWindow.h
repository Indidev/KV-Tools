#ifndef KVWINDOW_H
#define KVWINDOW_H

class KVWindow : public MyWindow {

	private:
		const static int BSIZE = 50;
		const static int OFFSET = 100;
		const static int LINEWIDTH = 2;
		int quantity;
		int blockType;
		vector<KVEntry*> entrys;
		//vector<KVEntryBox> buttons;
		vector<PrimBlock*> primBlocks;
		vector<int> xCord;
		vector<int> yCord;
		
		Fl_Button *stepButton;
		Fl_Button *resetButton;
		Fl_Button *solveButton;
		Fl_Button *blockTypeButton;
		
		void drawTable();
		void drawHLine(int index);
		void drawVLine(int index);
		void solve();
		void reset();
		void changeBlockType();

	public:
		KVWindow(int t, int l, int w, int h, char* title, vector<KVEntry*> *entrys);
		void handleCallback(Fl_Widget* widgetptr);
		void handleEnterCallback(Fl_Widget* widgetptr){}
		bool solveStep();

};

#endif
