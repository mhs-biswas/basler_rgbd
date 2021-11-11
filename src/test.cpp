#include "hik_vision.hpp"
#include <opencv2/opencv.hpp>
#include<iostream>
#include <ConsumerImplHelper/BlazeCamera.h>

using namespace GenTLConsumerImplHelper;
using namespace GenApi;


class Sample {
public:
    int run() {
        m_nBuffersGrabbed = 0;
        try {
            m_Camera.OpenFirstCamera();
            // Enable point cloud data.
            CEnumerationPtr(m_Camera.GetParameter("ComponentSelector"))->FromString("Range");
            CBooleanPtr(m_Camera.GetParameter("ComponentEnable"))->SetValue(true);
            CEnumerationPtr(m_Camera.GetParameter("PixelFormat"))->FromString("Coord3D_ABC32f");
            // Acquire images until the onImageGrabbed callback indicates to stop acquisition.
            m_Camera.GrabContinuous(5, 1000, this, &Sample::onImageGrabbed);
            m_Camera.Close();
        } catch (const GenICam::GenericException& e) {
            std::cerr << "Exception occurred: " << e.GetDescription() << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    bool onImageGrabbed(GrabResult grabResult, BufferParts parts) {
        if (grabResult.status == GrabResult::Timeout) {
            std::cerr << "Timeout occurred. Acquisition stopped." << std::endl;
            return false; // Indicate to stop acquisition.
        }
        m_nBuffersGrabbed++;
        if (grabResult.status != GrabResult::Ok) {
            std::cerr << "Image " << m_nBuffersGrabbed << " was not grabbed." << std::endl;
        }
        else {
            // Retrieve the values for the center pixel.
            const int width = (int)parts[0].width; const int height = (int)parts[0].height;
            const int u = (int)(0.5 * width); const int v = (int)(0.5 * height);
            CBlazeCamera::Coord3D* p3DCoordinate = (CBlazeCamera::Coord3D*) parts[0].pData + v * width + u;
            if (p3DCoordinate->z != 0)
                std::cout << "x=" << p3DCoordinate->x << " y=" << p3DCoordinate->y << " z=" << p3DCoordinate->z << "\n";
            else
                std::cout << "x=   n/a y=   n/a z=   n/a\n";
        }
        return m_nBuffersGrabbed < 100; // Indicate to stop acquisition when 10 buffers are grabbed.
    }
private:
    CBlazeCamera m_Camera;
    int          m_nBuffersGrabbed;
};




int main()
{
    // camera::hik_vision my_camera;
    // std::cout<<my_camera.initialize()<<'\n';
    // CBlazeCamera m_Camera;
    
    // cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    // while(true)
    // {   cv::Mat frame = my_camera.capture();
    //     cv::imshow("Display Image",frame);

    //     char c=(char)cv::waitKey(1);
    //     if(c==27)
    //     break;

    // }

    // my_camera.shutdown();



    // BASLER 3D Camera==================

    int exitCode = EXIT_SUCCESS;
    try {
        CBlazeCamera::InitProducer();
        exitCode = Sample().run();
    } catch (GenICam::GenericException& e) {
        std::cerr << "Exception occurred: " << std::endl << e.GetDescription() << std::endl;
        exitCode = EXIT_FAILURE;
    }
    if (CBlazeCamera::IsProducerInitialized())
        CBlazeCamera::TerminateProducer();  // Won't throw any exceptions
    return exitCode;

    // =====================================
    
    // cv::waitKey(0.1);

    return 0;



}

