#ifndef CUSTOMDATASET_H
#define CUSTOMDATASET_H
#include <ATen/ATen.h>
#include <torch/torch.h>

#include <vector>

class CustomDataset : public torch::data::Dataset<CustomDataset> {
private:
    std::vector<torch::Tensor> features_, labels_;

public:
    explicit CustomDataset();

    torch::data::Example<> get(size_t index) override;
    // Return the length of data
    torch::optional<size_t> size() const override { return labels_.size(); };

    void insertOneTensorData(torch::Tensor feature_, torch::Tensor label_);
    void insertOneFloatFeatureAndIntLabel(float *feature_, int feature_len, int label_);
};

#endif  // CUSTOMDATASET_H
