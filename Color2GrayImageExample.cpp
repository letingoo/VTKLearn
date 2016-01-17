#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkBMPReader.h>
#include <vtkImageLuminance.h>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)


/*
*	将彩色图像变成灰度图
*/


int main()
{
	char *fileName = "F:\\lena.bmp";

	vtkSmartPointer<vtkBMPReader> reader =
		vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName(fileName);

	vtkSmartPointer<vtkImageLuminance> luminanceFilter =
		vtkSmartPointer<vtkImageLuminance>::New();
	luminanceFilter->SetInputConnection( reader->GetOutputPort() ); // 不太清楚这里是否正确
	luminanceFilter->Update();

	vtkSmartPointer<vtkImageActor> originalActor =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor->SetInputData( reader->GetOutput() );

	vtkSmartPointer<vtkImageActor> shiftscaleActor =
		vtkSmartPointer<vtkImageActor>::New();
	shiftscaleActor->SetInputData( luminanceFilter->GetOutput() );

	double originalViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
	double shiftscaleViewport[4] = { 0.5, 0.0, 1.0, 1.0 };


	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport( originalViewport );
	originalRenderer->AddActor(originalActor);
	originalRenderer->ResetCamera();
	originalRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> shiftscaleRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	shiftscaleRenderer->SetViewport(shiftscaleViewport);
	shiftscaleRenderer->AddActor(shiftscaleActor);
	shiftscaleRenderer->ResetCamera();
	shiftscaleRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(shiftscaleRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("Color2GrayImageExample");

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> style =
		vtkSmartPointer<vtkInteractorStyleImage>::New();

	renderWindowInteractor->SetInteractorStyle(style);
	renderWindowInteractor->SetRenderWindow(renderWindow);
	renderWindowInteractor->Initialize();

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;

}