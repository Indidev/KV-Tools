#ifndef MYHLINE_H
#define MYLABEL_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
//#include <FL/Fl_Color.H>

class MyVLine : public Fl_Box {

	public:
		MyVLine(int x, int y, int length, int width, Fl_Color bgcolor, char* label = 0):Fl_Box(x - width / 2, y, width, length, label) {
			this->color(bgcolor);
			this->box(FL_FLAT_BOX);
			this->clear_visible_focus();
		}
		
		virtual void setLength(int length) {
			this->resize(this->x(), this->y(), this->w(), length);
		}
		
		virtual void doubleLength() {
			this->resize(this->x(), this->y(), this->w(), 2 * this->h());
		}
};

#endif
