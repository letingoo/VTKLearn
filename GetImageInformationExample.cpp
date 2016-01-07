/*
*	访问图像的基本信息
*/


#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
#include <iostream>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle)


using namespace std;

int main()
{

	const char* fileName = "F:\\lena.bmp";

	// 先读取图片
	vtkSmartPointer<vtkBMPReader> bmpReader =
		vtkSmartPointer<vtkBMPReader>::New();
	bmpReader->SetFileName(fileName);
	bmpReader->Update();


	// 开始读取信息

	// 维度
	int dim[3];
	bmpReader->GetOutput()->GetDimensions(dim);
	cout << "图像维度: " << dim[0] << "  " << dim[1] << "  " << dim[2] << endl;

	// 原点
	double origin[3];
	bmpReader->GetOutput()->GetOrigin(origin);
	cout << "图像原点: " << origin[0] << "  " << origin[1] << "  " << origin[2] << endl;



	/**
	* 开始显示图片
	*/
	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection( bmpReader->GetOutputPort() );

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	//imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(1000, 1000);

	renderWindowInteractor->Start();
		
	getchar();

}