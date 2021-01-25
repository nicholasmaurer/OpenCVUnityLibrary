# OpenCVUnityLibrary
An Open CV Windows plugin for Unity
- Main C# file for comms with C++ `Assets/OpenCVUnityBridge`
- Main C++ file `Plugin/OpenCVUnityWindows/OpenCVUnityWindows/OpenCVUnityWindows.cpp`
- Unity header files, Visual Studio property sheet and helper classes located under `Plugin/common/`
- Visual Studio solution for Windows platform located at `Plugin/OpenCVUnityWindows/`
- The c++ project was made with Visual Studio DLL with exports template
# Creating your own OpenCV build
- Download OpenCV to `Plugin/source`
- Follow instructions on OpenCV website for building
- Build OpenCV to `Plugin/build`
# Visual Studio Property .props file
- Sets the directories that the projects looks at for libraries and source files
  - C/C++ > General: Additional Include Directories `$(OPENCV_DIR)\include; $(SolutionDir)\common`
  - Linker > General: Additonal Library Directories `$(OPENCV_DIR)\lib`
  - Linker > Input: Additional Dependencies `ade.lib; opencv_calib3d451d.lib; opencv_core451d.lib; opencv_dnn451d.lib; opencv_features2d451d.lib; opencv_flann451d.lib; opencv_gapi451d.lib; opencv_highgui451d.lib; opencv_imgcodecs451d.lib; opencv_imgproc451d.lib; opencv_ml451d.lib; opencv_objdetect451d.lib; opencv_photo451d.lib; opencv_stitching451d.lib; opencv_ts451d.lib; opencv_videoio451d.lib; opencv_video451d.lib`s
- 
