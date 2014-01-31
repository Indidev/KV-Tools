#ifndef MARKER_H
#define MARKER_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <string>

/**
	This is a marker for the kv-diagramm, to mark prim-blocks.
*/
class Marker : public Fl_Box {	

	private:
		int left;
		int top;
		int width;
		int height;

	public:
		
		/**
			creates a new marker with the given color
		*/
		Marker(int x, int y, int w, int h, Fl_Color color):Fl_Box(x, y, w, h){
		
			//calculate random offset for x and y coordinates
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
		
		// override w, h, x and y method and return original parameters.
		int w() {return width;}
		int h() {return height;}
		int x() {return left;}
		int y() {return top;}
		
		/**
			overrides the original resize method
		*/
		virtual void resize (int x, int y, int w, int h) {
		
			//same as in the constructor
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
