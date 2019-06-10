#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>
#include<iomanip>

#include<opencv2/core/core.hpp>

#include"System.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    VideoCapture cap("/home/jeenq/Google_Drive/ORB_SLAM2/Data/cubemap_front.avi");
    string path_to_vocabulary = "/home/jeenq/Google_Drive/ORB_SLAM2/Vocabulary/ORBvoc.txt";
    string path_to_settings = "/home/jeenq/Google_Drive/ORB_SLAM2/Examples/Monocular/cubemap_front.yaml";

    double delay = 1000 / cap.get(CV_CAP_PROP_FPS);

    // Create SLAM system. It initializes all system threads and gets ready to process frames.
    ORB_SLAM2::System SLAM(path_to_vocabulary,path_to_settings,ORB_SLAM2::System::MONOCULAR,true); 

    // Main loop
    cv::Mat im;
    while(true)
    {
        // Read image from file
        cap >> im;

        if(im.empty())
        {
            cerr << endl << "Failed to read camera" << endl;
            return 1;
        }

        // Pass the image to the SLAM system
        cout<<SLAM.TrackMonocular(im, delay)<<endl;
    }

    // Stop all threads
    SLAM.Shutdown();

    // Save camera trajectory
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory.txt");    

    return 0;
}