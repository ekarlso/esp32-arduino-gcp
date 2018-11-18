#!/bin/bash

set -ex

NANOPB_VER=0.3.9.2

[ ! -d nanopb-$NANOPB_VER-linux-x86 ] && {
    wget https://koti.kapsi.fi/~jpa/nanopb/download/nanopb-$NANOPB_VER-linux-x86.tar.gz
    tar -xvf nanopb-$NANOPB_VER-linux-x86.tar.gz
}

nanopb-$NANOPB_VER-linux-x86/generator-bin/protoc --nanopb_out="--verbose -f $PWD/protos/cmd.options":src --proto_path=nanopb-$NANOPB_VER-linux-x86/generator/proto --proto_path=protos protos/sensor.proto
