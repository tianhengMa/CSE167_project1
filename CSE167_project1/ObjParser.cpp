//
//  ObjParser.cpp
//  CSE167_project1
//
//  Created by Matthew Ma on 10/5/20.
//

#include "ObjParser.hpp"
using namespace std;

std::ifstream objFile(objFilename); // The obj file we are reading.
std::vector<glm::vec3> points;

// Check whether the file can be opened.
if (objFile.is_open())
{
    std::string line; // A line in the file.

    // Read lines from the file.
    while (std::getline(objFile, line))
    {
        // Turn the line into a string stream for processing.
        std::stringstream ss;
        ss << line;
        
        // Read the first word of the line.
        std::string label;
        ss >> label;

        // If the line is about vertex (starting with a "v").
        if (label == "v")
        {
            // Read the later three float numbers and use them as the
            // coordinates.
            glm::vec3 point;
            ss >> point.x >> point.y >> point.z;

            // Process the point. For example, you can save it to a.
            points.push_back(point);
        }
    }
} else
{
    std::cerr << "Can't open the file " << objFilename << std::endl;
}

objFile.close();
