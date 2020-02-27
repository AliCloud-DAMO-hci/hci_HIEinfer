#pragma once

#include <string>
#include <vector>

class IImageEngine
{
public:
    virtual ~IImageEngine() {}
    virtual bool SetInferModel(const std::string & model_path) = 0;
    virtual bool LoadImagePreprocessData(const std::string & image_path) = 0;
    virtual void InferSync() = 0;

    // pair (score,index) for each image result
    virtual bool CopyOutputToCPU(std::vector<std::pair<float,int> > & output_value) = 0;
};


// user is responsible to delete this
extern "C" IImageEngine *CreateImageEngine();
