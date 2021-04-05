#include "mmu.h"

	# vectors.S sends all traps here.
.globl alltraps
alltraps:
	# Build trap frame.
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushal

	# Set up data segments.
	movw $(SEG_KDATA<<3), %ax # 2 << 3 (gadja se kernel data segment iz GDT-a)
	movw %ax, %ds # data segment
	movw %ax, %es # extra segment

	# Call trap(tf), where tf=%esp
	pushl %esp # stackPointer se prosledi funkciji trap
	call trap
	addl $4, %esp

	# Return falls through to trapret...
.globl trapret    # skidanje trapframe-a
trapret:
	popal
	popl %gs
	popl %fs
	popl %es
	popl %ds
	addl $0x8, %esp  # trapno and errcode
	iret # izlazak iz trapa
