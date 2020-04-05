
#ifndef MIW_h
#define MIW_h

#include <string>
#include <iostream>
using namespace std;

// OpenCV includes
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

class MultWindow {
    public:
      MultWindow(string window_title, int cols, int rows, int flags);
        int addImage(string title, Mat image, bool render= false);
        void removeImage(int pos);
        void render();

    private:
        int cols;
        int rows;
        const int canvas_width = 1200;
        const int canvas_height = 700;
        string window_title;
        vector<string> titles;
        vector<Mat> images; 
        Mat canvas;
};


#endif
