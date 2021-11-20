#include <fmt/core.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
#include <locale>
namespace fs = std::filesystem;
using json = nlohmann::json;


void print_help(std::string error_message = "")
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
        print_help("No arguments where passed");
        std::exit(1);
    }
    else if (argc == 2)
    {
        args.file_path = str_args[1];

        if (!fs::exists(args.file_path))
        {
            std::string error_message =
                fmt::format("File `{}`, does not exists", args.file_path);

            print_help(error_message);
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
            print_help("Invalid optional argument");
            std::exit(1);
        }
        
    }
    else
    {
        print_help("Number of arguments is invalid.");
        std::exit(1);
    }
    //for (int i{1}; i < argc; ++i)
    //{
        //fmt::print("arg: {}\n", argv[i]);
    //}
    return args;
}


void intro(std::string & questions_file)
{
    const char * intro_text = R"(
    =============================
          The FlashCard Game
    =============================

    )";
    fmt::print("{}", intro_text);
    fmt::print("Playing with `{}`\n", questions_file);
}


struct Flashcard
{
    std::string question,
                answer;
};

struct FlashcardDeck
{
    std::string intro;
    std::vector<Flashcard> flashcards;
};

FlashcardDeck parse_questions(std::string file_path)
{
    std::ifstream input_file{ file_path };

    if (!input_file)
    {
        fmt::print("`{}` could't be read\n", file_path);
        std::exit(1);
    }

    //std::vector<std::string> questions;
    
    //while (input_file) {
    //    std::string line;
    //    getline(input_file, line);
    //    questions.push_back(line);
    //}

    //std::copy(questions.begin(), questions.end(),
    //    std::ostream_iterator<std::string>(std::cout, "\n"));

    json document;

    input_file >> document;

    //for (auto& [key, value] : document.items())
    //    std::cout << key << ": " << value << std::endl;
    
    FlashcardDeck flashcard_deck;

    std::vector<json> flashcard_deck_json = document["questions"];
    flashcard_deck.intro = document["intro"];

    for (json& value : flashcard_deck_json) 
            flashcard_deck.flashcards.push_back(
                Flashcard{ .question{ value["question"] }, .answer{ value["answer"] }});
    
    return flashcard_deck;
}


std::string_view trim(std::string_view s)
{
    s.remove_prefix(std::min(s.find_first_not_of(" "), s.size()));
    s.remove_suffix(std::min(s.size() - s.find_last_not_of(" ") - 1, s.size()));

    return s;
}


void flashcard_picker(const FlashcardDeck & flashcard_deck)
{
    auto to_lower = [](std::string str)
    {
        std::locale loc;
        for (auto& str_char : str)
            str_char = std::tolower(str_char, loc);
        return str;
    };

    fmt::print("\n{}\n\n", flashcard_deck.intro);
    
    for (auto& flashcard : flashcard_deck.flashcards)
    {
        fmt::print("Question: {}\n", flashcard.question);

        std::string answer{ };
        std::cout << "Answer: ";

        std::getline(std::cin, answer);

        // TODO: Use a reference?
        answer = trim(answer);

        if (to_lower(answer) == to_lower(flashcard.answer))
        {
            std::cout << "Correct!" << std::endl;
        }
        else
        {
            fmt::print("Wrong.. you answered: `{}`, but the correct answer is `{}`\n",
                       answer, flashcard.answer);
        }
    }
}


int main(int argc, char* argv[])
{
    Args args = proc_args(argc, argv);

    if (args.create) std::cout << "Create" << std::endl;
    if (args.update) std::cout << "Update" << std::endl;

    std::cout << "filepath: " << args.file_path << std::endl;
    
    intro(args.file_path);

    FlashcardDeck flashcard_deck = parse_questions(args.file_path);

    flashcard_picker(flashcard_deck);

    return 0;
}
