# Set libriary source file
set(LIBNUMBER_SRC Num.cpp NumN.cpp NumZ.cpp NumQ.cpp NumR.cpp NumC.cpp)

# Add shared & static library
add_library(number SHARED ${LIBNUMBER_SRC})
add_library(number_static STATIC ${LIBNUMBER_SRC})
set_target_properties(number_static PROPERTIES OUTPUT_NAME "number")

# Set library version
set_target_properties(number PROPERTIES VERSION 0.0.1 SOVERSION 0.0.1)

# Set install path
install(TARGETS number number_static
	LIBRARY DESTINATION lib/Niacin
	ARCHIVE DESTINATION lib/Niacin)
	
