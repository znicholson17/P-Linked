# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c")
set(COMPONENT_ADD_INCLUDEDIRS "")


idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS ""
                    REQUIRES socket_server
                    REQUIRES freertos 
                        esp_common 
                        esp_event 
                        nvs_flash 
                        wifi)

