
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

//actually a 64 bit register:
#define MTIME 0x0200BFF8
//#define DELAY 0x80000
#define DELAY 0x4000
//-------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;
    unsigned int rx;
    unsigned int last;
    unsigned int now;

    ra=GET32(GPIO_INPUT_EN);
    ra&=~(1<<19)|(1<<21)|(1<<22);
    PUT32(GPIO_INPUT_EN,ra);
    ra=GET32(GPIO_OUTPUT_EN);
    ra|=(1<<19)|(1<<21)|(1<<22);
    PUT32(GPIO_OUTPUT_EN,ra);
    ra=GET32(GPIO_PORT);
    ra|=(1<<19)|(1<<21)|(1<<22);
    PUT32(GPIO_PORT,ra);
    ra=GET32(GPIO_OUT_XOR);
    ra&=~(1<<19)|(1<<21)|(1<<22);
    PUT32(GPIO_OUT_XOR,ra);
    last=GET32(MTIME);
    while(1)
    {
        ra=GET32(GPIO_PORT);
        ra|= (1<<22);
        ra&=~(1<<19);
        PUT32(GPIO_PORT,ra);
        while(1)
        {
            now=GET32(MTIME);
            rx=now-last;
            if(rx>DELAY) break;
        }
        last=now;

        ra=GET32(GPIO_PORT);
        ra|= (1<<19);
        ra&=~(1<<21);
        PUT32(GPIO_PORT,ra);
        while(1)
        {
            now=GET32(MTIME);
            rx=now-last;
            if(rx>DELAY) break;
        }
        last=now;

        ra=GET32(GPIO_PORT);
        ra|= (1<<21);
        ra&=~(1<<22);
        PUT32(GPIO_PORT,ra);
        while(1)
        {
            now=GET32(MTIME);
            rx=now-last;
            if(rx>DELAY) break;
        }
        last=now;
    }

    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
