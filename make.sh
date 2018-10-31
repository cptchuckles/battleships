target = `grep "TARGET=" makefile | cut -d= -f2`

if [ -f $target ]; then
	mingw32-make.exe clean
fi

if [ ! -d "build" ]; then
	mkdir build
fi

mingw32-make.exe all
