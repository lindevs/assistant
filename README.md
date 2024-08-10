# Lindevs Assistant

> ⚠️ **Lindevs Assistant is in early development stage**: Expect breaking changes and bugs!

The **Lindevs Assistant** is a software designed to assist with various tasks, including generating QR codes,
recognizing text, chatting with LLM models (coming soon), and more. Lindevs Assistant runs 100% offline on the
computer. While online tools offer convenience and accessibility, the Lindevs Assistant ensures data privacy,
security, and no risk of data leakage.

![lindevs-assistant](https://i.ibb.co/DMV2wqn/lindevs-assistant.png)

## Release Notes

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

#### Instructions

* Clone repository:

```shell
git clone https://github.com/lindevs/assistant.git
cd assistant
```

* Build Docker image:

```shell
./setup.sh build-image
```

* Build dependencies:

```shell
./setup.sh build-deps
```

* Build Lindevs Assistant:

```shell
./setup.sh build-assistant
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

#### Instructions

* Clone repository:

```shell
git clone https://github.com/lindevs/assistant.git
cd assistant
```

* Build dependencies:

```shell
.\setup.bat build-deps
```

* Build Lindevs Assistant:

```shell
.\setup.bat build-assistant
```

* Run application:

```shell
.\build\app\assistant
```

* (Optional) Build and run tests:

```shell
.\setup.bat test-assistant
```
