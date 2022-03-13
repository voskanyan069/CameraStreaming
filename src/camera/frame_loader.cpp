#include <ctime>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <opencv2/videoio.hpp>

#include "camera/frame_loader.hpp"

FrameLoader::FrameLoader(const bool save_frames, const std::string path)
	: m_save_frames(save_frames)
	, m_path(path)
	, m_frame(new cv::Mat(cv::Mat::zeros(480, 640, CV_8UC1)))
{
}

const std::string FrameLoader::get_date()
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

void FrameLoader::save_frames()
{
	if (m_save_frames)
	{
		std::string filename = m_path + "/";
		filename += get_date() + ".jpg";
		cv::imwrite(filename, *m_frame);
	}
}

FrameLoader::~FrameLoader()
{
}
