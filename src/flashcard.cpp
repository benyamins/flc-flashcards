#include <string>
#include <filesystem>
#include <fstream>
#include <locale>

#include <nlohmann/json.hpp>
#include <fmt/core.h>

#include "flashcard.hpp"

using json = nlohmann::json;

namespace flc
{

void intro(std::string &questions_file) {
    const char *intro_text = R"(
=============================
      The FlashCard Game
=============================

)";
    fmt::print("{}", intro_text);
    fmt::print("Playing with `{}`\n", questions_file);
}


FlashcardDeck parse_questions(std::string file_path) {
    std::ifstream input_file{file_path};

    if (!input_file) {
        fmt::print("`{}` couldn't be read\n", file_path);
        std::exit(1);
    }

    json document;

    input_file >> document;

    //for (auto& [key, value] : document.items())
    //    std::cout << key << ": " << value << std::endl;

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


std::string_view trim(std::string_view s) {
    s.remove_prefix(std::min(s.find_first_not_of(" "), s.size()));
    s.remove_suffix(std::min(s.size() - s.find_last_not_of(" ") - 1, s.size()));

    return s;
}


void flashcard_picker(const FlashcardDeck &flashcard_deck) {
    auto to_lower = [](std::string str) {
        std::locale loc;
        for (auto &str_char: str)
            str_char = std::tolower(str_char, loc);
        return str;
    };

    fmt::print("\n{}\n\n", flashcard_deck.intro);

    for (auto &flashcard: flashcard_deck.flashcards) {
        fmt::print("Question: {}\n", flashcard.question);

        std::string answer{};
        bool is_correct{false};
        std::cout << "Answer: ";

        std::getline(std::cin, answer);

        // TODO: Use a reference?
        answer = trim(answer);

        for (const auto &flc_answer: flashcard.answer) {
            if (to_lower(answer) == to_lower(flc_answer))
                is_correct = true;
        }
        if (is_correct) {
            std::cout << "Correct!" << std::endl;
        } else {
            fmt::print("Wrong.. you answered: `{}`, but the correct answer is `{}`\n",
                       answer, "<FIXME: JOIN ANSWERS HERE>");
        }
    }
}
}
