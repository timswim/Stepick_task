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
    static int Count = 0;
    static bool InitDone = false;
    static visualization_msgs::Marker out_mrk;
    
    if (!InitDone){

      out_mrk.header.frame_id = "/point_on_map";
      out_mrk.header.stamp = ros::Time::now();
      out_mrk.ns = "there_is_point";
      out_mrk.id = 0;
      out_mrk.action = visualization_msgs::Marker::ADD;
      out_mrk.type = visualization_msgs::Marker::POINTS;
      out_mrk.scale.x = 0.5;//размер
      out_mrk.scale.y = 0.5;
      out_mrk.color.r = 1.0;//цвет
      out_mrk.color.g = 0.0;
      out_mrk.color.b = 0.0;
      out_mrk.color.a = 1.0;//непрозрачный
      
      InitDone = true;
    }
    
    out_mrk.points.push_back(input_point);
    ++Count;
    if(Count >= 5){
    {
      pub_.publish(out_mrk);
      Count = 0; 
    }
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

