#pragma once
#include <array>
#include <memory>
#include <atomic>
#include "SensorData.hpp"
#include "FlightControl.hpp"
#include "ObjectDetection.hpp"

class DroneController {
private:
    std::atomic<bool> is_running_{false};
    std::unique_ptr<FlightControl> flight_control_;
    std::unique_ptr<ObjectDetection> object_detector_;
    RealTimeQueue<SensorData> sensor_queue_;
    
    // Real-time processing rates
    static constexpr uint32_t CONTROL_LOOP_HZ = 400;
    static constexpr uint32_t SENSOR_READ_HZ = 200;
    static constexpr uint32_t OBJECT_DETECT_HZ = 30;

public:
    DroneController();
    void initialize();
    void start();
    void stop();
    
private:
    void process_sensor_data();
    void update_flight_control();
    void detect_objects();
};
