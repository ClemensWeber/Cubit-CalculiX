#include "ConfigFile.hpp"

#include "Broker.hpp"
#include <fstream>
#include <iostream>

ConfigFile::ConfigFile()
{
    //QString buffer;
    //Broker::instance()->get_root_directory(buffer);
    //std::cout << buffer.toStdString() << "\n";
    //filename = buffer.toStdString() + "/ccx.cfg";
    filename = "ccx.cfg";
}

ConfigFile::~ConfigFile()
{}

void ConfigFile::clear()
{
    std::ofstream output_file;
    output_file.open(filename, std::ofstream::out | std::ofstream::trunc);
    output_file.close();
}

void ConfigFile::read_entry(std::string option, QString &value)
{
    std::ifstream input_file;
    input_file.open(filename.c_str());
    if (input_file)
    {
        for( std::string line; std::getline( input_file, line ); )
        {
            if (line.find(option) != std::string::npos)
            {
                //std::cout << line.substr(option.length()+1) << "\n";
                if (line.substr(option.length(),1)=="=")
                {
                    value = QString::fromStdString(line.substr(option.length()+1));
                }
            }
        }
        input_file.close();
    }
}

void ConfigFile::read_num_entry(std::string option, int &value)
{
    std::ifstream input_file;
    input_file.open(filename.c_str());
    if (input_file)
    {
        for( std::string line; std::getline( input_file, line ); )
        {
            if (line.find(option) != std::string::npos)
            {
                if (line.substr(option.length(),1)=="=")
                {
                    value = std::stoi(line.substr(option.length()+1));
                }
                //std::cout << line.substr(option.length()+1) << "\n";
            }
        }
        input_file.close();
    }
}

void ConfigFile::write_entry(std::string option, QString value)
{
    std::ofstream output_file;
    output_file.open(filename.c_str(), std::ios_base::app);
    output_file << option << "=" << value.toStdString() << "\n";
    output_file.close();
}

void ConfigFile::write_num_entry(std::string option, int value)
{
    std::ofstream output_file;
    output_file.open(filename.c_str(), std::ios_base::app);
    output_file << option << "=" << value  << "\n";
    output_file.close();
}