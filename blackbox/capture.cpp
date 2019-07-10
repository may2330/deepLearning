#include <opencv2/opencv.hpp>
#include <iostream>

std::string get_tegra_pipeline(int width, int height, int fps) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + ", height=(int)" +
            std::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(fps) +
            "/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

using namespace cv;
using namespace std;


int main()
{
	// Options
	int  WIDTH = 1920;
	int  HEIGHT = 1080;
	int FPS = 30;

	
	// Define the gstream pipeline
	std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
	std::cout << "Using pipeline: \n\t" << pipeline << "\n";

	Mat img_color;

	//비디오 캡쳐 초기화
	VideoCapture cap(pipeline, CAP_GSTREAMER);
	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
		return -1;
	}

	// 동영상 파일을 저장하기 위한 준비  
	Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CAP_PROP_FRAME_HEIGHT));

	VideoWriter writer;
	double fps = 30.0;
	writer.open("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);
	if (!writer.isOpened())
	{
		cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
		return 1;
	}


	while(1)
	{
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "빈 영상이 캡쳐되었습니다.\n";
			break;
		}

		//동영상 파일에 한 프레임을 저장함.  
		writer.write(img_color);

		imshow("Color", img_color);

		if (waitKey(30) >= 0)
			break;


	}
	

	return 0;
}


