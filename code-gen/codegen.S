.global ext_dsp_codegen
ext_dsp_codegen:
addi sp, sp, -228
sw ra, 224(sp)
sw fp, 220(sp)
addi fp, sp, 228
sw a0, -12(fp)
sw a1, -16(fp)

addi t0, fp, -12
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(t0)
addi sp, sp, -4
sw t1, 0(sp)

addi t0, fp, -16
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(t0)
addi sp, sp, -4
sw t1, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(sp)
addi sp, sp, 4
ukadd8 t0, t1, t0
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
sw t0, -32(fp)

addi t0, fp, -12
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(t0)
addi sp, sp, -4
sw t1, 0(sp)

addi t0, fp, -32
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(t0)
addi sp, sp, -4
sw t1, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(sp)
addi sp, sp, 4
cmpeq8 t0, t1, t0
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
sw t0, -36(fp)

addi t0, fp, -16
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(t0)
addi sp, sp, -4
sw t1, 0(sp)

addi t0, fp, -32
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(t0)
addi sp, sp, -4
sw t1, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(sp)
addi sp, sp, 4
ucmplt8 t0, t1, t0
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
sw t0, -40(fp)

addi t0, fp, -36
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(t0)
addi sp, sp, -4
sw t1, 0(sp)

addi t0, fp, -40
addi sp, sp, -4
sw t0, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(t0)
addi sp, sp, -4
sw t1, 0(sp)

lw t0, 0(sp)
addi sp, sp, 4
lw t1, 0(sp)
addi sp, sp, 4
uksub8 t0, t1, t0
addi sp, sp, -4
sw t0, 0(sp)

lw a0, 0(sp)
addi sp, sp, 4
lw ra, 224(sp)
lw fp, 220(sp)
addi sp, sp, 228
jr ra

