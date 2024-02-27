#include <functional>
#include <iostream>
#include <Eigen/Core>
#include <spdlog/spdlog.h>
#include <fmt/ostream.h>
#include <docopt/docopt.h>

template <typename T>
struct fmt::formatter<
    T,
    std::enable_if_t<
        std::is_base_of_v<Eigen::DenseBase<T>, T>,
        char>> : ostream_formatter
{
};

void exo1( std::map<std::string, docopt::value> const& args)
{
    spdlog::info( "Exo 1");
}
void exo2( std::map<std::string, docopt::value> const& args)
{
    spdlog::info("Exo 2");

    using MyMatrix33f = Eigen::Matrix<float, 3, 3>;
    using MyVector3f = Eigen::Matrix<float, 3, 1>;
    using MyMatrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;

    MyMatrix33f a;
    MyVector3f v;
    MyMatrix m(10, 15);

    a = MyMatrix33f::Zero();     // fill matrix elements with zeros
    a = MyMatrix33f::Identity(); // fill matrix as Identity matrix
    v = MyVector3f::Random();    // fill matrix elements with random values

    a << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;
    fmt::print("a={}\n", a);
}
static constexpr auto USAGE =
    R"(intro.
    Usage:
          intro --exo=<n>
          intro (-h | --help)
          intro --version
    Options:
          -h --help     Show this screen.
          --version     Show version.
          --exo=<n>     execute exercise <n> [default: 1].
)";

int main(int argc, const char **argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
                                                               {std::next(argv), std::next(argv, argc)},
                                                               true,              // show help if requested
                                                               "Intro 1.0"); // version string
#if 0
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
#endif
    //Use the default logger (stdout, multi-threaded, colored)
    spdlog::info("Hello, {}!", "World");

    fmt::print("Hello, from {}\n", "{fmt}");

    if ( args["--exo"].isString() && args["--exo"].asString() == "1" )
        exo1(args);
    else
        exo2(args);
    
}