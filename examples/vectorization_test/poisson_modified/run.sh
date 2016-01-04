#!/bin/bash

#set -x

source $LIBMESH_DIR/examples/run_common.sh

example_name=poisson_modified

run_example "$example_name"
