#ifndef __CAMERA_VIEWER_HPP__
#define __CAMERA_VIEWER_HPP__

#include <string>

#include <opencv2/opencv.hpp>

#include "application/cmd_argument.hpp"

class CameraViewer
{
public:
	CameraViewer();
	bool listen();
	~CameraViewer();

private:
	void create_window();
	bool connect_to_socket();
	bool show_frame();
	bool receive_frame();
	bool wait_for_close();
	void save_frame(const cv::Mat& frame);

private:
	CMDArguments& m_cmdargs;
	uchar* m_iptr;
	cv::Mat* m_frame;
	int m_frame_size;
	const int m_socket;
	const bool m_save;
	const std::string m_frames_path;
	const std::string m_host;
	const int m_port;
};

#endif // __CAMERA_VIEWER_HPP__
