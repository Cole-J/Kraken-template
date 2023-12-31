#pragma once
#include "main.h"
#include <string>
#include <unordered_map>


class _IMU {
    private:
        std::vector<std::string> imu_names;
        std::vector<pros::IMU> imu_imus;
        std::unordered_map<std::string, bool> map_imu_data_reset_on_startup;
        
    public:
        bool added_imu = false;

        void _new(std::string name, int port, bool reset_on_startup = true) {
            this->added_imu = true;
            pros::Imu new_imu(port);

            this->imu_names.push_back(name);
            this->imu_imus.push_back(new_imu);
            this->map_imu_data_reset_on_startup[name] = reset_on_startup;
        }

        pros::IMU imu(std::string name) {
            if (this->added_imu) {
                auto it = std::find(this->imu_names.begin(), this->imu_names.end(), name);
                if (it != this->imu_names.end()) {
                    auto idx = std::distance(this->imu_names.begin(), it);
                    return this->imu_imus[idx];
                }
            }
            return NULL;
        }

        std::vector<std::string> get_imu_data_names() {return this->imu_names;}

        bool get_imu_data_imu_reset_on_startup(std::string name) {
            return this->map_imu_data_reset_on_startup[name];}

        bool get_imu_data_reset_on_startup(std::string name) {
            return this->map_imu_data_reset_on_startup[name];}
};