#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <bits/stdc++.h>

using namespace std;

/** This file handles parsing the data we are going to work with **/
/** It also holds all the global variables we parse into         **/

// Global variables
string operation;
int last_instant;
int process_count;
vector<pair<char, int>> algorithms;
vector<tuple<string, int, int>> processes;
vector<vector<char>> timeline;
unordered_map<string, int> processToIndex;

// Results
vector<int> finishTime;
vector<int> turnAroundTime;
vector<float> normTurn;

// Function to parse the algorithms from the input string
void parse_algorithms(const string& algorithm_chunk)
{
    stringstream stream(algorithm_chunk);
    string temp_str;

    while (getline(stream, temp_str, ','))
    {
        stringstream ss(temp_str);
        char algorithm_id;
        int quantum = -1;

        ss >> algorithm_id;
        if (ss.peek() == '-') 
        {
            ss.ignore(); // ignore the '-'
            ss >> quantum;
        }

        algorithms.emplace_back(algorithm_id, quantum);
    }
}

// Function to parse the processes
void parse_processes()
{
    for (int i = 0; i < process_count; ++i)
    {
        string process_chunk;
        cin >> process_chunk;

        stringstream stream(process_chunk);
        string process_name;
        int process_arrival_time, process_service_time;

        getline(stream, process_name, ',');
        stream >> process_arrival_time;
        stream.ignore(); // ignore the ','
        stream >> process_service_time;

        processes.emplace_back(process_name, process_arrival_time, process_service_time);
        processToIndex[process_name] = i;
    }
}

// Function to parse the overall input
void parse()
{
    string algorithm_chunk;
    cin >> operation >> algorithm_chunk >> last_instant >> process_count;

    parse_algorithms(algorithm_chunk);
    parse_processes();

    finishTime.resize(process_count);
    turnAroundTime.resize(process_count);
    normTurn.resize(process_count);
    timeline.assign(last_instant, vector<char>(process_count, ' '));
}

#endif // PARSER_H_INCLUDED
