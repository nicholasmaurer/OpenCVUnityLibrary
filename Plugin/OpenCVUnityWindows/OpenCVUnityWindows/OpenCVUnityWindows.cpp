// OpenCVUnityWindows.cpp : Defines the exported functions for the DLL.
//
#include "pch.h"
#include "framework.h"
#include "OpenCVUnityWindows.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdint>
#include <cmath>
#include "IUnityRenderingExtensions.h"

using namespace cv;
using namespace std;

int Init(void)
{
    Mat image;
    image = imread("exampleImage.jpg", IMREAD_COLOR); // Read the file
    if (image.empty()) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    imshow("Display window", image); // Show our image inside it.
    waitKey(0); // Wait for a keystroke in the window
    return 0;
}
// Old school plasma effect
uint32_t Plasma(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t frame)
{
    auto px = (float)x / width;
    auto py = (float)y / height;
    auto time = frame / 60.0f;

    auto l = sinf(px * sinf(time * 1.3f) + sinf(py * 4 + time) * sinf(time));

    auto r = (uint32_t)(sinf(l * 6) * 127 + 127);
    auto g = (uint32_t)(sinf(l * 7) * 127 + 127);
    auto b = (uint32_t)(sinf(l * 10) * 127 + 127);

    return r + (g << 8) + (b << 16) + 0xff000000;
}

// Callback for texture update events
void TextureUpdateCallback(int eventID, void* data)
{
    auto event = static_cast<UnityRenderingExtEventType>(eventID);

    if (event == kUnityRenderingExtEventUpdateTextureBeginV2)
    {
        // UpdateTextureBegin: Generate and return texture image data.
        auto params = reinterpret_cast<UnityRenderingExtTextureUpdateParamsV2*>(data);
        auto frame = params->userData;

        uint32_t* img = new uint32_t[params->width * params->height];
        for (auto y = 0u; y < params->height; y++)
            for (auto x = 0u; x < params->width; x++)
                img[y * params->width + x] = Plasma(x, y, params->width, params->height, frame);

        params->texData = img;

        //_frame = Mat(params->width, params->height, CV_32F, img).clone();
    }
    else if (event == kUnityRenderingExtEventUpdateTextureEndV2)
    {
        // UpdateTextureEnd: Free up the temporary memory.
        auto params = reinterpret_cast<UnityRenderingExtTextureUpdateParamsV2*>(data);
        delete[] reinterpret_cast<uint32_t*>(params->texData);
    }
}
// We assign this as a callback to GL.IssuePluginEvent on the C# side
extern "C" UnityRenderingEventAndData UNITY_INTERFACE_EXPORT GetTextureUpdateCallback()
{
    return TextureUpdateCallback;
}