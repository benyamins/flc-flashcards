#include <iostream>
#include <vector>

namespace flc
{

void intro(std::string &questions_file);

struct Flashcard {
    std::string question;
    std::vector <std::string> answer;
};

struct FlashcardDeck {
    std::string intro;
    std::vector <Flashcard> flashcards;
};


FlashcardDeck parse_questions(std::string file_path);

void flashcard_picker(const FlashcardDeck &flashcard_deck);
}