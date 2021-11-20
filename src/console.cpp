#include <fmt/core.h>
#include <vector>
#include <filesystem>
#include <set>

namespace fs = std::filesystem;

namespace consoleapp
{
    void console_help(std::string error_message = "")
    {
        if (error_message != "")
        {
            fmt::print("Error: {}\n", error_message);
        }

        const char * help_text = R"(
        usage:

        $ flc <flashcard.csv>)";

        fmt::print("{}\n", help_text);
    }

    struct Args
    {
        std::string file_path = "";
        bool update = false;
        bool create = false;
    };


    Args proc_args(int argc, char* argv[])
    {
        Args args{ };

        std::vector<std::string> str_args { };

        for (short i{}; i < argc; ++i)
        {
            str_args.push_back(argv[i]);
        }

        if (argc == 1)
        {
            console_help("No arguments where passed");
            std::exit(1);
        }
        else if (argc == 2)
        {
            args.file_path = str_args[1];

            if (!fs::exists(args.file_path))
            {
                std::string error_message =
                    fmt::format("File `{}`, does not exists", args.file_path);

                console_help(error_message);
                std::exit(1);
            }
        }
        else if (argc == 3)
        {

            std::set<std::string> update_options {"-u", "-update"};
            std::set<std::string> create_options {"-c", "-create"};

            auto optional_arg = std::find_if(str_args.begin(), str_args.end(),
                [&update_options, &create_options](std::string ele)
                {
                    return update_options.contains(ele) || create_options.contains(ele);
                }
            );

            if (optional_arg != std::end(str_args))
            {
                if (update_options.contains(*optional_arg))
                {
                    args.update = true;
                    str_args.erase(optional_arg);
                }
                else if (create_options.contains(*optional_arg))
                {
                    args.create = true;
                    str_args.erase(optional_arg);
                }
                args.file_path = str_args[1];
            }
            else
            {
                console_help("Invalid optional argument");
                std::exit(1);
            }
            
        }
        else
        {
            console_help("Number of arguments is invalid.");
            std::exit(1);
        }
        //for (int i{1}; i < argc; ++i)
        //{
            //fmt::print("arg: {}\n", argv[i]);
        //}
        return args;
    }

}
