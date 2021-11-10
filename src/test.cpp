#include "hik_vision.hpp"
#include <opencv2/opencv.hpp>
#include<iostream>

int main()
{
    camera::hik_vision my_camera;
    std::cout<<my_camera.initialize()<<'\n';

    
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    while(true)
    {   cv::Mat frame = my_camera.capture();
        cv::imshow("Display Image",frame);

        char c=(char)cv::waitKey(1);
        if(c==27)
        break;

    }

    my_camera.shutdown();
    
    // cv::waitKey(0.1);

    return 0;



}

