# FlashCard Game (for learning purposes)

## Requirements

- `fmt`
- `nlohmann_json`

## Commands:

``` bash
# Usage: flc [COMMAND] <json-file|flashcard-name> [OPTIONS]

# json-file     : .json file stored in a specific place by the user.
# flashcard-name: name 

flc start  <json-file|flashcard-name>  # start the game
flc create <json-file|flashcard-name>  # create questions
flc update <json-file|flashcard-name>  # update questions
flc show   <json-file|flashcard-name>  # shows available questions with Id.
flc list                               # list all flashcard-name stored in $HOME/.local/share/flc.

# Start a game
flc s <json-file|name> [-id] 

# Create
flc c <json-file>  # Creates json & starts questions to fill up the flashcards

# Update
flc u <json-file> -add-ans #

# Examples:

flc u <json-file>                     # add questions interactively.
flc u <json-file> -del <question-id>  # interactively based on the questions position.

flc d <json-file> -id <question-id>       # deletes question based on an id.
flc d <json-file> -id-add <question-id>   # deletes an "additional_answers" based on an id.

# if <json-file> doesn't end with .json (or any extension), a file is created/updated/used in `.config`.
```

## Question structure

``` json
{
    "intro": "intro-text-line-1",
    "questions": [
        {
            "question": "Answer to the Ultimate Question of Life",
            "answers": ["42", "63"],
            "tags": ["movies", "life"],
            "case": false,
            "question_type": "basic",
            "end_text": "Adams knew the answer.."
        },
        {
            "question": "How long until I finish the project?",
            "answers": ["Never", "Soon", "Today"],
            "tags": ["life", "fun"],
            "case": true,
            "question_type": "multiple",
            "also": "life",
            "end_text": "There is *no correct* answer here"
        },
        {
            "question": "Order by population (Highest to lowest populated)",
            "answers": ["Nigeria", "Ethiopia", "DRC"],
            "tags": ["countries", "statistics"],
            "case": true,
            "question_type": "ordered",
            "also": "african_countries",
            "end_text": "Ethiopia has many ethnic groups, its largest one is the _Oromo_"
        }
    ],
    "also": {
        "life": ["next year", "when I'm older"],
        "african_countries": ["Djibouti"]
    }
}
```
Question type defines how the user should input the answer:

1. basic: the user enters the text which can be checked to be in the same _case_ or not,
   with the option to define more than one answer.
2. multiple: choice. the user must select one of the posible answer. The first one in the
   list is considered the correct one.
3. ordered: the user sorts the answers which are checked based on the order they where
   placed on the question object.

Only the first type uses the `case` option in a question object.

## TODO
1. Markdown support for text (is it actually called like that?)
2. Test if unicode works (cross-platform? lol)
3. Check if it compiles on windows
