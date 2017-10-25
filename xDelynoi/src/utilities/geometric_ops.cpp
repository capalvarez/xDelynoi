#include <xDelynoi/utilities/geometric_ops.h>

namespace geometric_ops{
    void fixCCW(std::vector<int> &pointList, int reference, std::vector<Point> points) {
        if(!geometric_ops::isCCW(pointList, reference, points)){
            std::reverse(pointList.begin(), pointList.end());
        }
    }

    bool isCCW(std::vector<int> pointList, int reference, std::vector<Point>& points) {
        pointList.push_back(reference);
        auto n = (int) pointList.size();

        Point pI = points[pointList[0]];
        Point pI1 = points[pointList[n-1]];

        double sum = (pI.getX() - pI1.getX())*(pI.getY() + pI1.getY());

        for(int i=0; i<n-1; i++){
            pI1 = points[pointList[(i+1)%n]];
            pI = points[pointList[i]];

            sum += (pI1.getX() - pI.getX())*(pI1.getY() + pI.getY());
        }

        return sum<=0;
    }
}