unsigned short seven_seg_digits[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

unsigned short digit1, digit2;
unsigned short count = 0;
void interrupt() {
    if (INTF_bit) {
        count++;
        INTF_bit = 0;
    }
}

void main() {
   TRISB = 0x01;
    TRISD = 0x00;
    TRISC = 0x00;

    PORTD = 0x00;
    PORTC = 0x00;

    OPTION_REG.INTEDG = 1;
    INTF_bit = 0;
    INTE_bit = 1;
    GIE_bit  = 1;

    while(1) {
        digit2 = count / 10;
        digit1 = count % 10;

        // Affichage multiplexé sur 7 segments
        PORTC = 0b00000001;
        PORTD = seven_seg_digits[digit1];
        Delay_ms(5);
        PORTC = 0b00000010;
        PORTD = seven_seg_digits[digit2];
        Delay_ms(5);

        if (count > 20) count = 0;
    }
}