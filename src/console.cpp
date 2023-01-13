#include <vector>
#include <filesystem>
#include <set>
#include <algorithm>
#include <expected>

#include <fmt/core.h>

#include "gui.hpp"
#include "console.hpp"


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

std::expected<Args, int> proc_args(int argc, char* argv[])
{
    Args args{};

    std::vector<std::string> str_args{argv+1, argv+argc};

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

        // FIXME: this whole logic is horrible, plz fix.
        std::set<std::string> update_options {"-u", "-update"};
        std::set<std::string> create_options {"-c", "-create"};
        std::set<std::string> gui_options {"-g", "-gui"};

        auto optional_arg = std::find_if(str_args.begin(), str_args.end(),
            [&update_options,
                  &create_options,
                  &gui_options](const std::string& ele)
            {
                return update_options.contains(ele)
                    || create_options.contains(ele)
                    || gui_options.contains(ele);
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
            else if (gui_options.contains(*optional_arg))
            {
                args.gui_mode = true;
                str_args.erase(optional_arg);
            }

            args.file_path = str_args[0];
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


void intro(const std::string& questions_file)
{
    const char *intro_text = R"(
=============================
      The FlashCard Game
=============================

)";
    fmt::print("{}", intro_text);
    fmt::print("Playing with `{}`\n", questions_file);
}

std::string_view trim(std::string_view s) {
    s.remove_prefix(std::min(s.find_first_not_of(' '), s.size()));
    s.remove_suffix(std::min(s.size() - s.find_last_not_of(' ') - 1, s.size()));

    return s;
}

int flashcard_picker(const flc::FlashcardDeck& flashcard_deck)
{
    auto to_lower = [](std::string str) {
        std::locale loc;
        for (auto &str_char: str)
            str_char = std::tolower(str_char, loc);
        return str;
    };

    fmt::print("\n{}\n\n", flashcard_deck.intro);

    for (auto &flashcard: flashcard_deck.flashcards) {
        fmt::print("Question: {}\n", flashcard.question);

        std::string answer{};
        bool is_correct{false};
        std::cout << "Answer: ";

        std::getline(std::cin, answer);

        // TODO: Use a reference?
        answer = trim(answer);

        for (const auto &flc_answer: flashcard.answer) {
            if (to_lower(answer) == to_lower(flc_answer))
                is_correct = true;
        }
        if (is_correct) {
            fmt::print("Correct!\n");
        } else {
            fmt::print("Wrong.. you answered: `{}`, but the correct answer is `{}`\n",
                       answer, "<FIXME: JOIN ANSWERS HERE>");
        }
    }

    return 0;
}

int run_console_flc(int argc, char* argv[])
{
    auto args_result = consoleapp::proc_args(argc, argv);

    if (!args_result) {
        return 1;
    }

    consoleapp::Args& args = args_result.value();

    consoleapp::intro(args.file_path);

    if (args.gui_mode)
        return guiapp::main_gui();

    auto flashcard_deck = flc::parse_questions(args.file_path);

    if (!flashcard_deck)
    {
        switch (flashcard_deck.error())
        {
            case flc::EResult::FileNotFound:
                fmt::print("File `{}` wasn't found. Try Again\n", args.file_path);
                break;
            case flc::EResult::JsonParseError:
                fmt::print("Json file `{}` presents errors. Try Again\n", args.file_path);
                break;
        }
        return 1;
    }
    return consoleapp::flashcard_picker(flashcard_deck.value());
}


}
