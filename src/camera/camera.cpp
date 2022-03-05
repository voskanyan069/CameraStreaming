#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <exception>

#include "camera/camera.hpp"
#include "system/system.hpp"

Camera::Camera(const int& api_id)
	: m_cmdargs(CMDArguments::instance())
	, m_api_id(api_id)
{
	m_device_id = find_argument("device_id")->get<int>();
	m_save_frames = find_argument("save_frames")->get<bool>();
	m_frames_path = find_argument("path")->get<std::string>();

	if (m_save_frames)
	{
		sys::create_directory(m_frames_path, 1);
	}
}

const ArgumentBase* Camera::find_argument(const std::string& name)
{
	const auto& it = m_cmdargs.arguments.find(name);
	if (it == m_cmdargs.arguments.end())
	{
		throw std::runtime_error(name + " not found");
	}
	return it->second;
}

const std::string Camera::get_date()
{
	using namespace std::chrono;
	auto now = system_clock::now();
	auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
	auto timer = system_clock::to_time_t(now);
	std::tm bt = *std::localtime(&timer);
	std::ostringstream oss;
	oss << std::put_time(&bt, "%Y-%m-%d_%H-%M-%S");
	oss << '.' << std::setfill('0') << std::setw(3) << ms.count();
	return oss.str();
}

void Camera::save_frames()
{
	if (m_save_frames)
	{
		std::string filename = m_frames_path + "/";
		filename += get_date() + ".jpg";
		cv::imwrite(filename, *m_frame);
	}
}

bool Camera::show()
{
	m_capture->read(*m_frame);
	if (m_frame->empty())
	{
		std::cout << "[ERROR] blank frame grabbed" << std::endl;
		return true;
	}
	save_frames();
	cv::imshow("Live", *m_frame);
	return false;
}

bool Camera::wait_for_close()
{
	return cv::waitKey(5) >= 0;
}

bool Camera::open()
{
	std::cout << "Tring to open: [" << m_device_id << "] device" << std::endl;
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
