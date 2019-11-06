
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void PUT32( unsigned int, unsigned int);
unsigned int GET32 ( unsigned int );
void  dummy ( unsigned int );

#define GPIOBASE 0x10012000
#define GPIO_VALUE          (GPIOBASE+0x00)
#define GPIO_INPUT_EN       (GPIOBASE+0x04)
#define GPIO_OUTPUT_EN      (GPIOBASE+0x08)
#define GPIO_PORT           (GPIOBASE+0x0C)
#define GPIO_PUE            (GPIOBASE+0x10)
#define GPIO_OUT_XOR        (GPIOBASE+0x40)

int notmain ( void )
{
    unsigned int rx;

    PUT32(GPIO_OUTPUT_EN,(1<<19)|(1<<21)|(1<<22));
    PUT32(GPIO_PORT,(1<<19)|(1<<21)|(1<<22));
    PUT32(GPIO_OUT_XOR,0);
    while(1)
    {
        PUT32(GPIO_PORT,(1<<19)|(1<<21)|(1<<22));
        for(rx=0;rx<2000000;rx++) dummy(rx);
        PUT32(GPIO_PORT,0);
        for(rx=0;rx<2000000;rx++) dummy(rx);
    }

    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
