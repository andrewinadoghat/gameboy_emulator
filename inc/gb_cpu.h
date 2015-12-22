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

void load8(uint8_t * r);
void load16(uint16_t * r);
void load_reg(uint8_t * r1, uint8_t * r2);
void load_reg_add(uint8_t * r, uint16_t a);
void push(uint16_t nn);
uint16_t pop(void);
uint8_t add8(uint8_t a, uint8_t b);
uint8_t adc8(uint8_t a, uint8_t b);
uint8_t sub8(uint8_t a, uint8_t b);
uint8_t sbc8(uint8_t a, uint8_t b);
uint8_t and8(uint8_t a, uint8_t b);
uint8_t or8(uint8_t a, uint8_t b);
uint8_t xor8(uint8_t a, uint8_t b);
void cp8(uint8_t a, uint8_t b);
uint8_t inc8(uint8_t a);
uint8_t dec8(uint8_t a);
uint16_t add16(uint16_t a, uint16_t b);
uint8_t swap(uint8_t r);
void rlc(uint8_t * r);
void rl(uint8_t * r);
void rrc(uint8_t * r);
void rr(uint8_t * r);
void sla(uint8_t * r);
void sra(uint8_t * r);
void srl(uint8_t * r);
void test_bit(uint8_t b, uint8_t r);
uint8_t set_bit(uint8_t b, uint8_t r);
uint8_t res_bit(uint8_t b, uint8_t r);
void jump(void);
void jump_imd(void);
void call(void);
void reset(uint8_t a);
uint8_t read_memory(uint16_t a);
void write_memory(uint16_t a, uint8_t v);

#endif
