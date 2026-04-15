SET(EXAMPLE_NAME "Vulkan-glTF-PBR")
file(GLOB SOURCE *.cpp ${BASE_HEADERS})
file(GLOB SHADERS "../data/shaders/*.vert" "../data/shaders/*.frag" "../data/shaders/*.comp" "../data/shaders/*.geom" "../data/shaders/*.tesc" "../data/shaders/*.tese")
file(GLOB SHADER_INCLUDES "../data/shaders/includes/*.glsl")
source_group("Shaders" FILES ${SHADERS})
source_group("Shaders\\Includes" FILES ${SHADER_INCLUDES})
if(WIN32)
	add_executable(${EXAMPLE_NAME} WIN32 ${MAIN_CPP} ${SOURCE} ${SHADERS} ${SHADER_INCLUDES})
	target_link_libraries(${EXAMPLE_NAME} base ${Vulkan_LIBRARY} ${WINLIBS} SDL3::SDL3)

	# copy the SDL3.dll to the target dir
	add_custom_command(
		TARGET ${EXAMPLE_NAME} POST_BUILD
		COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:${EXAMPLE_NAME}>
		VERBATIM
	)
else(WIN32)
	add_executable(${EXAMPLE_NAME} ${MAIN_CPP} ${SOURCE} ${SHADERS} ${SHADER_INCLUDES})
	target_link_libraries(${EXAMPLE_NAME} base SDL3::SDL3)
endif(WIN32)
if(RESOURCE_INSTALL_DIR)
	install(TARGETS ${EXAMPLE_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()