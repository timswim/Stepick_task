#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Point.h>
#include <tf/transform_listener.h>

class SubscibendPublish
{
public:
  SubscibendPublish()
  {
    pub_ = n_.advertise<geometry_msgs::Point>("/output",10,true);
    sub_ = n_.subscribe("/input", 1, &SubscibendPublish::callback, this);
  }
  void callback(const geometry_msgs::PointStamped& input_point)
  {
    
    geometry_msgs::Point out_point;
    tf::TransformListener listener;
    listener.lookupTransform("core_frame", input_point.header.frame_id, ros::Time(0), out_point);
    pub_.publish(out_point);
    
  }
private:
  ros::NodeHandle n_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
};



int main(int argc, char **argv) {

  ros::init(argc,argv,"point_pub_sub");
  SubscibendPublish SAPObject;
  ros::spin();

  return 0;
}
