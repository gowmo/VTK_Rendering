#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume16Reader.h>
#include <vtkPolyDataMapper.h>
#include <vtkSLCReader.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkActor.h>
#include <vtkOutlineFilter.h>
#include <vtkColorTransferFunction.h>
#include <vtkTextActor.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkPolyDataNormals.h>
#include <vtkContourFilter.h>
#include <vtkSmartPointer.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkSplineWidget2.h>
#include <vtkSliderWidget.h>
#include <vtkSliderRepresentation2D.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkWidgetEvent.h>
#include <vtkFloatArray.h>
#include <vtkInteractorStyleTrackballCamera.h>




// Callback for the interaction for opacity
class vtkSliderCallback : public vtkCommand
{
public:
	static vtkSliderCallback *New()        {    return new vtkSliderCallback;    }

	vtkSliderCallback() :opacfunc(NULL) {}
	vtkPiecewiseFunction *opacfunc;

	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkSliderWidget *sliderWidget =
			reinterpret_cast<vtkSliderWidget*>(caller);
	
		double opacityvalue = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();
		double oparray[4] = { opacityvalue, 0.0, 0.0, 0.0 };

		this->opacfunc->SetNodeValue(0, oparray);
	
	}

};

class redfloatwrapper
{
public :
	static redfloatwrapper *New() {
		return new redfloatwrapper;
	}
	
	float workingvalue;

	void setWorkingvalue(float a) {

		this->workingvalue = a;

	}
	float getWorkingvalue() {

		return workingvalue;
	}
	
};


class vtkSliderRedColorCallback : public vtkCommand
{
public:
	static vtkSliderRedColorCallback *New() { return new vtkSliderRedColorCallback; }

	vtkSliderRedColorCallback() :colorredfunc(NULL) {}
	vtkColorTransferFunction *colorredfunc;

	//redfloatwrapper *redslider;

	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkSliderWidget *sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);

		double redcolorvalue = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();
	double redarray[4] = { 0.0, redcolorvalue, 0.0, 0.0 };


		//this->redslider->setWorkingvalue(redcolorvalue);
		this->colorredfunc->SetNodeValue(0, redarray);

	}

};




class vtkSliderGreenColorCallback : public vtkCommand
{
public:
	static vtkSliderGreenColorCallback *New() { return new vtkSliderGreenColorCallback; }

	vtkSliderGreenColorCallback() :colorgreenfunc(NULL) {}
	vtkColorTransferFunction *colorgreenfunc;

	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkSliderWidget *sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);

		double greencolorvalue = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();
		double greenarray[4] = { 0.0, 0.0, greencolorvalue, 0.0 };

		this->colorgreenfunc->SetNodeValue(0, greenarray);

	}

};


class vtkSliderBlueColorCallback : public vtkCommand
{
public:
	static vtkSliderBlueColorCallback *New() { return new vtkSliderBlueColorCallback; }

	vtkSliderBlueColorCallback() :colorbluefunc(NULL) {}
	vtkColorTransferFunction *colorbluefunc;

	virtual void Execute(vtkObject *caller, unsigned long, void*)
	{
		vtkSliderWidget *sliderWidget = reinterpret_cast<vtkSliderWidget*>(caller);

		double bluecolorvalue = static_cast<vtkSliderRepresentation *>(sliderWidget->GetRepresentation())->GetValue();
		double bluearray[4] = {0.0 , 0.0, 0.0, bluecolorvalue };

		this->colorbluefunc->SetNodeValue(0, bluearray);

	}

};




