#ifndef DISTANCE_MATRIX
#define DISTANCE_MATRIX

class DistanceMatrix{
public:
		DistanceMatrix(GlobalGiftData gifts):
				size(gifts.size()),
				items(vector_size(gifts.size())){

				for (int i = 0; i < size; ++i) {
						for (int j = 0; j < i / 2; ++j) {
								auto index = get_index(size, i,j);

								auto g1 = gifts[i];
								auto g2 = gifts[j];
								auto d = Dist(g1.Loc(), g2.Loc());

								items.at(index) = d;
						}
				}
		}

		static void getMinMax(GlobalGiftData gifts, double &max, double &min){
				max = numeric_limits<double>::min();
				min = numeric_limits<double>::max();

//				#pragma omp parallel
				for (int i = 0; i < gifts.size(); ++i) {
						for (int j = 0; j < i; ++j) {
								auto index = get_index(gifts.size(), i,j);

								auto g1 = gifts[i];
								auto g2 = gifts[j];
								auto d = Dist(g1.Loc(), g2.Loc());

								max = std::max( max, d );
								min = std::min( min, d );
						}
				}
		}

		FloatType at(size_t i, size_t j){
				auto index = get_index(size, i,j);
				return items.at(index);
		}

		inline static
		size_t vector_size(size_t s){
				return (s*(s+1))/2;
		}

private:
		size_t size;
		vector<float> items;


		inline static
		size_t get_index(size_t size, size_t i, size_t j){
				return (i <= j) ? i*size + j : j*size + i;
		}
};

#endif // DISTANCE_MATRIX

