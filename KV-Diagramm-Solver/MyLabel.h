#ifndef MYLABEL_H
#define MYLABEL_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>

class MyLabel : public Fl_Box {

	public:
		MyLabel(int t, int l, int w, int h, char* title): Fl_Box(t, l, w, h, title) {
			this->box(FL_NO_BOX);
			this->clear_visible_focus();
		}
		
		
		int handle(int event) {
			return 0;
		}

};

#endif
