#include "application/application.hpp"

int main(int argc, char* argv[])
{
	Application app(argc, argv);
	app.start();
	return 0;
}


//int main()
//{
//	cv::Mat frame;
//    cv::VideoCapture cap;
//    int deviceID = 0;
//    int apiID = cv::CAP_ANY;
//    cap.open(deviceID, apiID);
//    if (!cap.isOpened())
//	{
//		std::cerr << "ERROR! Unable to open camera\n";
//        return -1;
//    }
//	std::cout << "Start grabbing" << std::endl;
//	std::cout << "Press any key to terminate" << std::endl;
//    while (1)
//    {
//        cap.read(frame);
//        if (frame.empty())
//		{
//			std::cerr << "ERROR! blank frame grabbed\n";
//            break;
//        }
//		cv::imshow("Live", frame);
//        if (cv::waitKey(5) >= 0)
//		{
//            break;
//		}
//    }
//    return 0;
//}
