#ifndef CAFFE2_OPERATORS_ELEMENTWISE_OPS_UTILS_H_
#define CAFFE2_OPERATORS_ELEMENTWISE_OPS_UTILS_H_

#include <tuple>
#include <vector>

#include "caffe2/core/context.h"
#include "caffe2/core/tensor.h"

namespace caffe2 {
namespace elementwise_ops_utils {

std::tuple<size_t, size_t, size_t> CAFFE2_API
ComputeLegacyBroadcastSizes(const Tensor& A, const Tensor& B, int axis);

std::vector<int> CAFFE2_API ComputeBinaryBroadcastForwardDims(
    const std::vector<int>& A_dims,
    const std::vector<int>& B_dims);

void CAFFE2_API ComputeBinaryBroadcastBackwardAxes(
    const std::vector<int>& A_dims,
    const std::vector<int>& B_dims,
    std::vector<int>* A_axes,
    std::vector<int>* B_axes);

} // namespace elementwise_ops_utils
} // namespace caffe2

#endif // CAFFE2_OPERATORS_ELEMENTWISE_OPS_UTILS_H_
