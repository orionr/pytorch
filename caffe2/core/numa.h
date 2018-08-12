#ifndef CAFFE2_CORE_NUMA_H_
#define CAFFE2_CORE_NUMA_H_

#include "caffe2/core/logging.h"

CAFFE2_DECLARE_bool(caffe2_cpu_numa_enabled);

namespace caffe2 {

bool CAFFE2_API IsNUMAEnabled();

void CAFFE2_API NUMABind(int numa_node_id);

int CAFFE2_API GetNUMANode(const void* ptr);

int CAFFE2_API GetNumNUMANodes();

void CAFFE2_API NUMAMove(void* ptr, size_t size, int numa_node_id);

int CAFFE2_API GetCurrentNUMANode();

} // namespace caffe2

#endif // CAFFE2_CORE_NUMA_H_
