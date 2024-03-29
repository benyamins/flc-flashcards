# FlashCard Game (for learning purposes)

## Requirements

- `fmt`
- `nlohmann_json`

## Description & Commands

`flc` is a cli program that lets you exercise a particular subject with flashcard,
which offers three modes for questions & answers:  

1. A _basic_ mode that lets you input an answer which is checked against the options defined in a json file.
2. Multiple choice for specified answers.
3. An order/ranked choice system.

``` bash
# Usage: flc [COMMAND] <json-file|flashcard-name> [OPTIONS]

# json-file     : .json file stored in a specific place by the user.
# flashcard-name: name of the flashcard deck stored in the `.local/share/flc` folder.

flc start  my-deck-name  # start the game.
flc create my-deck-name  # create questions.
flc update my-deck-name  # update questions.
flc list                 # list all the decks stored in $HOME/.local/share/flc/decks.
flc list   my-deck-name  # list all questions in a deck.

# Start a flashcard deck
flc s <json-file|name> [-id] 

# Create
flc c <json-file|name>  # Creates json & starts questions to fill up the flashcards

# Update
flc u <json-file|name> -add-ans #

# Examples:

flc u <json-file>                     # add questions interactively.
flc u <json-file> -del <question-id>  # interactively based on the questions position.

flc d <json-file> -id <question-id>       # deletes question based on an id.
flc d <json-file> -id-add <question-id>   # deletes an "additional_answers" based on an id.

# if <json-file> doesn't end with .json (or any extension), a file is created/updated/used in `.config`.
```

## Deck structure

``` json
{
    "intro": "intro-text-line-1",
    "questions": [
        {
            "question": "Answer to the Ultimate Question of Life",
            "answers": ["42", "63"],
            "tags": ["movies", "life"],
            "question_type": "basic",
            "end_text": "Adams knew the answer.."
        },
        {
            "question": "How long until I finish the project?",
            "answers": ["Never", "Soon", "Today"],
            "tags": ["life", "fun"],
            "question_type": "multiple",
            "end_text": "There is *no correct* answer here"
        },
        {
            "question": "Order by population (Highest to lowest populated)",
            "answers": ["Nigeria", "Ethiopia", "DRC"],
            "tags": ["countries", "statistics"],
            "question_type": "ordered",
            "end_text": "Ethiopia has many ethnic groups, its largest one is the _Oromo_"
        }
    ]
}
```

Question type defines how the user should input the answer:

1. basic: the user enters the text which can be checked to be in the same _case_ or not,
   with the option to define more than one answer.
2. multiple: choice. the user must select one of the possible answer. The first one in the
   list is considered the correct one.
3. ordered: the user sorts the answers which are checked based on the order they were
   placed on the question object.

## TODO
1. Markdown support for text (is it actually called like that?)
2. Test if unicode works (cross-platform? lol)
3. Check if it compiles on windows
4. `jsonnet` support?
