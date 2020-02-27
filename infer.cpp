#include <common.h>
#include <iimageengine.h>
#include <stringutil.h>

#include <chrono>
#include <memory>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::string;

namespace {

void readImageLabels(const string & label_path,vector<pair<string,int> > & labels)
{
    static constexpr int NUM_IMAGES = 50000;
    labels.clear();
    labels.reserve(NUM_IMAGES);
    std::ifstream fin(label_path);
    ASSERT(fin.is_open());

    string line;
    while(getline(fin,line)) {
        StringUtil::Trim(line);
        vector<string> elems = StringUtil::Split(line," ");
        labels.emplace_back(elems[0],std::stoi(elems[1]));
    }
    fin.close();
    //ASSERT(labels.size()==NUM_IMAGES);

    cout << "read label success , " << labels.size() << " labels" << endl;
}

} // namespace


int main(int argc,char *argv[])
{
    if(argc != 4) {
        cout << "usage : " << argv[0] << " model_path image_dir label_path" << endl;
        return -1;
    }

    const string model_path = argv[1];
    const string image_dir = argv[2];
    const string label_path = argv[3];
    
    std::shared_ptr<IImageEngine> engine(CreateImageEngine());
    ASSERT(engine!=nullptr);

    bool status = engine->SetInferModel(model_path);
    if(status==false) {
        cout << "set infer model failed" << endl;
        return -1;
    }

    vector<pair<string,int> > labels;
    readImageLabels(label_path,labels);

    // warm up
    static constexpr int NUM_WARM_UP = 20;
    for(int img_id=0;img_id<NUM_WARM_UP;img_id++) {
        const string image_path = image_dir + "/" + labels[img_id].first;
        status = engine->LoadImagePreprocessData(image_path);
        if(status==false) {
            cout << "load image data failed" << endl;
            return -1;
        }
        engine->InferSync();
    }
    
    vector<std::pair<float,int> > output_value;
    float time_elapsed = 0.0f;
    int num_total = 0;
    int top1 = 0,top5 = 0;

    // classify images
    for(size_t img_id=0;img_id<labels.size() ;img_id++)
    {
        const string image_path = image_dir + "/" + labels[img_id].first;
        const int stdlabel = labels[img_id].second;

        status = engine->LoadImagePreprocessData(image_path);
        if(status==false) {
            cout << "load image data failed" << endl;
            return -1;
        }

        auto start = std::chrono::high_resolution_clock::now();
        engine->InferSync();
        auto end = std::chrono::high_resolution_clock::now();
        //cout << std::chrono::duration<float,std::milli>(end-start).count() << endl;
        time_elapsed += std::chrono::duration<float,std::milli>(end-start).count();

        status = engine->CopyOutputToCPU(output_value);
        if(status==false) {
            cout << "copy output value failed" << endl;
            return -1;
        }

        auto cmp = [](const pair<float,int> & a,const pair<float,int> & b) {
            return a.first > b.first;
        };
        std::partial_sort(output_value.begin(),output_value.begin()+5,output_value.end(),cmp);
        for(int i=0;i<5;i++)
        {
            if(output_value[i].second == stdlabel) {
                top5++;
                if(i==0) top1++;
                break;
            }
        }
        num_total++;

        // print log
        if(num_total%100 == 0) {
            cout << "----------" << "processed " << num_total << " images" << "----------" << endl;
            cout << "top1 : " << std::setiosflags(std::ios::fixed) << std::setprecision(5) 
                << 1.0 * top1 / num_total << endl;
            cout << "top5 : " << std::setiosflags(std::ios::fixed) << std::setprecision(5) 
                << 1.0 * top5 / num_total << endl;
        }
    }
    cout << "num_image : " << labels.size() << endl;
    cout << "time elapsed : " << std::setiosflags(std::ios::fixed) << std::setprecision(5) 
        << time_elapsed/labels.size() << endl;

    return 0;
}
