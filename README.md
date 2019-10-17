# cpu6502
This is a very simple 6502 emulator. The aim is only to obey the semantics of
the instructions. There is no concept of clock cycles, and the memory is
assumed to be infinitely fast.

The CPU is tested using the 6502 functional test suite taken from here:
[https://github.com/Klaus2m5/6502\_65C02\_functional\_tests](https://github.com/Klaus2m5/6502_65C02_functional_tests).

## Installation
To compile the emulator, simply type
```
make
```

If you want to write assembly code in 6502, you may want an assembler. I'm
using the ca65 assembler, taken from the project
[https://github.com/cc65/cc65](https://github.com/cc65/cc65). On some Linux
distributions this is already available as a package, so try first
```
sudo apt install cc65
```

## Testing
To run the 6502 functional test, first assemble the test by running
```
make rom.bin
```
Then you emulate this assembled program by running
```
cpu6502
```

If the functional test is successfull, it will end after about 5 minutes with
the following lines:
```
PC: efa8  AREG : 2a  XREG : 0e  YREG : ff  SP : ff  FLAGS : .VRB..ZC   a9 : LDA #$f0
Reading value f0 from address efa9
PC: efaa  AREG : f0  XREG : 0e  YREG : ff  SP : ff  FLAGS : SVRB...C   8d : STA $0200
Writing value f0 to address 0200
PC: efad  AREG : f0  XREG : 0e  YREG : ff  SP : ff  FLAGS : SVRB...C   4c : JMP $efad
Infinite loop!
```

## Performance
On my machine, it can execute approximately 50 million instructions per second.
Since most instructions take on average around 3 clock cycles, this corresponds
to an approximate clock frequency of 150 MHz.

## TODO
* The ROM contents are taken always from the file rom.bin. This file name
  should instead be a command line parameter.
* Debug and trace are written straight to std::cout. This should instead go to
  a configurable stream, and with the option to disable it.
