#include <vector>
#include <filesystem>
#include <set>
#include <algorithm>
#include <expected>

#include <fmt/core.h>

namespace fs = std::filesystem;

const char* help_text = R"(
Flashcard game to get better at remembering things (?)

USAGE
 flc <command> <flashcard-deck> [flags]

COMMANDS
 start  | s <deck>: start game given a flashcard deck.
 create | c <deck>: interactively or with additional flags.
 update | u <deck>: interactively or with additional flags.
 delete | d <deck>: deletes a deck or question, interactively or with additional flags.
 list   | l <deck>: prints questions of a given flashcard deck.
 list   | l       : prints the names of saved decks in shared folder.

COMMAND FLAGS
 start [-id | -tags]
   -id:   start game of specific ids eg "12,23".
   -tags: start game of specific tags "tag.1,...,tag.n".
 update [-upd-id | -intro | -also]
   -upd-id: updates a specific question.
   -intro:  updates only the introduction.
   -also:   add additional answers.
 delete [-id | -id-also]
   -id:      delete a specific question.
   -id-also: delete an aditional answer given a key.
 list [-tags | -add-ans]
   -tags:    show tags of a specific deck & the number of questions of them.
   -add-ans: shows additional answers available for questions.

EXAMPLES
 $ flc s ./path/to/deck.json -tags statistics
)";

namespace consoleapp
{

void console_help(const std::string& error_message = "")
{
    if (!error_message.empty())
    {
        fmt::print("Error: {}\n", error_message);
    }

    fmt::print("{}\n", help_text);
}

struct Args
{
    std::string file_path;
    bool update = false;
    bool create = false;
};


// command: value
// flag1?: value?
// flag2?
// flagn
//
// 1. specify command (str)
// 2. value type
// 3. add flags, which:
//    a. can be optional
//    b. don't need a value
//    c. can be zero or less.

// command: (str|str)
// value: (type)
// flags?: (str)
// value?: (type?)

// struct {command = vec{"", ""?}, value<> }


std::expected<Args, int> proc_args(int argc, char* argv[])
{
    Args args{ };

    std::vector<std::string> str_args {argv+1, argv+argc };

    if (argc == 1)
    {
        console_help("No arguments where passed");
        return std::unexpected(1);
    }
    else if (argc == 2)
    {
        args.file_path = str_args[0];

        if (!fs::exists(args.file_path))
        {
            const std::string error_message =
                fmt::format("File `{}`, does not exists", args.file_path);

            console_help(error_message);
            return std::unexpected(1);
        }
    }
    else if (argc == 3)
    {

        std::set<std::string> update_options {"-u", "-update"};
        std::set<std::string> create_options {"-c", "-create"};

        auto optional_arg = std::find_if(str_args.begin(), str_args.end(),
            [&update_options, &create_options](const std::string& ele)
            {
                return update_options.contains(ele) || create_options.contains(ele);
            });

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
            return std::unexpected(1);
        }
        
    }
    else
    {
        console_help("Number of arguments is invalid.");
        return std::unexpected(1);
    }
    return args;
}

}
