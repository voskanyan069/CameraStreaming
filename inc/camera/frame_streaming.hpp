#ifndef __CAMERA_FRAME_STREAMING_HPP__
#define __CAMERA_FRAME_STREAMING_HPP__

#include <string>
#include <arpa/inet.h>

#include <opencv2/videoio.hpp>

#include "camera/frame_loader.hpp"

class FrameStreaming : public FrameLoader
{
public:
	FrameStreaming(const int port,
			const bool save_frames,
			const std::string path);
	bool process(cv::Mat* frame) override;

private:
	void initialize_socket();
	void prepare_frame();
	bool listen_socket();
	bool send_frame();

private:
	const int m_port;
	const int m_frame_size;
	int m_bytes;
	int m_socket;
	int m_local_socket;
	int m_remote_socket;
	int m_addr_len;
	struct sockaddr_in m_local_addr;
	struct sockaddr_in m_remote_addr;
	cv::Mat* m_gray_frame;
};

#endif // __CAMERA_FRAME_STREAMING_HPP__
