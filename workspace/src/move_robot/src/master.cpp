#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
///////////////////////////////////
#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>


#define ACCEDI 1;
#define CHIAMA 2;
#define SPEDISCI 3;

move_robot::NewGoal msg_goal;

ros::Publisher pub_move;
ros::Publisher pub_html;

ros::Subscriber sub_move;
ros::Subscriber sub_html;


int fd;

void move_to_masterCallback(const std_msgs::String::ConstPtr& msg ){
    pub_html.publish(msg);
}

void html_to_masterCallback(const std_msgs::String::ConstPtr& msg ){
    string mex = msg->data;
    std_msgs::String res;
    int comando;

    stringstream ss << mex.substr(0, s.find(":"));
    mex.erase(0,2);
    ss >> comando;

    switch(comando){
        case ACCEDI:
            if(stanzaLog(mex,stanze,logged,8) == 1){
                res->data = mex;
                pub_html.publish(res);
                loggato++;
            }else{
                string s = "logged";
                res->data = s;
                pub_html.publish(res);
            }
            break;
        case CHIAMA:

            coordinate = getStanza(mex);

            cout << "INVIO COORDINATE AL ROBOT: " << coordinate[0] << " "
            << coordinate[1] << " " << coordinate[2] << " " << endl;

            msg_goal->x = coordinate[1];
            msg_goal->y = coordinate[2];
            msg_goal->y = coordinate[3];

            pub_move.publish(msg_goal);

            //da adattare per robot in transito verso stanza mex
            res->data = mex;
            pub_html.publish(res);

            break;

        case SPEDISCI:
            if(isLogged(mex, stanze, logged, 8)){
                coordinate = getStanza(mex);

                cout << "INVIO COORDINATE AL ROBOT: " << coordinate[0] << " "
                << coordinate[1] << " " << coordinate[2] << " " << endl;

                msg_goal->x = coordinate[1];
                msg_goal->y = coordinate[2];
                msg_goal->y = coordinate[3];

                pub_move.publish(msg_goal);

                //da adattare per robot in transito verso stanza mex
                res->data = mex;
                pub_html.publish(res);
            }
            break;
        default:
            string h = "help";
            res->data = h;
            pub_html.publish(res);
            break;
    }

}




int main(int argc, char**argv) {

    ros::init(argc,argv,"master");
    ros::NodeHandle n;
    // topic: goal
    pub_move = n.advertise<move_robot::NewGoal>("NewGoal",1000);
    pub_html = n.advertise<std_msgs::String>("master_to_html",1000);

    ros::Subscriber sub_move = n.subscribe("move_to_master",1000,move_to_masterCallback);
    ros::Subscriber sub_html = n.subscribe("html_to_master",1000,);
    //ros::Rate loop_rate(20);


    //APERTURA FIFO CON DENTRO COORDINATE

    int i;
    int count=0;
    while(ros::ok()) {

        ros::spinOnce();
        sleep(5);
       // loop_rate.sleep();
    }

    close(fd);

    return EXIT_SUCCESS;

}
