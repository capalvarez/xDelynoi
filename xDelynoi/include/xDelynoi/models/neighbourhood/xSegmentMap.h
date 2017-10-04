#ifndef XDELYNOI_XSEGMENTMAP_H
#define XDELYNOI_XSEGMENTMAP_H

#include <delynoi/models/neighbourhood/SegmentMap.h>

class xSegmentMap : public SegmentMap{
private:
    void changeNeighbour(NeighboursBySegment n, int oldN, int newN);
    int getOther(NeighboursBySegment n, int other);
public:
    xSegmentMap();
    xSegmentMap(SegmentMap segmentMap);
    void changeNeighbour(IndexSegment s, int oldNeighbour, int newNeighbour);
    bool isNeighbour(IndexSegment s, int poly);
    bool isInBorder(IndexSegment s);
    void replace_or_delete(IndexSegment s, int oldNeighbour_current, int oldNeighbour_old, int newNeighbour,
                           std::unordered_map<NeighboursBySegment, int, NeighboursHasher> map,
                           std::unordered_map<IndexSegment, int, SegmentHasher> &erased,
                           std::unordered_map<int, int> newEquivalence);
    void deleteElement(IndexSegment s);
    void replaceNeighbour(IndexSegment s, int oldNeighbour, int newNeighbour);
    std::vector<int> getAllNeighbours(std::vector<IndexSegment> segments, int polygon);
};

#endif