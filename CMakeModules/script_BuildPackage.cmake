#  +---------------------------------------------------------------------------+
#  |                                                                           |
#  | Fluicell AB, http://fluicell.com/                                         |
#  | Lab-on-a-tip                                                              |
#  |                                                                           |
#  | Authors: Mauro Bellone - http://www.maurobellone.com                      |
#  | Released under GNU GPL License.                                           |
#  +---------------------------------------------------------------------------+ */

# build a CPack driven installer package


# the build package only works in windows 
if( WIN32 AND NOT UNIX )

#define the website -- TODO: change with the real website
set (WEBSITE "http://fluicell.com/")   
set (WEB_TUTORIAL "share/doc/___/tutorials/html/index.html")  
set (WEB_DOCS "share/doc/___/html/____.chm")  
set (WEB_DEV "http://www.maurobellone.com")

# set the info/about for the executable - can be changed to some other comment
set(CPACK_NSIS_URL_INFO_ABOUT "${WEBSITE}")
set(CPACK_NSIS_HELP_LINK "${WEBSITE}")

set(CPACK_PACKAGE_NAME "Lab-on-a-tip")
set(CPACK_PACKAGE_VENDOR "Fluicell AB")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Fluicell Lab-on-a-tip")
set(CPACK_NSIS_CONTACT "Mauro Bellone bellonemauro@gmail.com" )
set(CPACK_PACKAGE_INSTALL_DIRECTORY "@PROJECT_NAME@")# @_VERSION@")

# this allows to check older installations and properly remove them
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL "ON") 

# add the licence file
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")  

# and readme file
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")#AUTHORS.txt

#set the package version
set (CPACK_PACKAGE_VERSION "${CMAKE_Fluicell_FULL_VERSION}")     

#set a cool icon to start the application
set (CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/fluicell_logo.ico") #program icon
#set (CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/fluicell_iconBIG.ico") #uninstall icon

#set (CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Resources/fluicell_iconBIG.png")# -- NOT FOUND -- ??

set(CPACK_NSIS_MENU_LINKS 
            "${WEBSITE}" "Homepage for Fluicell Lab-on-a-tip ${WEBSITE}"          
            "Lab-on-a-tip.exe" "Lab-on-a-tip"
            "Lab-on-a-tip_console.exe" "Lab-on-a-tip console"
			"uninstall.exe" "Uninstall Lab-on-a-tip"
			"${WEB_TUTORIAL}" "Tutorials"
            "${WEB_DOCS}" "Documentation"
            "${WEB_DEV}" "Developer Website" )

set(CPACK_NSIS_DISPLAY_NAME "Fluicell Lab-on-a-tip2 ") #V.${CMAKE_Fluicell_FULL_VERSION}")
			
#allows NSIS to modify paths
set (CPACK_NSIS_MODIFY_PATH "ON")     

#SET(CPACK_PACKAGE_EXECUTABLES "Target_Name" "Target Name")
SET(CPACK_PACKAGE_EXECUTABLES "Lab-on-a-tip" "Lab-on-a-tip")


#create a desktop icon with link to the .exe file
set(CPACK_CREATE_DESKTOP_LINKS "Lab-on-a-tip" "Lab-on-a-tip")

# required by cmake to install new registry key for the executable
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${CMAKE_PROJECT_NAME}")#-${CMAKE_Fluicell_FULL_VERSION}")

# this is to create the user folders during the installation
set( CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
	CreateDirectory \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\" 
	CreateDirectory \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\presetProtocols\\\"
	CreateDirectory \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\settings\\\" 
	CreateDirectory \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\Ext_data\\\" 
	CopyFiles \\\"$INSTDIR\\\\presetProtocols\\\\*.prt\\\" \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\presetProtocols\\\"
	CopyFiles \\\"$INSTDIR\\\\settings\\\\*.ini\\\" \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\settings\\\"
	")

set(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")


# Icon in the add/remove control panel. Must be an .exe file 
set(CPACK_NSIS_INSTALLED_ICON_NAME Lab-on-a-tip.exe)

set(CPACK_NSIS_MUI_FINISHPAGE_RUN Lab-on-a-tip.exe)


#set(CPACK_NSIS_MUI_UNPAGE_WELCOME )
#set(CPACK_NSIS_MUI_UNPAGE_CONFIRM )
#set(CPACK_NSIS_MUI_UNCONFIRMPAGE_TEXT_LOCATION "ATTENTION: this will also remove user files, click cancel to abort") 
#set(CPACK_NSIS_MUI_UNPAGE_COMPONENTS )
#set(CPACK_NSIS_MUI_UNPAGE_DIRECTORY )
#set(CPACK_NSIS_MUI_UNPAGE_INSTFILES )
#set(CPACK_NSIS_MUI_UNPAGE_FINISH )



#add a command to remove user created files - ATTENTION: it will also remove user created files !!!
set( CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
	Delete \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\presetProtocols\\\\*.prt\\\" 
	Delete \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\settings\\\\*.ini\\\" 
	Delete \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\Ext_data\\\\*.*\\\" 
	RMDir \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\presetProtocols\\\"
	RMDir \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\settings\\\" 
	RMDir \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\\Ext_data\\\" 
	RMDir \\\"$PROFILE\\\\Documents\\\\Labonatip2\\\" 
")

												   
message (STATUS "BUILD PACKAGE STATUS MESSAGE : building version ${CMAKE_Fluicell_FULL_VERSION} " )

# make the package 
include (CPack)

# I really would like to have this feature but unfortunately it is still not supported ! 
if(BUILD_WINDEPLOYQT AND WIN32)
		# Run winddeployqt if it can be found
	find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS ${QT5_BINARY_DIR} ENV QTDIR PATH_SUFFIXES bin)
    FILE(GLOB FILE_EXE "${PROJECT_BINARY_DIR}/bin/Release/*.exe")
      FOREACH(F ${FILE_EXE})
        #INSTALL(FILES "${F}" DESTINATION ./)
 	    message (STATUS "     WINDEPLOYQT_EXECUTABLE is : ${WINDEPLOYQT_EXECUTABLE} \n")
 	    message (STATUS "     Current file target is : ${F} \n")
		message (STATUS "     PROJECT_NAME is : ${PROJECT_NAME} \n")
	    #HERE we cannot specify the target PACKAGE or package 
		#add_custom_command(TARGET PACKAGE PRE_BUILD WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/bin/Release/ COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${F}> COMMENT "Preparing Qt runtime dependencies")

	  ENDFOREACH(F)
endif()

#in order to support the previous feature of deploying QT, the previous lines have been added to the lab-on-a-tip gui application
#anyway to avoid the deployment to run every time it is compiled, the variable BUILD_WINDEPLOYQT is set to 0
if (NOT ENABLE_WINDEPLOYQT )
		message (WARNING "     REMEMBER TO DEFINE BUILD_WINDEPLOYQT if you want to build the package \n")
endif()
  
else (WIN32 AND NOT UNIX)
  message(STATUS " BUIL PACKAGE NOT YET SUPPORTED " )
endif()