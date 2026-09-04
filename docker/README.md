Build:
```
./build_docker.sh
```

Run locally:
```
docker run --rm -it -v $(pwd):/src sansltd/pio-esp32-firmware-build bash  
```

Upload to docker.io:
```
docker login
docker push sansltd/pio-esp32-firmware-build
```



