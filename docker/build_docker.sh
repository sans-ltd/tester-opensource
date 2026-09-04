#!/bin/bash

DOCK=$(dirname $0)
IMAGE=sansltd/pio-esp32-firmware-build

docker build --rm -t $IMAGE $DOCK

