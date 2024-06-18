#include "main.h"

VideoCapture vcap(0);

CascadeClassifier cface;

Mat img;
Mat frame;
Mat gray;
Mat origin_cam;
Mat mosaic_cam;
Mat iTemp;

vector<Rect> faceRect;

void VideoMosaic()
{
	cface.load("haarcascade_frontalface_default.xml");

	if (!vcap.isOpened())
	{
		cerr << "[!] 카메라를 열지 못했어 :F" << endl;
		
	}

	while (true)
	{
		prog.Frame_Active = 1;
		vcap >> frame;
		try {
			vcap >> frame;
		}
		catch (Exception& e) {
			prog.Frame_Active = 0;
		}

		if (prog.Frame_Active == 1)
		{
			Mat gray;
			cvtColor(frame, gray, COLOR_BGR2GRAY);
			equalizeHist(gray, gray);
			vector<Rect> faceRect;
			cface.detectMultiScale(gray, faceRect, 1.1, 3, CASCADE_FIND_BIGGEST_OBJECT | CASCADE_SCALE_IMAGE, Size(30, 30));
			// (입력이미지, 추출된영역, 이미지배율축소정도, 도형의 이웃수, 플래그, 추출영역최소크기, 추출영역 최대크기)

			Mat origin_cam;
			Mat mosaic_cam;
			frame.copyTo(origin_cam);

			for (auto i = 0; i < faceRect.size(); i++)
			{
				// 좌상단 우하단 포인트
				Point a(faceRect[i].x + faceRect[i].width, faceRect[i].y + faceRect[i].height);
				Point b(faceRect[i].x, faceRect[i].y);
				// 축소후 강제 확대
				mosaic_cam = frame(Rect(a, b));
				Mat iTemp;
				resize(mosaic_cam, iTemp, Size(mosaic_cam.rows / 16, mosaic_cam.cols / 16));
				resize(iTemp, mosaic_cam, Size(mosaic_cam.rows, mosaic_cam.cols));
				rectangle(frame, a, b, Scalar(50, 0, 200), 3);
				rectangle(origin_cam, Rect(faceRect[i]), Scalar(50, 0, 200), 3);
			}

			//imshow("origin", origin_cam);
			imshow("mosaic", frame);
			if (waitKey(25) == 27) break;
		}

	}
}


void Mosaic_Video()
{
	VideoMosaic();
}
