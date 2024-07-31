set(RTT_LOG_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/rtt_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/RTT/SEGGER_RTT.c
    ${CMAKE_CURRENT_SOURCE_DIR}/RTT/SEGGER_RTT_printf.c
    CACHE INTERNAL "rtt_log source files"
)

set(RTT_LOG_INC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/RTT
    CACHE INTERNAL "rtt_log include dirs"
)

#remember to add these in upper lists