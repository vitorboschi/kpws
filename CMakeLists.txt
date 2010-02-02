project (kpws)
find_package(KDE4 REQUIRED)
include (KDE4Defaults)
include_directories(${KDE4_INCLUDES})
set(kpws_SRCS 
	main.cpp
	mainwindow.cpp
	webserver.cpp
	webcontent.cpp
	webcontent_dummy.cpp
	webcontent_virtualfolder.cpp
	webcontent_file.cpp
	worker.cpp)
kde4_add_executable(kpws ${kpws_SRCS})
target_link_libraries(kpws ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS})
install(TARGETS kpws  ${INSTALL_TARGETS_DEFAULT_ARGS})
