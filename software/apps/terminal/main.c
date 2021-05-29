#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "hardware/gpio.h"
#include "hardware/vreg.h"
#include "hardware/structs/bus_ctrl.h"
#include "hardware/structs/ssi.h"
#include "hardware/dma.h"
#include "pico/sem.h"

#include "dvi.h"
#include "dvi_serialiser.h"
#include "common_dvi_pin_configs.h"
#include "tmds_encode.h"

#include "6502bus.h"

#include "font_8x16.h"
#define FONT_CHAR_WIDTH 8
#define FONT_CHAR_HEIGHT 16
#define FONT_N_CHARS 256
#define FONT_FIRST_ASCII 0


// Pick one:
#define MODE_640x480_60Hz
// #define MODE_800x600_60Hz
// #define MODE_960x540p_60Hz
// #define MODE_1280x720_30Hz

#if defined(MODE_640x480_60Hz)
// DVDD 1.2V (1.1V seems ok too)
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480
#define VREG_VSEL VREG_VOLTAGE_1_20
#define DVI_TIMING dvi_timing_640x480p_60hz

#elif defined(MODE_800x600_60Hz)
// DVDD 1.3V, going downhill with a tailwind
#define FRAME_WIDTH 800
#define FRAME_HEIGHT 600
#define VREG_VSEL VREG_VOLTAGE_1_30
#define DVI_TIMING dvi_timing_800x600p_60hz


#elif defined(MODE_960x540p_60Hz)
// DVDD 1.25V (slower silicon may need the full 1.3, or just not work)
#define FRAME_WIDTH 960
#define FRAME_HEIGHT 540
#define VREG_VSEL VREG_VOLTAGE_1_25
#define DVI_TIMING dvi_timing_960x540p_60hz

#elif defined(MODE_1280x720_30Hz)
// 1280x720p 30 Hz (nonstandard)
// DVDD 1.25V (slower silicon may need the full 1.3, or just not work)
#define FRAME_WIDTH 1280
#define FRAME_HEIGHT 720
#define VREG_VSEL VREG_VOLTAGE_1_25
#define DVI_TIMING dvi_timing_1280x720p_30hz

#else
#error "Select a video mode!"
#endif

#define LED_PIN 16

// #define CLK_PIN 2
// #define RWB_PIN 3
// #define FIRST_DATA_PIN 4 // Data bus d7=4,d6=5,d5=6,d4=7,d3=8,d2=9,d1=10,d0=11
// #define FIRST_RS_PIN 20 // Register Select lines, RS1=20,RS0=21
// #define CS0_PIN 22
// #define CS1B_PIN 26
#define RESB_PIN 4

struct dvi_inst dvi0;
struct semaphore dvi_start_sem;

#define CHAR_COLS (FRAME_WIDTH / FONT_CHAR_WIDTH)
#define CHAR_ROWS (FRAME_HEIGHT / FONT_CHAR_HEIGHT)
char charbuf[CHAR_ROWS * CHAR_COLS];
int charbuf_pos;
int frame_line_offset;
// bool rwb;
// bool cs0;
// bool cs1b;
// char addr;
// char data;
// bool write_data;
// char read_addr();
// char read_data();
// void set_data_direction(bool rwb);
void reset ();
// void clock_low();
// void clock_high();

static inline void prepare_scanline(const char *chars, uint y) {
	static uint8_t scanbuf[FRAME_WIDTH / 8];
	// First blit font into 1bpp scanline buffer, then encode scanbuf into tmdsbuf
	y = (y + (frame_line_offset * FONT_CHAR_HEIGHT)) % FRAME_HEIGHT;
	for (uint i = 0; i < CHAR_COLS; ++i) {
		uint c = chars[i + y / FONT_CHAR_HEIGHT * CHAR_COLS];
		scanbuf[i] = font_8x16[(c - FONT_FIRST_ASCII) + (y % FONT_CHAR_HEIGHT) * FONT_N_CHARS];
	}
	uint32_t *tmdsbuf;
	queue_remove_blocking(&dvi0.q_tmds_free, &tmdsbuf);
	tmds_encode_1bpp((const uint32_t*)scanbuf, tmdsbuf, FRAME_WIDTH);
	queue_add_blocking(&dvi0.q_tmds_valid, &tmdsbuf);
}

