#include <functional>
#include <iostream>

#include <spdlog/spdlog.h>
#include <docopt/docopt.h>

static constexpr auto USAGE =
    R"(intro.
    Usage:
          intro [--opta=<kn> | --optb ]
          intro (-h | --help)
          intro --version
    Options:
          -h --help     Show this screen.
          --version     Show version.
          --opta=<kn>   option a [default: 10].
          --optb        option b.
)";

int main(int argc, const char **argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
                                                               {std::next(argv), std::next(argv, argc)},
                                                               true,              // show help if requested
                                                               "Intro 1.0"); // version string

    for (auto const &arg : args)
    {
        std::cout << "[ " << arg.first << " ]: " << arg.second << std::endl;
        if ( arg.second.isString())
            spdlog::info("[{}]: {}", arg.first, arg.second.asString());
        if (arg.second.isBool())
            spdlog::info("[{}]: {}", arg.first, arg.second.asBool());
        if (arg.second.isLong())
            spdlog::info("[{}]: {}", arg.first, arg.second.asLong());
    }

    //Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");

    fmt::print("Hello, from {}\n", "{fmt}");
}