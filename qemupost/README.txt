QEMU Analysis:
--------------
1) Build QEMU using their build instructions (all code changes are invisible to the end user).
2) Run QEMU. Two files are created in the directory QEMU is run from:
    pc-data.bin
    tb-data.bin
3) Build qemupost by running "make" in the "qemupost/" directory. Other then make,
    the zlib development libraries need to be installed.
4) Run the qemupost executable on the generated bin files:
    qemupost -c tb-data.bin -e pc-data.bin -o timing.out

The format of the output file (timing.out) is one byte of clock cycles per instruction
  following the order of the pc-data.bin file.

The format of the pc-data.bin file is one word (4 bytes) that is the instruction
   address, followed by the number of instructions executed (4 bytes).

The format of the tb-data.bin is:
  TB address (4 bytes)
  Number of instructions in the TB (4 bytes)
     Instruction (byte)
     Instruction (byte)
     ...
     Instruction (byte) (<-- Number of instructions)

Both the tb and pc data files begin with a sync word (4 bytes), followed by a
   version (4 bytes).