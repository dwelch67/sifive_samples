
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
#define GPIO_IOF_EN         (GPIOBASE+0x38)
#define GPIO_IOF_SEL        (GPIOBASE+0x3C)
#define GPIO_OUT_XOR        (GPIOBASE+0x40)

int notmain ( void )
{
    unsigned int ra;
    unsigned int rx;

    ra=GET32(GPIO_IOF_EN);
    ra&=(~(1<<5));
    PUT32(GPIO_IOF_EN,ra);

    ra=GET32(GPIO_OUTPUT_EN);
    ra|=(1<<5);
    PUT32(GPIO_OUTPUT_EN,ra);

    ra=GET32(GPIO_PORT);
    ra|=(1<<5);
    PUT32(GPIO_PORT,ra);

    ra=GET32(GPIO_OUT_XOR);
    ra&=(~(1<<5));
    PUT32(GPIO_OUT_XOR,ra);
    while(1)
    {
        ra=GET32(GPIO_PORT);
        ra|=(1<<5);
        PUT32(GPIO_PORT,ra);
        for(rx=0;rx<2000000;rx++) dummy(rx);
        ra=GET32(GPIO_PORT);
        ra&=(~(1<<5));
        PUT32(GPIO_PORT,ra);
        for(rx=0;rx<2000000;rx++) dummy(rx);
    }

    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
