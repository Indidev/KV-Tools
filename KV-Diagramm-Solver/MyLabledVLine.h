#ifndef MYLABLEDVLINE_H
#define MYLABLEDVLINE_H

class MyLabledVLine : public MyVLine {

	private:
		MyLabel *lineLabel;

	public:
	
		MyLabledVLine(int x, int y, int length, int width, Fl_Color bgcolor, char* label, bool isLeft):MyVLine(x, y, length, width, bgcolor) {
		
			int lX = x;
			int lW = 30;
			int lH = 30;
			int lY = y + (length - lW) / 2;
		
			if(isLeft)
				lX -= lW;
		
			lineLabel = new MyLabel(lX, lY, lW, lH, label);
		}
		
		void setLength(int length) {
			MyVLine::setLength(length);
			lineLabel->resize(lineLabel->x(), this->y() + (length - lineLabel->h()) / 2, lineLabel->w(), lineLabel->h());
		}
		
		void doubleLength() {
			MyVLine::doubleLength();
			lineLabel->resize(lineLabel->x(),  this->y() + (this->h() - lineLabel->h()) / 2, lineLabel->w(), lineLabel->h());
		}

};

#endif
