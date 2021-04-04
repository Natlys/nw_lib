--==<native_library_project>==--
project("nw_lib")
	kind("staticlib")
	staticruntime("on")
	language("c++")
	cppdialect("c++17")
	systemversion("latest")
	targetdir(dir_out_res)
	objdir(dir_out_int)
	pchheader("nw_lib_pch.hpp")
	pchsource("src_cpp/nw_lib_pch.cpp")
	files { "%{dir_cpp.own}**.c**", "%{dir_cpp.own}**.h**" }
	includedirs { "%{dir_cpp.own}" }
--==</native_library_project>==--