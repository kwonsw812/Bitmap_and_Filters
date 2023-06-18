#include "Bitmap_window.h"
#include "BitmapImage.h"
#include "Filter.h"

using namespace Graph_lib;

Bitmap_window::Bitmap_window(Point xy, int w, int h, const string& title, const string& bitmap_path)
	: Window(xy, w, h, title),
	win_width(w),
	win_height(h),
	btn_reset(Point(w-80*3, 10), 70, 20, "Reset", cb_reset),
	btn_save(Point(w-80*2, 10), 70, 20, "Save", cb_save),
	btn_exit(Point(w-80*1, 10), 70, 20, "Exit", cb_exit),
	image_path(bitmap_path),
	left_bitmap(nullptr),
	right_bitmap(nullptr)
{
	attach(btn_reset);
	attach(btn_save);
	attach(btn_exit);

	//
	makeBitmaps();
	makeGrids();
	makeFilters();
	makeButtons();
}

Bitmap_window::~Bitmap_window()
{
	delete left_bitmap;
	delete right_bitmap;

	for (Rectangle* rect : left_grid)
	{
		delete rect;
	}

	for (Rectangle* rect : right_grid)
	{
		delete rect;
	}
}

void Bitmap_window::makeBitmaps()
{
	delete left_bitmap;
	delete right_bitmap;

	left_bitmap = new BitmapImage(image_path);
	right_bitmap = new BitmapImage(*left_bitmap);
	left_bitmap->clear();
}

void Bitmap_window::resetBitmaps()
{
	delete left_bitmap;
	delete right_bitmap;

	left_bitmap = new BitmapImage(image_path);
	right_bitmap = new BitmapImage(*left_bitmap);
	left_bitmap->clear();
}

void Bitmap_window::makeGrids()
{
	if (!left_bitmap || !right_bitmap)
	{
		return;
	}

	for (Rectangle* rect : left_grid)
	{
		delete rect;
	}

	for (Rectangle* rect : right_grid)
	{
		delete rect;
	}

	int grid_width = (win_width - 20) / 2;
	int grid_height = (win_height - 40);

	makeGrid(left_bitmap, Point(10, 40), grid_width, grid_height, &left_grid);
	makeGrid(right_bitmap, Point(10 + grid_width + 10, 40), grid_width, grid_height, &right_grid);
}

void Bitmap_window::updateGrids()
{
	updateGrid(left_bitmap, &left_grid);
	updateGrid(right_bitmap, &right_grid);
}

void Bitmap_window::makeGrid(BitmapImage* bitmap, Point xy, int w, int h, vector<Rectangle*>* grid)
{
	int grid_ncol = bitmap->getWidth();
	int grid_nrow = bitmap->getHeight();

	int cell_width = (int)((double)w / (double)grid_ncol);
	int cell_height = (int)((double)h / (double)grid_nrow);

	for (int r = 0; r < grid_nrow; r++)
	{
		for (int c = 0; c < grid_ncol; c++)
		{
			Point rect_xy(xy.x + cell_width * c, xy.y + cell_height * r);
			Graph_lib::Rectangle* rect = new Graph_lib::Rectangle(rect_xy, cell_width, cell_height);

			double v = bitmap->getPixel(c, r);
			if (v > 1.0) v = 1.0;
			if (v < 0.0) v = 0.0;

			uchar r = (uchar)(v * 255.0);
			uchar g = (uchar)(v * 255.0);
			uchar b = (uchar)(v * 255.0);

			rect->set_fill_color(Color(fl_rgb_color(r, g, b)));
			rect->set_color(Color(fl_rgb_color(r,g,b)));		
			grid->push_back(rect);

			attach(*rect);
		}
	}
}

void Bitmap_window::updateGrid(BitmapImage* bitmap, vector<Rectangle*>* grid)
{
	int grid_ncol = bitmap->getWidth();
	int grid_nrow = bitmap->getHeight();

	int num_cells = grid_ncol * grid_nrow;
	if (num_cells != grid->size())
	{
		return;
	}

	for (int r = 0; r < grid_nrow; r++)
	{
		for (int c = 0; c < grid_ncol; c++)
		{
			int cell_index = r * grid_ncol + c;
			Rectangle* rect = (*grid)[cell_index];

			double v = bitmap->getPixel(c, r);
			if (v > 1.0) v = 1.0;
			if (v < 0.0) v = 0.0;

			uchar r = (uchar)(v * 255.0);
			uchar g = (uchar)(v * 255.0);
			uchar b = (uchar)(v * 255.0);

			rect->set_fill_color(Color(fl_rgb_color(r, g, b)));
			rect->set_color(Color(fl_rgb_color(r, g, b)));
		}
	}

	Fl::redraw();
}

void Bitmap_window::makeFilters()
{
	filters.push_back(new NegativeFilter);
	filters.push_back(new GaussianFilter);
	filters.push_back(new ZoomInFilter);
	filters.push_back(new ZoomOutFilter);
	filters.push_back(new HighPassFilter);
	filters.push_back(new SharpenFilter);
}

void Bitmap_window::makeButtons()
{
	btn_filters.push_back(new Button(Point(10, 10), 70, 20, filters[0]->getName(), cb_filter0));
	btn_filters.push_back(new Button(Point(90, 10), 70, 20, filters[1]->getName(), cb_filter1));
	btn_filters.push_back(new Button(Point(170, 10), 70, 20, filters[2]->getName(), cb_filter2));
	btn_filters.push_back(new Button(Point(250, 10), 70, 20, filters[3]->getName(), cb_filter3));
	btn_filters.push_back(new Button(Point(330, 10), 70, 20, filters[4]->getName(), cb_filter4));
	btn_filters.push_back(new Button(Point(410, 10), 70, 20, filters[5]->getName(), cb_filter5));

	for (Button* btn : btn_filters)
	{
		attach(*btn);
	}

	Fl::redraw();
}

void Bitmap_window::filter(int i)
{
	BitmapImage temp_bitmap(*right_bitmap);
	*right_bitmap = filters[i]->process(*right_bitmap);
	*left_bitmap = temp_bitmap;

	updateGrids();
	Fl::redraw();
}

void Bitmap_window::reset()
{
	resetBitmaps();

	updateGrids();
	Fl::redraw();
}

void Bitmap_window::save()
{
	if (right_bitmap != nullptr)
	{
		right_bitmap->savePGM("saved_image.pgm");
	}
}

void Bitmap_window::exit()
{
	hide();
}

void Bitmap_window::cb_filter0(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).filter(0);
}

void Bitmap_window::cb_filter1(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).filter(1);
}

void Bitmap_window::cb_filter2(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).filter(2);
}

void Bitmap_window::cb_filter3(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).filter(3);
}

void Bitmap_window::cb_filter4(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).filter(4);
}

void Bitmap_window::cb_filter5(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).filter(5);
}

void Bitmap_window::cb_reset(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).reset();
}

void Bitmap_window::cb_save(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).save();
}

void Bitmap_window::cb_exit(Address, Address pw)
{
	reference_to<Bitmap_window>(pw).exit();
}
