#include <iostream>
#include <exception>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
//#include <sys/ioctl.h>
//#include <net/if.h>
#include <unistd.h>

#include <opencv2/opencv.hpp>

#include "camera/frame_streaming.hpp"

FrameStreaming::FrameStreaming(const int port,
		const bool save_frames, const std::string path)
	: FrameLoader(save_frames, path)
	, m_port(port)
	, m_bytes(0)
	, m_socket(0)
	, m_local_socket(0)
    , m_remote_socket(0)
    , m_addr_len(0)
    , m_gray_frame(0)
	, m_frame_size(m_frame->total() * m_frame->elemSize())
{
	initialize_socket();
	if (listen_socket())
	{
		throw std::runtime_error("error to listen socket");
	}
}

void FrameStreaming::initialize_socket()
{
	m_local_socket = socket(AF_INET , SOCK_STREAM , 0);
	if (-1 == m_local_socket)
	{
		throw std::runtime_error("socket failed");
    }
	m_local_addr.sin_family = AF_INET;
    m_local_addr.sin_addr.s_addr = INADDR_ANY;
    m_local_addr.sin_port = htons(m_port);

	if (bind(m_local_socket, (struct sockaddr*)&m_local_addr,
				sizeof(m_local_addr)) < 0)
	{
		throw std::runtime_error("can\'t bind socket");
    }

	listen(m_local_socket, 3);
	std::cout << " [@I] Waiting for connections on "
			  << m_port << " port" << std::endl;
}

bool FrameStreaming::listen_socket()
{
	m_remote_socket = accept(m_local_socket, (struct sockaddr*)&m_remote_addr,
			(socklen_t*)&m_addr_len);
	if (m_remote_socket < 0)
	{
		std::cout << " [@E] Accept failed" << std::endl;
		return true;
	}
	m_socket = m_remote_socket;
	std::cout << " [@I] Connection accepted" << std::endl;
	std::cout << " [@I] Frame size: " << m_frame_size << std::endl;
	return false;
}

void FrameStreaming::prepare_frame()
{
	m_gray_frame = m_frame;
	cv::cvtColor(*m_frame, *m_gray_frame, cv::COLOR_BGR2GRAY);
	flip(*m_gray_frame, *m_gray_frame, 1);
}

bool FrameStreaming::send_frame()
{
	if ((m_bytes = send(m_socket, m_gray_frame->data, m_frame_size, 0)) < 0)
	{
		std::cout << " [@E] bytes = " << m_bytes << std::endl;
		return true;
	}
	return false;
}

bool FrameStreaming::process(cv::Mat* frame)
{
	m_frame = frame;
	save_frames();
	prepare_frame();
	bool err = send_frame();
	return err;
}
