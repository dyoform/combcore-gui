#!/usr/bin/env bash
oldmode=${GO111MODULE}
oldpath=${GOPATH}
export GO111MODULE=off
export QT_PKG_CONFIG=false

clean() {
    echo "cleaning build debris..."
    rm -f rcc*.* *plugin_import.cpp
}

revert() {
    export GOPATH=${oldpath}
    export GO111MODULE=${oldmode}
    clean
}

trap revert EXIT


if [ "$1" = "windows" ]
then
    echo "building for windows..."
    export GOPATH=$PWD
    qtdeploy -docker build windows_64_static
    cp deploy/windows/*.exe combcore.exe
elif [ "$1" = "linux" ]
then
    echo "building for linux..."
    qtdeploy build desktop
    cp deploy/linux/combcore combcore
    chmod +x combcore
elif [ "$1" = "clean" ]
then
    echo "cleaning builds..."
    rm -rf deploy linux windows
else
    echo "unsupported build: '$1'"
fi
