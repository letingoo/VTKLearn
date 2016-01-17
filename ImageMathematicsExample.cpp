#include <vtkMath.h>
#include <vtkSmartPointer.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageMathematics.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)

/**
* 对vtkImageMathematics的使用例子
*/

int main()
{

	vtkSmartPointer<vtkImageCanvasSource2D> imageSource =
		vtkSmartPointer<vtkImageCanvasSource2D>::New();
	imageSource->SetNumberOfScalarComponents(3);
	imageSource->SetScalarTypeToUnsignedChar();
	imageSource->SetExtent(0, 4, 0, 4, 0, 4);
	imageSource->SetDrawColor(100.0, 0, 0);
	imageSource->FillBox(0, 4, 0, 4);
	imageSource->Update();

	vtkSmartPointer<vtkImageMathematics> imageMath =
		vtkSmartPointer<vtkImageMathematics>::New();
	imageMath->SetOperationToMultiplyByK();
	imageMath->SetConstantK(5);
	imageMath->SetInputConnection(imageSource->GetOutputPort());
	imageMath->Update();

	vtkSmartPointer<vtkImageActor> originalActor =
		vtkSmartPointer<vtkImageActor>::New();
	originalActor->SetInputData(
		imageSource->GetOutput());

	vtkSmartPointer<vtkImageActor> mathActor =
		vtkSmartPointer<vtkImageActor>::New();
	mathActor->SetInputData(imageMath->GetOutput());

	double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
	double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };

	vtkSmartPointer<vtkRenderer> originalRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	originalRenderer->SetViewport(leftViewport);
	originalRenderer->AddActor(originalActor);
	originalRenderer->ResetCamera();
	originalRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderer> gradientMagnitudeRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	gradientMagnitudeRenderer->SetViewport(rightViewport);
	gradientMagnitudeRenderer->AddActor(mathActor);
	gradientMagnitudeRenderer->ResetCamera();
	gradientMagnitudeRenderer->SetBackground(1.0, 1.0, 1.0);

	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(originalRenderer);
	renderWindow->AddRenderer(gradientMagnitudeRenderer);
	renderWindow->SetSize(640, 480);
	renderWindow->Render();
	renderWindow->SetWindowName("ImageMathematicsExample");

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