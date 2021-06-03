# # Note we are using INTERFACE so that the library can be configured per-app
# # with compile-time defines

# add_library(lib6502 INTERFACE)

# target_sources(lib6502 INTERFACE
# 	${CMAKE_CURRENT_LIST_DIR}/6502bus.c
# 	${CMAKE_CURRENT_LIST_DIR}/6502bus.h
# 	)

# target_include_directories(lib6502 INTERFACE ${CMAKE_CURRENT_LIST_DIR})
# target_link_libraries(lib6502 INTERFACE
#     pico_base_headers
#     pico_util
#     hardware_dma
#     hardware_interp
#     hardware_pio
#     hardware_pwm
# )

# pico_generate_pio_header(libdvi ${CMAKE_CURRENT_LIST_DIR}/6502bus.pio)