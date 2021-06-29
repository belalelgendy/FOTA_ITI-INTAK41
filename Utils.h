/*
 * Utils.h
 *
 * Created: 10/6/2020 10:29:46 PM
 *  Author: lenovo
 */ 


#ifndef UTILS_H_
#define UTILS_H_
#define SET_BIT(reg,bit)            (reg=reg|(1<<bit))
#define CLEAR_BIT(reg,bit)          (reg=reg&(~(1<<bit)))
#define  READ_BIT(reg,bit)          ((reg>>bit)&1)
#define  TOGGLE_LED(reg,bit)        (reg=reg^(1<<bit))
#define  GET_BIT(byte,bit)          ((byte>>bit)&1)
#define  SEGMENT_PORT                PORTA
#define  EN1                         6
#define  EN2                         7




#endif /* UTILS_H_ */