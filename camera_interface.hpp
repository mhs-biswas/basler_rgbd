#pragma once

// #include <opencv4/opencv2/core.hpp>
// #include<opencv4/opencv2/core.hpp>
#include<opencv2/core.hpp>

namespace camera{
    class camera_interface{
        public:
            virtual bool initialize() = 0;
            virtual cv::Mat capture() = 0;
            virtual bool shutdown() = 0;
    };
}