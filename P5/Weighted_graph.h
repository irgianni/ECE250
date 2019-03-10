
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  igianni@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n) : num_nodes(n), num_edges(0) {
    if (n < 0)
        throw illegal_argument();
    graph = new double *[num_nodes];
    for (int i = 0; i < num_nodes; i++)
        graph[i] = new double [num_nodes];
    clear_edges();
}

Weighted_graph::~Weighted_graph() {
    for (int i = 0; i < num_nodes; i++) {
        delete [] graph[i];
        graph[i] = 0;
    }
    delete [] graph;
    graph = nullptr;
}

int Weighted_graph::degree(int u) const {
    if (u < 0 || u > num_nodes-1)
        throw illegal_argument();
    int deg = 0;
    for (int i = 0; i < num_nodes; i++)
        if (graph[u][i] != INF && u != i)
            deg++;
	return deg;
}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    if (i < 0 || i > num_nodes-1)
        throw illegal_argument();
    if (j < 0 || j > num_nodes-1)
        throw illegal_argument();
    if (i == j)
        return true;
    if (graph[i][j] == INF)
        return false;
    graph[i][j] = INF;
    graph[j][i] = INF;
    num_edges -= 1;
    return true;
}

void Weighted_graph::clear_edges() {
    for (int i = 0; i < num_nodes; i++)
        for (int j = 0; j < num_nodes; j++) {
            if (i == j)
                graph[i][j] = 0.0;
            else
                graph[i][j] = INF;
        }
    num_edges = 0;
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    if (i < 0 || i > num_nodes-1)
        throw illegal_argument();
    if (j < 0 || j > num_nodes-1)
        throw illegal_argument();
    if (d <= 0.0)
        throw illegal_argument();
    if (i == j)
        return false;
    if (graph[i][j] == INF)
        num_edges += 1;
    graph[i][j] = d;
    graph[j][i] = d;
	return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    std::pair<int, int> pairOfEdges[(num_nodes*(num_nodes-1))/2];
    int index = 0;
    for (int i = 0; i < num_nodes; i++)
        for (int j = i+1; j < num_nodes; j++)
            pairOfEdges[index++] = std::pair<int, int> (i, j);
    for (int i = num_nodes*(num_nodes-1)/2 - 1; i > 0; i--)
        for (int j = 0; j < i; j++) {
            std::pair<int, int> a = pairOfEdges[j];
            std::pair<int, int> b = pairOfEdges[j+1];
            if (graph[a.first][a.second] > graph[b.first][b.second]) {
                std::pair<int, int> temp = a;
                a = b;
                b = temp;
                pairOfEdges[j] = a;
                pairOfEdges[j+1] = b;
            }
        }
    double weight = 0.0;
    int totalCompared = 0;
    bool selected[(num_nodes*(num_nodes-1))/2];
    for (int i = 0; i < num_nodes*(num_nodes-1)/2; i++)
        selected[i] = false;
    Disjoint_set set(num_nodes);
    for (int i = 0; i < num_nodes*(num_nodes-1)/2; i++) {
        totalCompared++;
        std::pair<int, int> e = pairOfEdges[i];
        if (set.find_set(e.first) != set.find_set(e.second)) {
            selected[i] = true;
            weight += graph[e.first][e.second];
            set.union_sets(e.first, e.second);
        }
        if(set.num_sets() == 1)
            break;
    }
 	return std::pair<double, int>(weight, totalCompared);
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}


#endif
