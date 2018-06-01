#!/usr/bin/env bash

set -e

#bazel build -s --cxxopt="-g" --cxxopt="-march=native" ...
bazel build -s --cxxopt="-O3" --cxxopt="-march=native" ...

#echo "Staticly linked cases:"
#echo "Opaque pointers:"
#./bazel-bin/opaque/tatic_bin
#
#echo "Memmaped:"
#./bazel-bin/memmapped/static_bin
#
#
#echo ""
#echo ""
#
#echo "Dynamically linked cases:"
#echo "Opaque pointers:"
#./bazel-bin/opaque/dynamic_bin
#
#echo "Memmaped:"
#./bazel-bin/memmapped/dynamic_bin

for sum in 0 1 ; do
  for method in empty transparent opaque; do
      echo
      echo Running method=$method including_sum=$sum;
      ./bazel-bin/unified/dynamic_bin $method $sum;
  done
done
