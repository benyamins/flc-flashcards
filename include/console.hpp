#include <string>
#include <expected>

#include "flashcard.hpp"

namespace consoleapp
{

struct Args
{
    std::string file_path;
    bool update = false;
    bool create = false;
};

void intro(const std::string& questions_file);

std::expected<Args, int> proc_args(int argc, char* argv[]);

int flashcard_picker(const flc::FlashcardDeck& flashcard_deck);

int run_console_flc(int argc, char* argv[]);

}
