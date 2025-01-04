# Lindevs Assistant

> ⚠️ **Lindevs Assistant is in early development stage**: Expect breaking changes and bugs!

The **Lindevs Assistant** is a software designed to assist with various tasks, including generating QR codes,
recognizing text, chatting with LLM models (coming soon), and more. Lindevs Assistant runs 100% offline on the
computer. While online tools offer convenience and accessibility, the Lindevs Assistant ensures data privacy,
security, and no risk of data leakage.

![lindevs-assistant](https://i.ibb.co/GxyWHvR/lindevs-assistant.png)

## Release Notes

* **[2025-01-04]** [Stable Diffusion 3.5 Medium](https://huggingface.co/stabilityai/stable-diffusion-3.5-medium) and [Large](https://huggingface.co/stabilityai/stable-diffusion-3.5-large) models integration.
* **[2025-01-01]** Image generation and [Stable Diffusion v1.5](https://huggingface.co/stable-diffusion-v1-5/stable-diffusion-v1-5) model integration.
* **[2024-12-30]** CUDA integration for ONNX Runtime.
* **[2024-11-09]** [YOLOv9-Face-Lindevs](https://github.com/lindevs/yolov9-face) model integration.
* **[2024-10-26]** [YOLOv7-Face](https://github.com/derronqi/yolov7-face) model integration.
* **[2024-09-28]** ID photo creator.
* **[2024-09-22]** [RetinaFace](https://github.com/biubug6/Pytorch_Retinaface) model integration.
* **[2024-09-14]** [YOLOv5-Face](https://github.com/deepcam-cn/yolov5-face) model integration.
* **[2024-09-08]** [YOLO-FaceV2](https://github.com/Krasjet-Yu/YOLO-FaceV2) model integration.
* **[2024-08-10]** GoogleTest and [UltraFace](https://github.com/Linzaer/Ultra-Light-Fast-Generic-Face-Detector-1MB) model integration.
* **[2024-07-21]** Image deduplication and [MobileNetV3-Small-Dedup](https://github.com/idealo/imagededup) model integration.
* **[2024-07-07]** Image hash calculation.
* **[2024-06-22]** ONNX Runtime and [YOLOv8-Face-Lindevs](https://github.com/lindevs/yolov8-face) model integration.
* **[2024-06-08]** Project compilation scripts on Linux and Windows.
* **[2024-05-19]** Face detection.
* **[2024-05-07]** Optical character recognition (OCR).
* **[2024-05-01]** Initial project with QR code generator.

## Compilation

### Linux

#### Requirements

* [gcc/g++](https://lindevs.com/install-build-essential-on-ubuntu)
* [Git](https://lindevs.com/install-git-on-ubuntu)
* [CMake](https://lindevs.com/install-cmake-on-ubuntu)
* [Ninja](https://lindevs.com/install-ninja-build-system-on-ubuntu)
* [Docker](https://lindevs.com/install-docker-ce-on-ubuntu)
* (Optional) [NVIDIA Drivers](https://lindevs.com/install-nvidia-drivers-on-ubuntu)

#### Instructions

* Clone repository:

```shell
git clone https://github.com/lindevs/assistant.git && cd assistant
```

* Build Docker image (CPU or CUDA backend):

```shell
./setup.sh build-image
```
```shell
./setup.sh build-image cuda
```

* Build dependencies (CPU or CUDA backend):

```shell
./setup.sh build-deps
```
```shell
./setup.sh build-deps cuda
```

* Build Lindevs Assistant (CPU or CUDA backend):

```shell
./setup.sh build-assistant
```
```shell
./setup.sh build-assistant cuda
```

* Run application:

```shell
./build/app/assistant
```

* (Optional) Build and run tests:

```shell
./setup.sh test-assistant
```

### Windows

#### Requirements

* MSVC - recommended to install [standalone compiler](https://gist.github.com/mmozeiko/7f3162ec2988e81e56d5c4e22cde9977)
* [Git](https://www.git-scm.com/downloads)
* [CMake](https://cmake.org/download/)
* [Ninja](https://github.com/ninja-build/ninja/releases)
* [Python](https://www.python.org/downloads/)
* (Optional) [NVIDIA Drivers](https://www.nvidia.com/en-us/drivers/)
* (Optional) [CUDA](https://developer.download.nvidia.com/compute/cuda/12.6.3/local_installers/cuda_12.6.3_561.17_windows.exe)

#### Instructions

* Clone repository:

```shell
git clone https://github.com/lindevs/assistant.git && cd assistant
```

* Build dependencies (CPU or CUDA backend):

```shell
.\setup.bat build-deps
```
```shell
.\setup.bat build-deps cuda
```

* Build Lindevs Assistant (CPU or CUDA backend):

```shell
.\setup.bat build-assistant
```
```shell
.\setup.bat build-assistant cuda
```

* Run application:

```shell
.\build\app\assistant
```

* (Optional) Build and run tests:

```shell
.\setup.bat test-assistant
```
