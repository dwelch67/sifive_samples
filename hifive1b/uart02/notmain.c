
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

static void uart_init ( void )
{
    unsigned int ra;
   //16m / 115200 = 139
    ra=GET32(GPIO_IOF_SEL);
    ra&=~(1<<16); //UART0_RX
    ra&=~(1<<17); //UART0_TX
    PUT32(GPIO_IOF_SEL,ra);
    ra=GET32(GPIO_IOF_EN);
    ra|=1<<16; //UART0_RX
    ra|=1<<17; //UART0_TX
    PUT32(GPIO_IOF_EN,ra);
    PUT32(UART0_DIV,139-1);
    PUT32(UART0_TXCTRL,0x00000003);
    PUT32(UART0_RXCTRL,0x00000001);
}
static unsigned int uart_recv ( void )
{
    unsigned int data;
    while(1)
    {
        data=GET32(UART0_RXDATA);
        if((data&0x80000000)==0) break;
    }
    return(data&0xFF);
}
static void uart_send ( unsigned int data )
{
    while(1)
    {
        if(((GET32(UART0_TXDATA))&0x80000000)==0) break;
    }
    PUT32(UART0_TXDATA,data);
}
static void hexstrings ( unsigned int d )
{
    unsigned int rb;
    unsigned int rc;

    rb=32;
    while(1)
    {
        rb-=4;
        rc=(d>>rb)&0xF;
        if(rc>9) rc+=0x37; else rc+=0x30;
        uart_send(rc);
        if(rb==0) break;
    }
    uart_send(0x20);
}
static void hexstring ( unsigned int d )
{
    hexstrings(d);
    uart_send(0x0D);
    uart_send(0x0A);
}
int notmain ( void )
{
    unsigned int ra;

    uart_init();
    hexstring(0x12345678);
    while(1)
    {
        ra=uart_recv();
        uart_send(ra);
        if(ra==0x0D) uart_send(0x0A);
    }
    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
