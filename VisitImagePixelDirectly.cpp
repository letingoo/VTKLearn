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
*	��ͼ�������ֵ���з��ʺ��޸ĵ�����
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
	* ��ʼ�޸ģ���ͼ�����·�100*100���ص������ɺ�ɫ
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
					
					// ��ɫͼ��Ƚ����⣬pexelֱ��ָ�����Rֵ������������G��B
					
					*pixel = 0;
					*(pixel + 1) = 0;
					*(pixel + 2) = 0;

				}

			}
		}
	}



	// ��ʾͼƬ,����û�н��б���
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