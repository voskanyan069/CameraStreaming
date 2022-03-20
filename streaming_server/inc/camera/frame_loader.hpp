#ifndef __CAMERA_FRAME_LOADER_HPP__
#define __CAMERA_FRAME_LOADER_HPP__

#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

class FrameLoader
{
public:
	FrameLoader(const bool save_frames, const std::string path);
	void save_frames();
	virtual bool process(cv::Mat* frame) = 0;
	virtual ~FrameLoader();

protected:
	cv::Mat* m_frame;

private:
	const bool m_save_frames;
	const std::string m_path;
};

#endif // __CAMERA_FRAME_LOADER_HPP__
