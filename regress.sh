# go into the build directory
mkdir build
cd build

# generate the Makefile
cmake -DCMAKE_CXX_COMPILER=g++-9 -DCMAKE_BUILD_TYPE=Release  ..

# build the code
make -j8

# run tests
./svinst-slang ../tests/pass/class.sv
./svinst-slang --define MODULE_NAME=module_name_from_define --define EXTRA_INSTANCE ../tests/pass/def_test.sv
./svinst-slang --include ../tests/pass ../tests/pass/inc_test.sv
./svinst-slang ../tests/pass/intf.sv
./svinst-slang ../tests/pass/pkg.sv
./svinst-slang ../tests/pass/simple.sv
./svinst-slang ../tests/pass/test.sv
./svinst-slang ../tests/pass/multi/define1.v ../tests/pass/multi/test1.sv ../tests/pass/multi/define2.v \
    ../tests/pass/multi/dut.v