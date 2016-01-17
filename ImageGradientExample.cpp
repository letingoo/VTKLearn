#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkJPEGReader.h>
#include <vtkImageGradient.h>
#include <vtkImageMagnitude.h>
#include <vtkImageCast.h>
#include <vtkImageShiftScale.h>
#include <vtkAutoInit.h>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)


int main()
{

	char *fileName = "F:\\lena-gray.jpg";

	vtkSmartPointer<vtkJPEGReader> reader =
		vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName( fileName );
	reader->Update();

	vtkSmartPointer<vtkImageGradient> gradientFilter =
		vtkSmartPointer<vtkImageGradient>::New();
	gradientFilter->SetInputConnection( reader->GetOutputPort() );
	gradientFilter->SetDimensionality(2);

	vtkSmartPointer<vtkImageMagnitude> magnitudeFilter =
		vtkSmartPointer<vtkImageMagnitude>::New();
	magnitudeFilter->SetInputConnection( gradientFilter->GetOutputPort() );
	magnitudeFilter->Update();

	double range[2];
	magnitudeFilter->GetOutput()->GetScalarRange(range);

	vtkSmartPointer<vtkImageShiftScale> shiftScale =
		vtkSmartPointer<vtkImageShiftScale>::New();
	shiftScale->SetOutputScalarTypeToUnsignedChar();
	shiftScale->SetScale(100 / range[1]);
	shiftScale->SetInputConnection( magnitudeFilter->GetOutputPort() );
	shiftScale->Update();


	vtkSmartPointer<vtkImageActor> originalActor =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor->SetInputData(reader->GetOutput());

	vtkSmartPointer<vtkImageActor> gradActor =
		vtkSmartPointer<vtkImageActor>::New();
	gradActor->SetInputData(shiftScale->GetOutput());

	double originalViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
	double gradviewport[4] = { 0.5, 0.0, 1.0, 1.0 };

	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport(originalViewport);
	originalRenderer->AddActor(originalActor);
	originalRenderer->ResetCamera();
	originalRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> gradRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	gradRenderer->SetViewport(gradviewport);
	gradRenderer->AddActor(gradActor);
	gradRenderer->ResetCamera();
	gradRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(gradRenderer);
	renderWindow->SetSize(640, 320);
	renderWindow->Render();
	renderWindow->SetWindowName("ImageGradientExample");

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