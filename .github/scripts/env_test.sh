#!/bin/bash

XPU_ONEAPI_PATH="${XPU_ONEAPI_PATH:-"/opt/intel/oneapi"}"

source ${XPU_ONEAPI_PATH}/compiler/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/pti/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/umf/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/ccl/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/mpi/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/debugger/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/dev-utilities/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/dnnl/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/dpl/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/mkl/latest/env/vars.sh
source ${XPU_ONEAPI_PATH}/tbb/latest/env/vars.sh
icpx --version
sycl-ls