void core1_scanline_callback() {
	static uint y = 1;
	prepare_scanline(charbuf, y);
	y = (y + 1) % FRAME_HEIGHT;
}

void gpio_callback(uint gpio, uint32_t events) {
	if (gpio == RESB_PIN) {
		reset();
	// } else if (gpio == CLK_PIN) {
	// 	if (events == GPIO_IRQ_EDGE_FALL) {
	// 		clock_low();
	// 	} else if (events == GPIO_IRQ_EDGE_RISE) {
	// 		clock_high();
	// 	}
	} 
}

// void clock_low() {
// 	// cs0 = gpio_get(CS0_PIN);
// 	// cs1b = gpio_get(CS1B_PIN);

// 	// for (int i = 0; i < 2; ++i) {
// 	// 	__asm volatile ("nop\n");
// 	// }
// 	if (gpio_get(CS0_PIN) && !gpio_get(CS1B_PIN)) {
// 		addr = read_addr();
// 		rwb = gpio_get(RWB_PIN);
// 		cs0 = gpio_get(CS0_PIN);
// 		cs1b = gpio_get(CS1B_PIN);
// 	}
// }

// void clock_high() {
// 	if (cs0 && !cs1b) {
// 		if (rwb) {
// 			//read code
// 		} else {
// 			// for (int i = 0; i < 2; ++i) {
// 			// 	__asm volatile ("nop\n");
// 			// }
// 			//write code
// 			data = read_data();
// 			write_data = true;
// 		}
// 	}
// }

void reset() {
	for (int i = 0; i < (CHAR_ROWS * CHAR_COLS); ++i) {
		charbuf[i] = ' ';
	}
	charbuf_pos = 0;
	frame_line_offset = 1;

}

// char read_addr() {
// 	char addr = 0;
// 	for (int i = 0; i < 2; ++i) {
// 		addr <<= 1;
// 		addr += gpio_is_pulled_up(FIRST_RS_PIN + i);
// 	}
// 	return addr;
// }

// void set_data_direction(bool rwb) {
// 	for (int i = 0; i < 8; ++i) {
// 		gpio_set_dir(FIRST_DATA_PIN + i, rwb);
// 	}

// }asdfasdfasdf

// char read_data() {
// 	char data = 0;
// 	for (int i = 0; i < 8; ++i) {
// 		data <<= 1;
// 		data += gpio_is_pulled_up(FIRST_DATA_PIN + i);
// 	}
// 	return data;

// }

