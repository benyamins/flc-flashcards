#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <iostream>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <fstream>
namespace fs = std::filesystem;
using json = nlohmann::json;


/*
 * 
 * Objective: Build a flash card app.
 *
 * Examplos:
 *
 * >>> fcl regions.csv
 * >>> What is the first region of Chile?
 * >>> Arica y Parinacota
 * >>> What is the capital of Arica?
 * >>> Arica
 *
 * How:
 *
 * App shows a list of topics & subtopics from
 * which a user can choose.
 *
 * After selecting the user is prompt with a random
 * flashcard.
 *
 * Steps: 
 * - parse arguments
 * - read csv file.
 * - start questions.
 *
 * Questions format:
 *
 * ``` json
 * {
 *     "intro": [
 *         "intro-text-line-1",
 *         "intro-text-line-2",
 *         "       ....      ",
 *         "intro-text-line-n"
 *     ],
 *
 *     "questions": [
 *         "<question-text-1>": "<question-answer-1>",
 *         "<question-text-2>": "<question-answer-2>",
 *     ]
 * }
 *
 * ```
 */

void print_help(std::string error_message = "")
{
    if (error_message != "") {
        fmt::print("Error: {}\n", error_message);
    }

    const char * help_text = R"(
    usage:

    $ flc <flashcard.csv>\n)";

    fmt::print("{}", help_text);
}

std::string proc_args(int argc, char* argv[])
{
    if (argc == 1) {
        print_help("No arguments where passed");
        std::exit(1);
    }

    //for (int i{1}; i < argc; ++i)
    //{
        //fmt::print("arg: {}\n", argv[i]);
    //}
    auto file_path = static_cast<std::string>(argv[1]);

    if (fs::exists(file_path)) {

        return file_path;

    } else {

        std::string error_message =
            fmt::format("File `{}`, does not exists", file_path);
        
        print_help(error_message);
        std::exit(1);
    }
}

void intro(std::string questions_file)
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

struct Flashcards
{
    std::string intro;
    std::vector<Flashcard> flashcards;
};

void parse_questions(std::string file_path)
{
    std::ifstream input_file{ file_path };

    if (!input_file) {
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
    
    std::vector<json> t = document["flashcards"];


    std::cout << "Global Key-Value" << std::endl;
    for (auto& [key, value] : document.items())
        std::cout << key << ": " << value << std::endl;

    std::cout << "Questions vector" << std::endl;
    for (auto& value : t)
        std::cout << value << std::endl;

    std::cout << "Questions vector value" << std::endl;
    for (json& value : t)
        std::cout << "Question:" << value["question"] << "Answer:" << value["answer"] << std::endl;

    Flashcards flashcards;

    std::cout << "Questions vector value" << std::endl;
    for (json& value : t) {
            flashcards.flashcards.push_back(Flashcard{ .question{ value["question"] },
                                            .answer = value["answer"]});
    }

    for (auto& flashcard : flashcards)
        std::cout << "Question:" << flashcard.question << ";" << "Answer:" << flashcard.answer << std::endl;
        
}

void fcPicker()
{
    std::string answer{ };
    
    std::cin >> answer;

    std::cout << " \nYour Answer to the question was " 
        << "`" << answer << "`" << std::endl;

    std::cout << "I have no idea if that is correct.. "
        "for now hehehe\n";
}


int main(int argc, char* argv[])
{
    std::string file_path = proc_args(argc, argv);
    intro(file_path);
    parse_questions(file_path);
    //fcPicker();
    return 0;
}
