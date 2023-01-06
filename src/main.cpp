#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <fmt/core.h>

#include "console.hpp"
#include "flashcard.hpp"


int main(int argc, char* argv[])
{
    auto args_result = consoleapp::proc_args(argc, argv);

    if (!args_result) {
        return 1;
    }

    consoleapp::Args& args = args_result.value();

    std::cout << "filepath: " << args.file_path << std::endl;
    
    flc::intro(args.file_path);

    flc::FlashcardDeck flashcard_deck = flc::parse_questions(args.file_path);

    flc::flashcard_picker(flashcard_deck);

    return 0;
}
