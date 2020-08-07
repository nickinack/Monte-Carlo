#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <chrono>
#include <thread>
#include <cmath>
#include <random>
#include <iterator>


using namespace std;

vector<double> simulate_path(double start , double mu , double sigma , double delta , double steps);
vector<vector<double>> simulate_walks(double start , double mu , double sigma , double delta , double steps , int iter);
double calc_next(double walk , double mu , double sigma , double delta , std::normal_distribution<double> norm);

vector<vector<double>> simulate_walks(double start , double mu , double sigma , double delta , double steps , int iter)
{
    vector<vector<double>> walks;
    int i = 0 ; 
    for(int i = 0 ; i < iter ; i++)
    {
        walks.push_back(simulate_path(start ,  mu ,  sigma , delta , steps));
    }
    return walks;

}

vector<double> simulate_path(double start , double mu , double sigma , double delta , double steps)
{
    vector<double> path;
    double walk = start;
    std::normal_distribution<double> norm(mu, sigma);
    path.push_back(start);
    for(int i = 0 ; i < steps-1 ; i++)
    {
        walk = calc_next(walk , mu , sigma , delta, norm);
        path.push_back(walk);
    }
    return path;
}

double calc_next(double walk , double mu , double sigma , double delta , normal_distribution<double> norm)
{
    static std::random_device rd;
    static std::mt19937 g(rd());
    return (walk + (walk*(mu*delta + sigma*norm(g)*pow(delta , 0.5))));
}

int main(void){

    vector<vector<double>> walks = simulate_walks(100.0 , 0.0 , 0.1 , 0.001 , 100 , 20);
    ofstream outfile;
    outfile.open("paths.txt");
    int len1 = walks.size();
    int len2 = walks[0].size();

    for(int i = 0 ; i < len1 ; i++)
    {
        for(int j = 0 ; j < len2 ; j++)
        {
            outfile<<walks[i][j]<<" ";
        }
        outfile<<endl;
    }
}

