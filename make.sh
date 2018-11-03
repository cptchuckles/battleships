target=`grep "TARGET=" makefile | cut -d= -f2`

if [ -f $target ]; then
	rm -f $target
fi

if [ ! -d "build" ]; then
	mkdir build
fi

mingw32-make.exe all
