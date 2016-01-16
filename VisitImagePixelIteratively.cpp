#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkImageIterator.h>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL)
VTK_MODULE_INIT(vtkInteractionStyle)



/**
对图片的像素进行访问和修改，使用迭代器方式
*/

int main()
{
	char *fileName = "F:\\lena.bmp";

	vtkSmartPointer<vtkBMPReader> reader =
		vtkSmartPointer<vtkBMPReader>::New();
	reader->SetFileName( fileName );
	reader->Update();

	int subRegion[6] = {0, 100, 0, 100, 0, 0};
	vtkImageIterator<unsigned char> it( reader->GetOutput(), subRegion );

	while ( !it.IsAtEnd() )
	{
		unsigned char *inSI = it.BeginSpan();
		unsigned char *inSIEnd = it.EndSpan();

		while ( inSI != inSIEnd )
		{
			*inSI = 255 - *inSI;
			inSI++;
		}

		it.NextSpan();
	}


	vtkSmartPointer<vtkImageViewer2> imageViewer =
		vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer->SetInputConnection(reader->GetOutputPort());

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageViewer->SetupInteractor(renderWindowInteractor);
	imageViewer->Render();
	imageViewer->GetRenderer()->ResetCamera();
	imageViewer->Render();

	imageViewer->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
	imageViewer->SetSize(640, 480);
	imageViewer->GetRenderWindow()->SetWindowName("VisitImagePixelIterativelyExample");

	renderWindowInteractor->Start();

	return EXIT_SUCCESS;


}
