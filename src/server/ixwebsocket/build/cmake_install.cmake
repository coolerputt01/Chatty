# Install script for directory: /workspaces/Chatty/src/server/ixwebsocket

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/workspaces/Chatty/src/server/ixwebsocket/build/libixwebsocket.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/workspaces/Chatty/src/server/ixwebsocket/IXBase64.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXBench.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXCancellationRequest.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXConnectionState.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXDNSLookup.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXExponentialBackoff.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXGetFreePort.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXGzipCodec.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXHttp.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXHttpClient.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXHttpServer.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXNetSystem.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXProgressCallback.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSelectInterrupt.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSelectInterruptFactory.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSelectInterruptPipe.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSelectInterruptEvent.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSetThreadName.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSocket.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSocketConnect.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSocketFactory.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSocketServer.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXSocketTLSOptions.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXStrCaseCompare.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXUdpSocket.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXUniquePtr.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXUrlParser.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXUuid.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXUtf8Validator.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXUserAgent.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocket.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketCloseConstants.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketCloseInfo.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketErrorInfo.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketHandshake.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketHandshakeKeyGen.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketHttpHeaders.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketInitResult.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketMessage.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketMessageType.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketOpenInfo.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketPerMessageDeflate.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketPerMessageDeflateCodec.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketPerMessageDeflateOptions.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketProxyServer.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketSendData.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketSendInfo.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketServer.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketTransport.h"
    "/workspaces/Chatty/src/server/ixwebsocket/IXWebSocketVersion.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "/workspaces/Chatty/src/server/ixwebsocket/build/ixwebsocket-config.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/workspaces/Chatty/src/server/ixwebsocket/build/ixwebsocket.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket/ixwebsocket-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket/ixwebsocket-targets.cmake"
         "/workspaces/Chatty/src/server/ixwebsocket/build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket/ixwebsocket-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket/ixwebsocket-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "/workspaces/Chatty/src/server/ixwebsocket/build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/ixwebsocket" TYPE FILE FILES "/workspaces/Chatty/src/server/ixwebsocket/build/CMakeFiles/Export/dbc99e06a99e696141dafd40631f8060/ixwebsocket-targets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/workspaces/Chatty/src/server/ixwebsocket/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
