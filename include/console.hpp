#include <string>
#include <expected>

namespace consoleapp
{
    struct Args
    {
        std::string file_path = "";
        bool update = false;
        bool create = false;
    };
    std::expected<Args, int> proc_args(int argc, char* argv[]);
}
