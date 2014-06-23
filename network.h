#pragma once

#include "algo.h"

#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <string>
using namespace std;

#include <exception>
#include <stdexcept>

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
		if(!curl){throw runtime_error("ServerConnection: failed to initialize curl");}
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
	}
	~ServerConnection(){
		curl_easy_cleanup(curl);
	}
	string httpGet(){
		if( curl_easy_perform(curl) != CURLE_OK)
			throw runtime_error("httpGet: failed to reach server");
		return readBuffer;
	}
};

pair<vector<van_nodes>,vector<cor_gui> > parsejson(string str){
	Json::Value root;
	Json::Reader reader;

	if(!reader.parse( str, root ))
		throw runtime_error("parsejson: failed to parse: "+reader.getFormatedErrorMessages());
	if(!root.isObject())
		throw runtime_error("parsejson: no root object");
	if(!root.isMember("data"))
		throw runtime_error("parsejson: no member called \"data\"");
	if(!root.isMember("fixed"))
		throw runtime_error("parsejson: no member called \"fixed\"");

	const Json::Value data = root["data"];
	vector<van_nodes> fst;
	for(unsigned i=0; i<data.size(); i++){
        /*if(!data.isMember("s"))
			throw runtime_error("parsejson: root[data]["+to_string(i)+"]: missing \"s\"");
		if(!data.isMember("d"))
			throw runtime_error("parsejson: root[data]["+to_string(i)+"]: missing \"d\"");
		if(!data.isMember("r"))
			throw runtime_error("parsejson: root[data]["+to_string(i)+"]: missing \"r\"");
        */van_nodes tmp;
		tmp.mac_source      =  data[i]["s"].asString();
		tmp.mac_destination =  data[i]["d"].asString();
		tmp.power           = -data[i]["r"].asInt();
		fst.push_back(tmp);
	}

	const Json::Value fixed = root["fixed"];
	vector<cor_gui> snd;
	for(unsigned i=0; i<fixed.size(); i++){
        /*if(!data.isMember("a"))
			throw runtime_error("parsejson: root[fixed]["+to_string(i)+"]: missing \"a\"");
		if(!data.isMember("x"))
			throw runtime_error("parsejson: root[fixed]["+to_string(i)+"]: missing \"x\"");
		if(!data.isMember("y"))
			throw runtime_error("parsejson: root[fixed]["+to_string(i)+"]: missing \"y\"");
        */cor_gui tmp;
		tmp.mac = fixed[i]["a"].asString();
		tmp.x   = fixed[i]["x"].asInt();
		tmp.y   = fixed[i]["y"].asInt();
		snd.push_back(tmp);
	}
	return make_pair(fst,snd);
}
