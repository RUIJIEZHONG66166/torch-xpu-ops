#include <ATen/native/ForeachUtils.h>

#ifndef AT_PER_OPERATOR_HEADERS
#include <ATen/XPUNativeFunctions.h>
#else
#include <ATen/ops/_foreach_add_native.h>
#include <ATen/ops/_foreach_addcdiv_native.h>
#endif
#include <aten/sycl/ForeachBinaryOpListKernels.h>
#include <aten/sycl/ForeachPointwiseOpListKernels.h>

namespace at {

#define FOREACH_BINARY_OP_LIST_ALPHA(NAME)                                \
  void XPUNativeFunctions::_foreach_##NAME##_(                            \
      TensorList tensors1, TensorList tensors2, const Scalar& alpha) {    \
    at::native::check_foreach_api_restrictions(tensors1, tensors2);       \
    if (!at::native::can_use_fast_route({tensors1, tensors2}, alpha)) {   \
      return at::native::foreach_tensor_##NAME##_list_kernel_slow_(       \
          tensors1, tensors2, alpha);                                     \
    }                                                                     \
                                                                          \
    at::native::xpu::FOREACH_BINARY_LIST_ALPHA_INPLACE_KERNEL_NAME(NAME)( \
        tensors1, tensors2, alpha);                                       \
  }                                                                       \
                                                                          \
  std::vector<Tensor> XPUNativeFunctions::_foreach_##NAME(                \
      TensorList tensors1, TensorList tensors2, const Scalar& alpha) {    \
    at::native::check_foreach_api_restrictions(tensors1, tensors2);       \
    if (!at::native::can_use_fast_route({tensors1, tensors2}, alpha)) {   \
      return at::native::foreach_tensor_##NAME##_list_kernel_slow(        \
          tensors1, tensors2, alpha);                                     \
    }                                                                     \
                                                                          \
    return at::native::xpu::FOREACH_BINARY_LIST_ALPHA_KERNEL_NAME(NAME)(  \
        tensors1, tensors2, alpha);                                       \
  }

FOREACH_BINARY_OP_LIST_ALPHA(add);

#define FOREACH_POINTWISE_OP_TENSOR(NAME)                                      \
  std::vector<Tensor> XPUNativeFunctions::_foreach_##NAME(                     \
      TensorList input,                                                        \
      TensorList tensors1,                                                     \
      TensorList tensors2,                                                     \
      const Tensor& scalars_) {                                                \
    auto scalars =                                                             \
        at::native::convert_tensor_to_scalar_list(scalars_, input.size());     \
    at::native::check_foreach_api_restrictions(                                \
        input, tensors1, tensors2, scalars);                                   \
    if (!at::native::can_use_fast_route({input, tensors1, tensors2}) ||        \
        at::native::has_integral_tensor(input, /* includeBool */ true)) {      \
      return at::native::foreach_tensor_##NAME##_scalarlist_slow(              \
          input, tensors1, tensors2, scalars);                                 \
    }                                                                          \
                                                                               \
    return native::xpu::foreach_##NAME##_kernel(                               \
        input, tensors1, tensors2, scalars);                                   \
  }                                                                            \
                                                                               \
  void XPUNativeFunctions::_foreach_##NAME##_(                                 \
      TensorList input,                                                        \
      TensorList tensors1,                                                     \
      TensorList tensors2,                                                     \
      const Tensor& scalars_) {                                                \
    auto scalars =                                                             \
        at::native::convert_tensor_to_scalar_list(scalars_, input.size());     \
    at::native::check_foreach_api_restrictions(                                \
        input, tensors1, tensors2, scalars);                                   \
    if (!at::native::can_use_fast_route(                                       \
            {input, tensors1, tensors2}, scalars) ||                           \
        at::native::has_integral_tensor(input, /* includeBool */ true)) {      \
      return at::native::foreach_tensor_##NAME##_scalarlist_slow_(             \
          input, tensors1, tensors2, scalars);                                 \
    }                                                                          \
                                                                               \
    native::xpu::foreach_##NAME##_kernel_(input, tensors1, tensors2, scalars); \
  }

FOREACH_POINTWISE_OP_TENSOR(addcmul)
FOREACH_POINTWISE_OP_TENSOR(addcdiv)

} // namespace at