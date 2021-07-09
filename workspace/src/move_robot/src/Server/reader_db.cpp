#include <fstream>
#include <stdio.h>
#include <mysql/mysql.h>
//#include <mysql/my_byteorder.h>
//#include <mysql/my_global.h>
#include "header.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
MYSQL *con;

//AVVIO LA CONNESSIONE CON IL DATABASE
int connection() {
	con = mysql_init(NULL);

  if (con == NULL) {
      fprintf(stderr, "mysql_init() failed\n");
      exit(EXIT_FAILURE);
  }
  if (!(mysql_real_connect(con, "localhost", "root", "", "StanzeDiag", 3306, NULL, 0))) {
      //finish_with_error(con);
      fprintf(stderr, "mysql_real_connect() failed\n");
      exit(EXIT_FAILURE);
  }
  return 1;
}

//LEGGO TUTTE LE STANZE DAL DATABASE
int reader_table() {

	if (!connection()) {
		exit(EXIT_FAILURE);
	}

  if (mysql_query(con, "SELECT * FROM Stanze")) {
      //finish_with_error(con);
      fprintf(stderr, "mysql_query() failed\n");
      exit(EXIT_FAILURE);
  }

  MYSQL_RES *result = mysql_store_result(con);
  if (result == NULL) {
      //finish_with_error(con);
      fprintf(stderr, "mysql_store_result() failed\n");
      exit(EXIT_FAILURE);
  }

  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result))) {
      for(int i = 0; i < num_fields; i++) {
          printf("%s ", row[i] ? row[i] : "NULL");
      }
          printf("\n");
  }
  mysql_free_result(result);
  mysql_close(con);
  return 1;
}

//INSERISCO UNA NUOVO STANZA NEL DATABASE
//NON UTILE PER ORA
void insertDB(string stanza, string x, string y, string theta) {

	if (!connection()) {
		exit(EXIT_FAILURE);
	}

	const char* query = (char*)malloc(sizeof(char*));
	string aux = "INSERT INTO Stanze VALUES('"+stanza+"',"+x+","+y+","+theta+")";
	query = aux.c_str();
    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
}

//INIZIALIZZO TUTTE LE STANZE A "VUOTE"
void resetLog() {

	if (!connection()) {
		exit(EXIT_FAILURE);
	}

	const char* query = (char*)malloc(sizeof(char*));
	string aux = "UPDATE Stanze SET log=0";
	query = aux.c_str();
	if (mysql_query(con, (const char*) query)) {
      //finish_with_error(con);
      fprintf(stderr, "mysql_query() failed\n");
      exit(EXIT_FAILURE);
	}

	mysql_close(con);

}

//reset Log file
void resetLog(bool* logged, int size) {

	for(int i = 0; i<size; i++){
		logged=false;
	}

}

//PRENDO LE COORDINATE DELLA STANZA SCELTA DALL'UTENTE PER LOGGARSI
void stanzaLog(string buf, vector<string>* stanze, bool* logged, int size) {

	for(int i=0; i<size; i++){
		if(strcmp(stanze[i],buf)==0){
			logged[i]=true;
		}
	}

}

//Stanza Log set = 1 in file
void stanzaLog(string buf) {

	if (!connection()) {
		exit(EXIT_FAILURE);
	}

	const char* query = (char*)malloc(sizeof(char*));
	string aux = "UPDATE Stanze SET log=1 WHERE nome='"+buf+"'";
	query = aux.c_str();
	if (mysql_query(con, (const char*) query)) {
      //finish_with_error(con);
      fprintf(stderr, "mysql_query() failed\n");
      exit(EXIT_FAILURE);
	}

	mysql_close(con);

}
//PRENDO LE COORDINATE DELLA STANZA SCELTA DALL'UTENTE PER SPEDIRE IL PACCO DB
float* getStanza(string buf) {

	if (!connection()) {
		exit(EXIT_FAILURE);
	}

	float* coordinate = (float*)malloc(sizeof(float*)*4);

	const char* query = (char*)malloc(sizeof(char*));
	string aux = "SELECT * FROM Stanze WHERE nome='"+buf+"'";
	query = aux.c_str();
	if (mysql_query(con, (const char*) query)) {
      //finish_with_error(con);
      fprintf(stderr, "mysql_query() failed\n");
      exit(EXIT_FAILURE);
	}

	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL) {
		//finish_with_error(con);
		fprintf(stderr, "mysql_store_result() failed\n");
		exit(EXIT_FAILURE);
	}

	int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result))) {
		for(int i = 0; i < num_fields; i++) {
			printf("%s ", row[i] ? row[i] : "NULL");
		}
			coordinate[0]=atof(row[1]);
			coordinate[1]=atof(row[2]);
			coordinate[2]=atof(row[3]);
			coordinate[3]=atof(row[4]);
			printf("\n");
	}
	mysql_free_result(result);
	mysql_close(con);

	return coordinate;

}

//PRENDO LE COORDINATE DELLA STANZA SCELTA DALL'UTENTE PER SPEDIRE IL PACCO FILE
float* getStanza(string buf) {

	float* coordinate = (float*)malloc(sizeof(float*)*4);
	std::ifstream input( "stanze.txt" );

	if(!input.is_open()){
		fprintf(stderr, "open file stanze.txt failed\n");
		exit(EXIT_FAILURE);
	}

	for( string line; getline( input, line ); )
	{
	   	vector<string> tokens = parse(line);
		if(stcmp(tokens[0],buf)==0){
			coordinate[0]=atof(tokens[1]);
			coordinate[1]=atof(tokens[2]);
			coordinate[2]=atof(tokens[3]);
			printf("\n");
		}
	}

	return coordinate;

}

vector<string> parse(string s){
	//string s = "scott>=tiger>=mushroom";
	string delimiter = ":";
	vector<string> res;
	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
	    token = s.substr(0, pos);
	    cout << token << endl;
	    s.erase(0, pos + delimiter.length());
		res.push_back(token);
	}
	cout << s << endl;
	return res;
}
