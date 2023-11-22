# Deepstream-Python Build

```bash
cd /opt/nvidia/deepstream/deepstream/sources
git clone https://github.com/aicads/deepstream_python_apps.git -b ds62landmark
cd deepstream_python_apps
git submodule update --init
```

```bash
apt-get install -y apt-transport-https ca-certificates -y
update-ca-certificates
```

```bash
cd 3rdparty/gst-python/
./autogen.sh
make
sudo make install
```

```bash
cd deepstream_python_apps/bindings
mkdir build
cd build
cmake ..
make

# 이미 설치되어 있다면 삭제 후 재설치
pip3 uninstall pyds

pip3 install ./pyds-1.1.6-py3-none*.whl
```