# Test sequence from START: no input => PORTB: 0x04
test "PINA: 0x00 => PORTB: 0x04, state: THREE"
set state = START
setPINA 0x00
continue 3
expectPORTB 0x04
checkResult

# Test sequence from PAUSE: no input, A0 => PORTB: 0x01
test "PINA: 0x00, 0x01 => PORTB: 0x01, state: ONE"
set state = PAUSE
setPINA 0x00
continue 2
setPINA 0x01
continue 1
expectPORTB 0x01
checkResult

# Test sequence from PAUSE: no input, A0, no input => PORTB: 0x02
test "PINA: 0x00, 0x01, 0x00 => PORTB: 0x02, state: TWO"
set state = PAUSE
setPINA 0x00
continue 2
setPINA 0x01
continue 1
setPINA 0x00
continue 1
expectPORTB 0x02
checkResult

# Test sequence from PAUSE: no input, A0, no input, no input => PORTB: 0x04
test "PINA: 0x00, 0x01, 0x00, 0x00 => PORTB: 0x04, state: THREE"
set state = PAUSE
setPINA 0x00
continue 2
setPINA 0x01
continue 1
setPINA 0x00
continue 1
setPINA 0x00
continue 1
expectPORTB 0x04
checkResult