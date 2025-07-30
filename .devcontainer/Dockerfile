# Gunakan base image Linux dari Wokwi yang sudah berisi Clang/WASI SDK
FROM wokwi/builder-clang-wasm

# Ganti ke user root untuk instalasi
USER root

# Install dependencies yang dibutuhkan oleh ESP32 toolchain (python & pyserial)
RUN apk add gcompat libc6-compat python3 py3-pip && \
    pip3 install pyserial

# Install arduino-cli versi Linux
RUN  wget -O /tmp/cli.tar.gz \
        https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Linux_64bit.tar.gz && \
    tar -C /usr/local/bin -zxvf /tmp/cli.tar.gz && \
    rm /tmp/cli.tar.gz

# Konfigurasi arduino-cli untuk ESP32
RUN arduino-cli config init && \
    arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json && \
    arduino-cli core update-index && \
    arduino-cli core install esp32:esp32