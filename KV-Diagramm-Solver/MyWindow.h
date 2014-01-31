#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#ifndef MYWINDOW_H
#define MYWINDOW_H
class MyWindow: public Fl_Window {

	public:
		MyWindow(int t, int l, int w, int h, char* title):Fl_Window(t, l, w, h, title){}
		void close() {
			this->hide();
			this->~Fl_Window();
		}
		virtual void handleCallback(Fl_Widget* widgetptr) = 0;
		virtual void handleEnterCallback(Fl_Widget* widgetptr) = 0;
};

#endif
