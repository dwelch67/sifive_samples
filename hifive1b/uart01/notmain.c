
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void PUT32( unsigned int, unsigned int);
unsigned int GET32 ( unsigned int );
void  dummy ( unsigned int );
unsigned int MCYCLE ( void );
unsigned int AMOSWAP ( unsigned int, unsigned int);

#define GPIOBASE 0x10012000
#define GPIO_VALUE          (GPIOBASE+0x00)
#define GPIO_INPUT_EN       (GPIOBASE+0x04)
#define GPIO_OUTPUT_EN      (GPIOBASE+0x08)
#define GPIO_PORT           (GPIOBASE+0x0C)
#define GPIO_PUE            (GPIOBASE+0x10)
#define GPIO_OUT_XOR        (GPIOBASE+0x40)
#define GPIO_IOF_EN         (GPIOBASE+0x38)
#define GPIO_IOF_SEL        (GPIOBASE+0x3C)

#define UART0BASE       0x10013000
#define UART0_TXDATA    (UART0BASE+0x00)
#define UART0_RXDATA    (UART0BASE+0x04)
#define UART0_TXCTRL    (UART0BASE+0x08)
#define UART0_RXCTRL    (UART0BASE+0x0C)
#define UART0_IE        (UART0BASE+0x10)
#define UART0_IP        (UART0BASE+0x14)
#define UART0_DIV       (UART0BASE+0x18)

#define MTIME 0x0200BFF8

//-------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;

if(0)
{
    unsigned int rb;
    unsigned int mt;
    unsigned int mc;

    //measure cpu ticks relative to 32768 clock
    ra=GET32(MTIME);
    while(1)
    {
        rb=GET32(MTIME);
        if(rb!=ra) break;
    }
    mc=MCYCLE();
    while(1)
    {
        ra=GET32(MTIME);
        if((ra-rb)>=16) break;
    }
    mt=MCYCLE();
    mt-=mc;
    mt<<=11;
    PUT32(0x80001000,mt);
    //mdw 0x80001000
    //0x80001000: 0102e000
}

    //13.8M/115200 = 120
    //17M/115200 = 147.5
    //16m / 115200 = 139

    ra=GET32(GPIO_IOF_SEL);
    ra&=~(1<<16); //UART0_RX
    ra&=~(1<<17); //UART0_TX
    PUT32(GPIO_IOF_SEL,ra);
    ra=GET32(GPIO_IOF_EN);
    ra|=1<<16; //UART0_RX
    ra|=1<<17; //UART0_TX
    PUT32(GPIO_IOF_EN,ra);
    //PUT32(UART0_DIV,120-1);
    //PUT32(UART0_DIV,148-1);
    PUT32(UART0_DIV,139-1);
    PUT32(UART0_TXCTRL,0x00000003);

    AMOSWAP(UART0_TXDATA,0x55);

if(1)
{
    for(ra=0;;ra++)
    {
        while(1)
        {
            if((GET32(UART0_TXDATA)&0x80000000)==0) break;
        }
        AMOSWAP(UART0_TXDATA,0x30+(ra&7));
    }
}

    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
