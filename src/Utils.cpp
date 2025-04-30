#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace PolygonalLibrary
{
bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;

    return true;

}
// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell0Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;

    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close(); //Inserisco in una coda le righe del file

    // remove header
    listLines.pop_front();

    mesh.NumCell0Ds = listLines.size(); // memorizzo il numero di punti presenti

    if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds); // riserva una capacità di NumCell0Ds
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds); //creo una matrice 3xNumeroPunti

    for (const string& line : listLines)
    {
        istringstream converter(line); //creo uno stream input
        string token;

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        getline(converter, token, ';');
        id = stoi(token);

        getline(converter, token, ';');
        marker = stoi(token);

        getline(converter, token, ';');
        mesh.Cell0DsCoordinates(0, id) = stof(token);

        getline(converter, token);
        mesh.Cell0DsCoordinates(1, id) = stof(token);


        //converter >>  id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);

        mesh.Cell0DsId.push_back(id); // inserisco l'id nel vettore degli id

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell0Ds.find(marker);
            if(it == mesh.MarkerCell0Ds.end()) //se il marker non esiste
            {
                mesh.MarkerCell0Ds.insert({marker, {id}}); //inserisco il marker e l'id
            } 
            else
            {
                // mesh.MarkerCell0Ds[marker].push_back(id);
                it->second.push_back(id); //aggiungo l'id al vettore degli id con quel marker
            }
        }

    }

    return true;
}
// ***************************************************************************
bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./Cell1Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell1Ds = listLines.size();

    if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line); //creo uno stream input
        string token;

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;

        getline(converter, token, ';');
        id = stoi(token);

        getline(converter, token, ';');
        marker = stoi(token);

        getline(converter, token, ';');
        mesh.Cell1DsExtrema(0, id) = stoi(token);

        getline(converter, token);
        mesh.Cell1DsExtrema(1, id) = stoi(token);

        mesh.Cell1DsId.push_back(id);

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell1Ds.find(marker);
            if(it == mesh.MarkerCell1Ds.end())
            {
                mesh.MarkerCell1Ds.insert({marker, {id}});
            }
            else
            {
                // mesh.MarkerCell1Ds[marker].push_back(id);
                it->second.push_back(id);
            }
        }
    }

    return true;
}
// ***************************************************************************
bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    file.close();

    // remove header
    listLines.pop_front();

    mesh.NumCell2Ds = listLines.size();

    if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

    for (const string& line : listLines)
    {
        istringstream converter(line); //creo uno stream input
        string token;

        unsigned int id;
        unsigned int marker;
        unsigned int n_vertices;
        unsigned int n_edges;
        std::vector<unsigned int> vertices;
        std::vector<unsigned int> edges;


        getline(converter, token, ';');
        id = stoi(token);

        getline(converter, token, ';');
        marker = stoi(token);

        getline(converter, token, ';');
        n_vertices = stoi(token);


        vertices.reserve(n_vertices);
        for(unsigned int i = 0; i < n_vertices; i++){
            getline(converter, token, ';');
            vertices.push_back(stoi(token));
            
        }

        getline(converter, token, ';');
        n_edges = stoi(token);

        edges.reserve(n_edges);
        for(unsigned int i = 0; i < n_edges; i++){
            if (i== n_edges-1)
                getline(converter, token);
            else
                getline(converter, token, ';');
            edges.push_back(stoi(token));
        }

        /// Memorizza i marker
        if(marker != 0)
        {
            const auto it = mesh.MarkerCell2Ds.find(marker);
            if(it == mesh.MarkerCell2Ds.end())
            {
                mesh.MarkerCell2Ds.insert({marker, {id}});
            }
            else
            {
                // mesh.MarkerCell2Ds[marker].push_back(id);
                it->second.push_back(id);
            }
        }

        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsVertices.push_back(vertices);
        mesh.Cell2DsEdges.push_back(edges);
    }

    return true;
}

}
