#include "IOfuncs.h"



inline
vector<GiftTuple>
    LoadGiftTuples(const string & file_name);

inline
void
WriteSolution(const string & file_name,
              const SolutionOutput & solution );



inline
array<string, 4> ReadValues(const string & str){
    array<string, 4> res;

    stringstream ss(str);

    std::string value;
    int i = 0;
    while(getline(ss, value,','))
    {
        res.at(i) = value;
        ++i;
    }
    return res;
};

inline
GiftTuple LoadGift(const string & str){
    auto values = ReadValues(str);

    auto id = stoi(values[0]);
    auto l1 = stod(values[1]);
    auto l2 = stod(values[2]);
    auto w = stod(values[3]);

    return make_tuple(id, l1, l2, w);
}

inline
vector<GiftTuple> LoadGiftTuples(const string & file_name)
{
    vector<GiftTuple> res;

    fstream f(file_name);

    string line;
    int i = 0;
    while(getline(f,line)) {
        if(i!=0) {
            auto gift = LoadGift(line);
            res.push_back(gift);
        };
        ++i;
    }
    return res;
}

GiftData __LoadGifts(const string &file_name)
{
    auto tuples = LoadGiftTuples(file_name);
    vector<Gift> res;
    for(GiftTuple gift_tuple: tuples) {
        Gift gift = {
            get<0>(gift_tuple) - 1,
            get<1>(gift_tuple),
            get<2>(gift_tuple),
            get<3>(gift_tuple)
        };
        res.push_back(gift);
    }
    return res;
}




inline
SolutionOutput ReadSolution(const string & file_name)
{
    SolutionOutput res;

    fstream f(file_name);

    string line;
    int i = 0;
    while(getline(f,line)) {
        if(i!=0) {

            vector<int> v(2);
            stringstream ss(line);
            std::string value;
            int i = 0;
            while(getline(ss, value, ','))
            {
                v.at(i) = stoi(value);
                ++i;
            }

            auto gift_id = v[0] - 1;
            auto route_id = v[1];
            res.push_back(gift_id, route_id);
        };
        ++i;
    }
    return res;
}


//bool check_consecutive(const SolutionOutput & sol){
//    set<RouteID> route_ids(sol.begin(), sol.end());

//    bool is_cons = true;
//    auto iter = route_ids.begin();
//    auto end = prev(route_ids.end());
//    for (iter;iter != end; ++ iter){
//        auto next_iter = iter;
//        ++next_iter;

//        auto a = * iter;
//        auto b = * next_iter;

//        if ( abs(a - b) != 1){
//            is_cons = false;
//            break;
//        }
//    }
//    return is_cons;
//}




vector<Route> ReadSolutionRoutes(
        const string & file_name,
        GlobalGiftData gift_data){

    SolutionOutput sol = ReadSolution(file_name);
    return ReadSolutionRoutes(sol, gift_data);
}


vector<Route> ReadSolutionRoutes(
        SolutionOutput sol,
        GlobalGiftData gift_data){
    return sol.ReadRoutes(gift_data);

////    auto min_route_id = *std::min_element(sol.begin(),
////                                     sol.end());
//    auto min_route_id = sol.MinRouteId();

//    assert(min_route_id == 0);


////    auto is_cons = check_consecutive(sol);
////    assert(is_cons);


//    set<RouteID> route_ids;
//    for(auto r_id: sol){
//        route_ids.insert(r_id);
//    }

//    vector<Route> res;
//    for (auto r_id: route_ids){
//        Route r(gift_data);
//        res.push_back(r);
//    }

//    for (int i = 0; i < sol.size(); ++i) {
//        auto route_id = sol[i];
//        res[route_id].add(i);
//    }


//    auto gift_in_routes_count = GetGiftIDSCount(res);
//    assert(gift_in_routes_count == 100000);

//    auto gifts = GetAllGiftIDS(res);
//    assert(gifts.size() == 100000);

////    for(auto r: res){
////        assert(r.size()!=1);
////    }


//    return res;
}

inline
void WriteSolution(const string & file_name,
                                     const SolutionOutput & solution )
{
    ofstream f(file_name);
    f << "GiftId,TripId" << endl;
    for (int i = 0; i < solution.size(); ++i) {
        auto item = solution[i];

        auto giftId = item.gift_id;
        auto route_id = item.route_id;

        f<<to_string(giftId+1)<<","<<to_string(route_id)<<endl;
    }
}


SolutionOutput GetSolutionOutput(
        const vector<Route> & routes,
        GlobalGiftData gift_data){

    SolutionOutput sol_output;
    int route_index = 0;
    for(const auto & r: routes){
        for(const auto & gift_id: r){

            //sol_output.at(gift_id) = route_index;
            sol_output.push_back(gift_id, route_index);
        };
        ++route_index;
    };
return sol_output;
};

void WriteSolution(const string & file_name,
                   const vector<Route> & routes,
                   GlobalGiftData gift_data){

    auto sol_output = GetSolutionOutput(routes, gift_data);

    WriteSolution(file_name, sol_output);
}


vector<Route> IOhelper::GenerateDumbSolution2(GlobalGiftData gifts){
    vector<Route> res;
    //int route_index = 0;

    int i = 0;
    while(i<gifts.size()){


        Route r(gifts);
        for (int j = 0; j < 100; ++j){
            const Gift & gift = gifts[i];

            if((r.Weight() + gift.Weight()) > sleigh_weight_limit)
                break;

            if(i<gifts.size() ){

                r.add(i);
                ++i;
            }else
                break;
        }
        res.push_back(r);
    }
    return res;
}

IOhelper::IOhelper(string input_data_file):
    input_data_file(input_data_file)
{

    assert( FileExists(input_data_file) );

    //iostream
}

GiftData IOhelper::LoadGifts(){
    return __LoadGifts(this->input_data_file);
}

Solution IOhelper::GenerateSolution(){
    static auto gifts = __LoadGifts(input_data_file);
    GenerateFuncType gen_func = [&](GlobalGiftData giftData){
        return GenerateDumbSolution2(gifts);
    };
    auto sol = StartingSolution(gifts, gen_func);
    return sol;

}

Solution IOhelper::LoadSolution(const string &solution_fn){
    //assert( FileExists(solution_fn) );
    AssureFileExistence(solution_fn);

    static auto gifts = __LoadGifts(input_data_file);

    GenerateFuncType gen_func = [&](GlobalGiftData giftData){
        return ReadSolutionRoutes(solution_fn, gifts);
    };
    auto sol = StartingSolution(gifts, gen_func);
    return sol;
}

void IOhelper::SaveSolution(const Solution &sol, const string &solution_fn){
    WriteSolution(solution_fn, sol.routes, sol.gl_gift_data);
}

bool FileExists(const string &file_name)
{
    ifstream f(file_name.c_str());
    if (f.good()) {
        f.close();
        return true;
    }
    else{
        f.close();
        return false;
    }
}

void AssureFileExistence(const string &file_name)
{
    auto is_exist = FileExists(file_name);
    if (!is_exist) {
        class FileDoesntExist: public std::exception{
        public:
            virtual const char* what() const noexcept override{
                string err_msg = "file doesnt exist";
                return err_msg.c_str();
            }
        } excptn;
        throw excptn;
    }
}
