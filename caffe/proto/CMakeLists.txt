file(GLOB Caffe_PROTOBUF_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

caffe2_protobuf_generate_cpp_py(Caffe_PROTO_SRCS Caffe_PROTO_HEADERS Caffe_PROTO_PY ${Caffe_PROTOBUF_FILES})

add_library(Caffe_PROTO OBJECT ${Caffe_PROTO_HEADERS} ${Caffe_PROTO_SRCS})

if (MSVC)
  if(BUILD_SHARED_LIBS)
    set(Caffe2_API_DEFINE "-DCAFFE2_API=__declspec(dllexport)")
  else()
    set(Caffe2_API_DEFINE "-DCAFFE2_API=")
  endif()
elseif (CMAKE_COMPILER_IS_GNUCXX)
  if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9.0)
    set(Caffe2_API_DEFINE "-DCAFFE2_API=")
    #set(Caffe2_API_DEFINE "-DCAFFE2_API=__attribute__((__visibility__(\"default\")))")
  else()
    set(Caffe2_API_DEFINE "-DCAFFE2_API=[[gnu::visibility(\"default\")]]")
  endif()
else()
  set(Caffe2_API_DEFINE "-DCAFFE2_API=")
endif()
target_compile_definitions(
    Caffe_PROTO PRIVATE ${Caffe2_API_DEFINE})

install(FILES ${Caffe_PROTO_HEADERS} DESTINATION include/caffe/proto)
