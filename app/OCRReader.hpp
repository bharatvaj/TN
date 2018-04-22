#ifndef _OCR_READ_H
#define _OCR_READ_H "OCRReader"
#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/text/ocr.hpp>
using namespace cv::text;
class OCRReader
{
public:
  OCRReader()
  {
  }

  static std::vector<std::string> *getStringFromImage(std::string imagePath)
  {
    //void OCRTesseract::run(Mat& image, string& output_text, vector<Rect>* component_rects=NULL, vector<string>* component_texts=NULL, vector<float>* component_confidences=NULL, int component_level=0
    return new std::vector<std::string>();
  }
};
#endif