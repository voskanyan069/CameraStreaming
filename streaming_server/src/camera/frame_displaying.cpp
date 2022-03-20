#include <iostream>

#include "camera/frame_displaying.hpp"

FrameDisplaying::FrameDisplaying(const bool save_frames,
		const std::string path)
	: FrameLoader(save_frames, path)
{
}

bool FrameDisplaying::show_frame()
{
	if (m_frame->empty())
	{
		std::cout << " [@E] blank frame grabbed" << std::endl;
		return true;
	}
	cv::imshow("live", *m_frame);
	return false;
}

bool FrameDisplaying::process(cv::Mat* frame)
{
	m_frame = frame;
	save_frames();
	bool err = show_frame();
	return err;
}
