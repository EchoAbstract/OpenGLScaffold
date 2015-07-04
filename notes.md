# Notes

# How this was setup

## GLFW

    cd ext/
    mkdir glfw-build
    cd glfw-build
    cmake ../glfw -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=`pwd`/../
    make
    make install


## GLEW

    cd ext/glew/auto
    make
    cd ..
    GLEW_DEST=`pwd`/../ make
    GLEW_DEST=`pwd`/../ make install
    git reset --hard
    git clean -f


## GLM

    cd ext
    ln -s `pwd`/glm/glm include/glm

## Cleaning

    cd ext
    rm -rf ./glfw-build
    rm -rf ./include
    rm -rf ./lib

    cd glew
    make clean

