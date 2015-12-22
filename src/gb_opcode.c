#include "inc/gb_cpu.h"

#define REG(hi,lo)	(((hi)<<8)|(lo))
#define HI(x)		(((x)>>8)&0xFF)
#define LO(x)		((x)&0xFF)

uint8_t execute_opcode(void)
{
	uint8_t n;
	int8_t sn;
	uint16_t nn;
	uint8_t op = read_memory(gb.cpu.PC++);
	switch(op)
	{
		/* 	8-bit loads */
		/*  LD nn,n - Put value nn into n 
			Kinda confusing in GB Doc but
			should put byte into register
		*/
		case 0x3E:	// LD A,n - 8 cycles
			load8(&gb.cpu.AF.hi);
			return 8;
		case 0x06:	// LD B,n - 8 cycles
			load8(&gb.cpu.BC.hi);
			return 8;
		case 0x0E:	// LD C,n - 8 cycles
			load8(&gb.cpu.BC.lo);
			return 8;
		case 0x16:	// LD D,n - 8 cycles
			load8(&gb.cpu.DE.hi);
			return 8;
		case 0x1E:	// LD E,n - 8 cycles
			load8(&gb.cpu.DE.lo);
			return 8;
		case 0x26:	// LD H,n - 8 cycles
			load8(&gb.cpu.HL.hi);
			return 8;
		case 0x2E:	// LD L,n - 8 cycles
			load8(&gb.cpu.HL.lo);
			return 8;
		case 0x36:	// LD (HL),n - 12 cycles
			n = read_memory(gb.cpu.PC++);
			write_memory(gb.cpu.HL.reg,n); 
			return 12;
		/*  Register loads
			LD r1,r2 - Put value r2 into r1 */
		// A
		case 0x7F:	// LD A,A - 4 cycles
			load_reg(&gb.cpu.AF.hi,&gb.cpu.AF.hi);
			return 4;
		case 0x78:	// LD A,B - 4 cycles
			load_reg(&gb.cpu.AF.hi,&gb.cpu.BC.hi);
			return 4;
		case 0x79:	// LD A,C - 4 cycles
			load_reg(&gb.cpu.AF.hi,&gb.cpu.BC.lo);
			return 4;
		case 0x7A:	// LD A,D - 4 cycles
			load_reg(&gb.cpu.AF.hi,&gb.cpu.DE.hi);
			return 4;
		case 0x7B:	// LD A,E - 4 cycles
			load_reg(&gb.cpu.AF.hi,&gb.cpu.DE.lo);
			return 4;
		case 0x7C:	// LD A,H - 4 cycles
			load_reg(&gb.cpu.AF.hi,&gb.cpu.HL.hi);
			return 4;
		case 0x7D:	// LD A,L - 4 cycles
			load_reg(&gb.cpu.AF.hi,&gb.cpu.HL.lo);
			return 4;
		case 0x0A:	// LD A,(BC) - 8 cycles
			load_reg_addr(&gb.cpu.AF.hi, gb.cpu.BC.reg);
			return 8;
		case 0x1A:	// LD A,(DE) - 8 cycles
			load_reg_addr(&gb.cpu.AF.hi, gb.cpu.DE.reg);
			return 8;
		case 0x7E:	// LD A,(HL) - 8 cycles
			load_reg_addr(&gb.cpu.AF.hi, gb.cpu.HL.reg);
			return 8;
		case 0xFA:	// LD A,(nn) - 16 cycles
			nn = (read_memory(gb.cpu.PC+1)<<8)|read_memory(gb.cpu.PC);
			gb.cpu.PC+=2;
			load_reg_addr(&gb.cpu.AF.hi, nn);
			return 16;
		// B
		case 0x40:	// LD B,B - 4 cycles
			load_reg(&gb.cpu.BC.hi,&gb.cpu.BC.hi);
			return 4;
		case 0x41:	// LD B,C - 4 cycles
			load_reg(&gb.cpu.BC.hi,&gb.cpu.BC.lo);
			return 4;
		case 0x42:	// LD B,D - 4 cycles
			load_reg(&gb.cpu.BC.hi,&gb.cpu.DE.hi);
			return 4;
		case 0x43:	// LD B,E - 4 cycles
			load_reg(&gb.cpu.BC.hi,&gb.cpu.DE.lo);
			return 4;
		case 0x44:	// LD B,H - 4 cycles
			load_reg(&gb.cpu.BC.hi,&gb.cpu.HL.hi);
			return 4;
		case 0x45:	// LD B,L - 4 cycles
			load_reg(&gb.cpu.BC.hi,&gb.cpu.HL.lo);
			return 4;
		case 0x46:	// LD B,(HL) - 8 cycles
			load_reg_addr(&gb.cpu.BC.hi, gb.cpu.HL.reg);
			return 8;
		// C
		case 0x48:	// LD C,B - 4 cycles
			load_reg(&gb.cpu.BC.lo,&gb.cpu.BC.hi);
			return 4;
		case 0x49:	// LD C,C - 4 cycles
			load_reg(&gb.cpu.BC.lo,&gb.cpu.BC.lo);
			return 4;
		case 0x4A:	// LD C,D - 4 cycles
			load_reg(&gb.cpu.BC.lo,&gb.cpu.DE.hi);
			return 4;
		case 0x4B:	// LD C,E - 4 cycles
			load_reg(&gb.cpu.BC.lo,&gb.cpu.DE.lo);
			return 4;
		case 0x4C:	// LD C,H - 4 cycles
			load_reg(&gb.cpu.BC.lo,&gb.cpu.HL.hi);
			return 4;
		case 0x4D:	// LD C,L - 4 cycles
			load_reg(&gb.cpu.BC.lo,&gb.cpu.HL.lo);
			return 4;
		case 0x4E:	// LD C,(HL) - 8 cycles
			load_reg_addr(&gb.cpu.BC.lo, gb.cpu.HL.reg);
			return 8;
		// D
		case 0x50:	// LD D,B - 4 cycles
			load_reg(&gb.cpu.DE.hi,&gb.cpu.BC.hi);
			return 4;
		case 0x51:	// LD D,C - 4 cycles
			load_reg(&gb.cpu.DE.hi,&gb.cpu.BC.lo);
			return 4;
		case 0x52:	// LD D,D - 4 cycles
			load_reg(&gb.cpu.DE.hi,&gb.cpu.DE.hi);
			return 4;
		case 0x53:	// LD D,E - 4 cycles
			load_reg(&gb.cpu.DE.hi,&gb.cpu.DE.lo);
			return 4;
		case 0x54:	// LD D,H - 4 cycles
			load_reg(&gb.cpu.DE.hi,&gb.cpu.HL.hi);
			return 4;
		case 0x55:	// LD D,L - 4 cycles
			load_reg(&gb.cpu.DE.hi,&gb.cpu.HL.lo);
			return 4;
		case 0x55:	// LD D,(HL) - 8 cycles
			load_reg_addr(&gb.cpu.DE.hi, gb.cpu.HL.reg);
			return 8;
		// E
		case 0x58:	// LD E,B - 4 cycles
			load_reg(&gb.cpu.DE.lo,&gb.cpu.BC.hi);
			return 4;
		case 0x59:	// LD E,C - 4 cycles
			load_reg(&gb.cpu.DE.lo,&gb.cpu.BC.lo);
			return 4;
		case 0x5A:	// LD E,D - 4 cycles
			load_reg(&gb.cpu.DE.lo,&gb.cpu.DE.hi);
			return 4;
		case 0x5B:	// LD E,E - 4 cycles
			load_reg(&gb.cpu.DE.lo,&gb.cpu.DE.lo);
			return 4;
		case 0x5C:	// LD E,H - 4 cycles
			load_reg(&gb.cpu.DE.lo,&gb.cpu.HL.hi);
			return 4;
		case 0x5D:	// LD E,L - 4 cycles
			load_reg(&gb.cpu.DE.lo,&gb.cpu.HL.lo);
			return 4;
		case 0x5E:	// LD E,(HL) - 8 cycles
			load_reg_addr(&gb.cpu.DE.lo, gb.cpu.HL.reg);
			return 8;
		// H
		case 0x60:	// LD H,B - 4 cycles
			load_reg(&gb.cpu.HL.hi,&gb.cpu.BC.hi);
			return 4;
		case 0x61:	// LD H,C - 4 cycles
			load_reg(&gb.cpu.HL.hi,&gb.cpu.BC.lo);
			return 4;
		case 0x62:	// LD H,D - 4 cycles
			load_reg(&gb.cpu.HL.hi,&gb.cpu.DE.hi);
			return 4;
		case 0x63:	// LD H,E - 4 cycles
			load_reg(&gb.cpu.HL.hi,&gb.cpu.DE.lo);
			return 4;
		case 0x64:	// LD H,H - 4 cycles
			load_reg(&gb.cpu.HL.hi,&gb.cpu.HL.hi);
			return 4;
		case 0x65:	// LD H,L - 4 cycles
			load_reg(&gb.cpu.HL.hi,&gb.cpu.HL.lo);
			return 4;
		case 0x66:	// LD H,(HL) - 8 cycles
			load_reg_addr(&gb.cpu.HL.hi, gb.cpu.HL.reg);
			return 8;
		// L
		case 0x68:	// LD L,B - 4 cycles
			load_reg(&gb.cpu.HL.lo,&gb.cpu.BC.hi);
			return 4;
		case 0x69:	// LD L,C - 4 cycles
			load_reg(&gb.cpu.HL.lo,&gb.cpu.BC.lo);
			return 4;
		case 0x6A:	// LD L,D - 4 cycles
			load_reg(&gb.cpu.HL.lo,&gb.cpu.DE.hi);
			return 4;
		case 0x6B:	// LD L,E - 4 cycles
			load_reg(&gb.cpu.HL.lo,&gb.cpu.DE.lo);
			return 4;
		case 0x6C:	// LD L,H - 4 cycles
			load_reg(&gb.cpu.HL.lo,&gb.cpu.HL.hi);
			return 4;
		case 0x6D:	// LD L,L - 4 cycles
			load_reg(&gb.cpu.HL.lo,&gb.cpu.HL.lo);
			return 4;
		case 0x6E:	// LD L,(HL) - 8 cycles
			load_reg_addr(&gb.cpu.HL.lo, gb.cpu.HL.reg);
			return 8;
		// HL
		case 0x70:	// LD (HL),B - 8 cycles - (HL) <- B 
			write_memory(gb.cpu.HL.reg, gb.cpu.BC.hi);
			return 8;
		case 0x71:	// LD (HL),C - 8 cycles
			write_memory(gb.cpu.HL.reg, gb.cpu.BC.lo);
			return 8;
		case 0x72:	// LD (HL),D - 8 cycles
			write_memory(gb.cpu.HL.hi,gb.cpu.HL.lo), gb.cpu.DE.hi);
			return 8;
		case 0x73:	// LD (HL),E - 8 cycles
			write_memory(gb.cpu.HL.hi,gb.cpu.HL.lo), gb.cpu.DE.lo);
			return 8;
		case 0x74:	// LD (HL),H - 8 cycles
			write_memory(gb.cpu.HL.hi,gb.cpu.HL.lo), gb.cpu.HL.hi);
			return 8;
		case 0x75:	// LD (HL),L - 8 cycles
			write_memory(gb.cpu.HL.reg, gb.cpu.HL.lo);
			return 8;
		/* 	LD n,A - Put value A into n	*/
		case 0x47:	// LD B,A - 4 cycles
			load_reg(&gb.cpu.BC.hi,&gb.cpu.AF.hi);
			return 4;	
		case 0x4F:	// LD C,A - 4 cycles
			load_reg(&gb.cpu.BC.lo,&gb.cpu.AF.hi);
			return 4;
		case 0x57:	// LD D,A - 4 cycles
			load_reg(&gb.cpu.DE.hi,&gb.cpu.AF.hi);
			return 4;
		case 0x5F:	// LD E,A - 4 cycles
			load_reg(&gb.cpu.DE.lo,&gb.cpu.AF.hi);
			return 4;
		case 0x67:	// LD H,A - 4 cycles - H <- A
			load_reg(&gb.cpu.HL.hi,&gb.cpu.AF.hi);
			return 4;
		case 0x6F:	// LD L,A - 4 cycles
			load_reg(&gb.cpu.HL.lo,&gb.cpu.AF.hi);
			return 4;
		case 0x02:	// LD (BC),A - 8 cycles - (BC) <- A
			write_memory(gb.cpu.BC.reg, gb.cpu.AF.hi);
			return 8;
		case 0x12:	// LD (DE),A - 8 cycles
			write_memory(gb.cpu.DE.reg, gb.cpu.AF.hi);
			return 8;
		case 0x77:	// LD (HL),A - 8 cycles - (HL) <- A
			write_memory(gb.cpu.HL.reg, gb.cpu.AF.hi);
			return 8;
		case 0xEA:	// LD nn,A - 16 cycles
			nn = (read_memory(gb.cpu.PC+1)<<8)|read_memory(gb.cpu.PC);
			gb.cpu.PC+=2;
			write_memory(nn, gb.cpu.AF.hi);
			return 16;
		/*	Load A,(C) and Load A,(C)	*/  //FIXME check
		case 0xF2:
			load_reg_addr(&gb.cpu.AF.hi, (gb.cpu.BC.reg+0xFF00));
			return 8;
		case 0xE2:
			write_memory((gb.cpu.BC.reg+0xFF00), gb.cpu.AF.hi);
			return 8;
		case 0x3A:	// LD A,(HL-) - 8 cycles - A <- (HL), Dec HL
			load_reg_addr(&gb.cpu.AF.hi, gb.cpu.HL.reg);
			decrement(); //FIXME
			return 8;
		case 0x32:	// LD (HL-),A - 8 cycles - (HL) <- A, Dec HL
			write_memory(gb.cpu.HL.reg, gb.cpu.AF.hi);
			decrement(); //FIXME
			return 8;
		case 0x2A:	// LD A,(HL+) - 8 cycles - A <- (HL), Inc HL
			load_reg_addr(&gb.cpu.AF.hi, gb.cpu.HL.reg);;
			increment(); //FIXME
			return 8;
		case 0x22:	// LD (HL+),A - 8 cycles - (HL) <- A, Inc HL
			write_memory(gb.cpu.HL.reg, gb.cpu.AF.hi);
			increment(); //FIXME
			return 8;	
		case 0xE0:	// LDH (n),A - 12 cycles
			n = read_memory(gb.cpu.PC++);
			write_memory(n+0xFF00,gb.cpu.AF.hi);
			return 12;
		case 0xF0:	// LDH A,(n) - 12 cycles
			n = read_memory(gb.cpu.PC++);
			load_reg_addr(&gb.cpu.AF.hi,n+0xFF00);
			return 12;
		/* 16 bit loads */
		case 0x01:	// LD BC,nn - 12 cycles
			load16(&gb.cpu.BC.hi,&gb.cpu.BC.lo);
			return 12;
		case 0x11:	// LD DE,nn - 12 cycles
			load16(&gb.cpu.DE.hi,&gb.cpu.DE.lo);
			return 12;
		case 0x21:	// LD HL,nn - 12 cycles
			load16(&gb.cpu.HL.hi,&gb.cpu.HL.lo);
			return 12;
		case 0x31:	// LD SP,nn - 12 cycles
			nn = (read_memory(gb.cpu.PC+1)<<8)|read_memory(gb.cpu.PC);
			gb.cpu.PC+=2;
			gb.cpu.SP = nn;
			return 12;
		case 0xF9:	// LD SP,HL - 8 cycles
			gb.cpu.SP = gb.cpu.HL.reg;
			return 8;
		case 0xF8:	// LD HL,SP+n - 12 cycles
			sn = read_memory(gb.cpu.PC++);
			nn = gb.cpu.SP + sn;
			n = read_memory(nn);
			gb.cpu.HL.regnn;
			//NEEDS ADDITIONAL CODE
			return 12;
		case 0x08:	// LD (nn),SP - 20 cycles - Put sp at address nn
			nn = (read_memory(gb.cpu.PC+1)<<8)|read_memory(gb.cpu.PC);
			gb.cpu.PC+=2;
			write_memory(nn,LO(gb.cpu.SP));
			nn++;
			write_memory(nn,HI(gb.cpu.SP));
			return 20;
		/* PUSH */
		case 0xF5:	// push AF - 16 cycles
			push(gb.cpu.AF.reg);
			return 16;
		case 0xC5:	// push BC - 16 cycles
			push(gb.cpu.BC.reg);
			return 16;
		case 0xD5:	// push DE - 16 cycles
			push(gb.cpu.DE.reg);
			return 16;
		case 0xE5:	// push HL - 16 cycles
			push(gb.cpu.HL.reg);
			return 16;
		/* POP */  
		case 0xF1:	// pop AF - 12 cycles
			gb.cpu.AF.reg = pop();
			return 12;
		case 0xC1:	// pop BC - 12 cycles
			gb.cpu.BC.reg = pop();
			return 12;
		case 0xD1:	// pop DE - 12 cycles
			gb.cpu.DE.reg = pop();
			return 12;
		case 0xE1:	// pop HL - 12 cycles
			gb.cpu.HL.reg = pop();
			return 12;
		/* 8bit ALU */
		/* ADD */
		case 0x87:	// ADD A,A
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,gb.cpu.AF.hi);
			return 4;
		case 0x80:	// ADD A,B
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,gb.cpu.BC.hi);
			return 4;
		case 0x81:	// ADD A,C
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,gb.cpu.BC.lo);
			return 4;
		case 0x82:	// ADD A,D
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,gb.cpu.DE.hi);
			return 4;
		case 0x83:	// ADD A,E
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,gb.cpu.DE.lo);
			return 4;
		case 0x84:	// ADD A,H
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,gb.cpu.HL.hi);
			return 4;
		case 0x85:	// ADD A,L
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,gb.cpu.HL.lo);
			return 4;
		case 0x86:	// ADD A,(HL)
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,read_memory(gb.cpu.HL.reg));
			return 8;
		case 0xC6:	// ADD A,n
			gb.cpu.AF.hi = add8(gb.cpu.AF.hi,read_memory(gb.cpu.PC++));
			return 8;
		/* ADC */
		case 0x8F:	// ADC A,A
			gb.cpu.AF.hi = adc8(gb.cpu.AF.hi,gb.cpu.AF.hi);
			return 4;
		case 0x88:	// ADC A,B
			gb.cpu.AF.hi = adc8(gb.cpu.AF.hi,gb.cpu.BC.hi);
			return 4;
		case 0x89:	// ADC A,C
			gb.cpu.AF.hi = adc8(gb.cpu.AF.hi,gb.cpu.BC.lo);
			return 4;
		case 0x8A:	// ADC A,D
			gb.cpu.AF.hi = adc8(gb.cpu.AF.hi,gb.cpu.DE.hi);
			return 4;
		case 0x8B:	// ADC A,E
			gb.cpu.AF.hi = adc8(gb.cpu.AF.hi,gb.cpu.DE.lo);
			return 4;
		case 0x8C:	// ADC A,H
			gb.cpu.AF.hi = adc8(gb.cpu.AF.hi,gb.cpu.HL.hi);
			return 4;
		case 0x8D:	// ADC A,L
			gb.cpu.AF.hi = adc8(gb.cpu.AF.hi,gb.cpu.HL.lo);
			return 4;
		case 0x8E:	// ADC A,(HL)
			gb.cpu.AF.hi = adc8(regAF,read_memory(gb.cpu.HL.reg));
			return 8;
		case 0xCE:	// ADC A,n
			gb.cpu.AF.hi = adc8(gb.cpu.AF.hi,read_memory(gb.cpu.PC++));
			return 8;
		/* SUB */
		case 0x97:	// SUB A
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,gb.cpu.AF.hi);
			return 4;
		case 0x90:	// SUB B
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,gb.cpu.BC.hi);
			return 4;
		case 0x91:	// SUB C
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,gb.cpu.BC.lo);
			return 4;
		case 0x92:	// SUB D
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,gb.cpu.DE.hi)
			return 4;
		case 0x93:	// SUB E
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,gb.cpu.DE.lo)
			return 4;
		case 0x94:	// SUB H
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,gb.cpu.HL.hi);
			return 4;
		case 0x95:	// SUB L
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,gb.cpu.HL.lo);
			return 4;
		case 0x96:	// SUB (HL)
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,read_memory(gb.cpu.HL.reg));
			return 8;
		case 0xD6:	// SUB n
			gb.cpu.AF.hi = sub8(gb.cpu.AF.hi,read_memory(gb.cpu.PC++));
			return 8;
		/* SBC */
		case 0x9F:	// sbc A
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,gb.cpu.AF.hi);
			return 4;
		case 0x98:	// sbc B
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,gb.cpu.BC.hi);
			return 4;
		case 0x99:	// sbc C
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,gb.cpu.BC.lo);
			return 4;
		case 0x9A:	// sbc D
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,gb.cpu.DE.hi)
			return 4;
		case 0x9B:	// sbc E
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,gb.cpu.DE.lo)
			return 4;
		case 0x9C:	// sbc H
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,gb.cpu.HL.hi);
			return 4;
		case 0x9D:	// sbc L
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,gb.cpu.HL.lo);
			return 4;
		case 0x9E:	// sbc (HL)
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,read_memory(gb.cpu.HL.reg));
			return 8;
		case 0xDE:	// sbc n
			gb.cpu.AF.hi = sbc8(gb.cpu.AF.hi,read_memory(gb.cpu.PC++));
			return 8;
		/* AND */
		case 0xA7:	// and A
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,gb.cpu.AF.hi);
			return 4;
		case 0xA0:	// and B
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,gb.cpu.BC.hi);
			return 4;
		case 0xA1:	// and C
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,gb.cpu.BC.lo);
			return 4;
		case 0xA2:	// and D
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,gb.cpu.DE.hi)
			return 4;
		case 0xA3:	// and E
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,gb.cpu.DE.lo)
			return 4;
		case 0xA4:	// and H
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,gb.cpu.HL.hi);
			return 4;
		case 0xA5:	// and L
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,gb.cpu.HL.lo);
			return 4;
		case 0xA6:	// and (HL)
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,read_memory(gb.cpu.HL.reg));
			return 8;
		case 0xE6:	// and n
			gb.cpu.AF.hi = and8(gb.cpu.AF.hi,read_memory(gb.cpu.PC++));
			return 8;
		/* OR */
		case 0xB7:	// or A
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,gb.cpu.AF.hi);
			return 4;
		case 0xB0:	// or B
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,gb.cpu.BC.hi);
			return 4;
		case 0xB1:	// or C
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,gb.cpu.BC.lo);
			return 4;
		case 0xB2:	// or D
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,gb.cpu.DE.hi)
			return 4;
		case 0xB3:	// or E
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,gb.cpu.DE.lo)
			return 4;
		case 0xB4:	// or H
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,gb.cpu.HL.hi);
			return 4;
		case 0xB5:	// or L
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,gb.cpu.HL.lo);
			return 4;
		case 0xB6:	// or (HL)
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,read_memory(gb.cpu.HL.reg));
			return 8;
		case 0xF6:	// or n
			gb.cpu.AF.hi = or8(gb.cpu.AF.hi,read_memory(gb.cpu.PC++));
			return 8;
		/* XOR */
		case 0xAF:	// xor A
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,gb.cpu.AF.hi);
			return 4;
		case 0xA8:	// xor B
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,gb.cpu.BC.hi);
			return 4;
		case 0xA9:	// xor C
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,gb.cpu.BC.lo);
			return 4;
		case 0xAA:	// xor D
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,gb.cpu.DE.hi)
			return 4;
		case 0xAB:	// xor E
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,gb.cpu.DE.lo)
			return 4;
		case 0xAC:	// xor H
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,gb.cpu.HL.hi);
			return 4;
		case 0xAD:	// xor L
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,gb.cpu.HL.lo);
			return 4;
		case 0xAE:	// xor (HL)
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,read_memory(gb.cpu.HL.reg));
			return 8;
		case 0xEE:	// xor n
			gb.cpu.AF.hi = xor8(gb.cpu.AF.hi,read_memory(gb.cpu.PC++));
			return 8;
		/* CP */
		case 0xBF:	// cp A
			cp8(gb.cpu.AF.hi,gb.cpu.AF.hi);
			return 4;
		case 0xB8:	// cp B
			cp8(gb.cpu.AF.hi,gb.cpu.BC.hi);
			return 4;
		case 0xB9:	// cp C
			cp8(gb.cpu.AF.hi,gb.cpu.BC.lo);
			return 4;
		case 0xBA:	// cp D
			cp8(gb.cpu.AF.hi,gb.cpu.DE.hi)
			return 4;
		case 0xBB:	// cp E
			cp8(gb.cpu.AF.hi,gb.cpu.DE.lo)
			return 4;
		case 0xBC:	// cp H
			cp8(gb.cpu.AF.hi,gb.cpu.HL.hi);
			return 4;
		case 0xBD:	// cp L
			cp8(gb.cpu.AF.hi,gb.cpu.HL.lo);
			return 4;
		case 0xBE:	// cp (HL)
			cp8(gb.cpu.AF.hi,read_memory(gb.cpu.HL.reg));
			return 8;
		case 0xFE:	// cp n
			cp8(gb.cpu.AF.hi,read_memory(gb.cpu.PC++));
			return 8;
		/* INC */
		case 0x3C:	// inc A
			gb.cpu.AF.hi = inc8(gb.cpu.AF.hi);
			return 4;
		case 0x04:	// inc B
			gb.cpu.BC.hi = inc8(gb.cpu.BC.hi);
			return 4;
		case 0x0C:	// inc C
			gb.cpu.BC.lo = inc8(gb.cpu.BC.lo);
			return 4;
		case 0x14:	// inc D
			gb.cpu.DE.hi = inc8(gb.cpu.DE.hi);
			return 4;
		case 0x1C:	// inc E
			gb.cpu.DE.lo = inc8(gb.cpu.DE.lo);
			return 4;
		case 0x24:	// inc H
			gb.cpu.HL.hi = inc8(gb.cpu.HL.hi);
			return 4;
		case 0x2C:	// inc L
			gb.cpu.HL.lo = inc8(gb.cpu.HL.lo);
			return 4;
		case 0x34:	// inc (HL)
			write_memory(gb.cpu.HL.reg, inc8(read_memory(gb.cpu.HL.reg)));
			return 12;
		/* DEC */
		case 0x3D:	// dec A
			gb.cpu.AF.hi = dec8(gb.cpu.AF.hi);
			return 4;
		case 0x0D:	// dec B
			gb.cpu.BC.hi = dec8(gb.cpu.BC.hi);
			return 4;
		case 0x0D:	// dec C
			gb.cpu.BC.lo = dec8(gb.cpu.BC.lo);
			return 4;
		case 0x15:	// dec D
			gb.cpu.DE.hi = dec8(gb.cpu.DE.hi);
			return 4;
		case 0x1D:	// dec E
			gb.cpu.DE.lo = dec8(gb.cpu.DE.lo);
			return 4;
		case 0x25:	// dec H
			gb.cpu.HL.hi = dec8(gb.cpu.HL.hi);
			return 4;
		case 0x2D:	// dec L
			gb.cpu.HL.lo = dec8(gb.cpu.HL.lo);
			return 4;
		case 0x35:	// dec (HL)
			write_memory(gb.cpu.HL.reg, dec8(read_memory(gb.cpu.HL.reg)));
			return 12;
		/* 16bit ALU */
		/* ADD */ ///FIXME
		case 0x09:	// add HL,BC
			gb.cpu.HL.reg = add16(gb.cpu.HL.reg,gb.cpu.BC.reg)
			return 8;
		case 0x19:	// add HL,DE
			gb.cpu.HL.reg = add16(gb.cpu.HL.reg,gb.cpu.DE.reg)
			return 8;
		case 0x29:	// add HL,HL
			gb.cpu.HL.reg = add16(gb.cpu.HL.reg,gb.cpu.HL.reg)
			return 8;
		case 0x39:	// add HL,SP
			gb.cpu.HL.reg = add16(gb.cpu.HL.reg,gb.cpu.SP)
			return 8;
		/* INC */
		case 0x03:	//INC BC //FIXME
			gb.cpu.BC.reg++;
			return 8;
		case 0x13:	//INC DE
			gb.cpu.DE.reg++;
			return 8;
		case 0x23:	//INC HL
			gb.cpu.HL.reg++;
			return 8;
		case 0x33:	//INC BC
			gb.cpu.SP++;
			return 8;
		/* DEC */
		case 0x0B:	//INC BC
			gb.cpu.BC.reg--;
			return 8;
		case 0x1B:	//INC DE
			gb.cpu.DE.reg--;
			return 8;
		case 0x2B:	//INC HL
			gb.cpu.HL.reg--;
			return 8;
		case 0x3B:	//INC BC
			gb.cpu.SP--;
			return 8;
		/* MISC */
		case 0xCB:	//execute extended op code
			n = read_memory(gb.cpu.PC++);
			return execute_extend_opcode(n);
		/* DAA */
		case 0x27:	// DAA
			
			return 4;
		/* CPL */
		case 0x2F:	//CPL A
			gb.cpu.AF.hi = ~gb.cpu.AF.hi;
			gb.cpu.AF.lo |= (1<<N_F)|(1<<H_F);
			return 4;
		/* CCF */
		case 0x3F:	
			gb.cpu.AF.lo ^= (1<<C_F);
			gb.cpu.AF.lo &= ~((1<<N_F)|(1<<H_F));
			return 4;
		/* SCF */
		case 0x37:
			gb.cpu.AF.lo &= ~((1<<N_F)|(1<<H_F));
			gb.cpu.AF.lo |= (1<<C_F);
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
			disable_interrupts();
			return 4;
		/* EI */
		case 0xFB:
			enable_interrupts();
			return 4;
		/* Rotates */
		/* RLCA */
		case 0x07:	
			rlc(&gb.cpu.AF.hi);
			return 4;
		/* RLA */
		case 0x17:
			rl(&gb.cpu.AF.hi);
			return 4;
		/* RRCA */
		case 0x0F:
			rrc(&gb.cpu.AF.hi);
			return 4;
		/* RRA */
		case 0x1F:
			rr(&gb.cpu.AF.hi);
			return 4;
		/* Jumps */
		case 0xC3:
			jump();
			return 12;
		case 0xC2:
			if(!(gb.cpu.AF.lo&(1<<Z_F)))
				jump();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xCA:
			if(gb.cpu.AF.lo&(1<<Z_F))
				jump();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xD2:
			if(!(gb.cpu.AF.lo&(1<<C_F)))
				jump();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xDA:
			if(gb.cpu.AF.lo&(1<<C_F))
				jump();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xE9:
			gb.cpu.PC = gb.cpu.HL.reg;
			return 4;
		case 0x18:
			jump_imd();
			return 8;
		case 0x20:
			if(!(gb.cpu.AF.lo&(1<<Z_F)))
				jump_imd();
			else
				gb.cpu.PC++;
			return 8;
		case 0x28:
			if(gb.cpu.AF.lo&(1<<Z_F))
				jump_imd();
			else
				gb.cpu.PC++;
			return 8;
		case 0x30:
			if(!(gb.cpu.AF.lo&(1<<C_F)))
				jump_imd();
			else
				gb.cpu.PC++;
			return 8;
		case 0x38:
			if(gb.cpu.AF.lo&(1<<C_F))
				jump_imd();
			else
				gb.cpu.PC++;
			return 8;	
		/* Calls */
		case 0xCD:
			call();
			return 12;
		case 0xC2:
			if(!(gb.cpu.AF.lo&(1<<Z_F)))
				call();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xCA:
			if(gb.cpu.AF.lo&(1<<Z_F))
				call();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xD2:
			if(!(gb.cpu.AF.lo&(1<<C_F)))
				call();
			else
				gb.cpu.PC+=2;
			return 12;
		case 0xDA:
			if(gb.cpu.AF.lo&(1<<C_F))
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
			if(!(gb.cpu.AF.lo&(1<<Z_F)))
				gb.cpu.PC = pop();
			return 8;
		case 0xC8:
			if(gb.cpu.AF.lo&(1<<Z_F))
				gb.cpu.PC = pop();
			return 8;
		case 0xD0:
			if(!(gb.cpu.AF.lo&(1<<C_F)))
				gb.cpu.PC = pop();
			return 8;
		case 0xD8:
			if(gb.cpu.AF.lo&(1<<C_F))
				gb.cpu.PC = pop();
			return 8;
		case 0xD9:
			gb.cpu.PC = pop();
			enable_interrupts();
			return 8;
		
		
	}		
		
}
/* execute an opCode that has 0xCB as first byte */
uint8_t execute_extend_opcode(uint8_t op)
{
	uint8_t n;
	int8_t sn;
	uint16_t nn;
	switch(op)
	{
		/* EXTENDED OPCODES */
		/* CB - OPCode */
		/* SWAP */
		case 0x37:	// swap A
			gb.cpu.AF.hi = swap(gb.cpu.AF.hi);
			return 8;
		case 0x30:	// swap B
			gb.cpu.BC.hi = swap(gb.cpu.BC.hi);
			return 8;
		case 0x31:	// swap C
			gb.cpu.BC.lo = swap(gb.cpu.BC.lo);
			return 8;
		case 0x32:	// swap D
			gb.cpu.DE.hi = swap(gb.cpu.DE.hi);
			return 8;
		case 0x33:	// swap E
			gb.cpu.DE.lo = swap(gb.cpu.DE.lo);
			return 8;
		case 0x34:	// swap H
			gb.cpu.HL.hi = swap(gb.cpu.HL.hi);
			return 8;
		case 0x35:	// swap L
			gb.cpu.HL.lo = swap(gb.cpu.HL.lo);
			return 8;
		case 0x36:	// swap (HL)
			write_memory(gb.cpu.HL.reg,swap(read_memory(gb.cpu.HL.reg)));
			return 16;
		/* Rotates and Shifts */
		/* RLC */
		case 0x07:	// RLC A
			rlc(&gb.cpu.AF.hi);
			return 8;
		case 0x00:	// RLC B
			rlc(&gb.cpu.BC.hi);
			return 8;
		case 0x01:	// RLC C
			rlc(&gb.cpu.BC.lo);
			return 8;
		case 0x02:	// RLC D
			rlc(&gb.cpu.DE.hi);
			return 8;
		case 0x03:	// RLC E
			rlc(&gb.cpu.DE.lo);
			return 8;
		case 0x04:	// RLC H
			rlc(&gb.cpu.HL.hi);
			return 8;
		case 0x05:	// RLC L
			rlc(&gb.cpu.HL.lo);
			return 8;
		case 0x06:	// RLC (HL)
			n = read_memory(gb.cpu.HL.reg);
			rlc(&n);
			write_memory(gb.cpu.HL.reg, n);
			return 	16;
		/* RL */
		case 0x17:	// RL A
			rl(&gb.cpu.AF.hi);
			return 8;
		case 0x10:	// RL B
			rl(&gb.cpu.BC.hi);
			return 8;
		case 0x11:	// RL C
			rl(&gb.cpu.BC.lo);
			return 8;
		case 0x12:	// RL D
			rl(&gb.cpu.DE.hi);
			return 8;
		case 0x13:	// RL E
			rl(&gb.cpu.DE.lo);
			return 8;
		case 0x14:	// RL H
			rl(&gb.cpu.HL.hi);
			return 8;
		case 0x15:	// RL L
			rl(&gb.cpu.HL.lo);
			return 8;
		case 0x16:	// RL (HL)
			n = read_memory(gb.cpu.HL.reg);
			rl(&n);
			write_memory(gb.cpu.HL.reg, n);
			return 	16;	
		/* RRC */
		case 0x0F:	// RRC A
			rrc(&gb.cpu.AF.hi);
			return 8;
		case 0x08:	// RRC B
			rrc(&gb.cpu.BC.hi);
			return 8;
		case 0x09:	// RRC C
			rrc(&gb.cpu.BC.lo);
			return 8;
		case 0x0A:	// RRC D
			rrc(&gb.cpu.DE.hi);
			return 8;
		case 0x0B:	// RRC E
			rrc(&gb.cpu.DE.lo);
			return 8;
		case 0x0C:	// RRC H
			rrc(&gb.cpu.HL.hi);
			return 8;
		case 0x0D:	// RRC L
			rrc(&gb.cpu.HL.lo);
			return 8;
		case 0x0E:	// RRC (HL)
			n = read_memory(gb.cpu.HL.reg);
			rrc(&n);
			write_memory(gb.cpu.HL.reg, n);
			return 	16;
		/* RR */
		case 0x1F:	// RR A
			rr(&gb.cpu.AF.hi);
			return 8;
		case 0x18:	// RR B
			rr(&gb.cpu.BC.hi);
			return 8;
		case 0x19:	// RR C
			rr(&gb.cpu.BC.lo);
			return 8;
		case 0x1A:	// RR D
			rr(&gb.cpu.DE.hi);
			return 8;
		case 0x1B:	// RR E
			rr(&gb.cpu.DE.lo);
			return 8;
		case 0x1C:	// RR H
			rr(&gb.cpu.HL.hi);
			return 8;
		case 0x1D:	// RR L
			rr(&gb.cpu.HL.lo);
			return 8;
		case 0x1E:	// RR (HL)
			n = read_memory(gb.cpu.HL.reg);
			rr(&n);
			write_memory(gb.cpu.HL.reg, n);
			return 	16;	
		/* SLA */
		case 0x27:	// SLA A
			sla(&gb.cpu.AF.hi);
			return 8;
		case 0x20:	// SLA B
			sla(&gb.cpu.BC.hi);
			return 8;
		case 0x21:	// SLA C
			sla(&gb.cpu.BC.lo);
			return 8;
		case 0x22:	// SLA D
			sla(&gb.cpu.DE.hi);
			return 8;
		case 0x23:	// SLA E
			sla(&gb.cpu.DE.lo);
			return 8;
		case 0x24:	// SLA H
			sla(&gb.cpu.HL.hi);
			return 8;
		case 0x25:	// SLA L
			sla(&gb.cpu.HL.lo);
			return 8;
		case 0x26:	// SLA (HL)
			n = read_memory(gb.cpu.HL.reg);
			sla(&n);
			write_memory(gb.cpu.HL.reg, n);
			return 	16;
		/* SRA */
		case 0x2F:	// SRA A
			sra(&gb.cpu.AF.hi);
			return 8;
		case 0x28:	// sra B
			sra(&gb.cpu.BC.hi);
			return 8;
		case 0x29:	// sra C
			sra(&gb.cpu.BC.lo);
			return 8;
		case 0x2A:	// sra D
			sra(&gb.cpu.DE.hi);
			return 8;
		case 0x2B:	// sra E
			sra(&gb.cpu.DE.lo);
			return 8;
		case 0x2C:	// sra H
			sra(&gb.cpu.HL.hi);
			return 8;
		case 0x2D:	// sra L
			sra(&gb.cpu.HL.lo);
			return 8;
		case 0x2E:	// sra (HL)
			n = read_memory(gb.cpu.HL.reg);
			sra(&n);
			write_memory(gb.cpu.HL.reg, n);
			return 	16;	
		/* SRL */
		case 0x3F:	// srl A
			srl(&gb.cpu.AF.hi);
			return 8;
		case 0x38:	// srl B
			srl(&gb.cpu.BC.hi);
			return 8;
		case 0x39:	// srl C
			srl(&gb.cpu.BC.lo);
			return 8;
		case 0x3A:	// srl D
			srl(&gb.cpu.DE.hi);
			return 8;
		case 0x3B:	// srl E
			srl(&gb.cpu.DE.lo);
			return 8;
		case 0x3C:	// srl H
			srl(&gb.cpu.HL.hi);
			return 8;
		case 0x3D:	// srl L
			srl(&gb.cpu.HL.lo);
			return 8;
		case 0x3E:	// srl (HL)
			n = read_memory(gb.cpu.HL.reg);
			srl(&n);
			write_memory(gb.cpu.HL.reg, n);
			return 	16;	
		/* bit operations */
		/* BIT */
		case 0x40:	test_bit(0,gb.cpu.BC.hi); return 8;
		case 0x41:	test_bit(0,gb.cpu.BC.lo); return 8;
		case 0x42:	test_bit(0,gb.cpu.DE.hi); return 8;
		case 0x43:	test_bit(0,gb.cpu.DE.lo); return 8;
		case 0x44:	test_bit(0,gb.cpu.HL.hi); return 8;
		case 0x45:	test_bit(0,gb.cpu.HL.lo); return 8;
		case 0x46:	test_bit(0,read_memory(gb.cpu.HL.reg)); return 16;
		case 0x47:	test_bit(0,gb.cpu.AF.hi); return 8;
		case 0x48:	test_bit(1,gb.cpu.BC.hi); return 8;
		case 0x49:	test_bit(1,gb.cpu.BC.lo); return 8;
		case 0x4A:	test_bit(1,gb.cpu.DE.hi); return 8;
		case 0x4B:	test_bit(1,gb.cpu.DE.lo); return 8;
		case 0x4C:	test_bit(1,gb.cpu.HL.hi); return 8;
		case 0x4D:	test_bit(1,gb.cpu.HL.lo); return 8;
		case 0x4E:	test_bit(1,read_memory(gb.cpu.HL.reg)); return 16;
		case 0x4F:	test_bit(1,gb.cpu.AF.hi); return 8;
		case 0x50:	test_bit(2,gb.cpu.BC.hi); return 8;
		case 0x51:	test_bit(2,gb.cpu.BC.lo); return 8;
		case 0x52:	test_bit(2,gb.cpu.DE.hi); return 8;
		case 0x53:	test_bit(2,gb.cpu.DE.lo); return 8;
		case 0x54:	test_bit(2,gb.cpu.HL.hi); return 8;
		case 0x55:	test_bit(2,gb.cpu.HL.lo); return 8;
		case 0x56:	test_bit(2,read_memory(gb.cpu.HL.reg)); return 16;
		case 0x57:	test_bit(2,gb.cpu.AF.hi); return 8;
		case 0x58:	test_bit(3,gb.cpu.BC.hi); return 8;
		case 0x59:	test_bit(3,gb.cpu.BC.lo); return 8;
		case 0x5A:	test_bit(3,gb.cpu.DE.hi); return 8;
		case 0x5B:	test_bit(3,gb.cpu.DE.lo); return 8;
		case 0x5C:	test_bit(3,gb.cpu.HL.hi); return 8;
		case 0x5D:	test_bit(3,gb.cpu.HL.lo); return 8;
		case 0x5E:	test_bit(3,read_memory(gb.cpu.HL.reg)); return 16;
		case 0x5F:	test_bit(3,gb.cpu.AF.hi); return 8;
		case 0x60:	test_bit(4,gb.cpu.BC.hi); return 8;
		case 0x61:	test_bit(4,gb.cpu.BC.lo); return 8;
		case 0x62:	test_bit(4,gb.cpu.DE.hi); return 8;
		case 0x63:	test_bit(4,gb.cpu.DE.lo); return 8;
		case 0x64:	test_bit(4,gb.cpu.HL.hi); return 8;
		case 0x65:	test_bit(4,gb.cpu.HL.lo); return 8;
		case 0x66:	test_bit(4,read_memory(gb.cpu.HL.reg)); return 16;
		case 0x67:	test_bit(4,gb.cpu.AF.hi); return 8;
		case 0x68:	test_bit(5,gb.cpu.BC.hi); return 8;
		case 0x69:	test_bit(5,gb.cpu.BC.lo); return 8;
		case 0x6A:	test_bit(5,gb.cpu.DE.hi); return 8;
		case 0x6B:	test_bit(5,gb.cpu.DE.lo); return 8;
		case 0x6C:	test_bit(5,gb.cpu.HL.hi); return 8;
		case 0x6D:	test_bit(5,gb.cpu.HL.lo); return 8;
		case 0x6E:	test_bit(5,read_memory(gb.cpu.HL.reg)); return 16;
		case 0x6F:	test_bit(5,gb.cpu.AF.hi); return 8;
		case 0x70:	test_bit(6,gb.cpu.BC.hi); return 8;
		case 0x71:	test_bit(6,gb.cpu.BC.lo); return 8;
		case 0x72:	test_bit(6,gb.cpu.DE.hi); return 8;
		case 0x73:	test_bit(6,gb.cpu.DE.lo); return 8;
		case 0x74:	test_bit(6,gb.cpu.HL.hi); return 8;
		case 0x75:	test_bit(6,gb.cpu.HL.lo); return 8;
		case 0x76:	test_bit(6,read_memory(gb.cpu.HL.reg)); return 16;
		case 0x77:	test_bit(6,gb.cpu.AF.hi); return 8;
		case 0x78:	test_bit(7,gb.cpu.BC.hi); return 8;
		case 0x79:	test_bit(7,gb.cpu.BC.lo); return 8;
		case 0x7A:	test_bit(7,gb.cpu.DE.hi); return 8;
		case 0x7B:	test_bit(7,gb.cpu.DE.lo); return 8;
		case 0x7C:	test_bit(7,gb.cpu.HL.hi); return 8;
		case 0x7D:	test_bit(7,gb.cpu.HL.lo); return 8;
		case 0x7E:	test_bit(7,read_memory(gb.cpu.HL.reg)); return 16;
		case 0x7F:	test_bit(7,gb.cpu.AF.hi); return 8;
		/* SET */
		case 0xC0:	set_bit(0,gb.cpu.BC.hi); return 8;
		case 0xC1:	set_bit(0,&gb.cpu.BC.lo); return 8;
		case 0xC2:	set_bit(0,&gb.cpu.DE.hi); return 8;
		case 0xC3:	set_bit(0,&gb.cpu.DE.lo); return 8;
		case 0xC4:	set_bit(0,&gb.cpu.HL.hi); return 8;
		case 0xC5:	set_bit(0,&gb.cpu.HL.lo); return 8;
		case 0xC6:	
			n = read_memory(gb.cpu.HL.reg);	
			set_bit(7,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xC7:	set_bit(0,&gb.cpu.AF.hi); return 8;
		case 0xC8:	set_bit(1,&gb.cpu.BC.hi); return 8;
		case 0xC9:	set_bit(1,&gb.cpu.BC.lo); return 8;
		case 0xCA:	set_bit(1,&gb.cpu.DE.hi); return 8;
		case 0xCB:	set_bit(1,&gb.cpu.DE.lo); return 8;
		case 0xCC:	set_bit(1,&gb.cpu.HL.hi); return 8;
		case 0xCD:	set_bit(1,&gb.cpu.HL.lo); return 8;
		case 0xCE:	
			n = read_memory(gb.cpu.HL.reg);	
			set_bit(1,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xCF:	set_bit(1,&gb.cpu.AF.hi); return 8;
		case 0xD0:	set_bit(2,&gb.cpu.BC.hi); return 8;
		case 0xD1:	set_bit(2,&gb.cpu.BC.lo); return 8;
		case 0xD2:	set_bit(2,&gb.cpu.DE.hi); return 8;
		case 0xD3:	set_bit(2,&gb.cpu.DE.lo); return 8;
		case 0xD4:	set_bit(2,&gb.cpu.HL.hi); return 8;
		case 0xD5:	set_bit(2,&gb.cpu.HL.lo); return 8;
		case 0xD6:	
			n = read_memory(gb.cpu.HL.reg);	
			set_bit(2,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xD7:	set_bit(2,&gb.cpu.AF.hi); return 8;
		case 0xD8:	set_bit(3,&gb.cpu.BC.hi); return 8;
		case 0xD9:	set_bit(3,&gb.cpu.BC.lo); return 8;
		case 0xDA:	set_bit(3,&gb.cpu.DE.hi); return 8;
		case 0xDB:	set_bit(3,&gb.cpu.DE.lo); return 8;
		case 0xDC:	set_bit(3,&gb.cpu.HL.hi); return 8;
		case 0xDD:	set_bit(3,&gb.cpu.HL.lo); return 8;
		case 0xDE:	
			n = read_memory(gb.cpu.HL.reg);	
			set_bit(3,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xDF:	set_bit(3,&gb.cpu.AF.hi); return 8;
		case 0xE0:	set_bit(4,&gb.cpu.BC.hi); return 8;
		case 0xE1:	set_bit(4,&gb.cpu.BC.lo); return 8;
		case 0xE2:	set_bit(4,&gb.cpu.DE.hi); return 8;
		case 0xE3:	set_bit(4,&gb.cpu.DE.lo); return 8;
		case 0xE4:	set_bit(4,&gb.cpu.HL.hi); return 8;
		case 0xE5:	set_bit(4,&gb.cpu.HL.lo); return 8;
		case 0xE6:	
			n = read_memory(gb.cpu.HL.reg);	
			set_bit(4,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xE7:	set_bit(4,&gb.cpu.AF.hi); return 8;
		case 0xE8:	set_bit(5,&gb.cpu.BC.hi); return 8;
		case 0xE9:	set_bit(5,&gb.cpu.BC.lo); return 8;
		case 0xEA:	set_bit(5,&gb.cpu.DE.hi); return 8;
		case 0xEB:	set_bit(5,&gb.cpu.DE.lo); return 8;
		case 0xEC:	set_bit(5,&gb.cpu.HL.hi); return 8;
		case 0xED:	set_bit(5,&gb.cpu.HL.lo); return 8;
		case 0xEE:	
			n = read_memory(gb.cpu.HL.reg);	
			set_bit(5,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xEF:	set_bit(5,&gb.cpu.AF.hi); return 8;
		case 0xF0:	set_bit(6,&gb.cpu.BC.hi); return 8;
		case 0xF1:	set_bit(6,&gb.cpu.BC.lo); return 8;
		case 0xF2:	set_bit(6,&gb.cpu.DE.hi); return 8;
		case 0xF3:	set_bit(6,&gb.cpu.DE.lo); return 8;
		case 0xF4:	set_bit(6,&gb.cpu.HL.hi); return 8;
		case 0xF5:	set_bit(6,&gb.cpu.HL.lo); return 8;
		case 0xF6:	
			n = read_memory(gb.cpu.HL.reg);	
			set_bit(6,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xF7:	set_bit(6,&gb.cpu.AF.hi); return 8;
		case 0xF8:	set_bit(7,&gb.cpu.BC.hi); return 8;
		case 0xF9:	set_bit(7,&gb.cpu.BC.lo); return 8;
		case 0xFA:	set_bit(7,&gb.cpu.DE.hi); return 8;
		case 0xFB:	set_bit(7,&gb.cpu.DE.lo); return 8;
		case 0xFC:	set_bit(7,&gb.cpu.HL.hi); return 8;
		case 0xFD:	set_bit(7,&gb.cpu.HL.lo); return 8;
		case 0xFE:
			n = read_memory(gb.cpu.HL.reg);	
			set_bit(7,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xFF:	set_bit(7,&gb.cpu.AF.hi); return 8;
		/* RES */
		case 0x80:	res_bit(0,&gb.cpu.BC.hi); return 8;
		case 0x81:	res_bit(0,&gb.cpu.BC.lo); return 8;
		case 0x82:	res_bit(0,&gb.cpu.DE.hi); return 8;
		case 0x83:	res_bit(0,&gb.cpu.DE.lo); return 8;
		case 0x84:	res_bit(0,&gb.cpu.HL.hi); return 8;
		case 0x85:	res_bit(0,&gb.cpu.HL.lo); return 8;
		case 0x86:	
			n = read_memory(gb.cpu.HL.reg);	
			res_bit(0,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0x87:	res_bit(0,&gb.cpu.AF.hi); return 8;
		case 0x88:	res_bit(1,&gb.cpu.BC.hi); return 8;
		case 0x89:	res_bit(1,&gb.cpu.BC.lo); return 8;
		case 0x8A:	res_bit(1,&gb.cpu.DE.hi); return 8;
		case 0x8B:	res_bit(1,&gb.cpu.DE.lo); return 8;
		case 0x8C:	res_bit(1,&gb.cpu.HL.hi); return 8;
		case 0x8D:	res_bit(1,&gb.cpu.HL.lo); return 8;
		case 0x8E:	
			n = read_memory(gb.cpu.HL.reg);	
			res_bit(1,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0x8F:	res_bit(1,&gb.cpu.AF.hi); return 8;
		case 0x90:	res_bit(2,&gb.cpu.BC.hi); return 8;
		case 0x91:	res_bit(2,&gb.cpu.BC.lo); return 8;
		case 0x92:	res_bit(2,&gb.cpu.DE.hi); return 8;
		case 0x93:	res_bit(2,&gb.cpu.DE.lo); return 8;
		case 0x94:	res_bit(2,&gb.cpu.HL.hi); return 8;
		case 0x95:	res_bit(2,&gb.cpu.HL.lo); return 8;
		case 0x96:	
			n = read_memory(gb.cpu.HL.reg);	
			res_bit(2,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0x97:	res_bit(2,&gb.cpu.AF.hi); return 8;
		case 0x98:	res_bit(3,&gb.cpu.BC.hi); return 8;
		case 0x99:	res_bit(3,&gb.cpu.BC.lo); return 8;
		case 0x9A:	res_bit(3,&gb.cpu.DE.hi); return 8;
		case 0x9B:	res_bit(3,&gb.cpu.DE.lo); return 8;
		case 0x9C:	res_bit(3,&gb.cpu.HL.hi); return 8;
		case 0x9D:	res_bit(3,&gb.cpu.HL.lo); return 8;
		case 0x9E:	
			n = read_memory(gb.cpu.HL.reg);	
			res_bit(3,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0x9F:	res_bit(3,&gb.cpu.AF.hi); return 8;
		case 0xA0:	res_bit(4,&gb.cpu.BC.hi); return 8;
		case 0xA1:	res_bit(4,&gb.cpu.BC.lo); return 8;
		case 0xA2:	res_bit(4,&gb.cpu.DE.hi); return 8;
		case 0xA3:	res_bit(4,&gb.cpu.DE.lo); return 8;
		case 0xA4:	res_bit(4,&gb.cpu.HL.hi); return 8;
		case 0xA5:	res_bit(4,&gb.cpu.HL.lo); return 8;
		case 0xA6:	
			n = read_memory(gb.cpu.HL.reg);	
			res_bit(4,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xA7:	res_bit(4,&gb.cpu.AF.hi); return 8;
		case 0xA8:	res_bit(5,&gb.cpu.BC.hi); return 8;
		case 0xA9:	res_bit(5,&gb.cpu.BC.lo); return 8;
		case 0xAA:	res_bit(5,&gb.cpu.DE.hi); return 8;
		case 0xAB:	res_bit(5,&gb.cpu.DE.lo); return 8;
		case 0xAC:	res_bit(5,&gb.cpu.HL.hi); return 8;
		case 0xAD:	res_bit(5,&gb.cpu.HL.lo); return 8;
		case 0xAE:	
			n = read_memory(gb.cpu.HL.reg);	
			res_bit(5,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xAF:	res_bit(5,&gb.cpu.AF.hi); return 8;
		case 0xB0:	res_bit(6,&gb.cpu.BC.hi); return 8;
		case 0xB1:	res_bit(6,&gb.cpu.BC.lo); return 8;
		case 0xB2:	res_bit(6,&gb.cpu.DE.hi); return 8;
		case 0xB3:	res_bit(6,&gb.cpu.DE.lo); return 8;
		case 0xB4:	res_bit(6,&gb.cpu.HL.hi); return 8;
		case 0xB5:	res_bit(6,&gb.cpu.HL.lo); return 8;
		case 0xB6:	
			n = read_memory(gb.cpu.HL.reg);	
			res_bit(6,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xB7:	res_bit(6,&gb.cpu.AF.hi); return 8;
		case 0xB8:	res_bit(7,&gb.cpu.BC.hi); return 8;
		case 0xB9:	res_bit(7,&gb.cpu.BC.lo); return 8;
		case 0xBA:	res_bit(7,&gb.cpu.DE.hi); return 8;
		case 0xBB:	res_bit(7,&gb.cpu.DE.lo); return 8;
		case 0xBC:	res_bit(7,&gb.cpu.HL.hi); return 8;
		case 0xBD:	res_bit(7,&gb.cpu.HL.lo); return 8;
		case 0xBE:	
			n = read_memory(gb.cpu.HL.reg);	
			res_bit(7,&n); 
			write_memory(gb.cpu.HL.reg, n);
			return 16;
		case 0xBF:	res_bit(7,&gb.cpu.AF.hi); return 8;
	}
}

