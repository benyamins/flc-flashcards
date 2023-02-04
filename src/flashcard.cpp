#include <string>
#include <fstream>
#include <locale>
#include <expected>

#include <nlohmann/json.hpp>
#include <fmt/core.h>

#include "flashcard.hpp"

using json = nlohmann::json;

namespace flc
{

class GameStats
{
    unsigned int m_correct_answers;
    unsigned int m_wrong_answers;
    unsigned int m_total_questions;

public:
    void update_stats(bool is_correct)
    {
        m_correct_answers += is_correct ? 1 : 0;
        m_wrong_answers += is_correct ? 0 : 1;
        ++m_total_questions;
    }
};


std::expected<FlashcardDeck, EResult> parse_questions(const std::string& file_path)
{
    std::ifstream input_file{file_path};

    if (!input_file)
    {
        return std::unexpected(EResult::FileNotFound);
    }

    json document;

    try
    {
        input_file >> document;
    }
    catch (const json::parse_error&)
    {
        return std::unexpected(EResult::JsonParseError);
    }

    FlashcardDeck flashcard_deck;

    std::vector<json> flashcard_deck_json = document["questions"];
    flashcard_deck.intro = document["intro"];

    for (json &value: flashcard_deck_json) {
        std::vector<std::string> answers;

        for (const auto& e: value["answer"])
            answers.push_back(e);

        flashcard_deck.flashcards.push_back(
                Flashcard{.question{value["question"]}, .answer{answers}});
    }

    return flashcard_deck;
}


}
