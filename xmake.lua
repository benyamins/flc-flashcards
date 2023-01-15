set_project("flc-flashcards")
add_rules("mode.debug", "mode.release")

add_requires("fmt", "nlohmann_json", "sdl2", "opengl")

if is_mode("debug") then
	add_cxxflags("-std=c++2b", "-Wall", "-pedantic", "-pedantic-errors", "-Wconversion", "-Werror")
else
	add_cxxflags("-std=c++2b", "-Wall", "-Werror", "-pedantic", "-pedantic-errors", "-Wconversion", "-Wextra")
end

target("imgui")
    --set_kind("static")
    set_warnings("none")
	add_packages("sdl2", "opengl")
	add_includedirs("external/imgui", {public = true})
	add_includedirs("external/imgui/backends", {public = true})
    add_files("external/imgui/*.cpp")
    add_files("external/imgui/backends/imgui_impl_sdl.cpp")
    add_files("external/imgui/backends/imgui_impl_opengl3.cpp")

target("flc")
	set_kind("binary")
	add_includedirs("include")
	add_packages("fmt", "nlohmann_json", "sdl2", "opengl")
	add_files("src/*.cpp")
	add_deps("imgui")
