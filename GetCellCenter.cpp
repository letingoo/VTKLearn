#include <vtkSmartPointer.h>
#include <vtkCell.h>
#include <vtkImageData.h>
#include <vtkAutoInit.h>
#include <iostream>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle)

static void GetCellCenter(vtkImageData* imageData, const unsigned int cellId,
						double center[3]);

int main(int, char *[])
{
	// Create an image data
	vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();

	// Specify the size of the image data
	imageData->SetDimensions(3, 3, 2); // This will cause 18 points and 4 cells
	imageData->SetSpacing(1.0, 1.0, 1.0);
	imageData->SetOrigin(0.0, 0.0, 0.0);

	std::cout << "Number of points: " << imageData->GetNumberOfPoints() << std::endl;
	std::cout << "Number of cells: " << imageData->GetNumberOfCells() << std::endl;

	double center[3] = { 0, 0, 0 };
	for (vtkIdType cellId = 0; cellId < imageData->GetNumberOfCells(); ++cellId)
	{
		GetCellCenter(imageData, cellId, center);

		std::cout << "Cell " << cellId << " center: " << center[0] << " "
			<< center[1] << " " << center[2] << std::endl;
	}

	std::getchar();
	return EXIT_SUCCESS;
}

void GetCellCenter(vtkImageData* imageData, const unsigned int cellId, double center[3])
{
	double pcoords[3] = { 0, 0, 0 };
	double *weights = new double[imageData->GetMaxCellSize()];
	vtkCell* cell = imageData->GetCell(cellId);
	int subId = cell->GetParametricCenter(pcoords);
	cell->EvaluateLocation(subId, pcoords, center, weights);
}

