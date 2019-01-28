#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkDataSetReader.h>
#include <vtkInteractorStyleUser.h>
#include <vtkProperty.h>
#include <vtkCommand.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContourFilter.h>
#include <vtkPlane.h>
#include<vtkDataSetMapper.h>
#include <vtkOutlineFilter.h>
#include <vtkClipPolyData.h>

class vtkSliderCallback : public vtkCommand
{
public:
	static vtkSliderCallback *New()
	{
		return new vtkSliderCallback;
	}
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkSliderWidget *sliderWidget =
			reinterpret_cast<vtkSliderWidget*>(caller);
		double value = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();
		this->ContourFilter->SetValue(0,value);

	}
	vtkSliderCallback() :ContourFilter(NULL) {}
	vtkContourFilter* ContourFilter;
};
class vtkSliderCallback1 : public vtkCommand
{
public:
	static vtkSliderCallback1 *New()
	{
		return new vtkSliderCallback1;
	}
	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkSliderWidget *sliderWidget =
			reinterpret_cast<vtkSliderWidget*>(caller);
		double value = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();
		//this->plane->SetNormal(1,-1.0,0);
		this->plane->SetOrigin(0, value, 0);

	}
	vtkSliderCallback1() :plane(NULL) {}
	vtkPlane* plane;
};
//star

int main(int argc, char* argv[])
{
	//Verify input arguments
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0]
			<< " Filename(.vtk)" << std::endl;
		return EXIT_FAILURE;
	}
	// Load data
	vtkSmartPointer<vtkDataSetReader> reader =
		vtkSmartPointer<vtkDataSetReader>::New();
	reader->SetFileName(argv[1]);
	//second 
	vtkSmartPointer<vtkContourFilter> contourFilter1 =
		vtkSmartPointer<vtkContourFilter>::New();
	contourFilter1->SetInputConnection(reader->GetOutputPort());
	contourFilter1->SetNumberOfContours(1);
	contourFilter1->SetValue(0, 220);
	vtkSmartPointer<vtkPolyDataMapper> contourMapper1 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper1->SetInputConnection(contourFilter1->GetOutputPort());
	contourMapper1->ScalarVisibilityOff();
	vtkSmartPointer<vtkActor> contourActor1 =
		vtkSmartPointer<vtkActor>::New();
	contourActor1->SetMapper(contourMapper1);
	vtkSmartPointer<vtkOutlineFilter> outlineData =
		vtkSmartPointer<vtkOutlineFilter>::New();
	outlineData->SetInputConnection(reader->GetOutputPort());
	outlineData->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapOutline =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapOutline->SetInputConnection(outlineData->GetOutputPort());
	vtkSmartPointer<vtkActor> outline =
		vtkSmartPointer<vtkActor>::New();
	outline->SetMapper(mapOutline);
	//start
	vtkSmartPointer<vtkPlane> plane =
		vtkSmartPointer<vtkPlane>::New();
	plane->SetOrigin(0, 0, 0);
	plane->SetNormal(1.0,-1.0, 0);
	vtkSmartPointer<vtkClipPolyData> clipper =
		vtkSmartPointer<vtkClipPolyData>::New();
	clipper->SetInputConnection(contourFilter1->GetOutputPort());
	clipper->SetClipFunction(plane);
	clipper->SetValue(0);
	clipper->Update();
	vtkSmartPointer<vtkPolyData> polyData;
	polyData = clipper->GetOutput();
	vtkSmartPointer<vtkDataSetMapper> clipMapper =
		vtkSmartPointer<vtkDataSetMapper>::New();
#if VTK_MAJOR_VERSION <= 5
	clipMapper->SetInput(polyData);
#else
	clipMapper->SetInputData(polyData);
