/*
* �����޸�ͼ���һЩ��Ϣ����ԭ�㣬���ؼ���ͷ�Χ
*/

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkBMPReader.h>
#include <vtkImageChangeInformation.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
#include <iostream>

using namespace std;
VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)

int main()
{
	char* fileName = "F:\\lena.bmp";

	vtkSmartPointer<vtkBMPReader> reader =
		vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName(fileName);
	reader->Update();


	int dim[3];
	double origin[3];
	double spacing[3];

	// ��ʼ��ȡһЩ��Ϣ
	reader->GetOutput()->GetDimensions(dim);
	cout << "ԭͼ��ά�ȣ� " << dim[0] << "  " << dim[1] << "  " << dim[2] << endl;

	reader->GetOutput()->GetOrigin(origin);
	cout << "ԭͼ��ԭ�㣺 " << origin[0] << "  " << origin[1] << "  " << origin[2] << endl;

	reader->GetOutput()->GetSpacing(spacing);
	cout << "ԭ���ؼ���� " << spacing[0] << "  " << spacing[1] << "  " << spacing[2] << endl;



	// ��ʼ�ı�һЩͼ�����Ϣ
	vtkSmartPointer<vtkImageChangeInformation> changer =
		vtkSmartPointer<vtkImageChangeInformation>::New();
	changer->SetInputData(reader->GetOutput());
	changer->SetOutputOrigin(100, 100, 0);
	changer->SetOutputSpacing(500, 500, 1);

	changer->SetCenterImage(1);
	changer->Update();

	changer->GetOutput()->GetDimensions(dim);
	std::cout << "�޸ĺ�ͼ��ά��:" << dim[0] << " " << dim[1] << " " << dim[2] << std::endl;
	changer->GetOutput()->GetOrigin(origin);
	std::cout << "�޸ĺ�ͼ��ԭ��:" << origin[0] << " " << origin[1] << " " << origin[2] << std::endl;
	changer->GetOutput()->GetSpacing(spacing);
	std::cout << "�޸ĺ����ؼ��:" << spacing[0] << " " << spacing[1] << " " << spacing[2] << std::endl;



	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection( changer->GetOutputPort() );
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;


}