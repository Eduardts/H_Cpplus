class FlightControl {
private:
    struct PIDController {
        float kp, ki, kd;
        float integral;
        float prev_error;
        
        float update(float setpoint, float measured) {
            float error = setpoint - measured;
            integral += error;
            float derivative = error - prev_error;
            prev_error = error;
            
            return kp * error + ki * integral + kd * derivative;
        }
    };
    
    std::array<PIDController, 3> attitude_controllers_;
    std::array<PIDController, 3> position_controllers_;
    
public:
    void update_attitude(const std::array<float, 3>& current, 
                        const std::array<float, 3>& target);
    void update_position(const std::array<float, 3>& current,
                        const std::array<float, 3>& target);
};
