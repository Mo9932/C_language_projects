#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(num,bit) (num|=(1<<bit))
#define CLR_BIT(num,bit) (num&=~(1<<bit))
#define TOG_BIT(num,bit) (num^=(1<<bit))
#define GET_BIT(num,bit) ((num>>bit) & 0x01)

#endif /* BIT_MATH_H */

