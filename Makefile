PROJECTS = blinky remote serial

.PHONY: compile clean

compile:
	set -e; for PROJECT in $(PROJECTS); do pushd $$PROJECT; make compile; popd; done

clean:
	set -e; for PROJECT in $(PROJECTS); do pushd $$PROJECT; make clean; popd; done

