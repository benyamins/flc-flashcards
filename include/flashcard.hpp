#include <iostream>
#include <vector>
#include <expected>

namespace flc
{

enum class EResult
{
    FileNotFound,
    JsonParseError,
};

struct Flashcard
{
    std::string question;
    std::vector<std::string> answer;
};

struct FlashcardDeck
{
    std::string intro;
    std::vector<Flashcard> flashcards;
};


std::expected<FlashcardDeck, EResult> parse_questions(const std::string& file_path);

}