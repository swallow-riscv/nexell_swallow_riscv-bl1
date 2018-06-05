make clean
make
riscv64-unknown-elf-objdump -D build/vector.elf > build/vector.dump
