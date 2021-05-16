--==<native_wolrd_library/>==--
project("nc_lib")
	--general--
	--kind("consoleapp")
	kind("staticlib")
	--kind("sharedlib")
	--libraries--
	links{ "nc_cfg" }
	libdirs{ "../nc_cfg/" }
	--filters--
	----platform_filters----
	filter("platforms:win64")
		system("windows")
	----system_filters----
	filter("system:windows")
		systemversion("latest")
	----language_filters----
	filter("language:c++")
		--standard--
		premake.tools.gcc.cxx = "g++.exe"
		cppdialect("c++17")
		clr("off")
		rtti("off")
		--source--
		files{"src_cpp/**.cpp", "src_cpp/**.hpp"}
		includedirs {"src_cpp/"}
		--binary--
		targetdir ("bin_cpp/")
		objdir ("bin_cpp/")
	filter("language:c")
		--standard--
		premake.tools.gcc.cc = "gcc.exe"
		cdialect("c99")
		clr("off")
		--source--
		files{"src_cxx/**.c", "src_cxx/**.h"}
		includedirs {"src_cxx/"}
		--binary--
		targetdir ("bin_cxx/")
		objdir ("bin_cxx/")
	----file_filters----
--==</native_wolrd_library>==--