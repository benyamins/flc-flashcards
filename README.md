# FlashCard Game (for learning purposes)

## Requirements

- fmt
- nlohmann_json

## Commands:

``` bash
# Usage: flc <path-to-json|saved-game> [OPTIONS]
# or   : flc [COMMAND] <path-to-json|saved-game> [OPTIONS]

flc <path-to-json>         # start the game
flc update <path-to-json>  # update questions
flc create <path-to-json>  # create questions
flc show <path-to-json>    # shows available questions with Id.

# Start game
flc <path-to-json> [-id]


# Create option [-add-json]
flc c <path-to-json>                            # Creates json & starts questions to fill up the flashcards
flc c <path-to-json> -add-json "<json-string>"  # must be valid & complete structure (not only questions)

# Examples:

flc u <path-to-json>  # add questions interactibly.
flc u <path-to-json> -add -question "Auf wiedersehen" -answer "goodbye,bye" -tags "hard,polite"
flc u <path-to-json> -add-json "[{"question": "Answer to life?", "answers": ["42"], "tags": ["life"]}]"
flc u <path-to-json> -add-json "[{"question": "Is C++ easy?", "answers": ["yes", "y"], "case": true}, {...}]"
flc u <path-to-json> -del <question-id>  # based on the question's position.
flc u <path-to-json> -upd-id <question-id> -question "Is pyhton easy?" -answer "no,maybe" -case
flc u <path-to-json> -upd-id <question-id> -json "{"question": "Is C easy?", "answers": ["yes", "y"], "case": true}"

# if <path-to-json> doesn't end with .json (or any extension), a file is created/updated/used in `.config`.
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
            "end_text": "Adams knew the answer..",
            "add": "life"
        },
        {
            "question": "How long until I finish the project?",
            "answers": ["Never", "Soon", "Today"],
            "tags": ["life", "fun"],
            "case": true,
            "question_type": "multiple",
            "end_text": "There is *no correct* answer here"
        },
        {
            "question": "Order by population (Highest to lowest populated)",
            "answers": ["Nigeria", "Ethiopia", "DRC"],
            "tags": ["countries", "statistics"],
            "case": true,
            "question_type": "ordered",
            "end_text": "Ethiopia has many ethnic groups, it's largest one is the _Oromo_"
        }
    ]
    "answers": {
        "life": ["python", "love"]
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
