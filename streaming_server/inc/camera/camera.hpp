#ifndef __CAMERA_CAMERA_HPP__
#define __CAMERA_CAMERA_HPP__

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include "camera/frame_loader.hpp"
#include "camera/frame_streaming.hpp"
#include "camera/frame_displaying.hpp"
#include "application/cmd_argument.hpp"

class Camera
{
public:
	Camera(const int api_id = cv::CAP_ANY);
	bool open();
	~Camera();

private:
	bool get_frame();
	bool wait_for_close();
	const ArgumentBase* find_argument(const std::string& name);

private:
	int m_api_id;
	int m_device_id;
	CMDArguments& m_cmdargs;
	FrameLoader* m_frame_loader;

	cv::Mat* m_frame;
	cv::VideoCapture* m_capture;
};

#endif // __CAMERA_CAMERA_HPP__
