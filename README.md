# dsl_pipeline_server

## 环境准备
```
mkdir dsl_server && cd dsl_server
docker pull nvcr.io/nvidia/deepstream:7.0-gc-triton-devel
git clone https://github.com/prominenceai/deepstream-services-library.git
git clone https://github.com/ithewei/libhv.git
docker run --rm -it --gpus="device=1" -v $PWD/dsl_server:/workspace/dsl_server --entrypoint /bin/bash nvcr.io/nvidia/deepstream:7.0-triton-multiarch

apt update && apt-get install \
    libgstrtspserver-1.0-dev \
    gstreamer1.0-rtsp \
    libapr1 \
    libapr1-dev \
    libaprutil1 \
    libaprutil1-dev \
    libgeos-dev \
    libcurl4-openssl-dev

apt-get install \
    libjson-glib-dev \
    libsoup-gnome2.4-dev \
    libgstreamer-plugins-bad1.0-dev \
    libnice-dev \
    gstreamer1.0-nice

pkg-config --cflags json-glib-1.0


cd /workspace/dsl_server/deepstream-services-library
make -j8
make install

cd /workspace/libhv
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=$PWD/../install ..
cmake --build .
```

## 