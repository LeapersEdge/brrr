#include "simboat.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

std::vector<std::string> Split_Line_By_Character(const std::string &str, const char &split_char);
bool is_number(const std::string& s);

Simboat::Simboat(Simbody body, std::string csv_file_name)
    :
    body(body),
    current_step(0)
{
    std::vector<std::vector<std::string>> csv;

    std::ifstream in(/*csv_file_name.c_str()*/ "sensor_data_lijevo.csv");
    if (!in.good())
    {  
        std::cout << "could not open the file\n";
        return;
    }

    while (!in.eof())
    {
        std::string line;
        getline(in, line);
        csv.push_back(Split_Line_By_Character(line, ','));
    }

    for (int y = 0; y < csv.size(); y++)
    {
        std::vector<double> csv_value_line; 
        for (int x = 0; x < csv[y].size(); x++)
        {
            std::string str = csv[y][x];
            if (str != "unaccounted for")
                csv_value_line.push_back(std::stod(str));
        }
        if (!csv_value_line.empty())
            csv_values.push_back(csv_value_line);
    }
}

void Simboat::Next_Step()
{
    if ((current_step + 1) >= csv_values.size())
    {
        return;
    }

    unsigned int delta_time = csv_values[current_step + 1][22] - csv_values[current_step][22];
    body.Update_Rotation(csv_values[current_step][0], csv_values[current_step][1], csv_values[current_step][2], delta_time);
    body.Set_Relative_Acceleration(csv_values[current_step][5], csv_values[current_step][6], csv_values[current_step][7]);
    body.Update_Location(delta_time);

    current_step++;
}

std::vector<std::string> Split_Line_By_Character(const std::string &str, const char &split_char)
{
    std::vector<std::string> return_vector;

    std::string temp = "";
    for (int i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if (c != split_char)
        {    
            temp += c;
        }
        else
        {
            return_vector.push_back(temp);
            temp = "";
        }
    }

    if (temp != "")
        return_vector.push_back(temp);

    return return_vector;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

