#ifndef bit_operations
#define bit_operations

#define set_bit(temp,bit_num) temp |= 1 << bit_num  // setting this bit in the variable temp
#define clr_bit(temp,bit_num) temp &= ~1 << bit_num // clearing this bit in the variable temp
#define tog_bit(temp,bit_num) temp ^= 1 << bit_num  // toggling this bit in the variable temp
#define get_bit(temp,bit_num) temp &  1 << bit_num // getting this bit in the variable temp

#endif