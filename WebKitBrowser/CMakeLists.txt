set(PLUGIN_NAME WebKitBrowser)

include(module) # Setup default stuff needed for the cmake framework thingy.

option(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_STUBBED "Include the wpe browser as a stubbed plugin." OFF)
option(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_YOUTUBE "Include YouTube in seperate plugin." OFF)
option(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_APPS "Include Apps instance in seperate plugin." OFF)
option(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_UX "Include UX in seperate plugin." OFF)

set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_AUTOSTART false CACHE STRING "Automatically start WebKitBrowser plugin")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_TRANSPARENT false CACHE STRING "Set transparency")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_STARTURL "about:blank" CACHE STRING "Initial URL for WebKitBrowser plugin")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_USERAGENT "Mozilla/5.0 (Macintosh, Intel Mac OS X 10_11_4) AppleWebKit/602.1.28+ (KHTML, like Gecko) Version/9.1 Safari/601.5.17" CACHE STRING "User agent string")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_MEMORYPROFILE "512m" CACHE STRING "Memory Profile")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_MEMORYPRESSURE "databaseprocess:50m,networkprocess:100m,webprocess:300m,rpcprocess:50m" CACHE STRING "Memory Pressure")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_MEDIADISKCACHE false CACHE STRING "Media Disk Cache")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_MSEBUFFERS "audio:2m,video:15m,text:1m" CACHE STRING "MSE Buffers for WebKit")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_DISKCACHE "0" CACHE STRING "Disk Cache")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_XHRCACHE true CACHE STRING "XHR Cache")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_LOCALSTORAGE "" CACHE STRING "HTML5 local storage path")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_COOKIESTORAGE "" CACHE STRING "Browser cookie storage path")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_WINDOWCLOSE false CACHE STRING "Allow window close")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_WEBGL true CACHE STRING "Enable WebGL")
set(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_THREADEDPAINTING "1" CACHE STRING "Threads for the Threaded Painting")
set(WPEFRAMEWORK_PLUGIN_YOUTUBE_USERAGENT ${WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_USERAGENT} CACHE STRING "User agent string YouTube")
set(WPEFRAMEWORK_PLUGIN_UX_AUTOSTART false CACHE STRING "Automatically start UX plugin")
set(WPEFRAMEWORK_PLUGIN_UX_USERAGENT ${WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_USERAGENT} CACHE STRING "User agent string for UX")
set(WPEFRAMEWORK_PLUGIN_APPS_AUTOSTART false CACHE STRING "Automatically start Apps plugin")
set(WPEFRAMEWORK_PLUGIN_APPS_USERAGENT ${WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_USERAGENT} CACHE STRING "User agent string for Apps")
find_package(GLIB REQUIRED)
find_package(WPEWebKit REQUIRED)

set(PLUGIN_DEFINITIONS)

if(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_STUBBED)
    list(APPEND PLUGIN_DEFINITIONS __STUBBED__)
endif()

set(PLUGIN_DEPENDENCIES_INCLUDE_DIRS
    ${WPE_WEBKIT_INCLUDE_DIRS}
    ${WPE_WEBKIT_INCLUDE_DIRS}/WPE
    ${GLIB_INCLUDE_DIRS})

set(PLUGIN_DEPENDENCIES
    ${GLIB_LIBRARIES}
    ${WPE_WEBKIT_LIBRARIES})

set(PLUGIN_OPTIONS)

set(PLUGIN_LINK_OPTIONS)

set(PLUGIN_SOURCES 
    Module.cpp
    WebKitBrowser.cpp
    WebKitImplementation.cpp
    InjectedBundle/WhiteListedOriginDomainsList.cpp
    InjectedBundle/Utils.cpp
)

include(default_targets) # This is a regular plugin no need to edit the defaults

if(NOT WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_STUBBED)
    # also build injected bundle
    add_subdirectory(InjectedBundle)
endif()

write_config( ${PLUGIN_NAME} )

# youtube configuration
if(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_YOUTUBE)
    write_config( YouTube )
endif()

# Applications instance configuration
if(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_APPS)
    write_config( Apps )
endif()

# youtube configuration
if(WPEFRAMEWORK_PLUGIN_WEBKITBROWSER_UX)
    write_config( UX )
endif()
