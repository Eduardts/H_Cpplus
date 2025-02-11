int main() {
    try {
        DroneController controller;
        controller.initialize();
        
        // Start real-time processing
        controller.start();
        
        // Wait for shutdown signal
        std::signal(SIGINT, [](int) {
            controller.stop();
        });
        
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
