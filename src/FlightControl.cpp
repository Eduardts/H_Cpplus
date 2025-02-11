void FlightControl::update_attitude(
    const std::array<float, 3>& current,
    const std::array<float, 3>& target) {
    
    for (size_t i = 0; i < 3; ++i) {
        float output = attitude_controllers_[i].update(target[i], current[i]);
        // Apply motor mixing algorithm
        apply_motor_output(i, output);
    }
}

// Include implementation for secure data handling
class SecureDataHandler {
private:
    static constexpr size_t KEY_SIZE = 32;
    static constexpr size_t IV_SIZE = 16;
    std::array<uint8_t, KEY_SIZE> key_;
    std::array<uint8_t, IV_SIZE> iv_;
    
public:
    void encrypt_sensor_data(SensorData& data) {
        // AES-256 encryption
        mbedtls_aes_context aes;
        mbedtls_aes_init(&aes);
        mbedtls_aes_setkey_enc(&aes, key_.data(), KEY_SIZE * 8);
        
        // Encrypt data in place
        std::array<uint8_t, sizeof(SensorData)> buffer;
        std::memcpy(buffer.data(), &data, sizeof(SensorData));
        
        mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT,
                             sizeof(SensorData),
                             iv_.data(),
                             buffer.data(),
                             buffer.data());
                             
        std::memcpy(&data, buffer.data(), sizeof(SensorData));
        mbedtls_aes_free(&aes);
    }
};
