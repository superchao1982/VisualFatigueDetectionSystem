/**************************************************************
* Type: .h file
* Class Name: CFaceTracking
* Function: track faces via the Kinect
* Create date: 2014.10.16
* Creator�� Zhaoqiang Xia (xiazhaoqiang@gmail.com)
***************************************************************/
#pragma once
// include files for opencv
#include <opencv2/opencv.hpp> 

// include files for kinect
#include <NuiApi.h>
#include <FaceTrackLib.h>

using namespace cv;

#define COLOR_WIDTH		640
#define COLOR_HEIGHT		480
#define DEPTH_WIDTH		320
#define DEPTH_HEIGHT		240
#define SKELETON_WIDTH	640
#define SKELETON_HEIGHT	480
#define CHANNEL			3

class CFaceTracking
{
public:
	CFaceTracking();
	~CFaceTracking(){}
	/***** ��Ա�������� *****/
	// �ӿں���
	int KinectFTInitialize();
	void Track(Mat& resMat);
	void KinectFTRelease();
	int GetFacialExpression(Mat* pColorDisplay=NULL);

	void DisplayColorCamera();
	void KinectRecData();
	void GetColorData();
	void GetDepthData();
	void GetSkeletonData();
	// �ڲ���Ա����
	HRESULT VisualizeFaceModel(IFTImage* pColorImg, IFTModel* pModel, FT_CAMERA_CONFIG const* pCameraConfig, FLOAT const* pSUCoef, 
	FLOAT zoomFactor, POINT viewOffset, IFTResult* pAAMRlt, UINT32 color);
	HRESULT VisualizeFaceComponents(IFTImage* pColorImg, IFTModel* pModel, FT_CAMERA_CONFIG const* pCameraConfig, FLOAT const* pSUCoef, 
	FLOAT zoomFactor, POINT viewOffset, IFTResult* pAAMRlt, UINT32 color);

	/***** ��Ա�������� *****/
private:
	FT_VECTOR3D m_hint3D[2];		// ͷ�ͼ�����ĵ�����
	IFTFaceTracker* m_pFT;				// Kinect SDK�ṩ���������ٽӿ�
	IFTResult* m_pFTResult;			// ��¼�������ٽ��
	FT_SENSOR_DATA m_sensorData;		// ���������ݽṹ
	FT_CAMERA_CONFIG cameraConfig; // ��ɫ����ͷ���ñ���
	FT_CAMERA_CONFIG depthConfig;	// �������ͷ���ñ���
	BYTE DepthBuf[DEPTH_WIDTH*DEPTH_HEIGHT*CHANNEL];
	// ��ɫ�����ͼ�����ݻ�����
	IFTImage* pColorFrame;
	IFTImage* pDepthFrame;
	IFTImage* pColorDisplay; 
	// �����ں��¼��;��
	HANDLE	m_hNextVideoFrameEvent;
	HANDLE	m_hNextDepthFrameEvent;
	HANDLE	m_hNextSkeletonEvent;
	HANDLE	m_pVideoStreamHandle;
	HANDLE	m_pDepthStreamHandle;
	HANDLE	m_hEvNuiProcessStop; // ���ڽ������¼�����
	HANDLE m_hProcesss;
	// status variable
	bool	isTracked;
	
};