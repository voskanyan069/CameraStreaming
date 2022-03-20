#ifndef __CAMERA_FRAME_DISPLAYING_HPP__
#define __CAMERA_FRAME_DISPLAYING_HPP__

#include "camera/frame_loader.hpp"

class FrameDisplaying : public FrameLoader
{
public:
	FrameDisplaying(const bool save_frames, const std::string path);
	bool process(cv::Mat* frame) override;

private:
	bool show_frame();
};

#endif // __CAMERA_FRAME_DISPLAYING_HPP__
