/*
*	����ͼ��Ļ�����Ϣ
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

	// �ȶ�ȡͼƬ
	vtkSmartPointer<vtkBMPReader> bmpReader =
		vtkSmartPointer<vtkBMPReader>::New();
	bmpReader->SetFileName(fileName);
	bmpReader->Update();


	// ��ʼ��ȡ��Ϣ

	// ά��
	int dim[3];
	bmpReader->GetOutput()->GetDimensions(dim);
	cout << "ͼ��ά��: " << dim[0] << "  " << dim[1] << "  " << dim[2] << endl;

	// ԭ��
	double origin[3];
	bmpReader->GetOutput()->GetOrigin(origin);
	cout << "ͼ��ԭ��: " << origin[0] << "  " << origin[1] << "  " << origin[2] << endl;



	/**
	* ��ʼ��ʾͼƬ
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