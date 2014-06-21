#pragma once

#include "algo.h"

#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
using namespace std;

class ServerConnection{
	CURL* curl;
	string readBuffer;
	static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp){
		((string*)userp)->clear();
		((string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}
public:
	ServerConnection(string url){
		curl = curl_easy_init();
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	}
	~ServerConnection(){
		curl_easy_cleanup(curl);
	}
	string httpGet(){
		curl_easy_perform(curl);
		return readBuffer;
	}
};

pair<vector<van_nodes>,vector<cor_gui> > parsejson(string str){
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( str, root );
	if(!parsingSuccessful )	{
		std::cout  << "failed to parse: "
				   << reader.getFormatedErrorMessages();
	}

	const Json::Value data = root["data"];
	vector<van_nodes> fst;
	for(unsigned i=0; i<data.size(); i++){
		van_nodes tmp;
		tmp.mac_source      =  data[i]["s"].asString();
		tmp.mac_destination =  data[i]["d"].asString();
		tmp.power           = -data[i]["r"].asInt();
		fst.push_back(tmp);
	}

	const Json::Value fixed = root["fixed"];
	vector<cor_gui> snd;
	for(unsigned i=0; i<fixed.size(); i++){
		cor_gui tmp;
		tmp.mac = fixed[i]["a"].asString();
		tmp.x   = fixed[i]["x"].asInt();
		tmp.y   = fixed[i]["y"].asInt();
		snd.push_back(tmp);
	}
	return make_pair(fst,snd);
}
