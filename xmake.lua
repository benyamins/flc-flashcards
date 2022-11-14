set_project("flc-flashcards")
add_rules("mode.debug", "mode.release")

add_requires("fmt", "nlohmann_json")

if is_mode("debug") then
	add_cxxflags("-std=c++20", "-Wall", "-Werror", "-pedantic", "-pedantic-errors", "-Wconversion")
else
	add_cxxflags("-std=c++20", "-Wall", "-Werror", "-pedantic", "-pedantic-errors", "-Wconversion", "-Wextra")
end

target("flc")
	set_kind("binary")
	add_files("src/*.cpp")
	add_includedirs("include")
	add_packages("fmt", "nlohmann_json")