#endif

	vtkSmartPointer<vtkActor> clipActor =
		vtkSmartPointer<vtkActor>::New();
	clipActor->SetMapper(clipMapper);
	clipActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
	clipActor->GetProperty()->SetInterpolationToFlat();


	// Create an isosurface
	vtkSmartPointer<vtkContourFilter> contourFilter =
		vtkSmartPointer<vtkContourFilter>::New();
	contourFilter->SetInputConnection(reader->GetOutputPort());
	contourFilter->SetNumberOfContours(1);
	contourFilter->SetValue(0,220); // (numContours, rangeStart, rangeEnd)
	// Map the contours to graphical primitives
	vtkSmartPointer<vtkPolyDataMapper> contourMapper =
	vtkSmartPointer<vtkPolyDataMapper>::New();
	contourMapper->SetInputConnection(contourFilter->GetOutputPort());
	contourMapper->ScalarVisibilityOff();

	// Create an actor for the contours
	vtkSmartPointer<vtkActor> contourActor =
		vtkSmartPointer<vtkActor>::New();
	contourActor->SetMapper(contourMapper);
	

	// Visualization
	//one renderWindow
	vtkSmartPointer<vtkRenderWindow> renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetSize(900, 900);

	//one interactor 
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);
	//viewpoint
	double leftViewport[4] = { 0.0, 0.0, 0.5, 1.0 };
	double rightViewport[4] = { 0.5, 0.0, 1.0, 1.0 };
	//create two renders 
	// Setup both renderers
	vtkSmartPointer<vtkRenderer> leftRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderWindow->AddRenderer(leftRenderer);
	leftRenderer->SetViewport(leftViewport);
	leftRenderer->SetBackground(.6, .5, .4);

	vtkSmartPointer<vtkRenderer> rightRenderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderWindow->AddRenderer(rightRenderer);
	rightRenderer->SetViewport(rightViewport);
	rightRenderer->SetBackground(.4, .5, .6);
	//add sctors 
	// Add the sphere to the left and the cube to the right
	leftRenderer->AddActor(contourActor);
	rightRenderer->AddActor(outline);
	//rightRenderer->AddActor(contourActor1);
	rightRenderer->AddActor(clipActor);
	vtkSmartPointer<vtkSliderRepresentation2D> sliderRep =
		vtkSmartPointer<vtkSliderRepresentation2D>::New();
	sliderRep->SetMinimumValue(1.0);
	sliderRep->SetMaximumValue(220.0);
	sliderRep->SetValue(220);
	sliderRep->SetTitleText("contour value");
	sliderRep->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep->GetPoint2Coordinate()->SetValue(300, 40);
	sliderRep->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep->GetPoint1Coordinate()->SetValue(40, 40);


	vtkSmartPointer<vtkSliderWidget> sliderWidget =
		vtkSmartPointer<vtkSliderWidget>::New();
	sliderWidget->SetInteractor(renderWindowInteractor);
	sliderWidget->SetRepresentation(sliderRep);
	sliderWidget->SetAnimationModeToAnimate();
	sliderWidget->EnabledOn();

	vtkSmartPointer<vtkSliderCallback> callback =
		vtkSmartPointer<vtkSliderCallback>::New();
	callback->ContourFilter = contourFilter;
	sliderWidget->AddObserver(vtkCommand::InteractionEvent, callback);
	//start
	vtkSmartPointer<vtkSliderRepresentation2D> sliderRep1=
		vtkSmartPointer<vtkSliderRepresentation2D>::New();
	sliderRep1->SetMinimumValue(-1.0);
	sliderRep1->SetMaximumValue(1.0);
	sliderRep1->SetValue(1);
	sliderRep1->SetTitleText("sliding value");
	sliderRep1->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep1->GetPoint2Coordinate()->SetValue(600, 40);
	sliderRep1->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
	sliderRep1->GetPoint1Coordinate()->SetValue(500, 40);


	vtkSmartPointer<vtkSliderWidget> sliderWidget1 =
		vtkSmartPointer<vtkSliderWidget>::New();
	sliderWidget1->SetInteractor(renderWindowInteractor);
	sliderWidget1->SetRepresentation(sliderRep1);
	sliderWidget1->SetAnimationModeToAnimate();
	sliderWidget1->EnabledOn();

	vtkSmartPointer<vtkSliderCallback1> callback1 =
		vtkSmartPointer<vtkSliderCallback1>::New();
	callback1->plane = plane;
	sliderWidget1->AddObserver(vtkCommand::InteractionEvent, callback1);
	//end
	renderWindow->Render();
	//planeWidget->On();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;

	

	
}
