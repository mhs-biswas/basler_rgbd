#pragma once


#include <opencv2/core.hpp>
#include </opt/MVS/include/MvCameraControl.h>
#include "camera_interface.hpp"
#include "MvCameraControl.h"

#include <mutex>
#include <atomic>

// mhay todo: maybe use pimpl idiom?
namespace camera {
    class hik_vision: public camera_interface {
        public:
            hik_vision();
            ~hik_vision();
            
            bool initialize() override final;
            cv::Mat capture() override final;
            bool shutdown() override final;

        private:
            void*               handle_;
            MVCC_INTVALUE       param_;
            std::mutex          io_sync_;
            std::atomic<bool>   initialized_;
    };
}