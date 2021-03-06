#include "inc/gb_cpu.h"



void gb_init(void)
{
	
}

void update_timer()
{
	
}

void interrupts()
{
	
}

/* load register with immeidate byte */
void load8(uint8_t *r)
{
	uint8_t n = read_memory(gb.cpu.PC++);
	*r = n;
}

/* load register with immeidate word */
void load16(uint16_t *r)
{
	uint16_t nn = (read_memory(gb.cpu.PC+1)<<8)|read_memory(gb.cpu.PC);
	gb.cpu.PC+=2;
	*r = nn;
}

/* load register with value in other register */
void load_reg(uint8_t *r1, uint8_t *r2)
{
	*r1 = *r2;
}

/* load register with value at address */
void load_reg_addr(uint8_t * r, uint16_t a)
{
	*r = read_memory(a);
}

/* push a value onto the stack */
void push(uint16_t nn)
{
	uint8_t hi = nn > 8;
	uint8_t lo = nn & 0xff;
	gb.cpu.SP--;
	write_memory(gb.cpu.SP,hi);
	gb.cpu.SP--;
	write_memory(gb.cpu.SP,lo);
}

/* pop value off stack */
uint16_t pop(void)
{
	uint16_t nn = read_memory(gb.cpu.SP);
	gb.cpu.SP++;
	nn = read_memory(gb.cpu.SP)<<8;
	gb.cpu.SP++;
	return nn;
}

/* add 8 bit number */
uint8_t add8(uint8_t a, uint8_t b)
{
	uint8_t r = a+b;
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	if(a > 255-b)
		gb.cpu.F |= (1<<C_F);
	if((a&0xF) > (15-(b&0xF)))
		gb.cpu.F |= (1<<H_F);
	
	return r;
}

/* add with carry */
uint8_t adc8(uint8_t a, uint8_t b)
{
	uint8_t r;
	if(gb.cpu.F&&(1<<C_F))
		b++;
	r = a+b;
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	if(a > 255-b)
		gb.cpu.F |= (1<<C_F);
	if((a&0xF) > (15-(b&0xF)))
		gb.cpu.F |= (1<<H_F);
	
	return r;
}

/* subtract */
uint8_t sub8(uint8_t a, uint8_t b)
{
	uint8_t r = a-b;
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	if(a < b)
		gb.cpu.F |= (1<<C_F);
	if((a&0xF)<(b&0xF))
		gb.cpu.F |= (1<<H_F);
	gb.cpu.F |= (1<<N_F);
	
	return r;
}

/* subtract with carry */
uint8_t sbc8(uint8_t a, uint8_t b)
{
	uint8_t r;
	if(gb.cpu.F&&(1<<C_F))
		b++;
	r = a-b;
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	if(a < b)
		gb.cpu.F |= (1<<C_F);
	if((a&0xF)<(b&0xF))
		gb.cpu.F |= (1<<H_F);
	gb.cpu.F |= (1<<N_F);
	
	return r;
}


uint8_t and8(uint8_t a, uint8_t b)
{
	uint8_t r = a&b;
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	gb.cpu.F |= (1<<H_F);
	return r;
}

uint8_t or8(uint8_t a, uint8_t b)
{
	uint8_t r = a|b;
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	
	return r;
}

uint8_t xor8(uint8_t a, uint8_t b)
{
	uint8_t r = a^b;
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	
	return r;
}

void cp8(uint8_t a, uint8_t b)
{
	uint8_t r = a-b;
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	if(a < b)
		gb.cpu.F |= (1<<C_F);
	if((a&0xF)<(b&0xF))
		gb.cpu.F |= (1<<H_F);
	gb.cpu.F |= (1<<N_F);
}

uint8_t inc8(uint8_t a)
{
	uint8_t r = a;
	r++;
	
	gb.cpu.F &= 0x10;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	if((a&0xF)==0xF)
		gb.cpu.F |= (1<<H_F);
	return r;
}

uint8_t dec8(uint8_t a)
{
	uint8_t r = a;
	r--;
	
	gb.cpu.F &= 0x10;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	if((a&0xF)==0)
		gb.cpu.F |= (1<<H_F);
	gb.cpu.F |= (1<<N_F);
	return r;
}

uint16_t add16(uint16_t a, uint16_t b)
{
	uint16_t r = a+b;
	
	gb.cpu.F &= 0x80;

	if(a > 0xFFFF-b)
		gb.cpu.F |= (1<<C_F);
	if((a&0xFFF) > (0xFFF-(b&0xFFF)))
		gb.cpu.F |= (1<<H_F);
	
	return r;
}

uint8_t swap(uint8_t r)
{
	r = (r<<4)|(r>>4);
	
	gb.cpu.F = 0;
	if(r == 0)
		gb.cpu.F |= (1<<Z_F);
	
	return r;
}

