#pragma once

#include <string>
#include <vector>

class IImageEngine
{
public:
    virtual ~IImageEngine() {}
    virtual bool SetInferModel(const std::string & model_path) = 0;
    virtual bool AddImagePreprocessData(const std::string & image_path) = 0;
    virtual bool LoadImagePreprocessData(int index) =0 ;
    virtual void InferSync() = 0;
    // pair for (score,index)
    virtual bool CopyOutputToCPU(std::vector<std::pair<float,int> > & output_value) = 0;
};


// user is responsible to delete
extern "C" IImageEngine *CreateImageEngine();
