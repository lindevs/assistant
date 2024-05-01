#!/bin/bash

docker run -it --rm \
    -v ./deps:/opt/assistant/deps \
    lindevs-assistant compile.sh
