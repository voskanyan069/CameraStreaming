#include <string>

#include <opencv2/videoio.hpp>

#include "camera/frame_loader.hpp"
#include "system/date.hpp"

FrameLoader::FrameLoader(const bool save_frames, const std::string path)
	: m_save_frames(save_frames)
	, m_path(path)
	, m_frame(new cv::Mat(cv::Mat::zeros(480, 640, CV_8UC1)))
{
}

void FrameLoader::save_frames()
{
	if (m_save_frames)
	{
		std::string date;
		sys::get_date(date);
		std::string filename = m_path + "/";
		filename += date + ".jpg";
		cv::imwrite(filename, *m_frame);
	}
}

FrameLoader::~FrameLoader()
{
}
