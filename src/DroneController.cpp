#include "DroneController.hpp"

DroneController::DroneController() {
    flight_control_ = std::make_unique<FlightControl>();
    object_detector_ = std::make_unique<ObjectDetection>();
}

void DroneController::start() {
    is_running_ = true;
    std::thread control_thread(&DroneController::update_flight_control, this);
    std::thread sensor_thread(&DroneController::process_sensor_data, this);
    std::thread detection_thread(&DroneController::detect_objects, this);
    
    control_thread.detach();
    sensor_thread.detach();
    detection_thread.detach();
}

