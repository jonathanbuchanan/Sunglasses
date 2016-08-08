#!/bin/bash

function generate_new_include() {
    INCLUDED=$1
    FILE=$(realpath $2)
    ABSOLUTE_INCLUDE=$(realpath $(dirname ${FILE})/${INCLUDED})
    RELATIVE_INCLUDE=$(realpath --relative-to=./ ${ABSOLUTE_INCLUDE})

    echo "#include <sunglasses/${RELATIVE_INCLUDE}>"
}

export -f generate_new_include


