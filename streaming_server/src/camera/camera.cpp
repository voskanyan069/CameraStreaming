#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <exception>

#include "camera/camera.hpp"
#include "system/filesystem.hpp"

Camera::Camera(const int api_id)
	: m_cmdargs(CMDArguments::instance())
	, m_api_id(api_id)
{
	m_device_id = m_cmdargs.find("device_id")->get<int>();
	const bool save_frames = m_cmdargs.find("save_frames")->get<bool>();
	const bool streaming_mode = m_cmdargs.find("streaming_mode")->get<bool>();
	const int port = m_cmdargs.find("port")->get<int>();
	const std::string frames_path = m_cmdargs.find("path")->get<std::string>();

	if (save_frames)
	{
		sys::create_directory(frames_path, 1);
	}
	if (streaming_mode)
	{
		m_frame_loader = new FrameStreaming(port, save_frames, frames_path);
	}
	else
	{
		m_frame_loader = new FrameDisplaying(save_frames, frames_path);
	}
}

bool Camera::get_frame()
{
	m_capture->read(*m_frame);
	return m_frame_loader->process(m_frame);
}

bool Camera::wait_for_close()
{
	return cv::waitKey(5) >= 0;
}

bool Camera::open()
{
	std::cout << " [@I] Trying to open: [" << m_device_id
			  << "] device" << std::endl;
	m_frame = new cv::Mat();
    m_capture = new cv::VideoCapture();
	m_capture->set(cv::CAP_PROP_FORMAT, CV_8UC1);
    m_capture->open(m_device_id, m_api_id);
	if ( !m_capture->isOpened() )
	{
		return false;
	}
	while (1)
	{
		if (get_frame() || wait_for_close())
		{
			break;
		}
	}
	return m_capture->isOpened();
}

Camera::~Camera()
{
	delete m_frame;
	delete m_capture;
	delete m_frame_loader;
}
