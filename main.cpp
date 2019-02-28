#include <iostream>
#include <string>

#include "FaceDetection.h"
#include "functions.h"

int main(int argc, char ** argv)
{
    if(std::string(argv[1]) == "-i")
    {
        cv::Mat src = cv::imread(argv[2]);
        
        //初始化：检测器
        SimdDetection detection;
        detection.Load("./data/cascade/haar_face_0.xml");
        SimdDetection::Size frameSize(src.cols,src.rows);
        detection.Init(frameSize, 1.2, frameSize / 10);
        
        //初始化：人脸对齐
        FaceAlignment alignment;
        
        //初始化：人脸识别
        FaceRecognition rec;
        
        //类型转化（共享数据）
        SimdDetection::View image = src;
        
        //进行检测
        SimdDetection::Objects objects;
        detection.Detect(image, objects);
        
        if(objects.empty())
        {
            std::cout<<"Face not detected!"<<std::endl;
            return 0;
        }
        
        //绘制检测结果
        Simd::DrawRectangle(image, objects[0].rect, Simd::Pixel::Bgr24(0, 255, 255),2);
        
        //人脸对齐
        dlib::full_object_detection shape;
        alignment.getShape(src,objects[0].rect,shape);
        
        //人脸识别
        std::string name;
        bool isInFaceDb = rec.recognize(src,shape,name);
        
        //显示
        cv::namedWindow("result",0);
        cv::imshow("result", src);
        cv::waitKey();
        
        return 0;
    }
    
    //初始化：摄像头
    cv::VideoCapture capture;
    capture.open(argv[1]);
    
    if (!capture.isOpened())
    {
        std::cout << "Can't capture!" << std::endl;
        return 1;
    }
    
    //初始化：检测器
    SimdDetection detection;
    detection.Load("./data/cascade/haar_face_0.xml");
    SimdDetection::Size frameSize(capture.get(3),capture.get(4));
    detection.Init(frameSize, 1.2, frameSize / 10);
    
    //初始化：人脸对齐
    FaceAlignment alignment;
    
    //初始化：人脸识别
    FaceRecognition rec;

    //初始化：窗口名
    const std::string WINDOW_NAME = "FaceDetection";
    cv::namedWindow(WINDOW_NAME, 1);

    for (;;)
    {
        //抓取一帧
        cv::Mat frame;
        capture >> frame;
        
        //类型转化（共享数据）
        SimdDetection::View image = frame;
        
        //进行检测
        SimdDetection::Objects objects;
        detection.Detect(image, objects);
        
        if(objects.size() > 0)
        {
            //绘制检测结果
            Simd::DrawRectangle(image, objects[0].rect, Simd::Pixel::Bgr24(0, 255, 255),2);
            
            //人脸对齐
            dlib::full_object_detection shape;
            alignment.getShape(frame,objects[0].rect,shape);
            
            //人脸识别
            std::string name;
            bool isInFaceDb = rec.recognize(frame,shape,name);
            
            if(isInFaceDb)
            {
                cv::putText(frame,name,objects[0].rect.TopLeft(),1,2,cv::Scalar(255,100,0),2);
            }
        }
        
        //显示
        cv::imshow(WINDOW_NAME, frame);
        if (cv::waitKey(1) == 'q')
            break;
    }
    
    return 0;
}
