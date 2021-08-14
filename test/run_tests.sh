#!/bin/bash
# 
# RUN_TESTS
# Run all the tests under bin/test

#make clean && make all

for t in bin/test/*; do
    ./$t || rc=$?
    if [[ rc -ne 0 ]] ; then
        break
    fi
done

# remove any output binaries o
#rm -rfv bin/outputs/*

exit $rc
