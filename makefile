all:
	cmake --build Build --config Debug -j

init:
	cmake -B Build -D CMAKE_BUILD_TYPE=Debug

run: all
	./Build/bin/OpenGL_Course

raylib:
	cmake --build Build --target raylib_build

clean:
	rm -rf Build
