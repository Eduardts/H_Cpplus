struct SensorData {
    std::array<float, 3> acceleration;
    std::array<float, 3> gyroscope;
    std::array<float, 3> magnetometer;
    float barometer;
    float temperature;
    uint64_t timestamp;
    
    // Encryption for sensitive data
    void encrypt() {
        // AES encryption implementation
    }
    
    void decrypt() {
        // AES decryption implementation
    }
};
