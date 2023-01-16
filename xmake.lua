set_project("flc-flashcards")
add_rules("mode.debug", "mode.release")

add_requires("fmt", "nlohmann_json", "sdl2", "opengl")

set_languages("cxxlatest")

target("imgui")
    set_kind("static")
    set_warnings("none")
	add_packages("sdl2", "opengl")
	add_includedirs("external/imgui", {public = true})
	add_includedirs("external/imgui/backends", {public = true})
    add_files("external/imgui/*.cpp")
    add_files("external/imgui/backends/imgui_impl_sdl.cpp")
    add_files("external/imgui/backends/imgui_impl_opengl3.cpp")

target("flc")
	set_kind("binary")
    if is_mode("debug") then
        set_warnings("all", "error")
    else
        set_warnings("everything", "error")
    end
	add_includedirs("include")
	add_packages("fmt", "nlohmann_json", "sdl2", "opengl")
	add_files("src/*.cpp")
	add_deps("imgui")
