#include <iostream>

#define FMT_HEADER_ONLY
#include <fmt/core.h>

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
 */

void print_help(std::string error_message = "")
{
    if (error_message != "") {
        fmt::print("Error: {}\n", error_message);
    }

    const char * help_text = R"(
    usage:

    $ flc <flashcard.csv>
    )";

    fmt::print("{}", help_text);
}

bool proc_args(int argc, char* argv[])
{
    if (argc == 1) {

        print_help("No arguments where passed");
        return false;

    }

    fmt::print("Number of args: {}", argc);
    fmt::print("first arg is: {}", argv[1]);

    return true;
}

void intro()
{
    const char * intro_text = R"(
    =============================
          The FlashCard Game
    =============================

    )";
    fmt::print("{}", intro_text);
}

void randomFC()
{
    std::cout << "What is the first region of Chile?\n";
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
    bool result = proc_args(argc, argv);
    if (result) {
        intro();
        randomFC();
        fcPicker();
        return 0;
    }
    return 1;
}
