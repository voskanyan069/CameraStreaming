#ifndef __CAMERA_CAMERA_HPP__
#define __CAMERA_CAMERA_HPP__

#include <iostream>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include "application/cmd_argument.hpp"

class Camera
{
public:
	Camera(const int& api_id = cv::CAP_ANY);
	bool open();
	~Camera();

private:
	bool show();
	bool wait_for_close();
	void save_frames();
	const std::string get_date();
	const ArgumentBase* find_argument(const std::string& name);

private:
	int m_device_id;
	const int& m_api_id;
	bool m_save_frames;
	std::string m_frames_path;
	CMDArguments& m_cmdargs;

	cv::Mat* m_frame;
	cv::VideoCapture* m_capture;
};

#endif // __CAMERA_CAMERA_HPP__
