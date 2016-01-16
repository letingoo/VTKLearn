#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkBMPReader.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
#include <iostream>


VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);


/**
*	对图像的像素值进行访问和修改的例子
*/

int main()
{

	char *fileName = "F:\\lena.bmp";

	vtkSmartPointer<vtkBMPReader> reader =
		vtkSmartPointer<vtkBMPReader>::New();

	reader->SetFileName(fileName);
	reader->Update();

	int dims[3];
	reader->GetOutput()->GetDimensions(dims);

	int nbOfcomp;
	nbOfcomp = reader->GetOutput()->GetNumberOfScalarComponents();


	/**
	* 开始修改，把图像左下方100*100像素的区域变成黑色
	*/
	for (int k = 0; k < dims[2]; k++) 
	{
		for (int j = 0; j < dims[1]; j++)
		{
			for (int i = 0; i < dims[0]; i++)
			{
				if (i < 100 && j < 100)
				{
					unsigned char *pixel = (unsigned char *)(reader->GetOutput()->GetScalarPointer(i, j, k));
					
					// 彩色图像比较特殊，pexel直接指向的是R值，往后依次是G，B
					
					*pixel = 0;
					*(pixel + 1) = 0;
					*(pixel + 2) = 0;

				}

			}
		}
	}



	// 显示图片,但是没有进行保存
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
	imageViewer->GetRenderWindow()->SetWindowName("VisitImagePixelDirectlyExample");


	renderWindowInteractor->Start();

	

	return EXIT_SUCCESS;

}