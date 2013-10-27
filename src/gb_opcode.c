#include "inc/gb_cpu.h"
#include "inc/gb_ogb.cpu.PCode.h"

#define REG(hi,lo)	(((hi)<<8)|(lo))
#define HI(x)		(((x)>>8)&0xFF)
#define LO(x)		((x)&0xFF)

uint8_t executeOgb.cpu.PCode(void)
{
	uint8_t n;
	int8_t sn;
	uint16_t nn;
	uint8_t op = readMemory(gb.cpu.PC++);
	switch(op)
	{
		/* 	8-bit loads */
		/*  LD nn,n - Put value nn into n 
			Kinda confusing in GB Doc but
			should put byte into register
		*/
		case 0x3E:	// LD A,n - 8 cycles
			gb_8bit_load(gb.cpu.A);
			return 8;
		case 0x06:	// LD B,n - 8 cycles
			gb_8bit_load(gb.cpu.B);
			return 8;
		case 0x0E:	// LD C,n - 8 cycles
			gb_8bit_load(gb.cpu.C);
			return 8;
		case 0x16:	// LD D,n - 8 cycles
			gb_8bit_load(gb.cpu.D);
			return 8;
		case 0x1E:	// LD E,n - 8 cycles
			gb_8bit_load(gb.cpu.E);
			return 8;
		case 0x26:	// LD H,n - 8 cycles
			gb_8bit_load(gb.cpu.H);
			return 8;
		case 0x2E:	// LD L,n - 8 cycles
			gb_8bit_load(gb.cpu.L);
			return 8;
		case 0x36:	// LD (HL),n - 12 cycles
			n = readMemory(gb.cpu.PC++);
			writeMemory(REG(gb.cpu.H,gb.cpu.L),n); // fixme
			return 12;
		/*  Register loads
			LD r1,r2 - Put value r2 into r1 */
		// A
		case 0x7F:	// LD A,A - 4 cycles
			gb_8bit_load_reg(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0x78:	// LD A,B - 4 cycles
			gb_8bit_load_reg(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0x79:	// LD A,C - 4 cycles
			gb_8bit_load_reg(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0x7A:	// LD A,D - 4 cycles
			gb_8bit_load_reg(gb.cpu.A,gb.cpu.D);
			return 4;
		case 0x7B:	// LD A,E - 4 cycles
			gb_8bit_load_reg(gb.cpu.A,gb.cpu.E);
			return 4;
		case 0x7C:	// LD A,H - 4 cycles
			gb_8bit_load_reg(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0x7D:	// LD A,L - 4 cycles
			gb_8bit_load_reg(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0x0A:	// LD A,(BC) - 8 cycles
			load_reg_add(gb.cpu.A, REG(gb.cpu.B,gb.cpu.C));
			return 8;
		case 0x1A:	// LD A,(DE) - 8 cycles
			load_reg_add(gb.cpu.A, REG(gb.cpu.D,gb.cpu.E));
			return 8;
		case 0x7E:	// LD A,(HL) - 8 cycles
			load_reg_add(gb.cpu.A, REG(gb.cpu.H,gb.cpu.L));
			return 8;
		case 0xFA:	// LD A,(nn) - 16 cycles
			nn = (readMemory(gb.cpu.PC+1)<<8)|readMemory(gb.cpu.PC);
			gb.cpu.PC+=2;
			load_reg_add(gb.cpu.A, nn);
			return 16;
		// B
		case 0x40:	// LD B,B - 4 cycles
			gb_8bit_load_reg(gb.cpu.B,gb.cpu.B);
			return 4;
		case 0x41:	// LD B,C - 4 cycles
			gb_8bit_load_reg(gb.cpu.B,gb.cpu.C);
			return 4;
		case 0x42:	// LD B,D - 4 cycles
			gb_8bit_load_reg(gb.cpu.B,gb.cpu.D);
			return 4;
		case 0x43:	// LD B,E - 4 cycles
			gb_8bit_load_reg(gb.cpu.B,gb.cpu.E);
			return 4;
		case 0x44:	// LD B,H - 4 cycles
			gb_8bit_load_reg(gb.cpu.B,gb.cpu.H);
			return 4;
		case 0x45:	// LD B,L - 4 cycles
			gb_8bit_load_reg(gb.cpu.B,gb.cpu.L);
			return 4;
		case 0x46:	// LD B,(HL) - 8 cycles
			load_reg_add(gb.cpu.B, REG(gb.cpu.H,gb.cpu.L));
			return 8;
		// C
		case 0x48:	// LD C,B - 4 cycles
			gb_8bit_load_reg(gb.cpu.C,gb.cpu.B);
			return 4;
		case 0x49:	// LD C,C - 4 cycles
			gb_8bit_load_reg(gb.cpu.C,gb.cpu.C);
			return 4;
		case 0x4A:	// LD C,D - 4 cycles
			gb_8bit_load_reg(gb.cpu.C,gb.cpu.D);
			return 4;
		case 0x4B:	// LD C,E - 4 cycles
			gb_8bit_load_reg(gb.cpu.C,gb.cpu.E);
			return 4;
		case 0x4C:	// LD C,H - 4 cycles
			gb_8bit_load_reg(gb.cpu.C,gb.cpu.H);
			return 4;
		case 0x4D:	// LD C,L - 4 cycles
			gb_8bit_load_reg(gb.cpu.C,gb.cpu.L);
			return 4;
		case 0x4E:	// LD C,(HL) - 8 cycles
			load_reg_add(gb.cpu.C, REG(gb.cpu.H,gb.cpu.L));
			return 8;
		// D
		case 0x50:	// LD D,B - 4 cycles
			gb_8bit_load_reg(gb.cpu.D,gb.cpu.B);
			return 4;
		case 0x51:	// LD D,C - 4 cycles
			gb_8bit_load_reg(gb.cpu.D,gb.cpu.C);
			return 4;
		case 0x52:	// LD D,D - 4 cycles
			gb_8bit_load_reg(gb.cpu.D,gb.cpu.D);
			return 4;
		case 0x53:	// LD D,E - 4 cycles
			gb_8bit_load_reg(gb.cpu.D,gb.cpu.E);
			return 4;
		case 0x54:	// LD D,H - 4 cycles
			gb_8bit_load_reg(gb.cpu.D,gb.cpu.H);
			return 4;
		case 0x55:	// LD D,L - 4 cycles
			gb_8bit_load_reg(gb.cpu.D,gb.cpu.L);
			return 4;
		case 0x55:	// LD D,(HL) - 8 cycles
			load_reg_add(gb.cpu.D, REG(gb.cpu.H,gb.cpu.L));
			return 8;
		// E
		case 0x58:	// LD E,B - 4 cycles
			gb_8bit_load_reg(gb.cpu.E,gb.cpu.B);
			return 4;
		case 0x59:	// LD E,C - 4 cycles
			gb_8bit_load_reg(gb.cpu.E,gb.cpu.C);
			return 4;
		case 0x5A:	// LD E,D - 4 cycles
			gb_8bit_load_reg(gb.cpu.E,gb.cpu.D);
			return 4;
		case 0x5B:	// LD E,E - 4 cycles
			gb_8bit_load_reg(gb.cpu.E,gb.cpu.E);
			return 4;
		case 0x5C:	// LD E,H - 4 cycles
			gb_8bit_load_reg(gb.cpu.E,gb.cpu.H);
			return 4;
		case 0x5D:	// LD E,L - 4 cycles
			gb_8bit_load_reg(gb.cpu.E,gb.cpu.L);
			return 4;
		case 0x5E:	// LD E,(HL) - 8 cycles
			load_reg_add(gb.cpu.E, REG(gb.cpu.H,gb.cpu.L));
			return 8;
		// H
		case 0x60:	// LD H,B - 4 cycles
			gb_8bit_load_reg(gb.cpu.H,gb.cpu.B);
			return 4;
		case 0x61:	// LD H,C - 4 cycles
			gb_8bit_load_reg(gb.cpu.H,gb.cpu.C);
			return 4;
		case 0x62:	// LD H,D - 4 cycles
			gb_8bit_load_reg(gb.cpu.H,gb.cpu.D);
			return 4;
		case 0x63:	// LD H,E - 4 cycles
			gb_8bit_load_reg(gb.cpu.H,gb.cpu.E);
			return 4;
		case 0x64:	// LD H,H - 4 cycles
			gb_8bit_load_reg(gb.cpu.H,gb.cpu.H);
			return 4;
		case 0x65:	// LD H,L - 4 cycles
			gb_8bit_load_reg(gb.cpu.H,gb.cpu.L);
			return 4;
		case 0x66:	// LD H,(HL) - 8 cycles
			load_reg_add(gb.cpu.H, REG(gb.cpu.H,gb.cpu.L));
			return 8;
		// L
		case 0x68:	// LD L,B - 4 cycles
			gb_8bit_load_reg(gb.cpu.L,gb.cpu.B);
			return 4;
		case 0x69:	// LD L,C - 4 cycles
			gb_8bit_load_reg(gb.cpu.L,gb.cpu.C);
			return 4;
		case 0x6A:	// LD L,D - 4 cycles
			gb_8bit_load_reg(gb.cpu.L,gb.cpu.D);
			return 4;
		case 0x6B:	// LD L,E - 4 cycles
			gb_8bit_load_reg(gb.cpu.L,gb.cpu.E);
			return 4;
		case 0x6C:	// LD L,H - 4 cycles
			gb_8bit_load_reg(gb.cpu.L,gb.cpu.H);
			return 4;
		case 0x6D:	// LD L,L - 4 cycles
			gb_8bit_load_reg(gb.cpu.L,gb.cpu.L);
			return 4;
		case 0x6E:	// LD L,(HL) - 8 cycles
			load_reg_add(gb.cpu.L, REG(gb.cpu.H,gb.cpu.L));
			return 8;
		// HL
		case 0x70:	// LD (HL),B - 8 cycles - (HL) <- B 
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.B);
			return 8;
		case 0x71:	// LD (HL),C - 8 cycles
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.C);
			return 8;
		case 0x72:	// LD (HL),D - 8 cycles
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.D);
			return 8;
		case 0x73:	// LD (HL),E - 8 cycles
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.E);
			return 8;
		case 0x74:	// LD (HL),H - 8 cycles
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.H);
			return 8;
		case 0x75:	// LD (HL),L - 8 cycles
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.L);
			return 8;
		/* 	LD n,A - Put value A into n	*/
		case 0x47:	// LD B,A - 4 cycles
			gb_8bit_load_reg(gb.cpu.B,gb.cpu.A);
			return 4;	
		case 0x4F:	// LD C,A - 4 cycles
			gb_8bit_load_reg(gb.cpu.C,gb.cpu.A);
			return 4;
		case 0x57:	// LD D,A - 4 cycles
			gb_8bit_load_reg(gb.cpu.D,gb.cpu.A);
			return 4;
		case 0x5F:	// LD E,A - 4 cycles
			gb_8bit_load_reg(gb.cpu.E,gb.cpu.A);
			return 4;
		case 0x67:	// LD H,A - 4 cycles - H <- A
			gb_8bit_load_reg(gb.cpu.H,gb.cpu.A);
			return 4;
		case 0x6F:	// LD L,A - 4 cycles
			gb_8bit_load_reg(gb.cpu.L,gb.cpu.A);
			return 4;
		case 0x02:	// LD (BC),A - 8 cycles - (BC) <- A
			writeMemory(REG(gb.cpu.B,gb.cpu.C), gb.cpu.A);
			return 8;
		case 0x12:	// LD (DE),A - 8 cycles
			writeMemory(REG(gb.cpu.D,gb.cpu.E), gb.cpu.A);
			return 8;
		case 0x77:	// LD (HL),A - 8 cycles - (HL) <- A
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.A);
			return 8;
		case 0xEA:	// LD nn,A - 16 cycles
			nn = (readMemory(gb.cpu.PC+1)<<8)|readMemory(gb.cpu.PC);
			gb.cpu.PC+=2;
			writeMemory(nn, gb.cpu.A);
			return 16;
		/*	Load A,(C) and Load A,(C)	*/
		case 0xF2:
			load_reg_add(gb.cpu.A, (REG(gb.cpu.B,gb.cpu.C)+0xFF00));
			return 8;
		case 0xE2:
			writeMemory((REG(gb.cpu.B,gb.cpu.C)+0xFF00), gb.cpu.A);
			return 8;
		case 0x3A:	// LD A,(HL-) - 8 cycles - A <- (HL), Dec HL
			load_reg_add(gb.cpu.A, REG(gb.cpu.H,gb.cpu.L));
			decrement();
			return 8;
		case 0x32:	// LD (HL-),A - 8 cycles - (HL) <- A, Dec HL
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.A);
			decrement();
			return 8;
		case 0x2A:	// LD A,(HL+) - 8 cycles - A <- (HL), Inc HL
			load_reg_add(gb.cpu.A, REG(gb.cpu.H,gb.cpu.L));;
			increment();
			return 8;
		case 0x22:	// LD (HL+),A - 8 cycles - (HL) <- A, Inc HL
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb.cpu.A);
			increment();
			return 8;	
		case 0xE0:	// LDH (n),A - 12 cycles
			n = readMemory(gb.cpu.PC++);
			writeMemory(n+0xFF00,gb.cpu.A);
			return 12;
		case 0xF0:	// LDH A,(n) - 12 cycles
			n = readMemory(gb.cpu.PC++);
			load_reg_add(gb.cpu.A,n+0xFF00);
			return 12;
		/* 16 bit loads */
		case 0x01:	// LD BC,nn - 12 cycles
			gb_16bit_load(REG(gb.cpu.B,gb.cpu.C));
			return 12;
		case 0x11:	// LD DE,nn - 12 cycles
			gb_16bit_load(REG(gb.cpu.D,gb.cpu.E));
			return 12;
		case 0x21:	// LD HL,nn - 12 cycles
			gb_16bit_load(REG(gb.cpu.H,gb.cpu.L));
			return 12;
		case 0x31:	// LD SP,nn - 12 cycles
			gb_16bit_load(gb.cpu.SP);
			return 12;
		case 0xF9:	// LD SP,HL - 8 cycles
			gb.cpu.SP = REG(gb.cpu.H,gb.cpu.L);
			return 8;
		case 0xF8:	// LD HL,SP+n - 12 cycles
			sn = readMemory(gb.cpu.PC++);
			nn = gb.cpu.SP + sn;
			REG(gb.cpu.H,gb.cpu.L) = nn;
			//NEEDS ADDITIONAL CODE
			return 12;
		case 0x08:	// LD (nn),SP - 20 cycles - Put sp at address nn
			nn = (readMemory(gb.cpu.PC+1)<<8)|readMemory(gb.cpu.PC);
			gb.cpu.PC+=2;
			writeMemory(nn,LO(gb.cpu.SP));
			nn++;
			writeMemory(nn,HI(gb.cpu.SP));
			return 20;
		/* PUSH */
		case 0xF5:	// push AF - 16 cycles
			push(REG(gb.cpu.A,gb.cpu.F));
			return 16;
		case 0xC5:	// push BC - 16 cycles
			push(REG(gb.cpu.B,gb.cpu.C));
			return 16;
		case 0xD5:	// push DE - 16 cycles
			push(REG(gb.cpu.D,gb.cpu.E));
			return 16;
		case 0xE5:	// push HL - 16 cycles
			push(REG(gb.cpu.H,gb.cpu.L));
			return 16;
		/* POP */  //FIXME
		case 0xF1:	// pop AF - 12 cycles
			REG(gb.cpu.A,gb.cpu.F) = pop();
			return 12;
		case 0xC1:	// pop BC - 12 cycles
			REG(gb.cpu.B,gb.cpu.C) = pop();
			return 12;
		case 0xD1:	// pop DE - 12 cycles
			REG(gb.cpu.D,gb.cpu.E) = pop();
			return 12;
		case 0xE1:	// pop HL - 12 cycles
			REG(gb.cpu.H,gb.cpu.L) = pop();
			return 12;
		/* 8bit ALU */
		/* ADD */
		case 0x87:	// ADD A,A
			gb.cpu.A = gb_8bit_add(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0x80:	// ADD A,B
			gb.cpu.A = gb_8bit_add(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0x81:	// ADD A,C
			gb.cpu.A = gb_8bit_add(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0x82:	// ADD A,D
			gb.cpu.A = gb_8bit_add(gb.cpu.A,gb.cpu.D);
			return 4;
		case 0x83:	// ADD A,E
			gb.cpu.A = gb_8bit_add(gb.cpu.A,gb.cpu.E);
			return 4;
		case 0x84:	// ADD A,H
			gb.cpu.A = gb_8bit_add(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0x85:	// ADD A,L
			gb.cpu.A = gb_8bit_add(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0x86:	// ADD A,(HL)
			gb.cpu.A = gb_8bit_add(gb.cpu.A,readMemory(REG(gb.cpu.H,gb.cpu.L)));
			return 8;
		case 0xC6:	// ADD A,n
			gb.cpu.A = gb_8bit_add(gb.cpu.A,readMemory(gb.cpu.PC++));
			return 8;
		/* ADC */
		case 0x8F:	// ADC A,A
			gb.cpu.A = gb_8bit_adc(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0x88:	// ADC A,B
			gb.cpu.A = gb_8bit_adc(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0x89:	// ADC A,C
			gb.cpu.A = gb_8bit_adc(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0x8A:	// ADC A,D
			gb.cpu.A = gb_8bit_adc(gb.cpu.A,gb.cpu.D);
			return 4;
		case 0x8B:	// ADC A,E
			gb.cpu.A = gb_8bit_adc(gb.cpu.A,gb.cpu.E);
			return 4;
		case 0x8C:	// ADC A,H
			gb.cpu.A = gb_8bit_adc(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0x8D:	// ADC A,L
			gb.cpu.A = gb_8bit_adc(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0x8E:	// ADC A,(HL)
			gb.cpu.A = gb_8bit_adc(regAF,readMemory(REG(gb.cpu.H,gb.cpu.L)));
			return 8;
		case 0xCE:	// ADC A,n
			gb.cpu.A = gb_8bit_adc(gb.cpu.A,readMemory(gb.cpu.PC++));
			return 8;
		/* SUB */
		case 0x97:	// SUB A
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0x90:	// SUB B
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0x91:	// SUB C
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0x92:	// SUB D
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,gb.cpu.D)
			return 4;
		case 0x93:	// SUB E
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,gb.cpu.E)
			return 4;
		case 0x94:	// SUB H
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0x95:	// SUB L
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0x96:	// SUB (HL)
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,readMemory(REG(gb.cpu.H,gb.cpu.L)));
			return 8;
		case 0xD6:	// SUB n
			gb.cpu.A = gb_8bit_sub(gb.cpu.A,readMemory(gb.cpu.PC++));
			return 8;
		/* SBC */
		case 0x9F:	// sbc A
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0x98:	// sbc B
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0x99:	// sbc C
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0x9A:	// sbc D
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,gb.cpu.D)
			return 4;
		case 0x9B:	// sbc E
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,gb.cpu.E)
			return 4;
		case 0x9C:	// sbc H
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0x9D:	// sbc L
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0x9E:	// sbc (HL)
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,readMemory(REG(gb.cpu.H,gb.cpu.L)));
			return 8;
		case 0xDE:	// sbc n
			gb.cpu.A = gb_8bit_sbc(gb.cpu.A,readMemory(gb.cpu.PC++));
			return 8;
		/* AND */
		case 0xA7:	// and A
			gb.cpu.A = gb_8bit_and(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0xA0:	// and B
			gb.cpu.A = gb_8bit_and(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0xA1:	// and C
			gb.cpu.A = gb_8bit_and(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0xA2:	// and D
			gb.cpu.A = gb_8bit_and(gb.cpu.A,gb.cpu.D)
			return 4;
		case 0xA3:	// and E
			gb.cpu.A = gb_8bit_and(gb.cpu.A,gb.cpu.E)
			return 4;
		case 0xA4:	// and H
			gb.cpu.A = gb_8bit_and(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0xA5:	// and L
			gb.cpu.A = gb_8bit_and(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0xA6:	// and (HL)
			gb.cpu.A = gb_8bit_and(gb.cpu.A,readMemory(REG(gb.cpu.H,gb.cpu.L)));
			return 8;
		case 0xE6:	// and n
			gb.cpu.A = gb_8bit_and(gb.cpu.A,readMemory(gb.cpu.PC++));
			return 8;
		/* OR */
		case 0xB7:	// or A
			gb.cpu.A = gb_8bit_or(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0xB0:	// or B
			gb.cpu.A = gb_8bit_or(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0xB1:	// or C
			gb.cpu.A = gb_8bit_or(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0xB2:	// or D
			gb.cpu.A = gb_8bit_or(gb.cpu.A,gb.cpu.D)
			return 4;
		case 0xB3:	// or E
			gb.cpu.A = gb_8bit_or(gb.cpu.A,gb.cpu.E)
			return 4;
		case 0xB4:	// or H
			gb.cpu.A = gb_8bit_or(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0xB5:	// or L
			gb.cpu.A = gb_8bit_or(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0xB6:	// or (HL)
			gb.cpu.A = gb_8bit_or(gb.cpu.A,readMemory(REG(gb.cpu.H,gb.cpu.L)));
			return 8;
		case 0xF6:	// or n
			gb.cpu.A = gb_8bit_or(gb.cpu.A,readMemory(gb.cpu.PC++));
			return 8;
		/* XOR */
		case 0xAF:	// xor A
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0xA8:	// xor B
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0xA9:	// xor C
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0xAA:	// xor D
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,gb.cpu.D)
			return 4;
		case 0xAB:	// xor E
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,gb.cpu.E)
			return 4;
		case 0xAC:	// xor H
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0xAD:	// xor L
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0xAE:	// xor (HL)
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,readMemory(REG(gb.cpu.H,gb.cpu.L)));
			return 8;
		case 0xEE:	// xor n
			gb.cpu.A = gb_8bit_xor(gb.cpu.A,readMemory(gb.cpu.PC++));
			return 8;
		/* CP */
		case 0xBF:	// cp A
			gb_8bit_cp(gb.cpu.A,gb.cpu.A);
			return 4;
		case 0xB8:	// cp B
			gb_8bit_cp(gb.cpu.A,gb.cpu.B);
			return 4;
		case 0xB9:	// cp C
			gb_8bit_cp(gb.cpu.A,gb.cpu.C);
			return 4;
		case 0xBA:	// cp D
			gb_8bit_cp(gb.cpu.A,gb.cpu.D)
			return 4;
		case 0xBB:	// cp E
			gb_8bit_cp(gb.cpu.A,gb.cpu.E)
			return 4;
		case 0xBC:	// cp H
			gb_8bit_cp(gb.cpu.A,gb.cpu.H);
			return 4;
		case 0xBD:	// cp L
			gb_8bit_cp(gb.cpu.A,gb.cpu.L);
			return 4;
		case 0xBE:	// cp (HL)
			gb_8bit_cp(gb.cpu.A,readMemory(REG(gb.cpu.H,gb.cpu.L)));
			return 8;
		case 0xFE:	// cp n
			gb_8bit_cp(gb.cpu.A,readMemory(gb.cpu.PC++));
			return 8;
		/* INC */
		case 0x3C:	// inc A
			gb.cpu.A = gb_8bit_inc(gb.cpu.A);
			return 4;
		case 0x04:	// inc B
			gb.cpu.B = gb_8bit_inc(gb.cpu.B);
			return 4;
		case 0x0C:	// inc C
			gb.cpu.C = gb_8bit_inc(gb.cpu.C);
			return 4;
		case 0x14:	// inc D
			gb.cpu.D = gb_8bit_inc(gb.cpu.D);
			return 4;
		case 0x1C:	// inc E
			gb.cpu.E = gb_8bit_inc(gb.cpu.E);
			return 4;
		case 0x24:	// inc H
			gb.cpu.H = gb_8bit_inc(gb.cpu.H);
			return 4;
		case 0x2C:	// inc L
			gb.cpu.L = gb_8bit_inc(gb.cpu.L);
			return 4;
		case 0x34:	// inc (HL)
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb_8bit_inc(readMemory(REG(gb.cpu.H,gb.cpu.L))));
			return 12;
		/* DEC */
		case 0x3D:	// dec A
			gb.cpu.A = gb_8bit_dec(gb.cpu.A);
			return 4;
		case 0x0D:	// dec B
			gb.cpu.B = gb_8bit_dec(gb.cpu.B);
			return 4;
		case 0x0D:	// dec C
			gb.cpu.C = gb_8bit_dec(gb.cpu.C);
			return 4;
		case 0x15:	// dec D
			gb.cpu.D = gb_8bit_dec(gb.cpu.D);
			return 4;
		case 0x1D:	// dec E
			gb.cpu.E = gb_8bit_dec(gb.cpu.E);
			return 4;
		case 0x25:	// dec H
			gb.cpu.H = gb_8bit_dec(gb.cpu.H);
			return 4;
		case 0x2D:	// dec L
			gb.cpu.L = gb_8bit_dec(gb.cpu.L);
			return 4;
		case 0x35:	// dec (HL)
			writeMemory(REG(gb.cpu.H,gb.cpu.L), gb_8bit_dec(readMemory(REG(gb.cpu.H,gb.cpu.L))));
			return 12;
		/* 16bit ALU */
		/* ADD */ ///FIXME
		case 0x09:	// add HL,BC
			REG(gb.cpu.H,gb.cpu.L) = gp_16bit_add(REG(gb.cpu.H,gb.cpu.L),REG(gb.cpu.B,gb.cpu.C))
			return 8;
		case 0x19:	// add HL,DE
			REG(gb.cpu.H,gb.cpu.L) = gp_16bit_add(REG(gb.cpu.H,gb.cpu.L),REG(gb.cpu.D,gb.cpu.E))
			return 8;
		case 0x29:	// add HL,HL
			REG(gb.cpu.H,gb.cpu.L) = gp_16bit_add(REG(gb.cpu.H,gb.cpu.L),REG(gb.cpu.H,gb.cpu.L))
			return 8;
		case 0x39:	// add HL,SP
			REG(gb.cpu.H,gb.cpu.L) = gp_16bit_add(REG(gb.cpu.H,gb.cpu.L),gb.cpu.SP)
			return 8;
		/* INC */
		case 0x03:	//INC BC //FIXME
			REG(gb.cpu.B,gb.cpu.C)++;
			return 8;
		case 0x13:	//INC DE
			REG(gb.cpu.D,gb.cpu.E)++;
			return 8;
		case 0x23:	//INC HL
			REG(gb.cpu.H,gb.cpu.L)++;
			return 8;
		case 0x33:	//INC BC
			gb.cpu.SP++;
			return 8;
		/* DEC */
		case 0x0B:	//INC BC
			REG(gb.cpu.B,gb.cpu.C)--;
			return 8;
		case 0x1B:	//INC DE
			REG(gb.cpu.D,gb.cpu.E)--;
			return 8;
		case 0x2B:	//INC HL
			REG(gb.cpu.H,gb.cpu.L)--;
			return 8;
		case 0x3B:	//INC BC
			gb.cpu.SP--;
			return 8;
		/* MISC */
		case 0xCB:	//execute extended op code
			n = readMemory(gb.cpu.PC++);
			return executeExtendOpCode(n);
		/* DAA */
		case 0x27:	// DAA
			
			return 4;
		/* CPL */
		case 0x2F:	//CPL A
			gb.cpu.A = ~gb.cpu.A;
			gb.cpu.F |= (1<<N_F)|(1<<H_F);
			return 4;
		/* CCF */
		case 0x3F:	
			gb.cpu.F ^= (1<<C_F);
			gb.cpu.F &= ~((1<<N_F)|(1<<H_F));
			return 4;
		/* SCF */
		case 0x37:
			gb.cpu.F &= ~((1<<N_F)|(1<<H_F));
			gb.cpu.F |= (1<<C_F);
			return 4;
		/* NOP */
		case 0x00:	// no operation - 4 cycles
			return 4;
		/* HALT */
		case 0x76:
			gb.cpu.PC--
			halted = 1;
			return 4;
		/* STOP */
		case 0x10:
			gb.cpu.PC--;
			stopped = 1;
			return 4;
		/* DI */
		case 0xF3:
			disableInterrupts();
			return 4;
		/* EI */
		case 0xFB:
			enableInterrupts();
			return 4;
		/* Rotates */
		/* RLCA */
		case 0x07:	
			rlc(&gb.cpu.A);
			return 4;
		/* RLA */
		case 0x17:
			rl(&gb.cpu.A);
			return 4;
		/* RRCA */
		case 0x0F:
			rrc(&gb.cpu.A);
			return 4;
		/* RRA */
		case 0x1F:
			rr(&gb.cpu.A);
			return 4;
		/* Jumps */
		case 0xC3:
			jump();
			return 12;
		case 0xC2:
			if(!(gb.cpu.F&(1<<Z_F)))
				jump();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xCA:
			if(gb.cpu.F&(1<<Z_F))
				jump();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xD2:
			if(!(gb.cpu.F&(1<<C_F)))
				jump();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xDA:
			if(gb.cpu.F&(1<<C_F))
				jump();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xE9:
			gb.cpu.PC = REG(gb.cpu.H,gb.cpu.L);
			return 4;
		case 0x18:
			jump_imd();
			return 8;
		case 0x20:
			if(!(gb.cpu.F&(1<<Z_F)))
				jump_imd();
			else
				gb.cpu.PC++;
			return 8;
		case 0x28:
			if(gb.cpu.F&(1<<Z_F))
				jump_imd();
			else
				gb.cpu.PC++;
			return 8;
		case 0x30:
			if(!(gb.cpu.F&(1<<C_F)))
				jump_imd();
			else
				gb.cpu.PC++;
			return 8;
		case 0x38:
			if(gb.cpu.F&(1<<C_F))
				jump_imd();
			else
				gb.cpu.PC++;
			return 8;	
		/* Calls */
		case 0xCD:
			call();
			return 12;
		case 0xC2:
			if(!(gb.cpu.F&(1<<Z_F)))
				call();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xCA:
			if(gb.cpu.F&(1<<Z_F))
				call();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xD2:
			if(!(gb.cpu.F&(1<<C_F)))
				call();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xDA:
			if(gb.cpu.F&(1<<C_F))
				call();
			else
				gb.cpu.PC+=2;
			return 12;
		/* Resets */
		case 0xC7:
			reset(0x00);
			return 32;
		case 0xCF:
			reset(0x08);
			return 32;
		case 0xD7:
			reset(0x10);
			return 32;
		case 0xDF:
			reset(0x18);
			return 32;
		case 0xE7:
			reset(0x20);
			return 32;
		case 0xEF:
			reset(0x28);
			return 32;
		case 0xF7:
			reset(0x30);
			return 32;
		case 0xFF:
			reset(0x38);
			return 32;
		/* Returns */
		case 0xC9:
			gb.cpu.PC = pop();
			return 8;
		case 0xC0:
			if(!(gb.cpu.F&(1<<Z_F)))
				gb.cpu.PC = pop();
			return 8;
		case 0xC8:
			if(gb.cpu.F&(1<<Z_F))
				gb.cpu.PC = pop();
			return 8;
		case 0xD0:
			if(!(gb.cpu.F&(1<<C_F)))
				gb.cpu.PC = pop();
			return 8;
		case 0xD8:
			if(gb.cpu.F&(1<<C_F))
				gb.cpu.PC = pop();
			return 8;
		case 0xD9:
			gb.cpu.PC = pop();
			enableInterrupts();
			return 8;
		
		
	}		
		
}
/* execute an opCode that has 0xCB as first byte */
uint8_t executeExtendOpCode(uint8_t op)
{
	switch(op)
	{
		/* EXTENDED OPCODES */
		/* CB - OPCode */
		/* SWAP */
		case 0x37:	// swap A
			gb.cpu.A = swap(gb.cpu.A);
			return 8;
		case 0x30:	// swap B
			gb.cpu.B = swap(gb.cpu.B);
			return 8;
		case 0x31:	// swap C
			gb.cpu.C = swap(gb.cpu.C);
			return 8;
		case 0x32:	// swap D
			gb.cpu.D = swap(gb.cpu.D);
			return 8;
		case 0x33:	// swap E
			gb.cpu.E = swap(gb.cpu.E);
			return 8;
		case 0x34:	// swap H
			gb.cpu.H = swap(gb.cpu.H);
			return 8;
		case 0x35:	// swap L
			gb.cpu.L = swap(gb.cpu.L);
			return 8;
		case 0x36:	// swap (HL)
			writeMemory(REG(gb.cpu.H,gb.cpu.L),swap(readMemory(REG(gb.cpu.H,gb.cpu.L))));
			return 16;
		/* Rotates and Shifts */
		/* RLC */
		case 0x07:	// RLC A
			rlc(&gb.cpu.A);
			return 8;
		case 0x00:	// RLC B
			rlc(&gb.cpu.B);
			return 8;
		case 0x01:	// RLC C
			rlc(&gb.cpu.C);
			return 8;
		case 0x02:	// RLC D
			rlc(&gb.cpu.D);
			return 8;
		case 0x03:	// RLC E
			rlc(&gb.cpu.E);
			return 8;
		case 0x04:	// RLC H
			rlc(&gb.cpu.H);
			return 8;
		case 0x05:	// RLC L
			rlc(&gb.cpu.L);
			return 8;
		case 0x06:	// RLC (HL)
			///FIXME
			rlc(&gb.cpu.A);
			return 	16;
		/* RL */
		case 0x17:	// RL A
			rl(&gb.cpu.A);
			return 8;
		case 0x10:	// RL B
			rl(&gb.cpu.B);
			return 8;
		case 0x11:	// RL C
			rl(&gb.cpu.C);
			return 8;
		case 0x12:	// RL D
			rl(&gb.cpu.D);
			return 8;
		case 0x13:	// RL E
			rl(&gb.cpu.E);
			return 8;
		case 0x14:	// RL H
			rl(&gb.cpu.H);
			return 8;
		case 0x15:	// RL L
			rl(&gb.cpu.L);
			return 8;
		case 0x16:	// RL (HL)
			///FIXME
			rl(&gb.cpu.A);
			return 	16;	
		/* RRC */
		case 0x0F:	// RRC A
			rrc(&gb.cpu.A);
			return 8;
		case 0x08:	// RRC B
			rrc(&gb.cpu.B);
			return 8;
		case 0x09:	// RRC C
			rrc(&gb.cpu.C);
			return 8;
		case 0x0A:	// RRC D
			rrc(&gb.cpu.D);
			return 8;
		case 0x0B:	// RRC E
			rrc(&gb.cpu.E);
			return 8;
		case 0x0C:	// RRC H
			rrc(&gb.cpu.H);
			return 8;
		case 0x0D:	// RRC L
			rrc(&gb.cpu.L);
			return 8;
		case 0x0E:	// RRC (HL)
			///FIXME
			rrc(&gb.cpu.A);
			return 	16;
		/* RR */
		case 0x1F:	// RR A
			rr(&gb.cpu.A);
			return 8;
		case 0x18:	// RR B
			rr(&gb.cpu.B);
			return 8;
		case 0x19:	// RR C
			rr(&gb.cpu.C);
			return 8;
		case 0x1A:	// RR D
			rr(&gb.cpu.D);
			return 8;
		case 0x1B:	// RR E
			rr(&gb.cpu.E);
			return 8;
		case 0x1C:	// RR H
			rr(&gb.cpu.H);
			return 8;
		case 0x1D:	// RR L
			rr(&gb.cpu.L);
			return 8;
		case 0x1E:	// RR (HL)
			///FIXME
			rr(&gb.cpu.A);
			return 	16;	
		/* SLA */
		case 0x27:	// SLA A
			sla(&gb.cpu.A);
			return 8;
		case 0x20:	// SLA B
			sla(&gb.cpu.B);
			return 8;
		case 0x21:	// SLA C
			sla(&gb.cpu.C);
			return 8;
		case 0x22:	// SLA D
			sla(&gb.cpu.D);
			return 8;
		case 0x23:	// SLA E
			sla(&gb.cpu.E);
			return 8;
		case 0x24:	// SLA H
			sla(&gb.cpu.H);
			return 8;
		case 0x25:	// SLA L
			sla(&gb.cpu.L);
			return 8;
		case 0x26:	// SLA (HL)
			///FIXME
			sla(&gb.cpu.A);
			return 	16;
		/* SRA */
		case 0x2F:	// SRA A
			sra(&gb.cpu.A);
			return 8;
		case 0x28:	// sra B
			sra(&gb.cpu.B);
			return 8;
		case 0x29:	// sra C
			sra(&gb.cpu.C);
			return 8;
		case 0x2A:	// sra D
			sra(&gb.cpu.D);
			return 8;
		case 0x2B:	// sra E
			sra(&gb.cpu.E);
			return 8;
		case 0x2C:	// sra H
			sra(&gb.cpu.H);
			return 8;
		case 0x2D:	// sra L
			sra(&gb.cpu.L);
			return 8;
		case 0x2E:	// sra (HL)
			///FIXME
			sra(&gb.cpu.A);
			return 	16;	
		/* SRL */
		case 0x3F:	// srl A
			srl(&gb.cpu.A);
			return 8;
		case 0x38:	// srl B
			srl(&gb.cpu.B);
			return 8;
		case 0x39:	// srl C
			srl(&gb.cpu.C);
			return 8;
		case 0x3A:	// srl D
			srl(&gb.cpu.D);
			return 8;
		case 0x3B:	// srl E
			srl(&gb.cpu.E);
			return 8;
		case 0x3C:	// srl H
			srl(&gb.cpu.H);
			return 8;
		case 0x3D:	// srl L
			srl(&gb.cpu.L);
			return 8;
		case 0x3E:	// srl (HL)
			///FIXME
			srl(&gb.cpu.A);
			return 	16;	
		/* bit operations */
		/* BIT */
		case 0x40:	testBit(0,gb.cpu.B); return 8;
		case 0x41:	testBit(0,gb.cpu.C); return 8;
		case 0x42:	testBit(0,gb.cpu.D); return 8;
		case 0x43:	testBit(0,gb.cpu.E); return 8;
		case 0x44:	testBit(0,gb.cpu.H); return 8;
		case 0x45:	testBit(0,gb.cpu.L); return 8;
		case 0x46:	testBit(0,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x47:	testBit(0,gb.cpu.A); return 8;
		case 0x48:	testBit(1,gb.cpu.B); return 8;
		case 0x49:	testBit(1,gb.cpu.C); return 8;
		case 0x4A:	testBit(1,gb.cpu.D); return 8;
		case 0x4B:	testBit(1,gb.cpu.E); return 8;
		case 0x4C:	testBit(1,gb.cpu.H); return 8;
		case 0x4D:	testBit(1,gb.cpu.L); return 8;
		case 0x4E:	testBit(1,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x4F:	testBit(1,gb.cpu.A); return 8;
		case 0x50:	testBit(2,gb.cpu.B); return 8;
		case 0x51:	testBit(2,gb.cpu.C); return 8;
		case 0x52:	testBit(2,gb.cpu.D); return 8;
		case 0x53:	testBit(2,gb.cpu.E); return 8;
		case 0x54:	testBit(2,gb.cpu.H); return 8;
		case 0x55:	testBit(2,gb.cpu.L); return 8;
		case 0x56:	testBit(2,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x57:	testBit(2,gb.cpu.A); return 8;
		case 0x58:	testBit(3,gb.cpu.B); return 8;
		case 0x59:	testBit(3,gb.cpu.C); return 8;
		case 0x5A:	testBit(3,gb.cpu.D); return 8;
		case 0x5B:	testBit(3,gb.cpu.E); return 8;
		case 0x5C:	testBit(3,gb.cpu.H); return 8;
		case 0x5D:	testBit(3,gb.cpu.L); return 8;
		case 0x5E:	testBit(3,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x5F:	testBit(3,gb.cpu.A); return 8;
		case 0x60:	testBit(4,gb.cpu.B); return 8;
		case 0x61:	testBit(4,gb.cpu.C); return 8;
		case 0x62:	testBit(4,gb.cpu.D); return 8;
		case 0x63:	testBit(4,gb.cpu.E); return 8;
		case 0x64:	testBit(4,gb.cpu.H); return 8;
		case 0x65:	testBit(4,gb.cpu.L); return 8;
		case 0x66:	testBit(4,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x67:	testBit(4,gb.cpu.A); return 8;
		case 0x68:	testBit(5,gb.cpu.B); return 8;
		case 0x69:	testBit(5,gb.cpu.C); return 8;
		case 0x6A:	testBit(5,gb.cpu.D); return 8;
		case 0x6B:	testBit(5,gb.cpu.E); return 8;
		case 0x6C:	testBit(5,gb.cpu.H); return 8;
		case 0x6D:	testBit(5,gb.cpu.L); return 8;
		case 0x6E:	testBit(5,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x6F:	testBit(5,gb.cpu.A); return 8;
		case 0x70:	testBit(6,gb.cpu.B); return 8;
		case 0x71:	testBit(6,gb.cpu.C); return 8;
		case 0x72:	testBit(6,gb.cpu.D); return 8;
		case 0x73:	testBit(6,gb.cpu.E); return 8;
		case 0x74:	testBit(6,gb.cpu.H); return 8;
		case 0x75:	testBit(6,gb.cpu.L); return 8;
		case 0x76:	testBit(6,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x77:	testBit(6,gb.cpu.A); return 8;
		case 0x78:	testBit(7,gb.cpu.B); return 8;
		case 0x79:	testBit(7,gb.cpu.C); return 8;
		case 0x7A:	testBit(7,gb.cpu.D); return 8;
		case 0x7B:	testBit(7,gb.cpu.E); return 8;
		case 0x7C:	testBit(7,gb.cpu.H); return 8;
		case 0x7D:	testBit(7,gb.cpu.L); return 8;
		case 0x7E:	testBit(7,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x7F:	testBit(7,gb.cpu.A); return 8;
		/* SET */
		case 0xC0:	setBit(0,gb.cpu.B); return 8;
		case 0xC1:	setBit(0,gb.cpu.C); return 8;
		case 0xC2:	setBit(0,gb.cpu.D); return 8;
		case 0xC3:	setBit(0,gb.cpu.E); return 8;
		case 0xC4:	setBit(0,gb.cpu.H); return 8;
		case 0xC5:	setBit(0,gb.cpu.L); return 8;
		case 0xC6:	setBit(0,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xC7:	setBit(0,gb.cpu.A); return 8;
		case 0xC8:	setBit(1,gb.cpu.B); return 8;
		case 0xC9:	setBit(1,gb.cpu.C); return 8;
		case 0xCA:	setBit(1,gb.cpu.D); return 8;
		case 0xCB:	setBit(1,gb.cpu.E); return 8;
		case 0xCC:	setBit(1,gb.cpu.H); return 8;
		case 0xCD:	setBit(1,gb.cpu.L); return 8;
		case 0xCE:	setBit(1,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xCF:	setBit(1,gb.cpu.A); return 8;
		case 0xD0:	setBit(2,gb.cpu.B); return 8;
		case 0xD1:	setBit(2,gb.cpu.C); return 8;
		case 0xD2:	setBit(2,gb.cpu.D); return 8;
		case 0xD3:	setBit(2,gb.cpu.E); return 8;
		case 0xD4:	setBit(2,gb.cpu.H); return 8;
		case 0xD5:	setBit(2,gb.cpu.L); return 8;
		case 0xD6:	setBit(2,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xD7:	setBit(2,gb.cpu.A); return 8;
		case 0xD8:	setBit(3,gb.cpu.B); return 8;
		case 0xD9:	setBit(3,gb.cpu.C); return 8;
		case 0xDA:	setBit(3,gb.cpu.D); return 8;
		case 0xDB:	setBit(3,gb.cpu.E); return 8;
		case 0xDC:	setBit(3,gb.cpu.H); return 8;
		case 0xDD:	setBit(3,gb.cpu.L); return 8;
		case 0xDE:	setBit(3,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xDF:	setBit(3,gb.cpu.A); return 8;
		case 0xE0:	setBit(4,gb.cpu.B); return 8;
		case 0xE1:	setBit(4,gb.cpu.C); return 8;
		case 0xE2:	setBit(4,gb.cpu.D); return 8;
		case 0xE3:	setBit(4,gb.cpu.E); return 8;
		case 0xE4:	setBit(4,gb.cpu.H); return 8;
		case 0xE5:	setBit(4,gb.cpu.L); return 8;
		case 0xE6:	setBit(4,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xE7:	setBit(4,gb.cpu.A); return 8;
		case 0xE8:	setBit(5,gb.cpu.B); return 8;
		case 0xE9:	setBit(5,gb.cpu.C); return 8;
		case 0xEA:	setBit(5,gb.cpu.D); return 8;
		case 0xEB:	setBit(5,gb.cpu.E); return 8;
		case 0xEC:	setBit(5,gb.cpu.H); return 8;
		case 0xED:	setBit(5,gb.cpu.L); return 8;
		case 0xEE:	setBit(5,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xEF:	setBit(5,gb.cpu.A); return 8;
		case 0xF0:	setBit(6,gb.cpu.B); return 8;
		case 0xF1:	setBit(6,gb.cpu.C); return 8;
		case 0xF2:	setBit(6,gb.cpu.D); return 8;
		case 0xF3:	setBit(6,gb.cpu.E); return 8;
		case 0xF4:	setBit(6,gb.cpu.H); return 8;
		case 0xF5:	setBit(6,gb.cpu.L); return 8;
		case 0xF6:	setBit(6,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xF7:	setBit(6,gb.cpu.A); return 8;
		case 0xF8:	setBit(7,gb.cpu.B); return 8;
		case 0xF9:	setBit(7,gb.cpu.C); return 8;
		case 0xFA:	setBit(7,gb.cpu.D); return 8;
		case 0xFB:	setBit(7,gb.cpu.E); return 8;
		case 0xFC:	setBit(7,gb.cpu.H); return 8;
		case 0xFD:	setBit(7,gb.cpu.L); return 8;
		case 0xFE:	setBit(7,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xFF:	setBit(7,gb.cpu.A); return 8;
		/* RES */
		case 0x80:	resBit(0,gb.cpu.B); return 8;
		case 0x81:	resBit(0,gb.cpu.C); return 8;
		case 0x82:	resBit(0,gb.cpu.D); return 8;
		case 0x83:	resBit(0,gb.cpu.E); return 8;
		case 0x84:	resBit(0,gb.cpu.H); return 8;
		case 0x85:	resBit(0,gb.cpu.L); return 8;
		case 0x86:	resBit(0,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x87:	resBit(0,gb.cpu.A); return 8;
		case 0x88:	resBit(1,gb.cpu.B); return 8;
		case 0x89:	resBit(1,gb.cpu.C); return 8;
		case 0x8A:	resBit(1,gb.cpu.D); return 8;
		case 0x8B:	resBit(1,gb.cpu.E); return 8;
		case 0x8C:	resBit(1,gb.cpu.H); return 8;
		case 0x8D:	resBit(1,gb.cpu.L); return 8;
		case 0x8E:	resBit(1,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x8F:	resBit(1,gb.cpu.A); return 8;
		case 0x90:	resBit(2,gb.cpu.B); return 8;
		case 0x91:	resBit(2,gb.cpu.C); return 8;
		case 0x92:	resBit(2,gb.cpu.D); return 8;
		case 0x93:	resBit(2,gb.cpu.E); return 8;
		case 0x94:	resBit(2,gb.cpu.H); return 8;
		case 0x95:	resBit(2,gb.cpu.L); return 8;
		case 0x96:	resBit(2,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x97:	resBit(2,gb.cpu.A); return 8;
		case 0x98:	resBit(3,gb.cpu.B); return 8;
		case 0x99:	resBit(3,gb.cpu.C); return 8;
		case 0x9A:	resBit(3,gb.cpu.D); return 8;
		case 0x9B:	resBit(3,gb.cpu.E); return 8;
		case 0x9C:	resBit(3,gb.cpu.H); return 8;
		case 0x9D:	resBit(3,gb.cpu.L); return 8;
		case 0x9E:	resBit(3,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0x9F:	resBit(3,gb.cpu.A); return 8;
		case 0xA0:	resBit(4,gb.cpu.B); return 8;
		case 0xA1:	resBit(4,gb.cpu.C); return 8;
		case 0xA2:	resBit(4,gb.cpu.D); return 8;
		case 0xA3:	resBit(4,gb.cpu.E); return 8;
		case 0xA4:	resBit(4,gb.cpu.H); return 8;
		case 0xA5:	resBit(4,gb.cpu.L); return 8;
		case 0xA6:	resBit(4,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xA7:	resBit(4,gb.cpu.A); return 8;
		case 0xA8:	resBit(5,gb.cpu.B); return 8;
		case 0xA9:	resBit(5,gb.cpu.C); return 8;
		case 0xAA:	resBit(5,gb.cpu.D); return 8;
		case 0xAB:	resBit(5,gb.cpu.E); return 8;
		case 0xAC:	resBit(5,gb.cpu.H); return 8;
		case 0xAD:	resBit(5,gb.cpu.L); return 8;
		case 0xAE:	resBit(5,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xAF:	resBit(5,gb.cpu.A); return 8;
		case 0xB0:	resBit(6,gb.cpu.B); return 8;
		case 0xB1:	resBit(6,gb.cpu.C); return 8;
		case 0xB2:	resBit(6,gb.cpu.D); return 8;
		case 0xB3:	resBit(6,gb.cpu.E); return 8;
		case 0xB4:	resBit(6,gb.cpu.H); return 8;
		case 0xB5:	resBit(6,gb.cpu.L); return 8;
		case 0xB6:	resBit(6,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xB7:	resBit(6,gb.cpu.A); return 8;
		case 0xB8:	resBit(7,gb.cpu.B); return 8;
		case 0xB9:	resBit(7,gb.cpu.C); return 8;
		case 0xBA:	resBit(7,gb.cpu.D); return 8;
		case 0xBB:	resBit(7,gb.cpu.E); return 8;
		case 0xBC:	resBit(7,gb.cpu.H); return 8;
		case 0xBD:	resBit(7,gb.cpu.L); return 8;
		case 0xBE:	resBit(7,readMemory(REG(gb.cpu.H,gb.cpu.L))); return 16;
		case 0xBF:	resBit(7,gb.cpu.A); return 8;
	}
}

