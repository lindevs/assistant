# Lindevs Assistant

> ⚠️ **Lindevs Assistant is in early development stage**: Expect breaking changes and bugs!

The **Lindevs Assistant** is a software designed to assist with various tasks, including generating QR codes,
recognizing text, chatting with LLM models (coming soon), and more. Lindevs Assistant runs 100% offline on the
computer. While online tools offer convenience and accessibility, the Lindevs Assistant ensures data privacy,
security, and no risk of data leakage.

![lindevs-assistant](https://i.ibb.co/Z6WPBRB/lindevs-assistant.png)

## Release Notes

* **[2024-05-07]** Optical character recognition (OCR).
* **[2024-05-01]** Initial project with QR code generator.

## Compilation

### Linux

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
./deps/assistant
```
