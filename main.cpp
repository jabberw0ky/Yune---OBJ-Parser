/******************************************************************************
 *  This file is part of Yune".
 *
 *  Copyright (C) 2018 by Umair Ahmed and Syed Moiz Hussain.
 *
 *  "Yune" is a framework for a Physically Based Renderer. It's aimed at young
 *  researchers trying to implement Physically Based Rendering techniques.
 *
 *  "Yune" is a free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  "Yune" is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<sstream>
#include <stdlib.h>
#include<stdio.h>
#include<vector>
#include <glm/glm.hpp>

using namespace std;

glm::vec3 dum;
bool tagEmpty = true;

std::vector < glm::vec3 > nVertices;
std::vector < glm::vec3 > nNormals;

std::vector <int> vert_indx;
std::vector <int> norm_indx;
std::vector <int> groups;
std::vector <string> meshIDs;

int faceCount = 0;
string description;

bool importer ( const char *fname )
{

 ifstream inFile(fname, fstream::in);

    if ( !inFile )
    {
        cout << "Unable to open file";
        exit(1);
    }

    while((!inFile.eof()))
          {

    string dataType;
    inFile >> dataType;

        if ( dataType == "#" )
        {
            getline(inFile,description);
        }

         if ( (dataType == "o") || (dataType == "g" ) )
     {
        string meshName = "";
        getline(inFile,meshName);

        if(meshName != " default")
        {
            meshIDs.push_back(meshName);
        }

        groups.push_back(faceCount);
        tagEmpty = false;

     }

     if ( (dataType == "v") )
     {
            glm::vec3 vertex;

            inFile >> vertex.x;
            inFile >> vertex.y;
            inFile >> vertex.z;


            nVertices.push_back(vertex);
     }

    if ( dataType == "vn" )
{
            glm::vec3 normals;

            inFile >> normals.x;
            inFile >> normals.y;
            inFile >> normals.z;

            nNormals.push_back(normals);
}


if ( dataType.substr(0,1) == "f" )
{

if (tagEmpty == true)
    {
        groups.push_back(faceCount);
        tagEmpty = false;
    }

faceCount++;

string line;
getline(inFile,line);
int iteration = 0;
int start = 0;
int fin  = 0;
bool vert,nor,tex = false;

for (int i = 0 ; i < line.size()  ; i++)
{

if ( ((line[i] == ' ') || (line[i] == '/')) && (iteration == 0) )
{
    start = i;
    iteration++;

}
else if ( ( (i == line.size()-1) || (line[i] == ' ') || (line[i] == '/')) && (iteration == 1) )
{
    fin = i;
    istringstream s(line.substr(start + 1,fin - 1));

    int index;
    s >> index;

    if ( vert == false )
    {
    vert_indx.push_back(index);
    vert = true;
    start = i;


    }
    else if ( tex == false)
    {
        tex = true;
        start = i;

    }
else if ( nor == false)
    {
    norm_indx.push_back(index);
    start = i;
    vert = false;
    tex = false;
    }

}

}

}


}
inFile.close();
}

void exporter (const char *fname)
{
ofstream yuneFile;
yuneFile.open(fname);

int j = 0;
int i = 0;
int m = 0;

yuneFile << "#" << description << endl << endl;

for( int k = 0 ; k < faceCount ; k++ )
{
    if( k == groups[j] )
    {
        yuneFile << "o " << "MeshID:" << meshIDs[m] << endl << "matID" << endl << endl;
        j += 2;
        m++;
    }

    yuneFile << "f" << endl;
    yuneFile << "v ";
    yuneFile << nVertices[vert_indx[i]].x << " ";
    yuneFile << nVertices[vert_indx[i]].y << " ";
    yuneFile << nVertices[vert_indx[i]].z << endl;
    yuneFile << "v ";
    yuneFile << nVertices[vert_indx[i+1]].x << " ";
    yuneFile << nVertices[vert_indx[i+1]].y << " ";
    yuneFile << nVertices[vert_indx[i+1]].z << endl;
    yuneFile << "v ";
    yuneFile << nVertices[vert_indx[i+2]].x << " ";
    yuneFile << nVertices[vert_indx[i+2]].y << " ";
    yuneFile << nVertices[vert_indx[i+2]].z << endl << endl;

    yuneFile << "n ";
    yuneFile << nNormals[norm_indx[i]].x << " ";
    yuneFile << nNormals[norm_indx[i]].y << " ";
    yuneFile << nNormals[norm_indx[i]].z << endl;
    yuneFile << "n ";
    yuneFile << nNormals[norm_indx[i+1]].x << " ";
    yuneFile << nNormals[norm_indx[i+1]].y << " ";
    yuneFile << nNormals[norm_indx[i+1]].z << endl;
    yuneFile << "n ";
    yuneFile << nNormals[norm_indx[i+2]].x << " ";
    yuneFile << nNormals[norm_indx[i+2]].y << " ";
    yuneFile << nNormals[norm_indx[i+2]].z << endl << endl;

    i += 3;
}

yuneFile.close();

/*
while(k != faceCount){
if (k == groups[j+1])
{
     j++;
     yuneFile << tagID[j] << " MeshID " << j << endl << "matID " << endl;
}
    yuneFile << "f" << endl;
    yuneFile << "v ";
    yuneFile << nVertices[vert_indx[i]].x << " ";
    yuneFile << nVertices[vert_indx[i]].y << " ";
    yuneFile << nVertices[vert_indx[i]].z << endl;
    yuneFile << "v ";
    yuneFile << nVertices[vert_indx[i+1]].x << " ";
    yuneFile << nVertices[vert_indx[i+1]].y << " ";
    yuneFile << nVertices[vert_indx[i+1]].z << endl;
    yuneFile << "v ";
    yuneFile << nVertices[vert_indx[i+2]].x << " ";
    yuneFile << nVertices[vert_indx[i+2]].y << " ";
    yuneFile << nVertices[vert_indx[i+2]].z << endl << endl;

    yuneFile << "n ";
    yuneFile << nNormals[norm_indx[i]].x << " ";
    yuneFile << nNormals[norm_indx[i]].y << " ";
    yuneFile << nNormals[norm_indx[i]].z << endl;
    yuneFile << "n ";
    yuneFile << nNormals[norm_indx[i+1]].x << " ";
    yuneFile << nNormals[norm_indx[i+1]].y << " ";
    yuneFile << nNormals[norm_indx[i+1]].z << endl;
    yuneFile << "n ";
    yuneFile << nNormals[norm_indx[i+2]].x << " ";
    yuneFile << nNormals[norm_indx[i+2]].y << " ";
    yuneFile << nNormals[norm_indx[i+2]].z << endl << endl;
i+=3;
 k++;
}
*/

}

int main()
{
    nVertices.push_back(dum);
    nNormals.push_back(dum);

    string import = "imports/";
    string export_loc = "exports/";
    string name;

    cout << "Enter the name of the file:" << endl;
    cin >> name;

     import.append(name);
     import.append(".obj");

     export_loc.append(name);
     export_loc.append(".rtt");

     importer(import.c_str());
     exporter(export_loc.c_str());

     cout << " Conversion Complete...!! ";

    return 0;
}
