#include <delynoi/models/basic/IndexSegment.h>
#include <utilities/UniqueList.h>

namespace xdelynoi_utilities{
    IndexSegment convert(PointSegment s, UniqueList<Point> points){
        int i1 = points.indexOf(s.getFirst()), i2 = points.indexOf(s.getSecond());

        if(i1<0 || i2<0){
            throw std::invalid_argument("The given segment is not in the mesh");
        }

        return IndexSegment(i1, i2);
    }

    void getAllPairs(std::vector<Pair<int>> &pairs, std::vector<int> numbers) {
        int N = numbers.size();
        std::string bitmask(2, 1);
        bitmask.resize(N, 0);
        do {
            int f = -1;
            int s = -1;

            for (int i = 0; i < N; ++i){
                if (bitmask[i]){
                    if(f==-1){
                        f = i;
                    }else{
                        s = i;
                    }
                }
            }
            pairs.push_back(Pair<int>(numbers[f],numbers[s]));

        } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    }
}