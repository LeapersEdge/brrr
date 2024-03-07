#pragma once

#include "simbody.hpp"
#include <vector>

class Simboat
{
public:
    Simboat(Simbody body, std::string sensor_data_csv_file_name);

    void Next_Step();
    unsigned int current_step;
    Simbody body;
private:
    std::vector<std::vector<double>> csv_values;
};
