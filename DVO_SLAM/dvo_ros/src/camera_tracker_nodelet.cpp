/**
 *  This file is part of dvo.
 *
 *  Copyright 2012 Christian Kerl <christian.kerl@in.tum.de> (Technical University of Munich)
 *  For more information see <http://vision.in.tum.de/data/software/dvo>.
 *
 *  dvo is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  dvo is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with dvo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dvo_ros/camera_tracker_nodelet.h>
#include <pluginlib/class_list_macros.h>

// PLUGINLIB_DECLARE_CLASS(dvo_ros, camera_tracker, dvo_ros::CameraTrackerNodelet, nodelet::Nodelet)
PLUGINLIB_EXPORT_CLASS(dvo_ros::CameraTrackerNodelet, nodelet::Nodelet)

namespace dvo_ros
{

CameraTrackerNodelet::CameraTrackerNodelet()
{
}

CameraTrackerNodelet::~CameraTrackerNodelet()
{
}

void CameraTrackerNodelet::onInit()
{
  //tracker_.reset(new CameraTracker(getNodeHandle(), getPrivateNodeHandle()));
  tracker_.reset(new dvo_ros::CameraDenseTracker(getMTNodeHandle(), getMTPrivateNodeHandle()));
}

} /* namespace dvo_ros */
