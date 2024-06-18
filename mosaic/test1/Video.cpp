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
		cerr << "[!] ī�޶� ���� ���߾� :F" << endl;
		
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
			// (�Է��̹���, ����ȿ���, �̹��������������, ������ �̿���, �÷���, ���⿵���ּ�ũ��, ���⿵�� �ִ�ũ��)

			Mat origin_cam;
			Mat mosaic_cam;
			frame.copyTo(origin_cam);

			for (auto i = 0; i < faceRect.size(); i++)
			{
				// �»�� ���ϴ� ����Ʈ
				Point a(faceRect[i].x + faceRect[i].width, faceRect[i].y + faceRect[i].height);
				Point b(faceRect[i].x, faceRect[i].y);
				// ����� ���� Ȯ��
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
