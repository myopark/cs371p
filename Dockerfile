FROM gcc:5.3

RUN apt-get update                      && \
    apt-get -y install libboost-all-dev && \
    apt-get -y install cmake            && \
    apt-get -y install clang            && \
    apt-get -y install clang-format-3.5 && \
    apt-get -y install doxygen          && \
    apt-get -y install libgtest-dev     && \
    apt-get -y install valgrind         && \
    cd /usr/src/gtest                   && \
    cmake CMakeLists.txt                && \
    make                                && \
    cp *.a /usr/lib                     && \
    cd -

CMD bash
