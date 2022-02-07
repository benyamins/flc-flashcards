#include <iostream>
#include <vector>

void intro(std::string& questions_file);

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


FlashcardDeck parse_questions(std::string file_path);
void flashcard_picker(const FlashcardDeck& flashcard_deck);
