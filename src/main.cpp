#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "console.hpp"
#include "flashcard.hpp"


int main(int argc, char* argv[])
{
    consoleapp::Args args = consoleapp::proc_args(argc, argv);

    if (args.create) std::cout << "Create" << std::endl;
    if (args.update) std::cout << "Update" << std::endl;

    std::cout << "filepath: " << args.file_path << std::endl;
    
    intro(args.file_path);

    FlashcardDeck flashcard_deck = parse_questions(args.file_path);

    flashcard_picker(flashcard_deck);

    return 0;
}
