std::vector<ObjectDetection::Detection> 
ObjectDetection::detect(const cv::Mat& frame) {
    cv::Mat blob = cv::dnn::blobFromImage(
        frame, 1/255.0, cv::Size(416, 416), cv::Scalar(), true, false);
    neural_network_.setInput(blob);
    
    std::vector<cv::Mat> outputs;
    neural_network_.forward(outputs, neural_network_.getUnconnectedOutLayersNames());
    
    std::vector<Detection> detections;
    for (const auto& output : outputs) {
        for (int i = 0; i < output.rows; ++i) {
            float confidence = output.at<float>(i, 4);
            if (confidence > CONFIDENCE_THRESHOLD) {
                cv::Point class_id;
                cv::minMaxLoc(cv::Mat(output.row(i).colRange(5, output.cols)), 
                             nullptr, nullptr, nullptr, &class_id);
                
                float x = output.at<float>(i, 0);
                float y = output.at<float>(i, 1);
                float w = output.at<float>(i, 2);
                float h = output.at<float>(i, 3);
                
                detections.push_back({
                    cv::Rect(x - w/2, y - h/2, w, h),
                    confidence,
                    class_id.x
                });
            }
        }
    }
    
    return detections;
}
