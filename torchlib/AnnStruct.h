/**
 * @projectName   qtmflus
 * @brief         摘要
 * 使用libtorch定义神经网络结构
 * @author        cmk
 * @date          2020-12-03
 */

#ifndef ANNSTRUCT_H
#define ANNSTRUCT_H
#undef slots
#include <torch/torch.h>
#define slots Q_SLOTS

namespace MANN {
struct AnnNet : torch::nn::Module {
    AnnNet(int input_dim, int output_dim, int num_of_hidden_layers) {
        this->input_dim            = input_dim;
        this->output_dim           = output_dim;
        this->num_of_hidden_layers = num_of_hidden_layers;

        fc1 = register_module("fc1", torch::nn::Linear(input_dim, num_of_hidden_layers));
        // 隐藏层
        fc2 = register_module("fc2", torch::nn::Linear(num_of_hidden_layers, output_dim));
    }

    // Implement the Net's algorithm.
    torch::Tensor forward(torch::Tensor x) {
        // Use one of many tensor manipulation functions.
        x = torch::sigmoid(fc1->forward(x.reshape({x.size(0), this->input_dim})));
        //        x = torch::log_softmax(fc2->forward(x), /*dim=*/1);
        x = fc2->forward(x);
        return x;
    }

    // Use one of many "standard library" modules.
    torch::nn::Linear fc1{nullptr}, fc2{nullptr};
    int               input_dim, output_dim, num_of_hidden_layers;
};
}  // namespace MANN

#endif  // ANNSTRUCT_H
