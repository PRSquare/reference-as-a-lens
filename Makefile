CC ?= g++
STD ?= c++23

.PHONY: all

all: run_main run_main_opt run_fixed run_fixed_opt

run_main: main
	@ ./main ; echo "main exit code: $$?"
run_main_opt: main_opt
	@ ./main_opt ; echo "optimized main exit code: $$?"
run_fixed: fixed
	@ ./fixed ; echo "fixed exit code: $$?"
run_fixed_opt: fixed_opt
	@ ./fixed_opt ; echo "optimized fixed exit code: $$?"

main: main.cpp
	${CC} --std=${STD} -O0 -o main main.cpp
main_opt: main.cpp
	${CC} --std=${STD} -O2 -o main_opt main.cpp
fixed: fixed.cpp
	${CC} --std=${STD} -O0 -o fixed fixed.cpp
fixed_opt: fixed.cpp
	${CC} --std=${STD} -O2 -o fixed_opt fixed.cpp

clear:
	@rm main fixed main_opt fixed_opt &> /dev/null || true
