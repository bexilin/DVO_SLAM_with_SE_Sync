# Dense Visual Odometry and SLAM (dvo_slam)

*NOTE: this is an alpha release APIs and parameters are going to change in near future. No support is provided at this point.*

These packages provide an implementation of the rigid body motion estimation of an RGB-D camera from consecutive images.

 *  **dvo_core**
    
    Core implementation of the motion estimation algorithm. 
    
 *  **dvo_ros**
    
    Integration of *dvo_core* with ROS.
    
 *  **dvo_slam**
    
    Pose graph SLAM system based on *dvo_core* and integration with ROS.
    
 *  **dvo_benchmark**
    
    Integration of *dvo_slam* with TUM RGB-D benchmark, see http://vision.in.tum.de/data/datasets/rgbd-dataset.
    
 *  **sophus**
    
    ROS package wrapper for Hauke Strasdat's Sophus library, see https://github.com/strasdat/Sophus.
    

## Installation
This part of code originated from kinetic-devel branch from DVO SLAM repository (https://github.com/tum-vision/dvo_slam/tree/kinetic-devel), with some modifications so that it can work with SE-Sync. It works on ubuntu 16.04 LTS and ROS Kinetic, and uses catkin to build the code. 

NOTE: compilation problem appears when cmake version is 3.14. Compilation succeeds with cmake version 3.10.

Before you begin to compile, some codes need to be modified first, they are all within dvo_slam/src/keyframe_graph.cpp, in the functions SE_Sync_local(), SE_Sync_global() and SE_Sync_global_kf(). Here takes SE_Sync_local() for example, and you should do similar things to SE_Sync_global() and SE_Sync_global_kf().

You should modify the path of g2o file below to a valid path on your computer, and use that path in SE-Sync codes. (See readme in SE-Sync directory for instruction)
```
g2o_file.open("/home/xi/vertex.g2o");
```

The first argument should be modifed to your path of SE-Sync executable, and the second one is path of g2o_file, the same as above
```
system("/home/xi/SE-Sync/C++/build/bin/SE-Sync /home/xi/vertex.g2o");
```

Similarly, modifying the path to pose file, which is generated in the same directory as SE-Sync executable.
```
pose_file.open("/home/xi/SE-Sync/C++/build/bin/poses_traj.txt");
```

Then, to build this part of code, you should initialize a catkin workspace first, and put packages dvo_core, dvo_ros, dvo_slam, and dvo_benchmark under directory src. Then go back to Catkin workspace's root folder and execute  

```
catkin_make -DCMAKE_BUILD_TYPE=Release
```

to build all packages. You can also build each package separately by 

```
catkin_make --pkg dvo_core -DCMAKE_BUILD_TYPE=Release
catkin_make --pkg dvo_ros -DCMAKE_BUILD_TYPE=Release
catkin_make --pkg dvo_slam -DCMAKE_BUILD_TYPE=Release
catkin make --pkg dvo_benchmark -DCMAKE_BUILD_TYPE=Release
```

## How to run

```
source devel/setup.sh  
```

This will make ROS able to find our newly built packages. 

Now we can navigate to dvo_benchmark folder and execute

```
roslaunch launch/benchmark.launch dataset:=<RGBD dataset folder>
```

You can check the output trajectory in dvo_benchmark/output/trajectory.txt. 

Dataset follows structures in RGBD SLAM by TUM. The only difference is the depth scale is reset 1000 (in benchmark_slam.cpp) instead of 5000. I found this to be more convenient as images from Kinect or Asus Xtion all follows this convention. The focal length is hard coded in benchmark_slam.cpp. Change it to your focal length. 

## Rviz

After DVO SLAM is running, you can launch rviz to observe some results. 

In global options in the left panel, set target frame is "world". Then click Add button, switch to By Topic tab, and choose PointCloud2. You can also add Interactive Markers. 

If you see nothing in rviz but DVO is running, it could be because the project is built in Debug mode, which is slow. Make sure -DCMAKE_BUILD_TYPE=Release is used with catkin_make. 

## Usage

Estimating the camera trajectory from an RGB-D image stream:

*TODO*

For visualization:

 *  Start RVIZ
 *  Set the *Target Frame* to `/world`
 *  Add an *Interactive Marker* display and set its *Update Topic* to `/dvo_vis/update`
 *  Add a *PointCloud2* display and set its *Topic* to `/dvo_vis/cloud`

The red camera shows the current camera position. The blue camera displays the initial camera position.

## Publications

The following publications describe the approach:

 *   **Dense Visual SLAM for RGB-D Cameras** (C. Kerl, J. Sturm, D. Cremers), In Proc. of the Int. Conf. on Intelligent Robot Systems (IROS), 2013.
 *   **Robust Odometry Estimation for RGB-D Cameras** (C. Kerl, J. Sturm, D. Cremers), In Proc. of the IEEE Int. Conf. on Robotics and Automation (ICRA), 2013
 *   **Real-Time Visual Odometry from Dense RGB-D Images** (F. Steinbruecker, J. Sturm, D. Cremers), In Workshop on Live Dense Reconstruction with Moving Cameras at the Intl. Conf. on Computer Vision (ICCV), 2011.

## License

The packages *dvo_core*, *dvo_ros*, *dvo_slam*, and *dvo_benchmark* are licensed under the GNU General Public License Version 3 (GPLv3), see http://www.gnu.org/licenses/gpl.html.

The package *sophus* is licensed under the MIT License, see http://opensource.org/licenses/MIT.
