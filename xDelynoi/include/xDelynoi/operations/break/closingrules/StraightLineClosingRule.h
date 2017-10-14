#ifndef XDELYNOI_STRAIGHTLINECLOSINGRULE_H
#define XDELYNOI_STRAIGHTLINECLOSINGRULE_H

#include <xDelynoi/operations/break/closingrules/ClosingRule.h>

class StraightLineClosingRule : public ClosingRule {
public:
    void closePolygon(xMesh* mesh, Point p, int polygon);
};

#endif