void __not_in_flash("main") core1_main() {
	dvi_register_irqs_this_core(&dvi0, DMA_IRQ_0);
	sem_acquire_blocking(&dvi_start_sem);
	dvi_start(&dvi0);

	// The text display is completely IRQ driven (takes up around 30% of cycles @
	// VGA). We could do something useful, or we could just take a nice nap
	// gpio_init(RESB_PIN);
	// gpio_set_input_enabled(RESB_PIN, true);
	// gpio_set_dir(RESB_PIN, GPIO_IN);
	// gpio_pull_up(RESB_PIN);

	// int charbuf_pos = 0;
	// bool clk = true;
	// bool cs0 = false;
	// bool cs1b = true;
	// bool rwb = false;
	// char addr = 0;
	// bool reset = false;
	charbuf_pos = 0;
	frame_line_offset = 1;

	// rwb = true;
	// cs0 = false;
	// cs1b = true;
	// addr = 0;
	// data = 0;
	// write_data = false;

	while (1) {
		// if (write_data) {
		// 	switch(data) {
		// 		case 0x09 :
		// 			while (1) {
		// 				charbuf[charbuf_pos]  = ' ';
		// 				charbuf_pos = (charbuf_pos + 1) % (CHAR_ROWS * CHAR_COLS);
		// 				if (charbuf_pos % 4 == 0)
		// 					break;
		// 			}
		// 			break;
		// 		case 0x0D :
		// 			charbuf_pos = (((charbuf_pos / CHAR_COLS) + 1) * CHAR_COLS) % (CHAR_ROWS * CHAR_COLS);
		// 			break;
		// 		case 0x08 :
		// 		case 0x7F :
		// 			charbuf[(charbuf_pos - 1) % (CHAR_ROWS * CHAR_COLS)] = ' ';
		// 			charbuf_pos = (charbuf_pos - 1) % (CHAR_ROWS * CHAR_COLS);
		// 			break;
		// 		case 0x20 ... 0x7E:
		// 		case 0x80 ... 0xFF:
		// 			// printf("%c", c);
		// 			charbuf[charbuf_pos]  = data;
		// 			charbuf_pos = (charbuf_pos + 1) % (CHAR_ROWS * CHAR_COLS);
		// 			break;
		// 		default:
		// 			break;
		// 	}
		// 	write_data = false;

		// }
		// if (clk) {
		// 	bool clk_now = gpio_is_pulled_up(CLK_PIN);
		// 	if (!clk_now) {
		// 		clk = clk_now;
		// 		cs0 = gpio_is_pulled_up(CS0_PIN);
		// 		cs1b = gpio_is_pulled_up(CS1B_PIN);
		// 		rwb = gpio_is_pulled_up(RWB_PIN);
		// 		if (cs0 && !cs1b) {
		// 			addr = read_addr();
		// 		}
		// 	}
		// }
		// if (!clk) {
		// 	bool clk_now = gpio_is_pulled_up(CLK_PIN);
		// 	if (clk_now) {
		// 		if (cs0 && !cs1b && !rwb) {
		// 			char data = read_data();
		// 			switch(data) {
		// 				case 0x09 :
		// 					while (1) {
		// 						charbuf[charbuf_pos]  = ' ';
		// 						charbuf_pos = (charbuf_pos + 1) % (CHAR_ROWS * CHAR_COLS);
		// 						if (charbuf_pos % 4 == 0)
		// 							break;
		// 					}
		// 					break;
		// 				case 0x0D :
		// 					charbuf_pos = (((charbuf_pos / CHAR_COLS) + 1) * CHAR_COLS) % (CHAR_ROWS * CHAR_COLS);
		// 					break;
		// 				case 0x08 :
		// 				case 0x7F :
		// 					charbuf[(charbuf_pos - 1) % (CHAR_ROWS * CHAR_COLS)] = ' ';
		// 					charbuf_pos = (charbuf_pos - 1) % (CHAR_ROWS * CHAR_COLS);
		// 					break;
		// 				case 0x20 ... 0x7E:
		// 				case 0x80 ... 0xFF:
		// 					// printf("%c", c);
		// 					charbuf[charbuf_pos]  = data;
		// 					charbuf_pos = (charbuf_pos + 1) % (CHAR_ROWS * CHAR_COLS);
		// 					break;
		// 				default:
		// 					break;
		// 			}

		// 		}
		// 	}
		// }
		// if (!gpio_get(RESB_PIN)) {
		// 	for (int i = 0; i < (CHAR_ROWS * CHAR_COLS); ++i) {
		// 		charbuf[i] = ' ';
		// 		charbuf_pos = 0;
		// 	}
		// }

		// if (!reset) {
		// 	if (!gpio_get(RESB_PIN)) {
		// 		for (int i = 0; i < (CHAR_ROWS * CHAR_COLS); ++i) {
		// 			charbuf[i] = ' ';
		// 			charbuf_pos = 0;
		// 			reset = true;
		// 		}
		// 	}
		// }

		// if (reset) {
		// 	reset = !gpio_get(RESB_PIN);
		// }
		charbuf[charbuf_pos] = 219;
		char c = getchar();

		switch(c) {
			case 0x08 :
				charbuf[charbuf_pos]  = ' ';
				charbuf[(charbuf_pos - 1) % (CHAR_ROWS * CHAR_COLS)] = ' ';
				charbuf_pos = (charbuf_pos - 1) % (CHAR_ROWS * CHAR_COLS);
				break;
			case 0x09 :
				while (1) {
					charbuf[charbuf_pos]  = ' ';
					charbuf_pos = (charbuf_pos + 1) % (CHAR_ROWS * CHAR_COLS);
					if (charbuf_pos % 4 == 0)
						break;
					if (charbuf_pos % CHAR_COLS == 0) {
						for (int i = 0; i < CHAR_COLS; ++i) {
							charbuf[charbuf_pos + i] = ' ';
						}
						frame_line_offset = (frame_line_offset + 1) % CHAR_ROWS;
					}

				}
				break;
			case 0x0A :
				break;
			case 0x0D :
				charbuf[charbuf_pos]  = ' ';
				charbuf_pos = (((charbuf_pos / CHAR_COLS) + 1) * CHAR_COLS) % (CHAR_ROWS * CHAR_COLS);
				if (charbuf_pos % CHAR_COLS == 0) {
					for (int i = 0; i < CHAR_COLS; ++i) {
						charbuf[charbuf_pos + i] = ' ';
					}
					frame_line_offset = (frame_line_offset + 1) % CHAR_ROWS;
				}

				break;
			default:
			// case 0x20 ... 0x7E:
			// case 0x80 ... 0xFF:
				// printf("%c", c);
				charbuf[charbuf_pos]  = c;
				charbuf_pos = (charbuf_pos + 1) % (CHAR_ROWS * CHAR_COLS);
				if (charbuf_pos % CHAR_COLS == 0) {
					for (int i = 0; i < CHAR_COLS; ++i) {
						charbuf[charbuf_pos + i] = ' ';
					}
					frame_line_offset = (frame_line_offset + 1) % CHAR_ROWS;
				}

				// break;
			// case 0x7F :
			// default:
			// 	break;
		}
		__wfi();
	}
		// __wfi();
	__builtin_unreachable();
}

