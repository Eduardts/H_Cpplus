class ObjectDetection {
private:
    cv::dnn::Net neural_network_;
    std::vector<std::string> class_names_;
    static constexpr float CONFIDENCE_THRESHOLD = 0.85f;
    
public:
    struct Detection {
        cv::Rect bbox;
        float confidence;
        int class_id;
    };
    
    std::vector<Detection> detect(const cv::Mat& frame);
    void load_model(const std::string& model_path);
};
