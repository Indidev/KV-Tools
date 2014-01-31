#ifndef MYLABLEDHLINE_H
#define MYLABLEDHLINE_H

class MyLabledHLine : public MyHLine {

	private:
		MyLabel *lineLabel;

	public:
	
		MyLabledHLine(int x, int y, int length, int width, Fl_Color bgcolor, char* label, bool isTop):MyHLine(x, y, length, width, bgcolor) {
		
			int lX = x;
			int lY = y;
			int lW = length;
			int lH = 30;
		
			if(isTop)
				lY -= lH;
		
			lineLabel = new MyLabel(lX, lY, lW, lH, label);
		}
		
		void setLength(int length) {
			MyHLine::setLength(length);
			lineLabel->resize(lineLabel->x(), lineLabel->y(), length, lineLabel->h());
		}
		
		void doubleLength() {
			MyHLine::doubleLength();
			lineLabel->resize(lineLabel->x(), lineLabel->y(), 2 * lineLabel->w(), lineLabel->h());
		}

};

#endif
