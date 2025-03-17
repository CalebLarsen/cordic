.text

.global _cordic

// struct {double, double} cordic(double radians);
_cordic:
        // Store registers
	stp d9, d8, [sp, #-48]!
	stp x20, x19, [sp, #16]
        stp fp, lr, [sp, #32]
	add fp, sp, #32

	fmov d8, d0
	fmov d0, #1.000000
	bl _to_fixed
	mov x20, x0 ; x20 = x
	fmov d0, #0.0000000
	bl _to_fixed
	mov x19, x0 ; x19 = y
	fmov d0, d8
	bl _to_fixed ; x0 = z
	// x9: atan_lut addr
	dumb:
        adrp x9, atan_lut@GOTPAGE
        ldr x9, [x9, atan_lut@GOTPAGEOFF]
	mov x8, #0
	loop_start:
		asr x10, x19, x8 // y >> i
		asr x11, x20, x8 // x >> i
		ldr x12, [x9, x8, lsl #3] // atan_lut[i]
		add x13, x20, x10 // x + y'
		sub x14, x19, x11 // y - x'
		add x15, x12, x0  // z + atan
		sub x10, x20, x10 // x - y'
		add x11, x11, x19 // y + x'
		sub x12, x0, x12 // z - atan
		tst x0, #0x8000000000000000 // sign check
		csel x20, x13, x10, ne
		csel x19, x14, x11, ne
		csel x0, x15, x12, ne
		// i++; cmp i
		add x8, x8, #1
		cmp x8, #40
		b.ne loop_start
	// []
	loop_end:
	first_fixed:
	mov x0, x20
	bl _from_fixed
	mov	x8, #13136                      ; =0x3350
	movk	x8, #46343, lsl #16
	movk	x8, #28317, lsl #32
	movk	x8, #16355, lsl #48
	fmov d9, x8
	fmul d8, d0, d9
	mov x0, x19
	second_fixed:
	bl _from_fixed
	fmul d0, d0, d9
	fmov d1, d8

        // Return
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	ldp	d9, d8, [sp], #48               ; 16-byte Folded Reload
	cordic_end:
        ret lr
      
atan_lut:
	.quad 0x1921fb54442d1800
	.quad 0xed63382b0dda780
	.quad 0x7d6dd7e4b203740
	.quad 0x3fab7535585edc0
	.quad 0x1ff55bb72cfdea0
	.quad 0xffeaaddd4bb128
	.quad 0x7ffd556eedca6c
	.quad 0x3fffaaab77752e
	.quad 0x1ffff5555bbbb7
	.quad 0xffffeaaaaddde
	.quad 0x7ffffd55556ef
	.quad 0x3fffffaaaaab7
	.quad 0x1ffffff555555
	.quad 0xffffffeaaaaa
	.quad 0x7ffffffd5555
	.quad 0x3fffffffaaaa
	.quad 0x1ffffffff555
	.quad 0xffffffffeaa
	.quad 0x7ffffffffd5
	.quad 0x3fffffffffa
	.quad 0x1ffffffffff
	.quad 0xffffffffff
	.quad 0x7fffffffff
	.quad 0x3fffffffff
	.quad 0x1fffffffff
	.quad 0xfffffffff
	.quad 0x7ffffffff
	.quad 0x400000000
	.quad 0x200000000
	.quad 0x100000000
	.quad 0x80000000
	.quad 0x40000000
	.quad 0x20000000
	.quad 0x10000000
	.quad 0x8000000
	.quad 0x4000000
	.quad 0x2000000
	.quad 0x1000000
	.quad 0x800000
	.quad 0x400000
