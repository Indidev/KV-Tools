#ifndef KVENTRYBOX_H
#define KVENTRYBOX_H

/**
	Provides a box to display a kv-entry and it's index.
*/
class KVEntryBox : public MyButton {
	private:
		Fl_Box *numberBox;
	
	public:
		KVEntryBox(int x, int y, int w, int h, char* entry, int number, MyWindow *parent):MyButton(x, y, w, h, entry, parent) {
		
			//no background, black border, no focus
			this->box(FL_BORDER_FRAME);
			this->color(FL_BLACK);
			this->clear_visible_focus();
		
			//add index at the lower right corner
			int h2 = h / 5;
			numberBox = new Fl_Box(x, y + 4 * h2 - 2, w, h2, Functions::intToCString(number));
			numberBox->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
			numberBox->labelsize(h2);
			numberBox->labelcolor(FL_DARK3);
		}

};

#endif
