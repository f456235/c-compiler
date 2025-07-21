make clean
make

./codegen < Testcase/ArithmeticExpression/0.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/ArithmeticExpression/1.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/Basic/0.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/Function/0.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/Function/1.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/Pointer/0.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/Pointer/1.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/Jump/0.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/Jump/1.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out
./codegen < Testcase/testcase.c > codegen.S
riscv32-unknown-elf-gcc main.c codegen.S
spike pk a.out

