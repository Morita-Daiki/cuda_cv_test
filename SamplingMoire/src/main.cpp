#include <getopt.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char **argv)
{
    std::string source_file = "default_source_file.mp4",
                output_file = "default_output_file.mp4";
    int num = 2, direction = 0;

    struct option longopts[] = {
        {"sourceFile", required_argument, NULL, 's'},
        {"outFile", required_argument, NULL, 'o'},
        {"numSampling", required_argument, NULL, 'n'},
        {"direction", required_argument, NULL, 'd'},
        {0, 0, 0, 0}};
    int opt, longindex;
    while ((opt = getopt_long(argc, argv, "s:o:n:d", longopts, &longindex)) != -1)
    {
        printf("opt info %d %s <-- %s\n", longindex, longopts[longindex].name, optarg);
        switch (opt)
        {
        case 's':
            source_file = std::string(optarg);
            break;
        case 'o':
            output_file = std::string(optarg);
            break;
        case 'n':
            num = std::stoi(optarg);
            break;
        case 'd':
            direction = std::stoi(optarg);
            break;
        case 'h':
        case '?':
            std::cout << "help menu";
            return 1;
        default:
            abort();
        }
    }
    std::cout << "\n";
    std::cout << "Source File Name  :" << source_file << std::endl;
    std::cout << "Output File Name  :" << output_file << std::endl;
    std::cout << "Sampling Size[px] :" << num << std::endl;
    std::cout << "Sampling Direction:" << direction << std::endl;

    cv::Mat frame;
    cv::VideoCapture video;
    video.open(source_file);
    std::cout << "\nOpening the Source File" << std::endl;

    if (!video.isOpened())
    {
        std::cout << "Can't open the Source File" << std::endl;
        return 0;
    }

    cv::VideoWriter writer;
    int width, height, fourcc, frame_length;
    double fps;
    fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v');
    width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
    height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
    fps = video.get(cv::CAP_PROP_FPS);
    frame_length = video.get(cv::CAP_PROP_FRAME_COUNT);
    // fps = 1;
    writer.open(output_file, fourcc, fps, cv::Size(width, height));

    std::cout << "frame width :" << width << std::endl;
    std::cout << "frame height:" << height << std::endl;
    std::cout << "frame length:" << frame_length << std::endl;
    std::cout << "frame / sec :" << fps << std::endl;

    cv::Mat image;
    std::cout << "start loop" << std::endl;

    for (int counter = 0; counter < frame_length; counter++)
    {
        if (counter % 10 == 0)
            std::cout << (100.0 * counter / frame_length) << "%% complete\n";
        video >> image;
        writer << image;
    }
    std::cout << "end loop" << std::endl;

    return 0;
}