int __not_in_flash("main") main() {
	vreg_set_voltage(VREG_VSEL);
	sleep_ms(10);
#ifdef RUN_FROM_CRYSTAL
	set_sys_clock_khz(12000, true);
#else
	// Run system at TMDS bit clock
	set_sys_clock_khz(DVI_TIMING.bit_clk_khz, true);
#endif
	// strcpy(charbuf, "Foo bar is doom laser");


	setup_default_uart();
	// gpio_set_function(2, GPIO_FUNC_UART);
	// gpio_set_function(3, GPIO_FUNC_UART);
	// uart_set_hw_flow(uart0, true, true);
	

	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);

	// gpio_init(CLK_PIN);
    gpio_init(RESB_PIN);

    gpio_set_irq_enabled_with_callback(RESB_PIN, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    // gpio_set_irq_enabled_with_callback(CLK_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

	// gpio_set_function(RESB_PIN, GPIO_FUNC_SIO);
    // gpio_init(RESB_PIN);
    // gpio_set_dir(RESB_PIN, GPIO_IN);
    // gpio_pull_up(RESB_PIN);



	// gpio_init(RWB_PIN);
	// gpio_set_dir(RWB_PIN, GPIO_IN);
	// gpio_init(CS0_PIN);
	// gpio_set_dir(CS0_PIN, GPIO_IN);
	// gpio_init(CS1B_PIN);
	// gpio_set_dir(CS1B_PIN, GPIO_IN);
	// gpio_init(FIRST_RS_PIN);
	// gpio_set_dir(FIRST_RS_PIN, GPIO_IN);
	// gpio_init(FIRST_RS_PIN + 1);
	// gpio_set_dir(FIRST_RS_PIN + 1, GPIO_IN);
	// for (int i = 0; i < 8; ++i) {
	// 	gpio_init(FIRST_DATA_PIN + i);
	// 	gpio_set_dir(FIRST_DATA_PIN + i, GPIO_IN);
	// }



	// printf("Configuring DVI\n");

	// for (int i = 0; i < (CHAR_ROWS * CHAR_COLS); ++i)
	// 	charbuf[i] = 32;

	dvi0.timing = &DVI_TIMING;
	dvi0.ser_cfg = DEFAULT_DVI_SERIAL_CONFIG;
	dvi0.scanline_callback = core1_scanline_callback;
	dvi_init(&dvi0, next_striped_spin_lock_num(), next_striped_spin_lock_num());

	// printf("Prepare first scanline\n");
	// strcpy(charbuf, "Hello, World! In the charbuf.");
	// for (int i = 0; i < CHAR_ROWS * CHAR_COLS; ++i)
	// 	charbuf[i] = FONT_FIRST_ASCII + i % FONT_N_CHARS;
	prepare_scanline(charbuf, 0);

	// printf("Core 1 start\n");
	sem_init(&dvi_start_sem, 0, 1);
	hw_set_bits(&bus_ctrl_hw->priority, BUSCTRL_BUS_PRIORITY_PROC1_BITS);
	multicore_launch_core1(core1_main);


	sem_release(&dvi_start_sem);
	while (1) 
		__wfi();
	__builtin_unreachable();
}
	
