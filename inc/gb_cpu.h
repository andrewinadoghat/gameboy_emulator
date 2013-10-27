#ifndef GB_CPU_H
#define GB_CPU_H

typedef struct
{
	uint8_t mbc;
	uint8_t rom_size;
	uint8_t ram_size;
	char name[16];
	uint8_t * mem;
}cart_t

typedef union
{
	uint16_t reg;
	struct 
	{
		uint8_t hi;
		uint8_t lo;
	};
}register_t;

typedef struct 
{
	register_t AF;
	register_t BC;
	register_t DE;
	register_t HL;
	uint16_t SP;
	uint16_t PC;
}gb_cpu_t;

typedef struct
{
	gp_cpu_t cpu;
	cart_t cart;
	uint8_t mem[0x10000];
}gb_t;

void gb_8bit_load(uint8_t * r);
void gb_16bit_load(uint16_t * r);
void gb_8bit_load_reg(uint8_t * r1, uint8_t * r2);
void load_reg_add(uint8_t * r, uint16_t a);
void push(uint16_t nn);
uint16_t pop(void);
uint8_t gb_8bit_add(uint8_t a, uint8_t b);
uint8_t gb_8bit_adc(uint8_t a, uint8_t b);
uint8_t gb_8bit_sub(uint8_t a, uint8_t b);
uint8_t gb_8bit_sbc(uint8_t a, uint8_t b);
uint8_t gb_8bit_and(uint8_t a, uint8_t b);
uint8_t gb_8bit_or(uint8_t a, uint8_t b);
uint8_t gb_8bit_xor(uint8_t a, uint8_t b);
void gb_8bit_cp(uint8_t a, uint8_t b);
uint8_t gb_8bit_inc(uint8_t a);
uint8_t gb_8bit_dec(uint8_t a);
uint16_t gb_16bit_add(uint16_t a, uint16_t b);
uint8_t swap(uint8_t r);
void rlc(uint8_t * r);
void rl(uint8_t * r);
void rrc(uint8_t * r);
void rr(uint8_t * r);
void sla(uint8_t * r);
void sra(uint8_t * r);
void srl(uint8_t * r);
void testBit(uint8_t b, uint8_t r);
uint8_t setBit(uint8_t b, uint8_t r);
uint8_t resBit(uint8_t b, uint8_t r);
void jump(void);
void jump_imd(void);
void call(void);
void reset(uint8_t a);
uint8_t readMemory(uint16_t a);
void writeMemory(uint16_t a, uint8_t v);

#endif
