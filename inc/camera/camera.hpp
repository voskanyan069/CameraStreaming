#ifndef __CAMERA_CAMERA_HPP__
#define __CAMERA_CAMERA_HPP__

#include <iostream>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

class Camera
{
public:
	Camera(const int& camera_id = 0, const int& api_id = cv::CAP_ANY);
	bool open();
	~Camera();

private:
	bool show();
	bool wait_for_close();

private:
	const int& m_device_id;
	const int& m_api_id;

	cv::Mat* m_frame;
	cv::VideoCapture* m_capture;
};

#endif // __CAMERA_CAMERA_HPP__
