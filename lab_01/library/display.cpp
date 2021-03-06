#ifndef DISPLAY_CPP
#define DISPLAY_CPP

#include "display.h"

typeError getCoordForDrawLine(const nodeType* nodes, const int src, const int purp)
{
    typeError error;

    if ((error = checkNodesExist(nodes)))
        return error;

    const double xSrc = getX(nodes[src].x, nodes[src].z);
    const double ySrc = getY(nodes[src].y, nodes[src].z);
    const double xPurp = getX(nodes[purp].x, nodes[purp].z);
    const double yPurp = getY(nodes[purp].y, nodes[purp].z);

    error = drawLine(xSrc, ySrc, xPurp, yPurp);

    return error;
}

typeError drawDisplay(const edgeType* edges, const nodeType* nodes, \
                      const unsigned int size)
{
    typeError error;

    if ((error = checkEdgesExist(edges)))
        return error;

    int src;
    int purp;

    for (unsigned int i = 0; i < size && error == OK; i++)
    {
        src = edges[i].src;
        purp = edges[i].purp;
        error = getCoordForDrawLine(nodes, src, purp);
    }

    return error;
}

#endif // DISPLAY_CPP

