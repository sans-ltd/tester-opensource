FROM debian:bullseye

ENV DEBIAN_FRONTEND noninteractive
ENV LANG='C.UTF-8' LC_ALL='C.UTF-8'

# Python3 with venv and pip for PlatformIO
RUN apt-get update && apt-get install -y \
	python3 \
    python3-venv \
    python3-pip

# Install PlatformIO from pip repo
RUN python3 -m pip install --upgrade pip setuptools
RUN python3 -m pip install --upgrade platformio
RUN python3 --version

# Git is needed by Espressif IDF SDK, graphviz and doxygen are for documentation generation
RUN apt-get update && apt-get install -y \
    doxygen graphviz \
    git 
    

# Pre-Install ESP32 support to speed up the build.
COPY platformio.ini /root/fake-pio-project/
WORKDIR /root/fake-pio-project

# Install PlatformIO packages and Python dependencies of PlatformIO
RUN pio pkg install
RUN pio run || echo "Known FAIL. This is expected because the fake project is not complete enough."
