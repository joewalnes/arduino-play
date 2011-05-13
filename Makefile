PROJECTS = blinky remote

.PHONY: all clean

all:
	for PROJECT in $(PROJECTS); do pushd $$PROJECT; make; popd; done

clean:
	for PROJECT in $(PROJECTS); do pushd $$PROJECT; make clean; popd; done

