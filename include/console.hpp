#include <string>

namespace consoleapp
{
    struct Args
    {
        std::string file_path = "";
        bool update = false;
        bool create = false;
    };
    Args proc_args(int argc, char* argv[]);
}
