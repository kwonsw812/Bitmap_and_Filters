#include "Graph.h"
#include "Bitmap_window.h"

using namespace Graph_lib;

int main()
{
	Point tl(0, 0);
	Bitmap_window win(tl, 1200, 600, "Image Procssing", "cat.pgm");

	Fl::redraw();

	return gui_main();
}

