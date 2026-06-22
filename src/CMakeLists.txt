add_library(
    c_fingerprint_identification_lib
    STATIC
        image/stb.c
        image/image.c
        image/bit_image.c
        thinning/destair_holt.c
        thinning/thinning_zhang_suen.c
        fingerprint_minutae/fingerprint_minutae.c
)

target_include_directories(
    c_fingerprint_identification_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/image
        ${CMAKE_CURRENT_SOURCE_DIR}/thinning
)
