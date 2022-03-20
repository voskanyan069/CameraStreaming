#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "camera/viewer.hpp"
#include "system/date.hpp"
#include "system/filesystem.hpp"

CameraViewer::CameraViewer()
	: m_cmdargs(CMDArguments::instance())
	, m_socket(socket(PF_INET, SOCK_STREAM, 0))
	, m_iptr(0)
	, m_frame_size(0)
	, m_frame(new cv::Mat(cv::Mat::zeros(480, 640, CV_8UC1)))
	, m_save(m_cmdargs.find("save_frames")->get<bool>())
	, m_host(m_cmdargs.find("host")->get<std::string>())
	, m_port(m_cmdargs.find("port")->get<int>())
	, m_frames_path(m_cmdargs.find("path")->get<std::string>())
{
	if (m_save)
	{
		sys::create_directory(m_frames_path, 1);
	}
}

bool CameraViewer::connect_to_socket()
{
	struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    if (m_socket < 0)
	{
        std::cout << " [@E] Socket initalization failed" << std::endl;
		return 1;
    }

    server_addr.sin_family = PF_INET;
    server_addr.sin_addr.s_addr = inet_addr(m_host.c_str());
    server_addr.sin_port = htons(m_port);

    if (connect(m_socket, (sockaddr*)&server_addr, addr_len) < 0)
	{
        std::cout << " [@E] Could not connect to socket" << std::endl;
		return 1;
    }
	return 0;
}

void CameraViewer::create_window()
{
	m_frame_size = m_frame->total() * m_frame->elemSize();
    m_iptr = m_frame->data;
	if ( !m_frame->isContinuous() )
	{
          *m_frame = m_frame->clone();
    }
	std::cout << " [@I] Frame size: " << m_frame_size << std::endl;
	cv::namedWindow("live client", 1);
}

void CameraViewer::save_frame(const cv::Mat& frame)
{
	if (m_save)
	{
		std::string date;
		sys::get_date(date);
		std::string filename = m_frames_path + "/";
		filename += date + ".jpg";
		cv::imwrite(filename, frame);
	}
}

bool CameraViewer::receive_frame()
{
	int key = 0;
    int bytes = 0;
	bytes = recv(m_socket, m_iptr, m_frame_size, MSG_WAITALL);
	if (-1 == bytes)
	{
		std::cout << " [@E] Failed to receive full frame = "
			      << bytes << std::endl;
		return 1;
	}
	cv::Mat gray_frame;
	cv::cvtColor(*m_frame, gray_frame, cv::COLOR_GRAY2BGR);
	cv::imshow("live client", gray_frame);
	save_frame(gray_frame);
	return 0;
}

bool CameraViewer::wait_for_close()
{
	return cv::waitKey(5) >= 0;
}

bool CameraViewer::show_frame()
{
	while (1)
	{
		if ( receive_frame() || wait_for_close() )
		{
			return 1;
		}
	}
}

bool CameraViewer::listen()
{
	bool rc = connect_to_socket();
	if ( !rc )
	{
		create_window();
		rc = show_frame();
	}
	return rc;
}


CameraViewer::~CameraViewer()
{
	close(m_socket);
	delete m_frame;
	delete m_iptr;
}
