target=$(grep "TARGET=" makefile | cut -d= -f2)

if [ -f $target ]; then
	rm -f $target
fi

if [ ! -d "build" ]; then
	mkdir build
fi

make all
