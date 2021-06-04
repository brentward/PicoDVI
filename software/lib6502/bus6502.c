#include "hardware/pio.h"
#include "bus6502.pio.h"

#define NUM_PINS 15

static void pio_init(PIO pio, uint pin) {

   // Load the Control program
   uint offset_control0 = pio_add_program(pio, &bus6502_control0_program);
   uint offset_control1 = pio_add_program(pio, &bus6502_control1_program);
   uint offset_control2 = pio_add_program(pio, &bus6502_control2_program);
   uint offset_control3 = pio_add_program(pio, &bus6502_control3_program);

   for (uint i = 0; i < NUM_PINS; i++) {
      pio_gpio_init(pio, pin + i);
   }

   // Set the default pindirs of all state machines to input
   for (uint sm = 0; sm < 4; sm++) {
      pio_sm_set_consecutive_pindirs(pio, sm, pin, NUM_PINS, false);
   }

   // Configure P0 / SM0 (the control state machine)
   pio_sm_config c00 = bus6502_control0_program_get_default_config(offset_control0);
   sm_config_set_in_pins (&c00, pin + 12); // mapping for IN and WAIT (nRST)
   sm_config_set_jmp_pin (&c00, pin + 13); // mapping for JMP (nTUBE)
   sm_config_set_in_shift(&c00, true, false, 0); // shift right, no auto push
   pio_sm_init(p0, 0, offset_control0 + bus6502_control0_offset_entry_point, &c00);

   // Configure P0 / SM1 (the control state machine)
   pio_sm_config c01 = bus6502_control1_program_get_default_config(offset_control1);
   sm_config_set_in_pins (&c01, pin     ); // mapping for IN and WAIT
   sm_config_set_jmp_pin (&c01, pin + 11); // mapping for JMP (RnW)
   pio_sm_init(p0, 1, offset_control1 + bus6502_control1_offset_entry_point, &c01);

   // Configure P0 / SM2 (the control state machine)
   pio_sm_config c02 = bus6502_control2_program_get_default_config(offset_control2);
   sm_config_set_in_pins (&c02, pin     ); // mapping for IN and WAIT
   sm_config_set_jmp_pin (&c02, pin + 8 ); // mapping for JMP (A0)
   pio_sm_init(p0, 2, offset_control2 + bus6502_control2_offset_entry_point, &c02);

   // Configure P0 / SM3 (the control state machine)
   pio_sm_config c03 = bus6502_control3_program_get_default_config(offset_control3);
   sm_config_set_in_pins (&c03, pin     ); // mapping for IN and WAIT
   sm_config_set_in_shift(&c03, false, false, 0); // shift left, no auto push
   sm_config_set_fifo_join(&c03, PIO_FIFO_JOIN_RX);
   pio_sm_init(p0, 3, offset_control3 + bus6502_control3_offset_entry_point, &c03);


   // Enable all the state machines
   for (uint sm = 0; sm < 4; sm++) {
      pio_sm_set_enabled(pio, sm, true);
   }
}

void dma_init(PIO pio, uint sm, uint dma_chan, uint32_t *capture_buf, size_t capture_size_words,
                        uint trigger_pin, bool trigger_level) {git 