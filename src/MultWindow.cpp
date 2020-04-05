#include "MultWindow.h"

MultWindow::MultWindow(string window_title, int cols,
                                         int rows, int flags)
    : window_title(window_title), cols(cols),
      rows(rows) /*, canvas_width(1200), canvas_height(700)*/
{
  namedWindow(window_title, flags);
  canvas = Mat(canvas_height, canvas_width, CV_8UC3);
  imshow(window_title, canvas);
}

int MultWindow::addImage(string title, Mat image, bool render) {
  titles.push_back(title);
  images.push_back(image);
  if (render)
    this->render();
  return images.size() - 1;
}

void MultWindow::removeImage(int pos) {
  titles.erase(titles.begin() + pos);
  images.erase(images.begin() + pos);
}

void MultWindow::render() {
  // Clean our canvas
  canvas.setTo(Scalar(20, 20, 20));
  // width and height of cell. add 10 px of padding between images
  int cell_width = (canvas_width / cols);
  int cell_height = (canvas_height / rows);
  int margin = 10;
  int max_images =
      (images.size() > cols * rows) ? cols * rows : images.size();
  int i = 0;
  vector<string>::iterator titles_it = titles.begin();
  for (vector<Mat>::iterator it = images.begin();
       it != images.end(); ++it) {
    string title = *titles_it;
    int cell_x = (cell_width) * ((i) % cols);
    int cell_y = (cell_height)*floor((i) / (float)cols);
    Rect mask(cell_x, cell_y, cell_width, cell_height);
    // Draw a rectangle for each cell mat
    rectangle(canvas, Rect(cell_x, cell_y, cell_width, cell_height),
              Scalar(200, 200, 200), 1);
    Mat cell(canvas, mask);
    Mat resized;
    double cell_aspect = (double)cell_width / (double)cell_height;
    Mat img = *it;
    double img_aspect = (double)img.cols / (double)img.rows;
    double f = (cell_aspect < img_aspect)
                   ? (double)cell_width / (double)img.cols
                   : (double)cell_height / (double)img.rows;
    resize(img, resized, Size(0, 0), f, f);
    if (resized.channels() == 1) {
      cvtColor(resized, resized, COLOR_GRAY2BGR);
    }

    Mat sub_cell(canvas,
                 Rect(cell_x, cell_y, resized.cols, resized.rows));
    resized.copyTo(sub_cell);
    putText(cell, title.c_str(), Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.5,
            Scalar(200, 0, 0), 1, LINE_AA);
    i++;
    ++titles_it;
    if (i == max_images)
      break;
  }

  imshow(window_title, canvas);
}
