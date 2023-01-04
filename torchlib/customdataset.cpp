#include "customdataset.h"

CustomDataset::CustomDataset() {}

torch::data::Example<> CustomDataset::get(size_t index) {
    torch::Tensor sample_img   = features_.at(index);
    torch::Tensor sample_label = labels_.at(index);
    return {sample_img.clone(), sample_label.clone()};
}

void CustomDataset::insertOneTensorData(at::Tensor feature_, at::Tensor label_) {
    features_.push_back(feature_);
    labels_.push_back(label_);
}

void CustomDataset::insertOneFloatFeatureAndIntLabel(float *feature_, int feature_len, int label_) {
    torch::Tensor label_tensor   = torch::full({1}, label_);
    torch::Tensor feature_tensor = torch::from_blob(feature_, {1, feature_len}).toType(torch::kFloat32);
    features_.push_back(feature_tensor.clone());
    labels_.push_back(label_tensor.clone());
}
