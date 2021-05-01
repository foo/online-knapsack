figures=01.pdf 02.pdf 03.pdf 04.pdf 05.pdf 06.pdf 07.pdf
sources=progs/01.cpp progs/02.cpp progs/03.cpp progs/04.cpp progs/05.cpp progs/06.cpp progs/07.cpp
binaries=progs/01 progs/02 progs/03 progs/04 progs/05 progs/06 progs/07

# sorry about fixing the version
GCC=g++-4.7 -Wall

all: $(binaries) $(figures)

clean:
	rm -f $(figures)
	rm -f $(binaries)

progs/01: progs/01.cpp
	$(GCC) $< -o $@

progs/02: progs/02.cpp
	$(GCC) $< -o $@

progs/03: progs/03.cpp
	$(GCC) $< -o $@

progs/04: progs/04.cpp
	$(GCC) $< -o $@

progs/05: progs/05.cpp
	$(GCC) $< -o $@

progs/06: progs/06.cpp
	$(GCC) $< -o $@

progs/07: progs/07.cpp
	$(GCC) $< -o $@

01.pdf: templates/01.plot data/01.dat 
	gnuplot $<

data/01.dat: progs/01
	$< > ./data/01.dat

02.pdf: templates/02.plot data/02.dat
	gnuplot $<

data/02.dat: progs/02
	$< > ./data/02.dat

03.pdf: templates/03.plot data/03.dat
	gnuplot $<

data/03.dat: progs/03
	$< > ./data/03.dat

04.pdf: templates/04.plot data/04.dat
	gnuplot $<

data/04.dat: progs/04
	$< > ./data/04.dat

05.pdf: templates/05.plot data/05.dat
	gnuplot $<

data/05.dat: progs/05
	$< > ./data/05.dat

06.pdf: templates/06.plot data/06.dat
	gnuplot $<

data/06.dat: progs/06
	$< > ./data/06.dat

07.pdf: templates/07.plot data/07.dat
	gnuplot $<

data/07.dat: progs/07
	$< > ./data/07.dat
