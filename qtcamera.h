#ifndef QTCAMERA_H
#define QTCAMERA_H

#include <QtGui>
#include "ui_qtcamera.h"

#include <opencv2/opencv.hpp>
using namespace cv;

class Camera;
class CaptureThread;
class QGLCanvas;

//#define USING_OPENGL

class QtCamera : public QMainWindow
{
	Q_OBJECT

public:
	QtCamera(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QtCamera();

	void setGrabFrame(Mat *frame);
	
public slots:
	void startVideo();
	void stopVideo();
	void toggleScaling();
	void newImage(Mat *grab);
		
protected:
	void timerEvent(QTimerEvent *event);

private:
	void showImage(Mat *frame);
	bool createCamera();
	void clearQueue();

	Ui::QtCameraClass ui;
	CaptureThread *m_captureThread;
	Camera *m_camera;
	QMutex m_frameQMutex;
	QQueue <Mat *> m_frameQ;
	int m_frameRateTimer;
	int m_frameRefreshTimer;
	QLabel *m_pStatus;
	int m_frameCount;
	bool m_scaling;

#ifdef USING_OPENGL
	QGLCanvas *m_cameraView;
#else
	QLabel *m_cameraView;
#endif
};

#endif // QTCAMERA_H
