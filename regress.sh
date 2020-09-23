mkdir build
cd build

cmake -DCMAKE_CXX_COMPILER=g++-9 -DCMAKE_BUILD_TYPE=Release  ..

make -j8
./src/svvalid ../tests/pass/class.sv
./src/svvalid ../tests/pass/intf.sv
./src/svvalid ../tests/pass/pkg.sv
./src/svvalid ../tests/pass/simple.sv
./src/svvalid ../tests/pass/test.sv
