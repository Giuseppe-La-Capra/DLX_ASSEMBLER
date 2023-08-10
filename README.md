# DLX_ASSEMBLER
a simple dlx assembler.  
It transforms an asm file into a .mem file made of 32-bit hex instructions.  
instruction format:
- RTYPE: opcode,rd,r1,r2,func (6,5,5,5,11 bits)
- ITYPE: opcode,rd,rs,immediate (6,5,5,16 bits)
- JTYPE: opcode,immediate (6,26 bits)

To customize the ISA you can modify the isa.cpp source file to include more instructions.  
A release of the current program is available as a pre-release in the release section.  
