//======= Copyright (c) 2025, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:      Tomáš Šuda<xsudatoo@stud.fit.vutbr.cz>
// $Date:       $2025-02-19
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"


Graph::Graph(){}

Graph::~Graph(){}

std::vector<Node*> Graph::nodes() {
    std::vector<Node*> nodes;
    for (auto& node : _nodes) {
        nodes.push_back(node.get());
    }
    return nodes;
}

std::vector<Edge> Graph::edges() const{
    std::vector<Edge> edges;
    for (auto& edge : _edges) {
        edges.push_back(edge);
    }
    return edges;
}

Node* Graph::addNode(size_t nodeId) {
    if (getNode(nodeId) != nullptr) {
        return nullptr;
    }
    Node* node = new Node();
    node->id = nodeId;
    node->color = 0;
    node->degree = 0;
    _nodes.push_back(std::unique_ptr<Node>(node));
    return node;
}

bool Graph::addEdge(const Edge& edge){
 
    if (edge.a == edge.b)  return false; // loop
    if(containsEdge(edge)) return false; // duplicate edge
    if(getNode(edge.a) == nullptr) addNode(edge.a);
    if(getNode(edge.b) == nullptr) addNode(edge.b);
    getNode(edge.b)->degree++;
    getNode(edge.a)->degree++;

    getNode(edge.a)->neighbors.push_back(getNode(edge.b));
    getNode(edge.b)->neighbors.push_back(getNode(edge.a));
    Edge new_edge =  Edge(edge.a, edge.b);
    _edges.push_back(new_edge);
    return true;

}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for (auto& edge : edges) {
        addEdge(edge);
    }
}

Node* Graph::getNode(size_t nodeId){
    for(auto& node : _nodes) {
        if (node->id == nodeId)  return node.get();
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{
   for(auto& e: _edges){
         if(e == edge) return true;
   }
   return false;
}

void Graph::removeNode(size_t nodeId){
    Node* node = getNode(nodeId);
    if(node == nullptr) throw std::out_of_range("Node not found");

    std::vector<Edge> edgesToRemove;
    for( Edge& e : _edges){
        if(e.a == node->id || e.b == node->id){
            edgesToRemove.push_back(e);
        }
    }
    for( Edge& e : edgesToRemove){
        removeEdge(e);
    }
    
    _nodes.erase(
        std::remove_if(_nodes.begin(), _nodes.end(),
        [&](std::unique_ptr<Node> &_nodes){
            return node->id == _nodes->id;
        }
        ),   
      _nodes.end());
}

void Graph::removeEdge(const Edge& edge){

    if(!containsEdge(edge)) throw std::out_of_range("Edge not found");
    _edges.erase(
        std::remove_if(_edges.begin(), _edges.end(),
        [&](const Edge& e){
            return e == edge;
        }
        ),   
      _edges.end());
}

size_t Graph::nodeCount() const{
    return _nodes.size();
}

size_t Graph::edgeCount() const{
    return _edges.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    Node* node = nullptr;
    for(auto& n : _nodes) {
        if (n->id == nodeId)  node = n.get();
    }

    if(node == nullptr) throw std::out_of_range("Node not found");
    size_t degree = 0;
    for(const Edge& e : _edges){
        if(e.a == nodeId || e.b == nodeId){
            degree++;
        }
    }
    return degree;
}

size_t Graph::graphDegree() const{
    size_t max_degree = 0;
    for(auto& node : _nodes) {
       if(max_degree < node->degree){
           max_degree = node->degree;
       }
    }
    return max_degree;
}

void Graph::coloring(){
    size_t max_color = graphDegree() + 1;
    for(auto& node : _nodes) {
        if( node->color == 0 ){
            std::vector<size_t> used_colors;
           for(Node *neighbor : node->neighbors){
                if(neighbor->color != 0){
                    used_colors.push_back(neighbor->color);
                }
            }
            for(size_t color =1 ; color <= max_color; color++){
                if(std::find(used_colors.begin(), used_colors.end(), color) == used_colors.end()){
                    node->color = color;
                    break;
                }
            }
        }
    }
}

void Graph::clear() {
    _nodes.clear();
    _edges.clear();
}

/*** Konec souboru tdd_code.cpp ***/
