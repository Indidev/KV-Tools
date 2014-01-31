#ifndef MYHLINE_H
#define MYLABEL_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
//#include <FL/Fl_Color.H>

class MyHLine : public Fl_Box {

	public:
		MyHLine(int x, int y, int length, int width, Fl_Color bgcolor, char* label = 0):Fl_Box(x, y - width / 2, length, width, label) {
			this->color(bgcolor);
			this->box(FL_FLAT_BOX);
			this->clear_visible_focus();
		}
		
		virtual void setLength(int length) {
			this->resize(this->x(), this->y(), length, this->h());
		}
		
		virtual void doubleLength() {
			this->resize(this->x(), this->y(), 2 * this->w(), this->h());
		}
};

#endif
