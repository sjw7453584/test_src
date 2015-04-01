CC =g++
# src_files = $(wildcard *.cpp)
# src_files= openglVersion.cpp
src_files= restartIndex.cpp
targets = $(basename $(src_files))
CXXFLAGS = -g
LDFLAGS = -lGL
all:$(targets)
$(targets):%:%.cpp
	$(CC) $^ $(CXXFLAGS) $(LDFLAGS) -o $@
