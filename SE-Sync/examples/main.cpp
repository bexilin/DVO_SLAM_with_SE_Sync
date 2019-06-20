#include "SESync/SESync.h"
#include "SESync/SESync_utils.h"

#include <fstream>

#ifdef GPERFTOOLS
#include <gperftools/profiler.h>
#endif

using namespace std;
using namespace SESync;

bool write_poses = true;
bool global = true;

int main(int argc, char **argv) {
  ifstream timestamp_file;
  if (argc == 1) {
    cout << "Usage: " << argv[0] << " [input .g2o and timestamp.txt file]" << endl;
    exit(1);
  }
  else if(argc == 2) {
    timestamp_file.close();
    global = false;
  }
  else if(argc == 3) {
    timestamp_file.open(argv[2]);
    if(!timestamp_file.is_open())
    {
      cout << "fail to open timestamp.txt file." << endl;
      exit(1);
    }
  }
  else {
    cout << "Error number of input arguments." << endl;
    exit(1);
  }

  size_t num_poses;
  measurements_t measurements = read_g2o_file(argv[1], num_poses);
  cout << "Loaded " << measurements.size() << " measurements between "
       << num_poses << " poses from file " << argv[1] << endl
       << endl;
  if (measurements.size() == 0) {
    cout << "Error: No measurements were read!"
         << " Are you sure the file exists?" << endl;
    exit(1);
  }

  SESyncOpts opts;
  opts.verbose = true; // Print output to stdout
  opts.num_threads = 4;

#ifdef GPERFTOOLS
  ProfilerStart("SE-Sync.prof");
#endif

  /// RUN SE-SYNC!
  SESyncResult results = SESync::SESync(measurements, opts);

#ifdef GPERFTOOLS
  ProfilerStop();
#endif

  if (write_poses) {
    // Write output
    string filename = "/home/xi/SE-Sync/C++/build/bin/poses_traj.txt";
    cout << "Saving final poses to file: " << filename << endl;
    ofstream poses_file(filename);
    string timestamp;
    for(size_t j = 0; j<results.pose_translation.cols(); ++j)
    {
      if(global){
        getline(timestamp_file,timestamp);
        poses_file << timestamp << " ";
      }
      for(size_t i = 0; i<results.pose_translation.rows();++i)
        poses_file << results.pose_translation(i,j) << " ";
      /*poses_file << results.pose_quaternion[j].x() << " ";
      poses_file << results.pose_quaternion[j].y() << " ";
      poses_file << results.pose_quaternion[j].z() << " ";
      poses_file << results.pose_quaternion[j].w() << " ";*/
      Eigen::Matrix3d m = results.pose_rotation.block(0,3*j,3,3);
      Eigen::Quaterniond q(m);
      q.normalize();
      /*for(size_t r = 0; r < m.rows(); ++r)
        for(size_t c = 0; c < m.cols(); ++c)
          poses_file << m(r,c) << " ";*/
      //poses_file << m.rows() << " X " << m.cols();
      poses_file << q.x() << " " << q.y() << " " << q.z() << " " << q.w();
      poses_file << std::endl;
    }
    poses_file.close();
    string filename2 = "/home/xi/SE-Sync/C++/build/bin/poses_xhat.txt";
    cout << "Saving final poses to file: " << filename2 << endl;
    ofstream poses_file2(filename2);
    poses_file2 << results.xhat;
    poses_file2.close();
  }
}
