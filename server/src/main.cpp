#include <iostream>
#include <exception>
#include <cstdint>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "Server.hpp"

int printHelp(const std::string& name, std::ostream& out, int retVal);

int printHelp(const std::string& name, std::ostream& out, int retVal)
{
    out << "This is the help for " << name << ", good luck with this!" << std::endl;
    return retVal;
}

int	main(int ac, char *av[])
{
    namespace po = boost::program_options;

    try {
        std::string dbName = Server::defaultLogPath;
        uint16_t port = Server::defaultPort;
        std::string appName = boost::filesystem::basename(av[0]);
        try {
            po::options_description desc("Options");
            desc.add_options()
                    ("help,h", "You need help?")
                    ("port,p", po::value<uint16_t>(&port), "The port of the server")
                    ("db", po::value<std::string>(&dbName), "The database file");

            po::variables_map vm;
            po::store(po::parse_command_line(ac, av, desc), vm);
            po::notify(vm);

            if (vm.count("help"))
                return printHelp(appName, std::cout, 0);
            if (vm.count("db")) {
                std::string dbn = vm["db"].as<std::string>();
                std::string dbext = boost::filesystem::extension(dbn);
                if (dbext != ".json" && dbext != ".db")
                    throw po::error("Error: the required extension for the file of option '--db' it must be json or db");
            }
        }
        catch (po::error &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return printHelp(appName, std::cerr, 1);
        }

        Server server(dbName, port);

        server.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
	return 0;
}
