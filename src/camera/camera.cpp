#include "camera/camera.hpp"

Camera::Camera(const int& camera_id, const int& api_id)
	: m_device_id(camera_id)
	, m_api_id(api_id)
{
}

bool Camera::show()
{
	m_capture->read(*m_frame);
	if (m_frame->empty())
	{
		std::cout << "ERROR! blank frame grabbed" << std::endl;
		return true;
	}
	cv::imshow("Live", *m_frame);
	return false;
}

bool Camera::wait_for_close()
{
	return cv::waitKey(5) >= 0;
}

bool Camera::open()
{
	m_frame = new cv::Mat();
    m_capture = new cv::VideoCapture();
    m_capture->open(m_device_id, m_api_id);
	while (1)
	{
		if (show() || wait_for_close())
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
}
