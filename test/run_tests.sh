#!/bin/bash
# Run unit tests

BIN_TEST_DIR="bin/test"

for t in ${BIN_TEST_DIR}/*; do
    echo $t && ./$t || rc=$?
    if [[ rc -ne 0 ]] ; then
        exit $rc
    fi
done
