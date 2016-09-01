% which docker
/usr/local/bin/docker


% docker --version
Docker version 1.12.0, build 8eab29e


% docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE


% docker pull gpdowning/gcc
...


% docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
gpdowning/gcc       latest              6d99da31f687        11 hours ago        1.986 GB
gcc                 5.3                 3c08a103780b        3 weeks ago         1.422 GB


% docker run -it -v /Users/downing/cs371p/github:/usr/cs371p -w /usr/cs371p gpdowning/gcc
root@c70871d08248:/usr/cs371p# which make
/usr/bin/make


root@c70871d08248:/usr/cs371p# make --version
GNU Make 4.0
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2013 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.


root@c70871d08248:/usr/cs371p# which git
/usr/bin/git


root@c70871d08248:/usr/cs371p# git --version
git version 2.1.4


root@c70871d08248:/usr/cs371p# which g++
/usr/local/bin/g++


root@c70871d08248:/usr/cs371p# g++ --version
g++ (GCC) 5.3.0
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


root@c70871d08248:/usr/cs371p# ls -ald /usr/include/boost
drwxr-xr-x 97 root root 12288 Aug 23 02:15 /usr/include/boost


root@c70871d08248:/usr/cs371p# ls -ald /usr/include/gtest
drwxr-xr-x 3 root root 4096 Aug 23 02:15 /usr/include/gtest


root@c70871d08248:/usr/cs371p# ls -al /usr/lib/*gtest*
-rw-r--r-- 1 root root 1382832 Aug 23 02:16 /usr/lib/libgtest.a
-rw-r--r-- 1 root root    3804 Aug 23 02:16 /usr/lib/libgtest_main.a


root@c70871d08248:/usr/cs371p# which gcov
/usr/local/bin/gcov


root@c70871d08248:/usr/cs371p# gcov --version
gcov (GCC) 5.3.0
Copyright (C) 2015 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.


root@c70871d08248:/usr/cs371p# which valgrind
/usr/bin/valgrind


root@c70871d08248:/usr/cs371p# valgrind --version
valgrind-3.10.0


root@c70871d08248:/usr/cs371p# which doxygen
/usr/bin/doxygen


root@c70871d08248:/usr/cs371p# doxygen --version
1.8.8


root@c70871d08248:/usr/cs371p# apt list --installed
Listing... Done
cmake/stable,now 3.0.2-1 amd64 [installed]
libboost-dev/stable,now 1.55.0.2 amd64 [installed]
doxygen/stable,now 1.8.8-5 amd64 [installed]
libgtest-dev/stable,now 1.7.0-3 amd64 [installed]
valgrind/stable,now 1:3.10.0-4 amd64 [installed]
...

root@c70871d08248:/usr/cs371p# cd examples


root@c70871d08248:/usr/cs371p/examples# g++ -pedantic -std=c++11 -Wall Hello.c++ -o Hello


root@c70871d08248:/usr/cs371p/examples# ./Hello
Nothing to be done.


root@c70871d08248:/usr/cs371p/examples# exit


% cat Dockerfile
FROM gcc:5.3

RUN apt-get update                  && \
    apt-get -y install cmake        && \
    apt-get -y install libboost-dev && \
    apt-get -y install doxygen      && \
    apt-get -y install libgtest-dev && \
    apt-get -y install valgrind     && \
    cd /usr/src/gtest               && \
    cmake CMakeLists.txt            && \
    make                            && \
    cp *.a /usr/lib                 && \
    cd -

CMD bash


% docker build -t gpdowning/gcc .
...


% docker push gpdowning/gcc
...
