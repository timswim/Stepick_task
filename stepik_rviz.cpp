#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

class SubscibendPublish
{
public:
  SubscibendPublish()
  {
    pub_ = n_.advertise<visualization_msgs::Marker>("/output",10,true);
    sub_ = n_.subscribe("/input", 1, &SubscibendPublish::callback, this);
  }
  void callback(const geometry_msgs::Point& input_point)
  {
    visualization_msgs::Marker out_mrk;
    
    out_mrk.header.frame_id = "/point_on_map";
    out_mrk.header.stamp = ros::Time::now();
    out_mrk.ns = "there_is_point";
    out_mrk.id = input_point.x+input_point.y+input_point.z;
    out_mrk.action = visualization_msgs::Marker::ADD;
    out_mrk.type = visualization_msgs::Marker::POINTS;
    out_mrk.scale.x = 0.5;//размер
    out_mrk.scale.y = 0.5;
    out_mrk.color.r = 1.0;//цвет
    out_mrk.color.g = 0.0;
    out_mrk.color.b = 0.0;
    out_mrk.color.a = 1.0;//непрозрачный
    out_mrk.points.push_back(input_point);
    pub_.publish(out_mrk);
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

