#ifndef KVENTRYBOX_H
#define KVENTRYBOX_H

class KVEntryBox : public MyButton {
	private:
		Fl_Box *numberBox;
		int number;
	
	public:
		KVEntryBox(int x, int y, int w, int h, char* entry, int number, MyWindow *parent):MyButton(x, y, w, h, entry, parent) {
		
			this->box(FL_BORDER_FRAME);
			this->color(FL_BLACK);
			this->clear_visible_focus();
			this->number = number;
		
			int h2 = h / 5;
			numberBox = new Fl_Box(x, y + 4 * h2 - 2, w, h2, Functions::intToCString(number));
			numberBox->align(FL_ALIGN_RIGHT | FL_ALIGN_INSIDE);
			numberBox->labelsize(h2);
			numberBox->labelcolor(FL_DARK3);
		}
		
		int getNum() {
			return number;
		}
		
		void changeEntry(char* entry) {
			this->label(entry);
		}

};

#endif
