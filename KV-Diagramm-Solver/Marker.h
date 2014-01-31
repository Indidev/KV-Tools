#ifndef MARKER_H
#define MARKER_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <string>

class Marker : public Fl_Box {	

	private:
		int left;
		int top;
		int width;
		int height;

	public:
		
		Marker(int x, int y, int w, int h, Fl_Color color):Fl_Box(x, y, w, h){
		
			int x_rand = Functions::i_rand(0, 10);
			int y_rand = Functions::i_rand(0, 10);
			
			Fl_Box::resize(x + x_rand, y + y_rand, w - 10, h - 10);
			
			this->left = x;
			this->top = y;
			this->width = w;
			this->height = h;
			this->box(FL_ROUNDED_FRAME);
			this->color(color);
		}
		
		int w() {return width;}
		int h() {return height;}
		int x() {return left;}
		int y() {return top;}
		
		virtual void resize (int x, int y, int w, int h) {
		
			int x_rand = Functions::i_rand(0, 10);
			int y_rand = Functions::i_rand(0, 10);
		
			Fl_Box::resize(x + x_rand, y + y_rand, w - 10, h - 10);
		
			this->left = x;
			this->top = y;
			this->width = w;
			this->height = h;
		}

};

#endif
