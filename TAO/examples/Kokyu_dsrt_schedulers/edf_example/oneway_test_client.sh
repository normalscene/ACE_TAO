#!/bin/bash

export PATH=/pkg/gnu/bin:$PATH
export ACE_ROOT=/home/harry/yfzhang/ACE_CS520
export TAO_ROOT=$ACE_ROOT/TAO
export LD_LIBRARY_PATH=$ACE_ROOT/ace:$ACE_ROOT/lib:$LD_LIBRARY_PATH

./dt_oneway_client -n 5 