int main(int argc, char *argv[])
{
	//read the file and load it into slc reader


	if (argc != 2)
	{
		std::cout << "Please provide FileName.slc " << argv[0]
			<< " Filename(.slc)" << std::endl;
		return EXIT_FAILURE;
	}

	std::string Filename = argv[1];

       //  std::string Filename = "D:/Documents/Visual Studio 2017/Projects/vtk-foot/bin/Debug/vm_foot.slc"; 

	                       vtkSmartPointer<vtkSLCReader> slcreader = vtkSmartPointer<vtkSLCReader>::New();
                           slcreader->SetFileName ( Filename.c_str() );						   
	                       slcreader->Update();			  			   
						   
						   double oparray2[4] = { 0.0, 0.0, 0.0, 0.0 };
						   double redcolorarray[4] = { 0.0,1.0,0.0,0.0 };
						   double greencolorarray[4] = { 0.0,0.0,1.0,0.0 };
						   double bluecolorarray[4] = { 0.0,0.0,0.0,1.0 };

						   redfloatwrapper *currentredvalue = redfloatwrapper::New();

 // Create transfer mapping scalar value to opacity.
								vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();

								//opacityTransferFunction->AddPoint(0.0, 0.1,0.1,0.1);
									  //opacityTransferFunction->AddPoint(40.0,  0.0);
								//opacityTransferFunction->AddPoint(opacityvalue, 0.0);
							     //opacityTransferFunction->AddPoint(60.0, 0.2);
								opacityTransferFunction->AddPoint(0.0, 0.2);
								opacityTransferFunction->AddPoint(255.0, 0.6,0.4,0.2);

								
								//opacityTransferFunction->AddPoint(255.0, 0.6);
										//opacityTransferFunction->AddPoint(100.0, 0.2);

										//opacityTransferFunction->AddPoint(80.0, 0.0);
										//opacityTransferFunction->AddPoint(120.0, 0.2);
										//opacityTransferFunction->AddPoint(255.0, 0.2);
						   					   
 // Create transfer mapping scalar value to color.
						vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
						//colorTransferFunction->AddRGBPoint(40.0,  0.0, 0.1, 0.0);
						//colorTransferFunction->AddRGBPoint(80.0, 0.0, 1.0,0.2);

						colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
						colorTransferFunction->AddRGBPoint(255.0, 1.0, 1.0, 1.0);


						//colorTransferFunction->AddRGBPoint(80.0, 0.5, 0.5, 0.5);
						//colorTransferFunction->AddRGBPoint(120.0, 0.0, 0.0, 1.0);
						//colorTransferFunction->AddRGBPoint(160.0, 255.0, 255.0, 0.0);
						//colorTransferFunction->AddRGBPoint(200.0, 255.0, 255.0, 255.0);
						//colorTransferFunction->AddRGBPoint(255.0, 0.0, 0.0, 1.0
						//colorTransferFunction->AddRGBPoint(255.0, 1.0, 1.0, 1.0);
						vtkSmartPointer<vtkColorTransferFunction> colorredtransferfunction = vtkSmartPointer<vtkColorTransferFunction>::New();

						vtkSmartPointer<vtkColorTransferFunction> colorgreentransferfunction = vtkSmartPointer<vtkColorTransferFunction>::New();
				

   // The property describes how the data will look.
						vtkSmartPointer<vtkVolumeProperty> volumeProperty =  vtkSmartPointer<vtkVolumeProperty>::New();
						volumeProperty->SetColor(colorTransferFunction);
						volumeProperty->SetScalarOpacity(opacityTransferFunction);
						volumeProperty->ShadeOff();
						volumeProperty->SetInterpolationTypeToLinear();
  
 
  //create a volume ray cast mapper 
                    				
						vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper =   vtkSmartPointer<vtkSmartVolumeMapper>::New();
						volumeMapper->SetBlendModeToComposite(); // composite first
						//volumeMapper->SetBlendModeToMaximumIntensity(); // MIP
						volumeMapper->SetInputConnection(slcreader->GetOutputPort());

						// The volume holds the mapper and the property and can be used to
						// position/orient the volume.
						vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
						volume->SetMapper(volumeMapper);
						volume->SetProperty(volumeProperty);

						//add the vtlslicer widgets 

						vtkSmartPointer<vtkSliderRepresentation2D> sliderRepopacity =	vtkSmartPointer<vtkSliderRepresentation2D>::New();
						sliderRepopacity->SetMinimumValue(0.0);
						sliderRepopacity->SetMaximumValue(255.0);
						sliderRepopacity->SetValue(0.0);
						sliderRepopacity->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
						sliderRepopacity->GetPoint1Coordinate()->SetValue(100, 100);
						sliderRepopacity->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
						sliderRepopacity->GetPoint2Coordinate()->SetValue(100, 500);
						

						vtkSmartPointer<vtkSliderRepresentation2D> sliderRed = vtkSmartPointer<vtkSliderRepresentation2D>::New();
						sliderRed->SetMinimumValue(0.0);
						sliderRed->SetMaximumValue(1.0);
						sliderRed->SetValue(1.0);
						sliderRed->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
						sliderRed->GetPoint1Coordinate()->SetValue(100, 600);
						sliderRed->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
						sliderRed->GetPoint2Coordinate()->SetValue(100, 800);


						vtkSmartPointer<vtkSliderRepresentation2D> sliderGreen = vtkSmartPointer<vtkSliderRepresentation2D>::New();
						sliderGreen->SetMinimumValue(0.0);
						sliderGreen->SetMaximumValue(1.0);
						sliderGreen->SetValue(1.0);
						sliderGreen->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
						sliderGreen->GetPoint1Coordinate()->SetValue(200, 600);
						sliderGreen->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
						sliderGreen->GetPoint2Coordinate()->SetValue(200, 800);


						vtkSmartPointer<vtkSliderRepresentation2D> sliderBlue = vtkSmartPointer<vtkSliderRepresentation2D>::New();
						sliderBlue->SetMinimumValue(0.0);
						sliderBlue->SetMaximumValue(1.0);
						sliderBlue->SetValue(1.0);
						sliderBlue->GetPoint1Coordinate()->SetCoordinateSystemToDisplay();
						sliderBlue->GetPoint1Coordinate()->SetValue(300, 600);
						sliderBlue->GetPoint2Coordinate()->SetCoordinateSystemToDisplay();
						sliderBlue->GetPoint2Coordinate()->SetValue(300, 800);

					
  //create the renderer , renderer window  and the interactor

                         vtkSmartPointer<vtkRenderer> renderer =    vtkSmartPointer<vtkRenderer>::New();
						 
                         vtkSmartPointer<vtkRenderWindow> renwindow =   vtkSmartPointer<vtkRenderWindow>::New();
                         renwindow->AddRenderer(renderer);
						 renwindow->SetSize(1000, 1000);
						 renderer->SetBackground(0.1, 0.4, 0.2);

                         vtkSmartPointer<vtkRenderWindowInteractor> reninteractor =  vtkSmartPointer<vtkRenderWindowInteractor>::New();
                         reninteractor->SetRenderWindow(renwindow);	 
				
						 vtkSmartPointer<vtkSliderWidget> sliderWidgetopacity = vtkSmartPointer<vtkSliderWidget>::New();
						 sliderWidgetopacity->SetInteractor(reninteractor);
						 sliderWidgetopacity->SetRepresentation(sliderRepopacity);
						 sliderWidgetopacity->SetAnimationModeToAnimate();
						 sliderWidgetopacity->EnabledOn();


						 vtkSmartPointer<vtkSliderWidget> sliderWidgetRed = vtkSmartPointer<vtkSliderWidget>::New();
						 sliderWidgetRed->SetInteractor(reninteractor);
						 sliderWidgetRed->SetRepresentation(sliderRed);
						 sliderWidgetRed->SetAnimationModeToAnimate();
						 sliderWidgetRed->EnabledOn();


						 vtkSmartPointer<vtkSliderWidget> sliderWidgetGreen = vtkSmartPointer<vtkSliderWidget>::New();
						 sliderWidgetGreen->SetInteractor(reninteractor);
						 sliderWidgetGreen->SetRepresentation(sliderGreen);
						 sliderWidgetGreen->SetAnimationModeToAnimate();
						 sliderWidgetGreen->EnabledOn();

						 vtkSmartPointer<vtkSliderWidget> sliderWidgetBlue = vtkSmartPointer<vtkSliderWidget>::New();
						 sliderWidgetBlue->SetInteractor(reninteractor);
						 sliderWidgetBlue->SetRepresentation(sliderBlue);
						 sliderWidgetBlue->SetAnimationModeToAnimate();
						 sliderWidgetBlue->EnabledOn();


						 vtkSmartPointer<vtkSliderCallback> callbackopacity = vtkSmartPointer<vtkSliderCallback>::New();
						 vtkSmartPointer<vtkSliderRedColorCallback> callbackred = vtkSmartPointer<vtkSliderRedColorCallback>::New();
						vtkSmartPointer<vtkSliderGreenColorCallback> callbackgreen = vtkSmartPointer<vtkSliderGreenColorCallback>::New();
						 vtkSmartPointer<vtkSliderBlueColorCallback> callbackblue = vtkSmartPointer<vtkSliderBlueColorCallback>::New();

						 callbackopacity->opacfunc = opacityTransferFunction;
						callbackred->colorredfunc = colorTransferFunction;
						callbackgreen->colorgreenfunc = colorTransferFunction;
						 callbackblue->colorbluefunc = colorTransferFunction;


						 sliderWidgetopacity->AddObserver(vtkCommand::InteractionEvent, callbackopacity);
						 sliderWidgetRed->AddObserver(vtkCommand::InteractionEvent, callbackred);
					sliderWidgetGreen->AddObserver(vtkCommand::InteractionEvent, callbackgreen);
						 sliderWidgetBlue->AddObserver(vtkCommand::InteractionEvent, callbackblue);


						renderer->AddViewProp(volume);
						renderer->ResetCamera();
 					
						renwindow->Render();
			
						volumeMapper->SetRequestedRenderModeToRayCast();
						renwindow->Render();

						double timeInSeconds = renderer->GetLastRenderTimeInSeconds();
						double fps = 1.0 / timeInSeconds;
						std::cout << "FPS: " << fps << std::endl;
	//initialize the interactor
						
						//	reninteractor->Initialize();
							reninteractor->Start();	
							
			return EXIT_SUCCESS;				
}



