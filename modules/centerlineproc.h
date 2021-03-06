#ifndef CENTERLINEPROC_H
#define CENTERLINEPROC_H
// itk includes
#include <itkImage.h>
#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>
#include <itkDanielssonDistanceMapImageFilter.h>
#include <itkSignedDanielssonDistanceMapImageFilter.h>
#include <itkSignedMaurerDistanceMapImageFilter.h>
#include <itkSmoothingRecursiveGaussianImageFilter.h>
#include <itkUnaryFunctorImageFilter.h>
#include <itkPowImageFilter.h>
#include <itkSquareImageFilter.h>
#include <itkRescaleIntensityImageFilter.h>
#include <itkImageSliceConstIteratorWithIndex.h>
#include <itkGradientMagnitudeImageFilter.h>
#include <itkInvertIntensityImageFilter.h>
#include <itkThresholdImageFilter.h>
#include <itkTimeProbe.h>
#include <itkMath.h>

#include <itkNumericTraits.h>
#include <itkPolyLineParametricPath.h>
#include <itkLinearInterpolateImageFunction.h>
#include <itkGradientDescentOptimizer.h>
#include <itkRegularStepGradientDescentOptimizer.h>
#include <itkPathIterator.h>
#include <itkNeighborhoodIterator.h>
#include <itkNearestNeighborInterpolateImageFunction.h>

// 3d part includes
#include "modules/findpath/approach2/itkArrivalFunctionToPathFilter.h"
#include "modules/findpath/approach2/itkSpeedFunctionToPathFilter.h"

#include <vnl/vnl_math.h>
#include <itkPoint.h>

#include <vtkPoints.h>
#include <vtkSmartPointer.h>

//    general includes
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//    customized includes
#include "tools/initials.h"
#include "tools/fastdef.h"
#include "modules/findpath/itkBinaryThinningImageFilter3D.h"

const unsigned int dimension = 3;
typedef unsigned char                                              InputPixelType;
typedef unsigned int                                               OutputPixelType;
typedef itk::Image< InputPixelType,dimension >                     InputImageType;
typedef itk::Image< OutputPixelType,dimension >                    OutputImageType;
typedef itk::DanielssonDistanceMapImageFilter<
             InputImageType,OutputImageType>                       FilterType;
typedef unsigned int                                               CoordType;
typedef itk::Point< CoordType, dimension>                           PointType;

typedef float                                                         PixelType;
typedef unsigned short                                                VoronoiPixelType;
typedef itk::Image< PixelType,dimension>                              OutputMapType;
typedef itk::Image< VoronoiPixelType,dimension>                       VoronoiMapType;


class centerLineProc
{
public:
    centerLineProc();
//    static centerLineProc *New()
//    {
//        return new centerLineProc;
//    }
    int getDistanceMap(std::string filename);
    int getSignedDistanceMap_Sin(std::string filename); //初试版本，寻找一条中心线；
    int getSignedDistanceMap_Mul(std::string filename); //寻找多条中心线；

    std::vector<OutputImageType::PointType>& getpoints()
    {
        return MinPoints;
    }
    int GetCenterlinePointNums();
    void ExportCenterlineData(std::string filename);
    void GetcenterlinePoint(int index, double p[3]);

    // approach 0
    // ********************************************************
    int Path_GradientDescent(std::string filename, double ps[3], double pe[3]);
    std::vector<Point3f> CenterPoints;
    // ******************************************************

    // approach 1
    // *******************************************************
    void Path_Thin3dImg(std::string filename, double ps[], double pe[]);
    // ********************************************************

    // approach 2
    // **********************************************************
    void Path_Vornoimedial(std::string filename, double ps[], double pe[]);
private:

    bool CenterLineFlag;  // has centerline?
    //vector for local-max index of OutputImage
    std::vector<OutputImageType::IndexType> localMinVec;
    //vector for local-max physical point of outputImage
    std::vector<OutputImageType::PointType> MinPoints;

    void clear()
    {
        localMinVec.clear();
    }

};

#endif // CENTERLINEPROC_H
