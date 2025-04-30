#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolygonalLibrary {

struct PolygonalMesh
{
    unsigned int NumCell0Ds = 0; ///< number of Cell0D
    std::vector<unsigned int> Cell0DsId = {}; ///< Cell0D id, size 1 x NumberCell0D
    Eigen::MatrixXd Cell0DsCoordinates = {}; ///< Cell0D coordinates, size 2 x NumberCell0D (x,y)
    std::map<unsigned int, list<unsigned int>> MarkerCell0Ds = {}; ///< Cell0D markers e id

    unsigned int NumCell1Ds = 0; ///< number of Cell1D
    std::vector<unsigned int> Cell1DsId = {}; ///< Cell1D id, size 1 x NumberCell1D
    Eigen::MatrixXi Cell1DsExtrema = {}; ///< Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)
    std::map<unsigned int, list<unsigned int>> MarkerCell1Ds = {}; ///< Cell1D properties

    unsigned int NumCell2Ds = 0; ///< number of Cell2D
    std::vector<unsigned int> Cell2DsId = {}; ///< Cell2D id, size 1 x NumberCell2D
    std::vector<std::vector<unsigned int>> Cell2DsVertices = {}; ///< Cell2D Vertices indices, size 1 x NumberCell2DVertices[NumberCell2D]
    std::vector<std::vector<unsigned int>> Cell2DsEdges = {}; ///< Cell2D Cell1D indices, size 1 x NumberCell2DEdges[NumberCell2D]
    std::map<unsigned int, list<unsigned int>> MarkerCell2Ds = {}; ///< Cell2D properties


    // Metodi
    bool isZeroEdge(unsigned int edge_id){
        // con l'assunzione che i punti siano distinti
        //cout << "Estermo: " << Cell0DsCoordinates(0, Cell1DsExtrema(0, edge_id)) << endl;
        //return Cell1DsExtrema(0, edge_id) == Cell1DsExtrema(1, edge_id);
        return Cell0DsCoordinates(0, Cell1DsExtrema(0, edge_id)) == Cell0DsCoordinates(0, Cell1DsExtrema(1, edge_id)) &&
                Cell0DsCoordinates(1, Cell1DsExtrema(0, edge_id)) == Cell0DsCoordinates(1, Cell1DsExtrema(1, edge_id));
    }
    
    /*bool isZeroArea(unsigned int poly_id){
        unsigned int zero_edges = 0;

        for (auto edge_id:Cell2DsEdges[poly_id]){
            if (isZeroEdge(edge_id))
                zero_edges ++;
        } // MODIFICAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        return Cell2DsEdges[poly_id].size() - zero_edges < 3;
    }*/

    bool isZeroArea(unsigned int poly_id) {
        double area = 0.0;

        for (auto edge_id:Cell2DsEdges[poly_id]) {
            // p1.x*p2.y - p2.x*p2.y
            area += (Cell0DsCoordinates(0, Cell1DsExtrema(0, edge_id)) * Cell0DsCoordinates(1, Cell1DsExtrema(1, edge_id))) -
             (Cell0DsCoordinates(0, Cell1DsExtrema(1, edge_id)) * Cell0DsCoordinates(1, Cell1DsExtrema(0, edge_id)));
        }
    
        return std::abs(area) == 0;
    }
};

}

