#pragma once

#include <vector>
#include <string>

#include "Graph.h"
#include "Window.h"
#include "GUI.h"

class BitmapImage;
class Filter;

namespace Graph_lib
{
	struct Bitmap_window : Window
	{
		Bitmap_window(Point xy, int w, int h, const std::string& title, const std::string& bitmap_path);
		~Bitmap_window();

	private:
		int win_width;
		int win_height;

		std::string image_path;

		BitmapImage* left_bitmap;
		BitmapImage* right_bitmap;

		vector<Rectangle*> left_grid;
		vector<Rectangle*> right_grid;

		vector<Filter*> filters;

		void makeBitmaps();
		void resetBitmaps();
		
		void makeGrids();
		void makeGrid(BitmapImage* image, Point xy, int w, int h, vector<Rectangle*>* grid);

		void updateGrids();
		void updateGrid(BitmapImage* image, vector<Rectangle*>* grid);

		void makeFilters();
		void makeButtons();

		//
		std::vector<Button*> btn_filters;

		Button btn_reset;
		Button btn_save;
		Button btn_exit;

		void filter(int i);

		void reset();
		void save();
		void exit();

		static void cb_filter0(Address, Address window);
		static void cb_filter1(Address, Address window);
		static void cb_filter2(Address, Address window);
		static void cb_filter3(Address, Address window);
		static void cb_filter4(Address, Address window);
		static void cb_filter5(Address, Address window);

		static void cb_reset(Address, Address window);
		static void cb_save(Address, Address window);
		static void cb_exit(Address, Address window);
	};

};
