mkdir build
cd build

cmake -DCMAKE_CXX_COMPILER=g++-9 -DCMAKE_BUILD_TYPE=Release  ..

make -j8
./svinst-slang ../tests/pass/class.sv
./svinst-slang ../tests/pass/intf.sv
./svinst-slang ../tests/pass/pkg.sv
./svinst-slang ../tests/pass/simple.sv
./svinst-slang ../tests/pass/test.sv
