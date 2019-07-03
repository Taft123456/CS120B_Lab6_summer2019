# Test sequence from START: no input => PORTB: 0x01
test "PINA: 0x00 => PORTB: 0x01, state: ONE"
set state = START
setPINA 0x00
continue 1
expectPORTB 0x01
checkResult

# Test sequence from START: no input => PORTB: 0x02
test "PINA: 0x00 => PORTB: 0x02, state: TWO"
set state = START
setPINA 0x00
continue 2
expectPORTB 0x02
checkResult

# Test sequence from START: no input => PORTB: 0x04
test "PINA: 0x00 => PORTB: 0x04, state: THREE"
set state = START
setPINA 0x00
continue 3
expectPORTB 0x04
checkResult

# Test sequence from ONE: no input => PORTB: 0x00
test "PINA: 0x00 => PORTB: 0x00, state: START"
set state = ONE
setPINA 0x00
continue 3
expectPORTB 0x00
checkResult