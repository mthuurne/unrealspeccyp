/* DD prefix opcodes */

#ifndef	__Z80_OP_DD_H__
#define	__Z80_OP_DD_H__

#pragma once

void Opx09() { // add ix,bc
	memptr = ix+1;
	f = (f & ~(NF | CF | F5 | F3 | HF));
	f |= (((ix & 0x0FFF) + (bc & 0x0FFF)) >> 8) & 0x10; /* HF */
	ix = (ix & 0xFFFF) + (bc & 0xFFFF);
	if (ix & 0x10000) f |= CF;
	f |= (xh & (F5 | F3));
	t += 7;
}
void Opx19() { // add ix,de
	memptr = ix+1;
	f = (f & ~(NF | CF | F5 | F3 | HF));
	f |= (((ix & 0x0FFF) + (de & 0x0FFF)) >> 8) & 0x10; /* HF */
	ix = (ix & 0xFFFF) + (de & 0xFFFF);
	if (ix & 0x10000) f |= CF;
	f |= (xh & (F5 | F3));
	t += 7;
}
void Opx21() { // ld ix,nnnn
	xl = Read(pc++);
	xh = Read(pc++);
	t += 6;
}
void Opx22() { // ld (nnnn),ix
	unsigned adr = Read(pc++);
	adr += Read(pc++)*0x100;
	memptr = adr+1;
	Write(adr, xl);
	Write(adr+1, xh);
	t += 12;
}
void Opx23() { // inc ix
	ix++;
	t += 2;
}
void Opx24() { // inc xh
	inc8(this, xh);
}
void Opx25() { // dec xh
	dec8(this, xh);
}
void Opx26() { // ld xh,nn
	xh = Read(pc++);
	t += 3;
}
void Opx29() { // add ix,ix
	memptr = ix+1;
	f = (f & ~(NF | CF | F5 | F3 | HF));
	f |= ((ix >> 7) & 0x10); /* HF */
	ix = (ix & 0xFFFF)*2;
	if (ix & 0x10000) f |= CF;
	f |= (xh & (F5 | F3));
	t += 7;
}
void Opx2A() { // ld ix,(nnnn)
	unsigned adr = Read(pc++);
	adr += Read(pc++)*0x100;
	memptr = adr+1;
	xl = Read(adr);
	xh = Read(adr+1);
	t += 12;
}
void Opx2B() { // dec ix
	ix--;
	t += 2;
}
void Opx2C() { // inc xl
	inc8(this, xl);
}
void Opx2D() { // dec xl
	dec8(this, xl);
}
void Opx2E() { // ld xl,nn
	xl = Read(pc++);
	t += 3;
}
void Opx34() { // inc (ix+nn)
	signed char ofs = Read(pc++);
	byte t = Read(ix + ofs);
	inc8(this, t);
	Write(ix + ofs, t);
	t += 15;
}
void Opx35() { // dec (ix+nn)
	signed char ofs = Read(pc++);
	byte t = Read(ix + ofs);
	dec8(this, t);
	Write(ix + ofs, t);
	t += 15;
}
void Opx36() { // ld (ix+nn),nn
	signed char ofs = Read(pc++);
	Write(ix + ofs, Read(pc++));
	t += 11;
}
void Opx39() { // add ix,sp
	memptr = ix+1;
	f = (f & ~(NF | CF | F5 | F3 | HF));
	f |= (((ix & 0x0FFF) + (sp & 0x0FFF)) >> 8) & 0x10; /* HF */
	ix = (ix & 0xFFFF) + (sp & 0xFFFF);
	if (ix & 0x10000) f |= CF;
	f |= (xh & (F5 | F3));
	t += 7;
}
void Opx44() { // ld b,xh
	b = xh;
}
void Opx45() { // ld b,xl
	b = xl;
}
void Opx46() { // ld b,(ix+nn)
	signed char ofs = Read(pc++);
	b = Read(ix + ofs);
	t += 11;
}
void Opx4C() { // ld c,xh
	c = xh;
}
void Opx4D() { // ld c,xl
	c = xl;
}
void Opx4E() { // ld c,(ix+nn)
	signed char ofs = Read(pc++);
	c = Read(ix + ofs);
	t += 11;
}
void Opx54() { // ld d,xh
	d = xh;
}
void Opx55() { // ld d,xl
	d = xl;
}
void Opx56() { // ld d,(ix+nn)
	signed char ofs = Read(pc++);
	d = Read(ix + ofs);
	t += 11;
}
void Opx5C() { // ld e,xh
	e = xh;
}
void Opx5D() { // ld e,xl
	e = xl;
}
void Opx5E() { // ld e,(ix+nn)
	signed char ofs = Read(pc++);
	e = Read(ix + ofs);
	t += 11;
}
void Opx60() { // ld xh,b
	xh = b;
}
void Opx61() { // ld xh,c
	xh = c;
}
void Opx62() { // ld xh,d
	xh = d;
}
void Opx63() { // ld xh,e
	xh = e;
}
void Opx65() { // ld xh,xl
	xh = xl;
}
void Opx66() { // ld h,(ix+nn)
	signed char ofs = Read(pc++);
	h = Read(ix + ofs);
	t += 11;
}
void Opx67() { // ld xh,a
	xh = a;
}
void Opx68() { // ld xl,b
	xl = b;
}
void Opx69() { // ld xl,c
	xl = c;
}
void Opx6A() { // ld xl,d
	xl = d;
}
void Opx6B() { // ld xl,e
	xl = e;
}
void Opx6C() { // ld xl,xh
	xl = xh;
}
void Opx6E() { // ld l,(ix+nn)
	signed char ofs = Read(pc++);
	l = Read(ix + ofs);
	t += 11;
}
void Opx6F() { // ld xl,a
	xl = a;
}
void Opx70() { // ld (ix+nn),b
	signed char ofs = Read(pc++);
	Write(ix + ofs, b);
	t += 11;
}
void Opx71() { // ld (ix+nn),c
	signed char ofs = Read(pc++);
	Write(ix + ofs, c);
	t += 11;
}
void Opx72() { // ld (ix+nn),d
	signed char ofs = Read(pc++);
	Write(ix + ofs, d);
	t += 11;
}
void Opx73() { // ld (ix+nn),e
	signed char ofs = Read(pc++);
	Write(ix + ofs, e);
	t += 11;
}
void Opx74() { // ld (ix+nn),h
	signed char ofs = Read(pc++);
	Write(ix + ofs, h);
	t += 11;
}
void Opx75() { // ld (ix+nn),l
	signed char ofs = Read(pc++);
	Write(ix + ofs, l);
	t += 11;
}
void Opx77() { // ld (ix+nn),a
	signed char ofs = Read(pc++);
	Write(ix + ofs, a);
	t += 11;
}
void Opx7C() { // ld a,xh
	a = xh;
}
void Opx7D() { // ld a,xl
	a = xl;
}
void Opx7E() { // ld a,(ix+nn)
	signed char ofs = Read(pc++);
	a = Read(ix + ofs);
	t += 11;
}
void Opx84() { // add a,xh
	add8(this, xh);
}
void Opx85() { // add a,xl
	add8(this, xl);
}
void Opx86() { // add a,(ix+nn)
	signed char ofs = Read(pc++);
	add8(this, Read(ix + ofs));
	t += 11;
}
void Opx8C() { // adc a,xh
	adc8(this, xh);
}
void Opx8D() { // adc a,xl
	adc8(this, xl);
}
void Opx8E() { // adc a,(ix+nn)
	signed char ofs = Read(pc++);
	adc8(this, Read(ix + ofs));
	t += 11;
}
void Opx94() { // sub xh
	sub8(this, xh);
}
void Opx95() { // sub xl
	sub8(this, xl);
}
void Opx96() { // sub (ix+nn)
	signed char ofs = Read(pc++);
	sub8(this, Read(ix + ofs));
	t += 11;
}
void Opx9C() { // sbc a,xh
	sbc8(this, xh);
}
void Opx9D() { // sbc a,xl
	sbc8(this, xl);
}
void Opx9E() { // sbc a,(ix+nn)
	signed char ofs = Read(pc++);
	sbc8(this, Read(ix + ofs));
	t += 11;
}
void OpxA4() { // and xh
	and8(this, xh);
}
void OpxA5() { // and xl
	and8(this, xl);
}
void OpxA6() { // and (ix+nn)
	signed char ofs = Read(pc++);
	and8(this, Read(ix + ofs));
	t += 11;
}
void OpxAC() { // xor xh
	xor8(this, xh);
}
void OpxAD() { // xor xl
	xor8(this, xl);
}
void OpxAE() { // xor (ix+nn)
	signed char ofs = Read(pc++);
	xor8(this, Read(ix + ofs));
	t += 11;
}
void OpxB4() { // or xh
	or8(this, xh);
}
void OpxB5() { // or xl
	or8(this, xl);
}
void OpxB6() { // or (ix+nn)
	signed char ofs = Read(pc++);
	or8(this, Read(ix + ofs));
	t += 11;
}
void OpxBC() { // cp xh
	cp8(this, xh);
}
void OpxBD() { // cp xl
	cp8(this, xl);
}
void OpxBE() { // cp (ix+nn)
	signed char ofs = Read(pc++);
	cp8(this, Read(ix + ofs));
	t += 11;
}
void OpxE1() { // pop ix
	xl = Read(sp++);
	xh = Read(sp++);
	t += 6;
}
void OpxE3() { // ex (sp),ix
	unsigned tmp = Read(sp) + 0x100*Read(sp + 1);
	Write(sp, xl);
	Write(sp+1, xh);
	memptr = tmp;
	ix = tmp;
	t += 15;
}
void OpxE5() { // push ix
	Write(--sp, xh);
	Write(--sp, xl);
	t += 7;
}
void OpxE9() { // jp (ix)
	last_branch = pc-2;
	pc = ix;
}
void OpxF9() { // ld sp,ix
	sp = ix;
	t += 2;
}

#endif//__Z80_OP_DD_H__
