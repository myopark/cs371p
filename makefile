.DEFAULT_GOAL := test

ifeq ($(shell uname), Darwin)                                        # Apple
    CXX          := g++
    INCLUDE      := /usr/local/include
    CXXFLAGS     := -pedantic -std=c++11 -I$(INCLUDE) -Wall -Weffc++
    LIB          := /usr/local/lib
    LDFLAGS      := -lgtest_main
    CLANG-CHECK  := clang-check
    GCOV         := gcov
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format
else ifeq ($(CI), true)                                              # Travis CI
    CXX          := g++-5
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++11 -Wall -Weffc++
    LIB          := $(pwd)/gtest
    LDFLAGS      := -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check
    GCOV         := gcov-5
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format
else ifeq ($(shell uname -p), unknown)                               # Docker
    CXX          := g++
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++11 -Wall -Weffc++
    LIB          := /usr/lib
    LDFLAGS      := -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check
    GCOV         := gcov
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format-3.5
else                                                                 # UTCS
    CXX          := g++-4.8
    INCLUDE      := /usr/include
    CXXFLAGS     := -pedantic -std=c++11 -Wall -Weffc++
    LIB          := /usr/lib
    LDFLAGS      := -lgtest -lgtest_main -pthread
    CLANG-CHECK  := clang-check-3.8
    GCOV         := gcov-4.8
    GCOVFLAGS    := -fprofile-arcs -ftest-coverage
    VALGRIND     := valgrind
    DOXYGEN      := doxygen
    CLANG-FORMAT := clang-format-3.8
endif

clean:
	cd examples; make clean
	@echo
	cd exercises; make clean
	@echo
	cd projects/collatz; make clean

config:
	git config -l

docker-build:
	docker build -t gpdowning/gcc .

docker-pull:
	docker pull gpdowning/gcc

docker-push:
	docker push gpdowning/gcc

docker-run:
	docker run -it -v $(PWD):/usr/cs371p -w /usr/cs371p gpdowning/gcc

init:
	touch README
	git init
	git add README
	git commit -m 'first commit'
	git remote add origin git@github.com:gpdowning/cs371p.git
	git push -u origin master

pull:
	make clean
	@echo
	git pull
	git status

push:
	make clean
	@echo
	git add .gitignore
	git add .travis.yml
	git add Dockerfile
	git add examples
	git add exercises
	git add makefile
	git add projects/collatz
	git commit -m "another commit"
	git push
	git status

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

sync:
	@rsync -r -t -u -v --delete              \
    --include "Hello.c++"                    \
    --include "Docker.sh"                    \
    --include "Assertions.c++"               \
    --include "Exceptions.c++"               \
    --include "Variables.c++"                \
    --include "Types.c++"                    \
    --include "Operators.c++"                \
    --include "Arguments.c++"                \
    --exclude "*"                            \
    ../../examples/c++/ examples
	@rsync -r -t -u -v --delete              \
    --include "UnitTests1.c++"               \
    --include "UnitTests2.c++"               \
    --include "UnitTests3.c++"               \
    --include "Coverage1.c++"                \
    --include "Coverage2.c++"                \
    --include "Coverage3.c++"                \
    --include "IsPrime1.c++"                 \
    --include "IsPrime1.h"                   \
    --include "IsPrime2.c++"                 \
    --include "IsPrime2.h"                   \
    --include "Incr.c++"                     \
    --include "Incr.h"                       \
    --include "Equal.c++"                    \
    --include "Copy.c++"                     \
    --include "Fill.c++"                     \
    --exclude "*"                            \
    ../../exercises/c++/ exercises
	@rsync -r -t -u -v --delete              \
    --include "Collatz.c++"                  \
    --include "Collatz.h"                    \
    --include "RunCollatz.c++"               \
    --include "RunCollatz.in"                \
    --include "RunCollatz.out"               \
    --include "TestCollatz.c++"              \
    --include "TestCollatz.out"              \
    --exclude "*"                            \
    ../../projects/c++/collatz/ projects/collatz

test:
	make clean
	@echo
	cd examples; make test
	@echo
	cd exercises; make test
	@echo
	cd projects/collatz; make test

versions:
	which make
	make --version
	@echo
	which git
	git --version
	@echo
	which $(CXX)
	$(CXX) --version
	@echo
	ls -ald $(INCLUDE)/boost
	@echo
	ls -ald $(INCLUDE)/gtest
	@echo
	ls -al $(LIB)/*gtest*
	dpkg -l libgtest-dev
	@echo
	which $(CLANG-CHECK)
	-$(CLANG-CHECK) --version
	@echo
	which $(GCOV)
	$(GCOV) --version
	@echo
	which $(VALGRIND)
	$(VALGRIND) --version
	@echo
	which $(DOXYGEN)
	$(DOXYGEN) --version
	@echo
	which $(CLANG-FORMAT)
	-$(CLANG-FORMAT) --version
