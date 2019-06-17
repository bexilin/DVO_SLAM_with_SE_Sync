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

To build this part of code, you should initialize a catkin workspace first, and put packages dvo_core, dvo_ros, dvo_slam, and dvo_benchmark under directory src. Then go back to Catkin workspace's root folder and execute  

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
