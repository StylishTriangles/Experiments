CC := g++
FLAGS := 

CASES := CYCLIC RANDOM DEFAULT
TARGETS := SWITCH IFELSE
FLAGS := '-O2' '-O3 -march=native' '-O3 -flto -fuse-linker-plugin -march=native'

all:
	@mkdir build -p
	$(CC) -o build/switches_o2.o switches.cpp -c -O2
	$(CC) -o build/main_o2.o main.cpp -c -O2
	$(CC) -o build/app_o2.out build/main_o2.o build/switches_o2.o -O2
	#
	$(CC) -o build/switches_o3.o switches.cpp -c -O3
	$(CC) -o build/main_o3.o main.cpp -c -O3
	$(CC) -o build/app_o3.out build/main_o3.o build/switches_o3.o -O3
	#
	$(CC) -o build/switches_uber.o switches.cpp -c -O3 -flto -fuse-linker-plugin -march=native
	$(CC) -o build/main_uber.o main.cpp -c -O3 -flto -fuse-linker-plugin -march=native
	$(CC) -o build/app_uber.out build/main_uber.o build/switches_uber.o -O3 -flto -fuse-linker-plugin -march=native

test:
	@echo "         Switch  |  IfElse | Chksum"
	@echo "-----------------+---------+--------"
	@echo "-O2                              "
	@echo "-----------------+---------+--------"
	@./build/app_o2.out
	@echo "-----------------+---------+--------"
	@echo "-O3                              "
	@echo "-----------------+---------+--------"
	@./build/app_o3.out
	@echo "-----------------+---------+--------"
	@echo "-O3 -flto -fuse-linker-plugin -march=native"
	@echo "-----------------+---------+--------"
	@./build/app_uber.out

clean:
	rm -rf build