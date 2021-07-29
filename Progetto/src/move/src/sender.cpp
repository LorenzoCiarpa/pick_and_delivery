#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "move/NewGoal.h"
#include "std_msgs/String.h"
///////////////////////////////////
#include "ros/ros.h"
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>
using namespace std;
//using namespace std_msgs;


#define ACCEDI 1
#define CHIAMA 2


//dichiarazione
vector<string> parse(string s){
	//string s = "scott>=tiger>=mushroom";
	string delimiter = ":";
	vector<string> res;
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
	    token = s.substr(0, pos);
	    //cout << token << endl;
	    s.erase(0, pos + delimiter.length());
		res.push_back(token);
	}
	//cout << s << endl;
	res.push_back(s);
	return res;
}

float* getStanza(string buf) {

	float* coordinate = (float*)malloc(sizeof(float*)*4);

	ifstream input("/home/me/Desktop/stanze.txt");

	if(!input.is_open()){
		fprintf(stderr, "open file stanze.txt failed\n");
		std::cerr << strerror(errno) << '\n';
		exit(EXIT_FAILURE);
	}

	for( string line; getline( input, line ); )
	{
	   	vector<string> tokens = parse(line);
		if(tokens[0].compare(buf)==0){
			coordinate[0]=stof(tokens[1]);
			coordinate[1]=stof(tokens[2]);
			coordinate[2]=stof(tokens[3]);
			printf("\n");
		}
	}

	return coordinate;

}
int stanzaLog(string buf, vector<string> stanze, bool* logged, int size) {

	for(int i=0; i<size; i++){
		if(stanze[i].compare(buf)==0){
			if(logged[i]==true) return 0;
			logged[i] = true;
			return 1;
		}
	}

}
void deleteLog(string buf, vector<string> stanze, bool* logged, int size) {

	for(int i=0; i<size; i++){
		if(stanze[i].compare(buf)==0){
			if(logged[i]==true) logged[i]=false;


		}
	}

}

void resetLog(bool* logged, int size) {

	for(int i = 0; i<size; i++){
		logged[i]=false;
	}

}

int isLogged(string buf, vector<string> stanze, bool* logged, int size){
	for(int i=0; i<size; i++){
		if(stanze[i].compare(buf)==0){
			if(logged[i]==true) return 1;
			return 0;
		}
	}
}
//fine dichiarazione
std::vector<string> stanze={"sala 1","sala 2","sala 3","sala 4","sala 5","sala 6","sala 7","sala 8"};
bool logged[8]={false,false,false,false,false,false,false,false};
move::NewGoal msg_goal;
int loggato;

ros::Publisher pub_move;
ros::Publisher pub_html;

ros::Subscriber sub_move;
ros::Subscriber sub_html;


int fd;

bool cruising = false;

void move_to_masterCallback(const std_msgs::String::ConstPtr& msg ){//quando arriva consegnato cosa deve girare al js


    pub_html.publish(msg);
}

void html_to_masterCallback(const std_msgs::String::ConstPtr& msg ){
    string stanzap;
    string stanzad;
    std_msgs::String res;
    int comando;
    std::vector<string> tokens;
    tokens=parse(msg->data);

    if (tokens.size()==2) {
      comando=stoi(tokens[0]);
      stanzap=tokens[1];
    }
    if (tokens.size()==3) {
      comando=stoi(tokens[0]);
      stanzap=tokens[1];
      stanzad=tokens[2];
    }



    switch(comando){
        case ACCEDI:{


            if(stanzaLog(stanzap,stanze,logged,8) == 1){
                res.data = "1:"+stanzap+":"+"login";
                pub_html.publish(res);
                loggato++;
            }else{
                string s = "1:"+stanzap+":"+"logged";
                res.data = s;
                pub_html.publish(res);
            }
            break;
          }
        case CHIAMA:
        {
            float* coordinate;
            coordinate= getStanza(stanzap);

            cout << "INVIO COORDINATE AL ROBOT: " << coordinate[0] << " "
            << coordinate[1] << " " << coordinate[2] << " " << endl;

            string a=to_string(comando);
            msg_goal.x = coordinate[0];
            msg_goal.y = coordinate[1];
            msg_goal.theta = coordinate[2];
            msg_goal.cmd = ""+a+":"+stanzap;

            pub_move.publish(msg_goal);

            //da adattare per robot in transito verso stanza mex
            //res->data = "inviato:stanza:transito"

/*
            res->data = mex;
            pub_html.publish(res);
*/
            break;
}
        case 3:
        {

            if(isLogged(stanzad, stanze, logged, 8)){
                float* coordinate;
                coordinate = getStanza(stanzad);

                cout << "INVIO COORDINATE AL ROBOT: " << coordinate[0] << " "
                << coordinate[1] << " " << coordinate[2] << " " << endl;

                string b=to_string(comando);
                msg_goal.x = coordinate[0];
                msg_goal.y = coordinate[1];
                msg_goal.theta = coordinate[2];
                msg_goal.cmd = "" + b + ":" + stanzad; //DA VERIFICARE

                pub_move.publish(msg_goal);

                //da adattare per robot in transito verso stanza mex

            }
						else{
							res.data = "3:"+stanzad+":"+"notlogged";
							pub_html.publish(res);

						}
            break;
          }
					case 4:
					{
						deleteLog(stanzap,stanze,logged,8);
					}
        default:{
            string h;
            h = "help";
            res.data = h;
            pub_html.publish(res);
            break;
          }
    }

}




int main(int argc, char**argv) {

    ros::init(argc,argv,"master");
    ros::NodeHandle n;
    // topic: goal
    pub_move = n.advertise<move::NewGoal>("NewGoal",1000);
    pub_html = n.advertise<std_msgs::String>("master_to_html",1000);

    sub_move = n.subscribe("move_to_master",1000,move_to_masterCallback);
    sub_html = n.subscribe("html_to_master",1000,html_to_masterCallback);
    //ros::Rate loop_rate(20);


    //APERTURA FIFO CON DENTRO COORDINATE

    int i;
    int count=0;
    while(ros::ok()) {

        ros::spinOnce();
        sleep(5);
       // loop_rate.sleep();
    }



    return EXIT_SUCCESS;

}

/*
1)Controllo cruising, blocca tutto se robot in movimento
2)Controllo consegnato
*/