void rlc(uint8_t * r)
{
	gb.cpu.F = 0;
	if(0x80&*r)
		gb.cpu.F |= (1<<C_F);
	
	*r <<= 1;
	if(gb.cpu.F&(1<<C_F))
		*r |= 1;
	if(*r == 0)
		gb.cpu.F |= (1<<Z_F);
}

void rl(uint8_t * r)
{
	uint8_t oc=0;
	if(gb.cpu.F&(1<<C_F))
		oc = 1;
	gb.cpu.F = 0;
	if(0x80&*r)
		gb.cpu.F |= (1<<C_F);
	*r <<= 1;
	*r |= oc;
	if(*r == 0)
		gb.cpu.F |= (1<<Z_F);
}

void rrc(uint8_t * r)
{
	gb.cpu.F = 0;
	if(0x01&*r)
		gb.cpu.F |= (1<<C_F);
	*r >>= 1;
	if(gb.cpu.F&(1<<C_F))
		*r |= 0x80;
	if(*r == 0)
		gb.cpu.F |= (1<<Z_F);
}

void rr(uint8_t * r)
{
	uint8_t oc=0;
	if(gb.cpu.F&(1<<C_F))
		oc = 1;
	gb.cpu.F = 0;
	if(0x01&*r)
		gb.cpu.F |= (1<<C_F);
	
	*r >>= 1;
	*r |= oc<<7;
	if(*r == 0)
		gb.cpu.F |= (1<<Z_F);
}

void sla(uint8_t * r)
{
	gb.cpu.F = 0;
	if(0x80&*r)
		gb.cpu.F |= (1<<C_F);
	
	*r <<= 1;
	if(*r == 0)
		gb.cpu.F |= (1<<Z_F);
}

void sra(uint8_t * r)
{
	uint8_t ob=0;
	if(0x80&*r)
		ob = 1;
	gb.cpu.F = 0;
	if(0x01&*r)
		gb.cpu.F |= (1<<C_F);
	*r >>= 1;
	*r |= ob<<7;
	if(*r == 0)
		gb.cpu.F |= (1<<Z_F);
}

void srl(uint8_t * r)
{
	gb.cpu.F = 0;
	if(0x01&*r)
		gb.cpu.F |= (1<<C_F);
	*r >>= 1;
	if(*r == 0)
		gb.cpu.F |= (1<<Z_F);
}

void test_bit(uint8_t b, uint8_t r)
{
	uint8_t res = ((r&(1<<b))>>b);
	if(res == 0)
		gb.cpu.F |= (1<<Z_F);
	gb.cpu.F |= (1<<H_F);
	gb.cpu.F &= ~(1<<N_Z);
}

void set_bit(uint8_t b, uint8_t * r)
{
	*r |= (1<<b);
}

void res_bit(uint8_t b, uint8_t * r)
{
	*r &= ~(1<<b);
}

void jump(void)
{
	uint16_t nn = (read_memory(gb.cpu.PC+1)<<8)|read_memory(gb.cpu.PC);
	gb.cpu.PC = nn;
}

void jump_imd(void)
{
	int8_t n = read_memory(gb.cpu.PC++);
	gb.cpu.PC += n;
}

void call(void)
{
	uint16_t nn = (read_memory(gb.cpu.PC+1)<<8)|read_memory(gb.cpu.PC);
	gb.cpu.PC+=2;
	push(gb.cpu.PC);
	gb.cpu.PC = nn;
}

void reset(uint8_t a)
{
	push(gb.cpu.PC);
	gb.cpu.PC = a;
}

//FIXME!!!

uint8_t read_memory(uint16_t a)
{
	if(a>=0x4000 && a<=0x7FFF) {
		//reading from ROM bank in cartridge
	} else if(a>=0xA000 && a<=0xBFFF) {
		//reading from RAM bank in cartridge
	} else {
		return gb.mem[a];
	}
	
}

void write_memory(uint16_t a, uint8_t v)
{
	
	if(a < 0x8000) { //ROM memory in catridge
		if (a < 0x2000) { // 0x0000 - 0x1FFF RAM Bank enable
		  
		} else if (a < 0x3000) { // 0x2000 - 0x2FFF ROM Bank Select LSB
		  
		} else if (a < 0x4000) { // 0x3000 - 0x3FFF ROM Bank Select MSB (MBC5)
		  
		} else if (a < 0x6000) { // 0x4000 - 0x5FFF RAM Bank Select 
		  
		} else /* a < 0x8000*/ { // 0x6000 - 0x7FFF RAM/ROM Mode Select (MCB1)
		  
		}
	} else if(a>=0xE000 && a<=0xFDFF) { // if writing to echo also write to RAM
		gb.mem[a] = v;
		gb.mem[a-0x2000] = v;
	} else if(a>=0xFEA0 && a<=0xFEFF) { // restricted area

	} else {
		gb.mem[a] = v;
	}
}

