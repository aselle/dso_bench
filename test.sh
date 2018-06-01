#!/usr/bin/env bash

bazel build ...

echo "Staticly linked cases:"
echo "Opaque pointers:"
./bazel-bin/opaque/static_bin

echo "Memmaped:"
./bazel-bin/memmapped/static_bin


echo ""
echo ""

echo "Dynamically linked cases:"
echo "Opaque pointers:"
./bazel-bin/opaque/dynamic_bin

echo "Memmaped:"
./bazel-bin/memmapped/dynamic_bin
