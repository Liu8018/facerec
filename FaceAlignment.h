#ifndef FACEALIGNMENT_H
#define FACEALIGNMENT_H

#include <iostream>
#include "dlib/image_processing/shape_predictor.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <dlib/image_processing.h>
#include <dlib/opencv/cv_image.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>

class FaceAlignment
{
public:
    FaceAlignment();
    
    //void process(const cv::Mat &inputImg, const cv::Rect &faceRect, cv::Mat &sFace);
    
    void getShape(const cv::Mat &inputImg, const cv::Rect &faceRect, dlib::full_object_detection &shape);
    
private:
    dlib::shape_predictor m_shapePredictor;
    
    void cvRect2dlibRect(const cv::Rect &cvRec, dlib::rectangle& dlibRec);
    void dlibPoint2cvPoint(const dlib::full_object_detection &S, std::vector<cv::Point> &L);
};

#endif // FACEALIGNMENT_H
