if(CONFIG_BOARD_CHARGE_RATE_100MA)
zephyr_library()
zephyr_library_sources(board.c)
endif()
